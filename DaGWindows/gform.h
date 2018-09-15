! GWindows Form Widget
!
! By L. Ross Raszewski
! lraszewski@loyola.edu
! *This documentation is incomplete*
!
! The GWindows form widget is a widget for creating dialog windows
! A form is composed of components, which are primitives each filling a
! specific purpose. Form components are similar in purpose to many of the
! controls one would find in a more traditional gui toolkit
!
! Though there's no reason you have to do it this way, GForms were designed
! to be used in tandem with the modal system to produce modal forms.
!
!
! Each component has the following properties:
!
!    click_event  <- event triggered when the user clicks on the component
!    char_event   <- event triggered when the user types while the component
!                       has focus. If char_event returns false, the component
!                       is taken to have "yielded focus" to the next component
!    redraw
!    width, height <- These may be set dynamically by redraw
!    printtext  <- the default implementation of redraw moves the cursor to the
!                  right location for the widget, and executes printtext.
!                  printtext should return the length in characters of
!                  what it has printed.
!    x,y   <- this is the relative position of the component
!    xpos(), ypos()   <- this is the actual position of the component;
!                       you specify x and y, and use xpos and ypos in glk calls
!
!  Additionally, many widgets use the 'text' property to store the actual
!  text of their contents
!
!
! The components:
!  GFBox: A box is a rectangular grouping of components. A box maintains
!         'focus', which is a notion of which component is responsive
!         to character input. Boxes may be nested. A GForm is itself a box.
!  GFToggle: A toggle is a component which simply maps the space and enter
!            keys to a click
!  GFLabel: A label simply prints the contents of its 'text' property
!  GFButton: A button is a GFToggle which prints the contents of its
!               text property enclosed by brackets (as "[OK]")
!  GFCheckbox: A checkbox is a toggle which, when clicked, changes between
!               the 'on' and 'off' state. When on, its text is prefaced
!               by a marked box ('[X] '), and when off, by an empty one
!               ('[ ] ')
!  GFRadioOption: A radio option is identical to a checkbox, except
!               that switching on a radio option automatically
!               switches off every other radio option in that Box.
!               Radio options are indicated as "(*)" and "( )"

Class GFComponent
 with redraw
      [; glk_window_move_cursor(self.parentwindow().winid,self.xpos(), self.ypos());
               self.width=self.printtext();
             ],
      xpos [; return self.x + parent(self).xpos(); ],
      ypos [; return self.y+parent(self).ypos();],
      parentwindow [x; x=self; do x=parent(x); until (x ofclass GForm);
                        return x;
                        ],
      printtext [; ],
      x,y,width,height 1;

Class GFBox
 class GFComponent,
 with redraw [o;
      if (self ofclass GForm) glk_window_clear(self.winid);
                objectloop(o in self)
                 o.redraw();
             ],
      scale_x, scale_y,
      focus,
      char_event [ x;
                   if (self.focus==0 || self.focus notin self) self.focus=child(self);
                   if (~~(self.focus provides char_event &&
                       self.focus.char_event(x)))
                      { if (sibling(self.focus))
                         self.focus=sibling(self.focus);
                        else {
                         self.focus=child(self);
                         return false;
                         }
                      }
                      return true;
                 ],
      click_event [x_ y_ o;
                     objectloop(o in self)
                     {
                     #ifdef USE_GCONSOLE;
                      GConsole.penon();
                      print "[GForm]: Matching click to component ", (name) o,
                              " (",o.x, ", ", o.y, ", ", o.width, ", ", o.height, ").^";
                      GConsole.penoff();
                     #endif;
                     if (o provides click_event &&
                         x_ >= o.x && y_ >= o.y && x_<(o.width+o.x)
                        && y_ < (o.height+o.y))
                        {
                     #ifdef USE_GCONSOLE;
                      GConsole.penon();
                      print "[GForm]: Match found.^";
                      GConsole.penoff();
                     #endif;

                        self.focus=o;
                        o.click_event(x_-o.x,y_-o.y);
                        }
                     }
                   ],
      has on;
Class GForm
 class  GFBox TextGrid,
with         xpos [; return 0; ],


        ypos [; return 0; ],
        click_event [x y; self.GFBox::click_event(x,y);
                          if (self has general) GW_ForceRedraw(self);
                    ];

Class GFToggle
 with
      char_event [x; if (x==keycode_Return or ' ' or 10 or 13)
                      {
                       if (self provides click_event) self.click_event(0,0);
                       rtrue;
                       }
                       rfalse;
                       ];
  
Class GFLabel
 class GFComponent,
 with   text,
        printtext [; 
                printanything(self.text);
                return PrintAnyToArray(gg_arguments,0,self.text);
        ];
Class GFButton
 class GFComponent GFToggle,
 with text,
      printtext [; print (char) '[';
                   printanything(self.text);
                   print (char) ']';
                   return 2+PrintAnyToArray(gg_arguments,0,self.text);
                ];
Class GFCheckBox
 class GFComponent GFToggle,
  with text,
      printtext [; if (self has on) print "[X] ";
                   else print "[ ] ";
                   printanything(self.text);
                   return 4+PrintAnyToArray(gg_arguments,0,self.text);
                ],
      click_event [x y;
                     #ifdef USE_GCONSOLE;
                      GConsole.penon();
                      print "[GForm]: Click detected in checkbox ", (name) self, ".^";
                      GConsole.penoff();
                     #endif;

                   y=x;
                    if (self has on) give self ~on;
                    else give self on;
                    give self.parentwindow() general;
                   ];

Class GFRadioOption
 class GFComponent GFToggle, 
 with 
      printtext [; if (self has on) print "(*) ";
                   else print "( ) ";
                   printanything(self.text);
                  return 4+PrintAnyToArray(gg_arguments,0,self.text);
                ],
click_event [x y; x=y; if (self hasnt on)
                { objectloop(y in parent(self))
                   if (y ofclass GFRadioOption)
                        give y ~on;
                   give self on;
                   give self.parentwindow() general;
                   }
                   ];


Class GFDListOption
 with     printtext [; if (self has on) print "> ";
                   else print "  ";
                   printanything(self.text);
                   return 2+PrintAnyToArray(gg_arguments,0,self.text);
                ];
Class GFListOption
   class GFDlistOption GFCheckBox;
Class GFSingleListOption
   class GFDlistOption GFRadioOption;

! GPopup.h   - GWindows popup window widget
!
!
! Usage:
! Create a GPopupWin as you would a normal window, but specify its split
! size using the 'asplit' property rather than the 'split' property.
!
! Initially, the GPopupWin will be invisible. 
! When you call the .activate() method, the window will be resized
! as apropriate (you may need to call redraw on the parent window pair)
! calling .deactivate() will return the window to invisibility
!
! If you create a popup as the first window of a pair, you *must*
! set the split_key property of the popup to the window from which
! the popup is split (usually, the last windowpair created)
!
! GPopupWindow must be combined with TextBuffer, TextGrid, GraphWin,
! or a derived class to be usable.
!
! User-configurable properties:
!  asplit: size when active
!  dsplit: size when inactive
!
! Derived classes: GPopupMenu, GTransient
!
ifndef GW_GPOPUP_H;
system_file; 
Constant GW_GPOPUP_H;

Class GPopupWin
 with  dsplit 0,
       asplit 100,
       split 0,
       split_key 0,
       activate [;
       #ifdef USE_GCONSOLE;
       GConsole.penon();
       print "[GPopupWin]: Activating window ", (name) self, ".^";
       GConsole.penoff();
       #endif;
       self.changestate(asplit);
       ],
       validate [i j;
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GPopupWin]: Window ", (name) self, " validating size.^";
GConsole.penoff();
#endif;

                i=self.split;
                self.split=-1;
                if (i==self.dsplit)
                    j=dsplit;
                else j=asplit;
                self.changestate(j);
                ],
       deactivate [;
       #ifdef USE_GCONSOLE;
       GConsole.penon();
       print "[GPopupWin]: Deactivating window ", (name) self, ".^";
       GConsole.penoff();
       #endif;
       self.changestate(dsplit); ],
 private changestate
                [x i j;
                    if (self.split~=self.x)
                    {
                    self.split=self.x;
                    i=self.split_dir;
                    if (self.split_key) j=self.split_key;
                    else j=parent(self);
                    if (self has abssplit) i=i|winmethod_Fixed;
                    else i=i|winmethod_Proportional;
                    glk_window_set_arrangement(j.winid,
                                               i,
                                               self.split,
                                               self.winid);
                    give j general;
                 }
                ];

endif;

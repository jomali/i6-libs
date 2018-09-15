! GWindows      Beta .7
! Screen API for glulx
! By L. Ross Raszewski
!
! GWinCls.h     GWindows Window Class Framework
! Include this file *after* the parser
!
!
!--------------------------------------------------------------------------
!
! NOTA DE ELIUK BLAU: Correcciones... (buscar comentarios con "Eliuk")
!
! 1) Se corrige pequeño despiste del programador-autor que producia un
!    warning de variable global no usada por haber sido declarada antes
!    de 'system_file'.
!
!--------------------------------------------------------------------------

ifndef GW_GWINCLS_H;
system_file;
Constant GW_GWINCLS_H;  ! CORREGIDO POR:
global redraw_reason=0;	! ELIUK BLAU
Include "gcore";
Class WindowPair
 with   winid 0,
        deep_redraw [ o;

#ifdef USE_GCONSOLE;
                     
                     GConsole.penon();
                     print "[GWindows]: Redrawing pair window ~", (name) self, "~.^";
                     GConsole.penoff();
#endif;                    
                    objectloop(o in self)
                     o.deep_redraw();

!                    self.deep_update();
                    give self ~general;
#ifdef USE_GCONSOLE;
                    GConsole.penon();
                    print "[GWindows]: Pair window ~", (name) self, "~ redraw complete.^";
                    GConsole.penoff();
#endif;
                ],
        deep_update [ o;
#ifdef USE_GCONSOLE;
                      Gconsole.penon();
                      print "[GWindows]: Updating pair window ~", (name) self, "~.^";
                      GCOnsole.penoff();
#endif;
#ifdef GWINDOWS_OPTIMIZE;
                objectloop(o in self)
                  if (o ofclass WindowPair || o provides update) o.deep_update();

#ifnot;
                objectloop(o in self)
                  o.deep_update();
#endif;
#ifdef USE_GCONSOLE;
                      Gconsole.penon();
                      print "[GWindows]: Pair window ~", (name) self, "~ update complete.^";
                      GCOnsole.penoff();
#endif;
                   ],
        checkredraw [ o ii;
        ii=0;
                if (self has general) {
#ifdef USE_GCONSOLE;
                      Gconsole.penon();
                      print "[GWindows]: Pair window ~", (name) self, "~ needs redraw; forcing redraw from here down.^";
                      GCOnsole.penoff();
#endif;
                      self.deep_redraw();
                }
                objectloop(o in self)
                {

! if (redraw_reason) {
!        ii=glk_stream_get_current();
!        glk_set_window(Main_GWindow.winid);
!        print "Redrawing ", (name) o, "^";
!        glk_stream_set_current(ii);
!        }


#ifdef GWINDOWS_OPTIMIZE;
                 if (o has general) o.deep_redraw();
                 else if (o ofclass WindowPair && (o hasnt static ||  GW_Action_Reason==GW_REASON_REDRAW))
                  o.checkredraw();
#ifnot;
                 if (o has general) o.deep_redraw();
                 else if (o provides checkredraw)
                  o.checkredraw();
#endif;
                }
                ],
        g_open [ from x y;
#ifdef USE_GCONSOLE;
                      Gconsole.penon();
                      print "[GWindows]: Opening pair window ~", (name) self, "~.^";
                      GCOnsole.penoff();
#endif;
                 y=child(self).g_open(from);
                 x=sibling(child(self));
                 y=x.g_open(y);
                 self.winid=glk_window_get_parent(y);
                 give self open;
                 give self ~absent;
#ifdef USE_GCONSOLE;
                      Gconsole.penon();
                      print "[GWindows]: Pair window ~", (name) self, "~ opened.^";
                      GCOnsole.penoff();
#endif;
                 return self.winid;
             ];
Class GWindow
 with   winid,
       split,
       split_dir,
        wintype,
        width,
        height,
        checkredraw [;
        if (self has general) self.deep_redraw();

        else
        {
#ifdef USE_GCONSOLE;
          GConsole.penon();
          print "[GWindows]: Window ~", (name) self, "~ does not need redraw.^";
          GConsole.penoff();
#endif;
        }
        ],
        deep_redraw [ o;
#ifdef USE_GCONSOLE;
                GConsole.penon();
                print "[GWindows]: Window ~", (name) self, "~ redrawing.^";
                GCOnsole.penoff();
!                GCOnsole.wait();
#endif;

                      if (~~self.winid) @throw GW_ERR_RED_NO_WIN GW_Massive_Error;
                      if (self.wintype==wintype_Blank)
                      {
#ifdef USE_GCONSOLE;
                GConsole.penon();
                print "[GWindows]: Window ~", (name) self, "~ is blank. Not redrawing.^";
                GCOnsole.penoff();
!                GCOnsole.wait();
#endif;
                return;
                      }

                      if (self provides getsize) self.getsize();
                      if (self provides redraw)
                      {
                      o=glk_stream_get_current();
                      if (self.wintype==wintype_TextGrid or wintype_TextBuffer)
                      glk_set_window(self.winid);

                      self.redraw();
                      if (o) glk_stream_set_current(o);
#ifdef USE_GCONSOLE;
                      GConsole.penon();
                      print "[GWindows]: Window ~", (name) self, "~ redraw complete.^";
                      GCOnsole.penoff();
#endif;
                      }
                      else {
#ifdef USE_GCONSOLE;
                      GConsole.penon();
                      print "[GWindows]: Window ~", (name) self, "~ does not support automatic redraw.^";
                      GConsole.penoff();
#endif;
                      }
                      give self ~general;

                    ],
        deep_update [ o;
#ifdef USE_GCONSOLE;
                      Gconsole.penon();
                      print "[GWindows]: Updating window ~", (name) self, "~.^";
                      GCOnsole.penoff();
#endif;
                      if (self.wintype==wintype_Blank)
                      {
#ifdef USE_GCONSOLE;
                GConsole.penon();
                print "[GWindows]: Window ~", (name) self, "~ is blank. Not updating.^";
                GCOnsole.penoff();
!                GCOnsole.wait();
#endif;
                return;
                      }

                      if (self provides update)
                      {
                      o=glk_stream_get_current();
                      if (self.wintype==wintype_TextGrid or wintype_TextBuffer)
                       glk_set_window(self.winid);
                      self.update();
                      if (o) glk_stream_set_current(o);
#ifdef USE_GCONSOLE;
                      GConsole.write("[GWindows]: Window updated.^");
#endif;
                      }
                        else
                        {
#ifdef USE_GCONSOLE;
                        GConsole.write("[GWindows]: Window does not support automatic update.^");
#endif;
                        }
                    ],
        g_open [ from x i rr;
                if (rr==0) rr=self;
#ifdef USE_GCONSOLE;
                GConsole.penon();
                print "[GWindows]: Preparing to open window ~", (name) self, "~.^";
                GCOnsole.penoff();
#endif;
                if (self has abssplit) x=winmethod_Fixed;
                else if (from==0) x=0;
                else x=winmethod_Proportional;
#ifdef USE_GCONSOLE;
                GConsole.penon();
#endif;
                if (self provides stylehints)
                 for(i=0:i<(self.#stylehints/WORDSIZE):i=i+3)
                 {
#ifdef USE_GCONSOLE;
                  print "[GWindows]: Setting stylehint ",
                         self.&stylehints-->(i+1),
                         " for style ", self.&stylehints-->(i),
                         " to value ", self.&stylehints-->(i+2),
                         " on window ~", (name) self, "~.^";
#endif;
                  glk_stylehint_set(self.wintype,self.&stylehints-->i,
                                    self.&stylehints-->(i+1),
                                    self.&stylehints-->(i+2));

                 }
#ifdef USE_GCONSOLE;
                 GConsole.penoff();
#endif;
!if (self.split==0) self.split=2;
!               print "About to open window ", (name) self, " from ", (name) from, " split ", self.split, ".^";
                self.winid=GWindows_open_window(from,self.split_dir|x,self.split,self.wintype,
                            rr);
                if (self.winid==0) @throw GW_ERR_NO_OPEN GW_Massive_Error;
                give self ~absent;
                self.getsize();
                if (self provides stylehints)
                 for(i=0:i<(self.#stylehints/WORDSIZE):i=i+3)
                  glk_stylehint_clear(self.wintype,self.&stylehints-->i,
                                    self.&stylehints-->(i+1));

#ifdef USE_GCONSOLE;
                GConsole.penon();
                print "[GWindows]: Window ~", (name) self, "~ open.  Window ID is ", self.winid, ".^";
                GCOnsole.penoff();
#endif;
               return self.winid;
             ],
        getsize [;
                glk_window_get_size(self.winid,self.&width,self.&height);
                ];

Class TextBuffer
 class GWindow,
 with wintype wintype_TextBuffer;
Class GPersistantWin
 class TextBuffer
 with init [; glk_window_clear(self.winid); ],
 g_open [x;
                if (gw_persistant_win==self) return self.winid;
                gw_persistant_win=self;
                return self.GWindow::g_open(x,0,0,GW_PERSISTANT_ROCK);
             ];
Class TextGrid
 class GWindow,
 with wintype wintype_TextGrid;
Class GraphWin
 class GWindow
 with wintype wintype_Graphics,
 g_open [x; if (~~(GW_Abilities & GWIN_GWOK)) {
                self.wintype=wintype_Blank;
                if (self has abssplit)
                 @throw GW_ERR_ABS_GRAPH GW_Massive_Error;
                }

#ifndef GW_NO_TAILCALL;
               @copy x sp;
               x=self.GWindow::g_open;
               @tailcall x  1;
#ifnot;
               return self.GWindow::g_open(x);
#endif;
            ];

[ StreamWord x y z;
#ifdef USE_GCONSOLE;
  GConsole.write("[GWindows]: Inserting text into the input stream.^");
#endif;
  glk_cancel_line_event(Input_GWindow.winid,GG_ARGUMENTS);
  y=GG_ARGUMENTS-->2;
  if (buffer-->y==10) y--;
  buffer-->0=y;
  z=PrintAnyToArray(buffer+WORDSIZE+y,INPUT_BUFFER_LEN-WORDSIZE-y,x);
  buffer-->0=y+z;
  if (input_GWindow ~= Main_GWindow)
  glk_window_clear(Input_GWindow.winid);
  glk_request_line_event(Input_GWindow.winid,buffer+WORDSIZE,INPUT_BUFFER_LEN-WORDSIZE,
        buffer-->0);

];
[ FindWindowBy x p y z o;
  if (y==0) y=Active_UI;
  if (y provides p && y.p==x) return y;
  objectloop(o in y)
  {
   z=FindWindowBy(x,p,o);
   if (z) return z;
  }
  rfalse;
];
[ FindWindowByWinid x y;
 if (x)
 {
! print "Getting rock for ", (name) x, "(", x, ")^";
 y=glk_window_get_rock(x);
 if (y==GW_PERSISTANT_ROCK) return GW_Persistant_Win;
 if (y) return y;
 }
 return FindWindowBy(x,winid,y);
];
Array draw_params --> 6;

[ gwin_image_draw_auto x y z w a b o;
 o=glk_window_get_rock(x);
 if (o==GW_PERSISTANT_ROCK) o=GW_Persistant_Win;
 if (o has aspected) return gwin_image_draw_aspect(x,y,z,w,a,b);
 else return gwin_image_draw(x,y,z,w,a,b);
];
[ gwin_image_draw x y z w a b;
 if (GW_Abilities &GWIN_DROK)
 if(y ofclass routine) return rundrawrout(x,y,z,w,a,b);
 else
return glk_image_draw_scaled(x,y,z,w,a,b);
];
[ gwin_image_draw_aspect x y z w a b ww hh ii jj;
 if (~~(GW_Abilities &GWIN_DROK)) return;
 if(y ofclass routine) return rundrawrout(x,y,z,w,a,b);

 glk_image_get_info(y,gg_arguments, gg_arguments+WORDSIZE);
 ww=gg_arguments-->0;
 hh=gg_arguments-->1;
 ii=(a*100)/ww; ! ii = proportion to scale x
 jj=(b*100)/hh; ! jj = proportion to scale y
 if (ii>jj) ! since horizontal scaling is bigger,
            ! we will scale vertically and pad on the left
 {
   ww=(ww*jj)/100;
   z=z+((a-ww)/2);
   a=ww;
 }
 else if (jj>ii)
 {
  hh=(hh*ii)/100;
  w=w+((b-hh)/2);
  b=hh;
 }
 prepdrawrout(x, y,z,w,a,b);
 return glk_image_draw_scaled(x,y,z,w,a,b);
];

[ gwin_image_drawf x y z w;
 if (GW_Abilities &GWIN_DROK)
 if (y ofclass Routine) return rundrawrout(x,y,z,w);
 else
return glk_image_draw(x,y,z,w);
];
[ rundrawrout x y z w a b;
prepdrawrout(x,y,z,w,a,b);
return y();
];
[ prepdrawrout x y z w a b;
draw_params-->0=x;
draw_params-->1=y;
draw_params-->2=z;
draw_params-->3=w;
draw_params-->4=a;
draw_params-->5=b;

];
[ GW_ForceRedraw x y g;
 g=GW_Massive_Error;
 @catch GW_Massive_Error ?rednerr;
 GWindowsErrorHandler(GW_Massive_Error);
 GW_Massive_Error=g;
 .rednerr;
 y=glk_stream_get_current();
 give x general;
 GW_Action_Reason=GW_REASON_REDRAW;
 Active_UI.checkredraw();
 Active_UI.deep_update(); 
 glk_stream_set_current(y);
];
[ RestartGWindows;
 GWin_Core.init_reason=INIT_REASON_GW_RESTART;
 InitGlkWindow(0);
];
[ GWindowsErrorHandler x;
  if (GWindowsHandleError(x)==2) {
        return;
        }
  print "[GWindows irrecoverable error: ";
  PrintAnything(x);
  print "]^^";
  quit;
];
object gw_dummy
with redraw, update, click_event, char_event, stylehints, validate;
endif;

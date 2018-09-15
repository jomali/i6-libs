! WrapMenu         - GWindows menu with line-wrapping
!
!
! Usage: Use a WrapMenu as you would a GMenu.
!
! If more than one WrapMenu can be active at the same time, they must
! declare a 'wrapper proxy':
!
! ww_contents my_proxy;
!
! WrapMenu wmen
!  with
!       ...
!       wrapper my_proxy;
!
! Any WrapMenu which does not explicitly declare its wrapper proxy
! will use the system default wrapper proxy. At most one menu at a time can
! use any particular wrapper proxy
!
! WrapMenu will automatically combine with GPopupWin; you may inherit from
! both classes without use of a GCombiner
!
!
! Constants:
!
!  GW_MAX_MENU_SIZE: Maximum number of lines in a WrapMenu. This is the
!                    maximum actual number of lines; each element in the menu
!                    might take up several lines. (Default: 256)
!  GW_MAX_WRAPS: Maximum number of lines to be allocated to any single
!                menu item. If the name is so long that it would require more
!                lines, it is simply cut off. (Default: 256, ie. "As many as
!                it takes")
!
! Although WrapMenus can fold over many lines, the maximum length of a menu
! item is still bound by the GMenu name size limit (GW_BUFFER_SIZE). The display
! will break down if the width of the menu drops below 3.
!
! WrapMenu will attempt to wrap at word boundaries, but splits in the middle
! of a word if to do otherwise would be silly.
!
! (c) 2003 by L. Ross Raszewski, but freely usable


ifndef GW_WMENU_H;
system_file;
Constant GW_WMENU_H;



Include "gmenu";

Default GW_MAX_MENU_SIZE 256;
Default GW_MAX_WRAPS 256;

Array wrap_namebuffer -> (GW_BUFFER_SIZE+8);

object ww_prox;

[ Wrap_Deflash o;
!  if (wrap_namebuffer-->0 ~=o)
!  {
   wrap_namebuffer-->1=PrintAnyToArray(wrap_namebuffer+8,GW_BUFFER_SIZE,o);
   wrap_namebuffer-->0=o;
!  }
   return wrap_namebuffer-->1;
];

Class ww_contents
 with current_menu,
  winid,
  update [o oo;
  if (~~self.current_menu) return;
   if (self.current_menu provides update &&
                        self.current_menu.update()) rtrue;
             oo=child(self);
             objectloop(o in self.current_menu)
             {
              if (oo && oo.proxies_to ~=o) rtrue;
              while(oo && oo.proxies_to == o) oo=sibling(oo);
             }
          ],
  number,
  deactivate [; if (self.current_menu provides deactivate) return self.current_menu.deactivate(); ];

ww_contents wrap_contents;


Class wmenu_proxy(GW_MAX_MENU_SIZE)
 with short_name
        [i l j o ;

             o=scion(parent(self),parent(self).winid.sel_num + parent(self).winid.number -1);
             if (o&& o.proxies_to==self.proxies_to)
             { o=1; glk_set_style(style_User1); }
             else o=0;


              l=Wrap_Deflash(self.proxies_to);
              if (l<self.number) rtrue;
              if (self.number > 0) { print (char) ' '; j=1; }
!                ii=glk_stream_get_current();
!                glk_set_window(Main_GWindow.winid);
!                print "Printing^";
!                glk_stream_set_current(ii);

              for(i=self.number:i<l && j<self.sel_num:i++,j++)
               print (char) wrap_namebuffer->(i+8);
                if (o) glk_set_style(style_Normal);              
                rtrue;
         ],
      fixed_print [x; 
               x=self.short_name;
               @tailcall x  0;
                        ],
      number,
      sel_num,
      proxies_to,
      select [; if (self.proxies_to provides select) return self.proxies_to.select(); ];


Class WrapMenu class GMenu
 with 
      active_menu [; if (self hasnt on) rfalse; return self.current_menu.current_menu;],
      activate [x;
                  self.prepare_menu(x);
                  self.gmenu::activate(self.wrapper);
                  if (self ofclass GPopupWin) self.gpopupwin::activate();
                ],
      redraw [ii;
if (~~self.wrapper.current_menu) rtrue;
                ii=glk_stream_get_current();
!                glk_set_window(Main_GWindow.winid);
!                print "Preparing menu ", (name) self.wrapper.current_menu, "^";
!                glk_stream_set_current(ii);
      self.prepare_menu(self.wrapper.current_menu);
 !               ii=glk_stream_get_current();
 !               glk_set_window(Main_GWindow.winid);
 !               print "Drawing menu!^";
 !              glk_stream_set_current(ii);

                self.gmenu::redraw();
             ],
      prepare_menu [ m o l p c i cc;
                      self.wrapper.winid=self;
                      while(child(self.wrapper))
                       wmenu_proxy.destroy(child(self.wrapper));
                      while(child(ww_prox))
                       wmenu_proxy.destroy(child(ww_prox));

                      self.wrapper.number=self.wrap_at;
                      self.wrapper.current_menu=m;
                      objectloop(o in m)
                      {
                      l=Wrap_Deflash(o);
#ifdef USE_GCONSOLE;
GConsole.penon();
                      print "[WMENU] Name is ~";
                      for(i=0:i<l:i++)
                      print (char) wrap_namebuffer->(i+8);
                      print "~: ", l, " characters.^";
GConsole.penoff();
#endif;
                      if (l<self.wrap_at)
                       {
#ifdef USE_GCONSOLE;
GConsole.penon();

                        print "[WMENU] Not wrapping.^";
GConsole.penoff();
#endif;
                        p=wmenu_proxy.create();
                        if (~~p) "[ERROR]: Wrapped menu size exceeded! Increase MAX_MENU_SIZE.";
                        if (o has absent) give p absent; else
                        give p ~absent;
                        p.number=0;
                        p.sel_num=1024;
                        p.proxies_to=o;
 !                       print (name) p, "^";
                        move p to ww_prox;

                       }
                      else
                       {
#ifdef USE_GCONSOLE;
GConsole.penon();
                         print "[WMENU] Wrapping.^";
GConsole.penoff();
#endif;
                         c=0;
                         cc=0;
                         while(c<l && cc < GW_MAX_WRAPS)
                         {
                          cc++;
                          p=wmenu_proxy.create();
                          if (~~p) "[ERROR]: Wrapped menu size exceeded! Increase MAX_MENU_SIZE.";
                          if (cc==1 && o hasnt absent) give p ~absent;
                          else give p absent;
                          p.number=c;
                          p.proxies_to=o;
                          if (l-c < self.wrap_at) {
!                             print "Last one!^";
                            p.sel_num=500;
                            c=l;
                          }
                          else {
                          for(i=self.wrap_at:i>(self.wrap_at/3) &&
                                            wrap_namebuffer->(i+c+8)~=' ' or '-':
                                            i--);
                          if (wrap_namebuffer->(i+c+8)~=' 'or '-') i=self.wrap_at;
                          p.sel_num=i+1;
                          c=c+i+1;
                          }
!                          print (name) p, "^";
#ifdef USE_GCONSOLE;
GConsole.penon();
                          print "[WMENU] Slice goes from ", p.number, " to ", p.sel_num, ": ~";
                          for(i=0:i<p.sel_num && (i+p.number) < l:i++)
                           print (char) wrap_namebuffer->(i+p.number+8);
                           print "~^";
GCOnsole.penoff();
#endif;
                          move p to ww_prox;

                         }

                       }
                      }
                      while(child(ww_prox)) move child(ww_prox) to self.wrapper;
                ],
      wrap_at 20,
      wrapper wrap_contents,
      deactivate [;
                   self.wrapper.current_menu=0;
                   self.gmenu::deactivate();
                   if (self ofclass GPopupWin) self.gpopupwin::deactivate();
                  ];

endif;

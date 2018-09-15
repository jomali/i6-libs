! Gmenu         - GWindows simple menu widget
!
! Usage: GMenu is a grid window which provides a menu.
! to activate the menu, call (window).activate(x);, where x is
! the menu information.
!
! To disable the menu, call (window).deactivate();
!
! The menu will automatically handle mouse and keyboard input,
! and multiple-layout pages
!
! The menu information is passed via an object. The children of this
! object become options on this menu.
!
! When the user selects an option from the menu, the .select() message
! is sent to the selected object. If the object does not provide a select
! method, an error will result.
!
! Items on the menu which have the 'absent' flag set are not accessable via
! keyboard; the cursor will skip over them as the menu is navigated. Thus,
! an option like this:
!
! object "-----" with select [;], has absent;
!
! Can be used to form a separator in a menu.
!
!
! If you want to have a menu window which only appears when the menu is
! active, use gPopupMenu
!
!
! User-configurable properties:
!  redraw: This routine is called to draw the menu
!  click_event(x,y): This routine handles menu selection
!  char_event(x): This routine transforms character input into a click event,
!                 and hands off the processing to click_event.
!                 The version used here accepts the following keys:
!                 Up, P - move the selection point up
!                 Down, N - move the selection point down
!                 Page Down - next page of menu
!                 Page Up - previous page of menu
!                 Enter, Space - select current option
!                 Escape, Q - calls the 'deactivate' method on the current menu
!                       (if available)
!  stylehints: style_Normal for unselected menu options, style_User1 for
!              selected ones
!  convertclick(x,y): used to translate the co-ordinates of a click.
!              Should return the number in the menu of the item clicked
!              Note: Here and elsewhere "number in the menu" refers
!              to the ordinal position of the item within in the page of the
!              menu currently displayed; in a normal menu, this is the line
!              number on which the click occured.
!  sel_marker: ('>') the character used to indicate the current selection
!  prev_word: ("  <Previous>") word printed to indicate upward paging
!  next_word: ("  <Next") word printed to indicate downward paging
!  locateEntry(x,y): position the cursor for output of menu
!               item number y, and indent x spaces.
!  displayEntries(): returns the maximum number of entries to display in
!               the current view of the menu
!  Attribute: unpageable - if this flag is set, the menu will not
!                       display the <next> and <previous>
!                       paging items, even if there is more data
!                       than is visible.
!  active_menu(): returns the current menu, or false if no menu is showing.
!
! User-testable properties:
!  DEPRECATED
!  current_menu: contains the menu information object for the current menu
!       or 0 if the menu is inactive
!
!  Attribute: on - set if the menu is active
!  
!
!User-configurable properties of the menu information object:
! 
! update(): This function will be called whenever the menu window wants to
!        update its display. It should return true if the menu needs to be
!        redrawn.
! deactivate(): This function, if provided, is called when the user tries
!       to quit the menu by pressing Q or Escape. If you are going to allow
!       the user to quit from the menu, this method should shut down
!       the menu window.
!
!
! Inherits from: TextGrid
! Derived classes: GPopupMenu, GColumnMenu

ifndef GW_GMENU_H;
system_file;

Constant GW_GMENU_H;
Attribute unpageable;
Constant GW_MENU_NW "  <Next>";
Constant GW_MENU_PW "  <Previous>";
array namebuffer ->GW_BUFFER_SIZE;
Class GMenu
 class TextGrid,
 private
      select,
      last 0,
 with
      sel_num 1,      
      number 1,
      sel_marker '>',
      next_word  GW_MENU_NW,
      prev_word GW_MENU_PW,
      stylehints
       style_User1  stylehint_ReverseColor   1,
      current_menu 0,
      active_menu [; if (self hasnt on) rfalse; return self.current_menu; ],
      activate [ x;
                 self.current_menu=x;
                 self.number=1;
                 self.sel_num=1;
                 if (self hasnt on)
                 {
                  glk_request_char_event(self.winid);
                  glk_request_mouse_event(self.winid);
                 }
                 give self on;
                 give self general;
#ifdef USE_GCONSOLE;
                GConsole.penon();
                print "[GMenu]: Activating menu ", (name) x, " in window ", (name) self, ".^";
                GConsole.penoff();
#endif;
               
               ],
      deactivate [;
                  self.current_menu=0;
                  if (self has on)
                  {
                   glk_cancel_char_event(self.winid);
                   glk_cancel_mouse_event(self.winid);
                  }
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GMenu]: Deactivating menu window ", (name) self, ".^";
GConsole.penoff();
#endif;
                  give self ~on;
                 ],
      displayEntries [;
                        return self.height-1;
                     ],
      redraw [ o y l m ;
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GMenu]: Performing redraw of ", (name) self, ". Page starts at ", self.number, ".^";
GConsole.penoff();
#endif;

               if (self hasnt on) return;
  !              ii=glk_stream_get_current();
  !              glk_set_window(Main_GWindow.winid);
  !              print "Redrawing: clear and set up^";
  !              glk_stream_set_current(ii);

               y=1;
               glk_window_clear(self.winid);
               glk_set_Style(style_Normal);
               if (self hasnt unpageable && self.number>1)
               {
                if (self.sel_num==0)
                {
                 self.LocateEntry(0,0);
                 print (char) self.sel_marker;
                 glk_set_style(style_User1);
                }
                self.locateEntry(1,0);
                PrintANything(self.prev_word);
                glk_set_style(style_Normal);
               }
 !               ii=glk_stream_get_current();
 !               glk_set_window(Main_GWindow.winid);
 !               print "Drawing menu items^";
 !               glk_stream_set_current(ii);

               for(o=scion(self.current_menu,self.number):o:o=sibling(o))
               {
                if (y > self.displayEntries() || ((self hasnt unpageable || ~~sibling(o)) && y == self.displayEntries())) break;
!                ii=glk_stream_get_current();
!                glk_set_window(Main_GWindow.winid);
!                print "Drawing ", (name) o, "^";
!                glk_stream_set_current(ii);

                if (self.sel_num==y)
                {

                 self.locateEntry(0, y);
                 print (char) self.sel_marker;
                 glk_set_style(style_User1);
                }
!                ii=glk_stream_get_current();
!                glk_set_window(Main_GWindow.winid);
!                print "Locating^";
!                glk_stream_set_current(ii);


                self.locateEntry(1,y);
!                glk_set_hyperlink(y);
!                ii=glk_stream_get_current();
!                glk_set_window(Main_GWindow.winid);
!                print "Flashing^";
!                glk_stream_set_current(ii);
                if (o provides fixed_print)
                {
!                ii=glk_stream_get_current();
!                glk_set_window(Main_GWindow.winid);
!                print "Performing fixed print^";
!                glk_stream_set_current(ii);

                 o.fixed_print();
!                ii=glk_stream_get_current();
!                glk_set_window(Main_GWindow.winid);
!                print "Done fixed print^";
!                glk_stream_set_current(ii);

                }
                else
                {
                l=PrintAnyToArray(namebuffer,GW_BUFFER_SIZE,o);
                if (l>=self.width) l=self.width-1;

!                ii=glk_stream_get_current();
!                glk_set_window(Main_GWindow.winid);
!                print "printing^";
!                glk_stream_set_current(ii);

                for(m=0:m<l:m++)
                print (char) namebuffer->m;
               }
!                glk_set_hyperlink(0);
                glk_set_Style(style_Normal);
                y++;
   !             ii=glk_stream_get_current();
   !             glk_set_window(Main_GWindow.winid);
   !             print "Done Drawing ", (name) o, "^";
   !             glk_stream_set_current(ii);

               }
    !            ii=glk_stream_get_current();
    !            glk_set_window(Main_GWindow.winid);
    !            print "Done drawing entries ", (name) o, "^";
    !            glk_stream_set_current(ii);

               self.last=o;
               if (self.last && self hasnt unpageable )
               {
                if (self.sel_num==self.displayEntries())
                {
                 self.locateEntry(0,self.DisplayEntries());
                 print (char) self.sel_marker;
                 glk_set_style(style_User1);

                }
                self.locateEntry(1,self.displayEntries());
                printAnything(self.next_word);
                glk_set_style(style_Normal);

               }
             ],
      locateEntry [x y z;
                z=self.winid;
                @copy y sp;
                @copy x sp;
                @copy z sp;
                @tailcall glk_window_move_cursor 3;
!                    glk_window_move_cursor(self.winid,x,y);
                  ],
      char_event [ x op;
                   op=self.click_event;
                   if (self hasnt on) rtrue;
                   if (x==keycode_Up or 'p' or 'P')
                      {
                       self.sel_num--;
                       while(self.sel_num>0 && scion(self.current_menu,
                                self.sel_num+self.number-1) has absent)
                         self.sel_num--;

                      }
                   else if (x==keycode_Down or 'n' or 'N')
                     {
                     self.sel_num++;
                       for(x=scion(self.current_menu,self.sel_num+self.number-1):
                          self.sel_num<self.displayEntries() &&
                          x &&
                          x has absent:
                          x=scion(self.current_menu,self.sel_num+self.number-1))
                          self.sel_num++;
                        }
                   else if (x==keycode_Pagedown)
{
                        x=self.displayEntries();
                        @copy x sp;
                        @copy 0 sp;
                        @tailcall op 2;

!                           return self.click_event(0,self.displayEntries());
}
                   else if (x==keycode_Pageup)
 {
!                        x=self.sel_num;
                        @copy 0 sp;
                        @copy 0 sp;
                        @tailcall op 2;

   !                        return self.click_event(0,0);
  }
                   else if (x==10 or 13 or keycode_Return or ' ')
                   {
                        x=self.sel_num;
                        @copy x sp;
                        @copy 0 sp;
                        @tailcall op 2;
!                           return self.click_event(0,self.sel_num);
                   }
                   else if (x==keycode_Escape or 'q' or 'Q' && self.current_menu provides deactivate)
                    {
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GMenu]: Window ", (name) self, " telling the menu data object (",
        (name) self.current_menu,
        ") to deactivate.^";
GConsole.penoff();
#endif;
                       
                     x=self.current_menu.deactivate;
                     @tailcall x 0;
!                    return self.current_menu.deactivate();
                    }
                   if (self.sel_num==0 && self.number<=1)
                    self.sel_num=1;
                   else if (self.sel_num < 0)
                    self.sel_num=self.number==1;
                   else if (self.sel_num == (self.displayEntries()) && self.last==0)
                    self.sel_num=self.displayEntries()-1;
                   else if (self.sel_num > (self.displayEntries()))
                    self.sel_num=self.displayEntries()-(self.last==0);
                   else if (self.sel_num+self.number-1 > children(self.current_menu))
                    self.sel_num = children(self.current_menu)-self.number+1;

                   @copy self sp;     
                   @tailcall GW_ForceRedraw 1;
!                   GW_ForceRedraw(self);
                 ],
      convertclick [ x y; x=0;
                        return y;
                    ],
      click_event [ x y;

                   if (self hasnt on) rtrue;
                    y=self.convertclick(x,y);
!print "Gmenu: click at ", y, "^";
                    if (self hasnt unpageable && y==0
                        && self.number > 1)
                    {
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GMenu]: Window ", (name) self, " paging upward.^";
GConsole.penoff();
#endif;

                     self.number=self.number-self.displayEntries()+2;
                     if (self.number<1) self.number=1;
                     self.sel_num=1;
                    }
                    else if (self hasnt unpageable &&
                        y==(self.displayEntries()) && self.last)

                    {
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GMenu]: Window ", (name) self, " paging downward.^";
GConsole.penoff();
#endif;

                     self.number=age(self.last)-1;
                     self.sel_num=1;
                    }
                    else if ((y+self.number-1)>0
                             && (y+self.number-1) <=
                                children(self.current_menu))
                            {
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GMenu]: Window ", (name) self, " selecting option ",
        (y+self.number-1), "(", (name) scion(self.current_menu,
                                                (y+self.number-1)),
        ") from ",(name) self.current_menu, ".^";
GConsole.penoff();
#endif;

                            self.sel_num=y;
                            x=scion(self.current_menu,
                                  (y+self.number-1));

                             if (self.current_menu provides init)
                              self.current_menu.init(x);
                                  if (x provides select) x.select();
                            

                                  }
!print "Gmenu: done what I'm gonna. Preparing to redraw ^";
redraw_reason=1;
                        GW_ForceRedraw(self);
redraw_reason=0;
!print "Gmenu: redraw complete^";
                  ],
      update [;
               if (self has on && self.current_menu && self.current_menu provides update)
                 if (self.current_menu.update()) {
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GMenu]: Window ", (name) self, " refreshing on request from menu data object.^";
GConsole.penoff();
#endif;

                 self.redraw();
                 }
             ];


#ifndef GW_WMENU_H;
object __gmenu with fixed_print 0;
#endif;


endif;

! Gtrans.h      GWindows Transient Popup Window widget
!
! usage:
! Create as you would a popup window. Call .activate(x), where X is the number
! of turns for which you wish the window to remain visible.
! The window will automatically conceal itself after this time
!
! Inherits from: GPopupWin
! Derived classes: GQuoteWin
ifndef GW_GTRANS_H;
system_file;
Constant GW_GTRANS_H;
include "gpopup";
Class GTransient
 class GPopupWin,
 with time_left,
 time_out [; self.GPopupwin::deactivate(); ],
 activate [x; starttimer(self,x);
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GTransient]: Transient window ", (name) self, " activated for ", x, " turns.^";
GConsole.penoff();
#endif;

              self.GPopupWin::activate();
          ],
 deactivate [; stoptimer(self);
               self.GPopupwin::deactivate();
            ];

endif;

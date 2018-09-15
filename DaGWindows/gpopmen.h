! gpopmen - Popup Menu
!
! Usage:  As GMenu and GPopup. 
!
! This is a trivial implementation which uses a GCombiner to
! connect GMenu and GPopupWin, but it's a useful enough paradigm
! to make it into the main distribution
!
! Inherits from: Gmenu, GPopupWin
!
ifndef GW_GPOPMEN_H;
system_file;
Constant GW_GPOPMEN_H;
include "gcombine";
include "gpopup";
include "gmenu";

class GPopupMenu
 class GCombinerAD Gmenu GPopupWin;
endif;

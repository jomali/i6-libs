!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! GModal.h              Modal add-on for GWindows
!                       by L. Ross Raszewski
!
!
! Requires GWindows .7b or greater
!
! The majority of the work done in a UI is "modeless" in the sense that
! at any time, the player can click or type input into any window in the
! active UI. Howeverm there may be conditions where you wish to limit
! input for a time to a single window or some subset of the UI, such
! as a form for the player to fill out, or a menu from which the player must
! select an option. Alternatively, you may wish to present a UI which
! responds to input, but does not trigger the normal turn sequence, such as
! a "splash screen".  Since GWindows normally only processes window input
! while waiting for player input as part of a normal inform turn sequence,
! this can be slightly cumbersome.
!
! This library offers a "modal" form of operation. When a window is made
! "modal", the normal sequence of the inform library halts until the modal
! request terminates. Furthermore, any attempts to give input to windows
! outside the modal window are ignored. The rest of the interface is
! effectively frozen (though you can still display output there if you wish).
! Once modality is deactivated, the game continues as normal.
!
! Roughly speaking, opening a modal context is like waiting for
! normal player input (but without actually getting it), in that the
! GWindows event handlers will be called to respond to character and mouse
! input. Closing a modal context is like the player actually submitting
! normal game input.
!
! To create a modal context, call:
! GoModal(win);
! The 'win' argument is the Gwindow you wish to make modal; it will continue
! to respond to player input, but all other windows will not.
! win may be an actual window, or a window pair.  Calling 'GoModal()'
! will make the entire interface modal: every window will respond to player
! input, but normal game input will be suspended (That is, typing in the
! Input_GWindow will have no effect).  This is the call you would generally
! make when displaying a "special" interface such as a full-screen menu or
! title page. GoModal with no argument (or, equivalently, GoModal(Active_UI))
! is similar in effect to calling
! KeyboardPrimitive, except that normal input is not requested, and
! will not cause the function to return.
!
! Calls to GoModal may be nested; you may want to activate a popup window
! while in a modal state, and make the new popup into a modal window
! (Just as, in graphical operating systems, one dialog box may open another
! dialog on top of itself). However, you should be careful not to allow
! GoModal calls to be nested too deeply, and certainly not to an
! unlimited depth; you may nest GoModal calls only as deep as the Glulx
! interpreter has stack space for.  Only the constraints of the most recent
! call are used to determine which windows are within the modal context:
! if you call GoModal(y) while inside the modal context created by a call
! GoModal(x), y will accept input, but x will not, untill the new modal
! context is closed (Unless y is a pair window which contains x. If, on
! the other hand, x contains y, then in the inner modal context,
! everything in x but is not in y will not accept input.)
!
! To exit the modal context, call the function EndModal();
! Unlike virtually every other function you may have seen, EndModal() does
! *not* return. Any code after a call to EndModal() will *not* be executed,
! though, unlike statements like print_ret and quit, the inform compiler
! will not alert you to this.
!
! When GoModal is called, the modal state begins. GoModal returns only
! when EndModal ends the modal state, so after a call to EndModal,
! execution continues after the most recent call to GoModal.
!
! Warning: If you open a modal context in a window that is not requesting
! input, you may never get the chance to call EndModal(). If no other events
! have been requested (such as sound or timer events), the game will just sit
! there waiting for an input which will never come. 
!
! EndModal can also be called with a single argument. EndModal(1) will force
! the game to return to a non-modal state: EndModal() by itself only cancels
! the current modal state. If you have nested several calls
! to GoModal, EndModal() ends the most deeply nested one. If you want to
! end all modal calls (If, for example, the user finds himself too deeply
! nested in menus, and presses a "quit" button), EndModal(1) will
! terminate the outermost modal call (and all the inner ones as well).
! In this case, execution continues as if EndModal() had been called from within
! the first modal context.
!
! It is illegal to call EndModal() or EndModal(1) outside of a modal context.
! Attempting to doso will generate a GWindows internal error
! (GW_ERR_NOT_MODAL).  You can check whether or not you are in a modal context
! at any time by checking the variable 'GW_Modal': it will be nonzero if
! you are in a modal context.

ifndef GW_GMODAL_H;

system_file;
Constant GW_GMODAL_H;

Global GW_Modal=0;
Global GW_Modal_Top=0;
Constant GW_ERR_NOT_MODAL "Not in a modal context.";
[ EndModal x y;
  if (GW_Modal==0) @throw GW_ERR_NOT_MODAL GW_Massive_Error;
  if (x) y=GW_Modal_Top;
  else y=GW_Modal;
#ifdef USE_GCONSOLE;
GConsole.PenOn();
print "[GModal]: Closing modal context ", y, ".";
GConsole.PenOff();
#endif;
 @throw x y;

];
[ GoModal win  wid gwm f erf msl mss;
 if (win==0) win=Active_UI;
 if (GW_Modal==0) f=1;
 gwm=GW_Modal;
 erf=GW_Massive_Error;
 msl=self;
 mss=sender;
 @catch GW_Modal ?modebody;
 GW_Massive_Error=erf;
 if (f) GW_Modal_Top=0;
 GW_Modal=gwm;
 self=msl;
 sender=mss;
 DrawStatusLine();
 return;
 .modebody;
#ifdef USE_GCONSOLE;
GConsole.PenOn();
print "[GModal]: Opening new modal context (", GW_Modal, ").";
GConsole.PenOff();
#endif;
 
 if (f) GW_Modal_Top=GW_Modal;
 while(1)
 {
 DrawStatusLine();
 glk_select(gg_event);
 wid=FindWindowByWinid(gg_event-->1);
 if (gg_event-->0 ~= evtype_MouseInput or evtype_CharInput
        || wid==win || IndirectlyContains(win,wid))
   HandleGlkEvent(gg_event, 1, gg_arguments);
 else
  if (gg_event-->0 == evtype_MouseInput)
   glk_request_mouse_event(gg_event-->1);
  else
  if (gg_event-->0 == evtype_CharInput)
   glk_request_char_event(gg_event-->1);

 }
];
endif;

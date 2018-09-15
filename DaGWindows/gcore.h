! GWindows Core module                 L. Ross Raszewski
! 1.0                                  2002
!
! This is the very core of GWindows; it controls the loading of independent
! GWindows Modules.
!
! The primary function of the Core is to load and integrate various functions
! that use the Inform Library's Glk entrypoints.
#ifndef GW_CORE;
constant GW_CORE;
#ifdef GW_CORE;
#endif;
include "utility";
Constant INIT_REASON_GW_RESTART "GWindows restart";
Constant INIT_REASON_SYSSTART  "System startup";
Constant INIT_REASON_UNKNOWN "Unknown";
Object GWin_Core "GWindows Core"
 with name 'gwcore',
      prepare,
      event_handler,
      init, identify, update,
      number "1.0",
      init_reason INIT_REASON_SYSSTART;
Class GWin_Module;

!! XXX - v1.2x
![ AnnounceModule x;
! print (name) x;
! if (x provides number)
! {
!  print " ";
!  printanything(x.number);
! }
!];

[ InstallCore o;
 if (GWin_Core has general) rtrue;
 objectloop(o ofclass GWin_Module)
 {
  move o to GWin_Core;
  if (o provides prepare) o.prepare();
 }
 give GWin_Core general;
];

!! XXX - v1.2x
![ Banner i j;
!   InstallCore();
!   if (Story ~= 0)
!   {
!   glk($0086, 3); ! set header style
!   print (string) Story;
!   glk($0086, 0); ! set normal style
!   }
!   if (Headline ~= 0)
!       print (string) Headline;
!   print "Release ";
!   @aloads 52 0 i;
!   print i;
!   print " / Serial number ";
!   for (i=0:i<6:i++) print (char) 54->i;
!   print " / Inform v"; inversion;
!   print " Library ", (string) LibRelease;
!
!#ifdef DEBUG;
!   print " ";
!#endif;
!#ifdef STRICT_MODE;
!   print "S";
!#endif;
!#ifdef INFIX;
!   print "X";
!#endif;
!#ifdef DEBUG;
!   print "D";
!#endif;
! objectloop(i in GWin_Core)
! if (i hasnt general)
! {
!  j++;
!  print " / ";
!  AnnounceModule(i);
! }
! if (j==0) {
! print " / ";
! AnnounceModule(GWin_Core);
! }
! new_line;
!];

[ InitGlkWindow x o w i;
   InstallCore();
 objectloop(o in GWin_Core)
 if (o provides init)
 { i=o.init(x);
   if (i>w) w=i;
 }
 GWin_Core.init_reason=INIT_REASON_UNKNOWN;
 return w;
];
[ IdentifyGlkObject phase type ref rock o i w;
   InstallCore();
 objectloop(o in GWin_Core)
 if (o provides identify) { i=o.identify(phase,type,ref,rock);
        if (i>w) w=i;
        }
        return w;
];
[ DrawStatusLine o;
        InstallCore();
 objectloop(o in GWin_Core)
 if (o provides update)  o.update();

];


[ HandleGlkEvent ev x abortres i o w;
   InstallCore();
 objectloop(o in GWin_Core)
 if (o provides event_handler) { i=o.event_handler(ev,x,abortres);
        if (i>w) w=i;
        }
        return w;
];
#endif;

! gloader.h     -  GWindows UI Loader
! (c) 2006 by L. Ross Raszewski
!
! GLoader is a subsystem for abstracting user interfaces and facilitating
! the use of loadable UI templates.
!
! With GLoader, you can download a predefined template and include it in
! your game with minimal difficulty. GLoader also allows access to a number
! of typical UI functions in an abstract way, making it easier to write
! UI-independant code.
!
! See gltemplate.inf for an example of how to use GLoader
!
! Usage:
! * Include gloader.h
! * If using UIs with graphics, include resource definitions
!   * A template UI may provide more than one set of graphics.
!     You should include the set you wish to use in your resource
!     definitions. Using more than one set of graphics with a
!     template will require making some modifications to the template.
! * Include the template UIs you wish to use
! * In InitGWindows, include this line:
!       if (Active_UI==0)  GW_LoadUI(<name of initial UI you wish to use>);
! * In Initialise, include this line:
!       if (Active_UI provides before) Active_UI.before();
!
! Gloader system configuration:
!  Before including Gloader, you may define these constants to alter GLoader
!  behavior:
!  * TEXTMENU_TX (Default: "Select one of the following options:^^")
!       Text printed at the top of menus when using in-line minimalist menus
!  * GWL_FAIL_CLASSIC (Default: true)
!       If true, provide the "Classic" UI, and use it whenever unable to
!       generate the requested user interface.
!
! GLoader functions:
!   GW_LoadUI(ui)
!       Set the specified UI as the current interface. This should be used
!       to set the initial screen UI.  To change UIs at runtime, use
!       GW_ChangeUI instead
!
!   GW_ChangeUI(ui)
!       Change the screen layout to the specifed UI. Similar to GW_LoadUI,
!       But also forces a restart of the window system and performs
!       initialization steps. Returns the new UI (which may not be the one
!       you specified; see notes on failovers below)
!
!   GW_ShowImage(image)
!       Shows the specified image.  If the current UI specifies a graphics
!       window, the image will be shown there according to the usual
!       settings (That is, scaled to fit the window, obeying the windows's
!       aspect ratio settings).  If no graphics window is specifed,
!       the image is displayed at its natural size in the
!       main window.  Returns false if the image could not be displayed
!       (because the interpreter does not support graphics)
!
!   GW_ShowMenu(menu)
!      If the current UI specifies a menu window, shows the specifed menu
!      in it.  Returns false and does nothing if the current UI does not
!      provide a window for menus.  If your menu is for game-critical events
!      (as opposed to a simple alternative to typing), use GW_ShowModalMenu
!      instead. 
!
!   GW_EndMenu()
!       Deactivates the menu currently displayed in the menu window
!
!   GW_ShowModalMenu(menu)
!       Shows a modal menu.  If the current UI provides a menu window,
!       the menu will be shown there within a modal context (that is,
!       normal input will be disallowed while the menu is active).
!       If the current UI does not provide a menu window, the menu will be
!       displayed in-line using a simplified menu interface such as:
!
!               Select one of the following options:
!
!                1. Go
!                2. Stop
!                3. Quit
!                [1-3] >>
!
!  GW_EndModalMenu()
!       Deactivates the current modal menu.  Note that this function
!       behaves slightly differently when a simplified text menu is used:
!       When used with a text menu, the menu will terminate after
!       the current .select() routine returns.  When using
!       a menu window, this function does not return, but terminates
!       the menu immediately.  For best compatability, you should
!       return immediately after using this function.
!
!
! Building and using templatized UIs
!
! A templatized UI is similar to a normal GWindows UI. Technically,
! the only difference is that it provides a little extra information
! to help the GLoader API functions.
!
! When writing a template, however, you should observe certain style
! guidelines to make your template easy to use:
! * Templates should be compliant with the requirements of a persistant
!   main window
! * Avoid cluttering the namespace by using naming conventions for all public
!   symbols, and using private symbols unlikely to collide with the work of
!   other authors.  By convention, all symbols defined in a GLoader template
!   should begin with the name of the template, followed by an underscore.
!   The UI object itself should be named UI_<name of template>.
! * Use ifdefs where appropriate to define helper functions so that many
!   templates may use compatible definitions.
! * Include all standard widgets used by the template.
!
! To make a UI compatable with GLoader, you must make a few changes to the
! root WindowPair of your UI:
!  * Change the class from WindowPair to GWin_UI
!  * Provide whichever of the following properties apply to your UI:
!   *  g_mainwin - the main output window of the UI (manditory)
!   *  g_inputwin - the main input window of the UI (if different from mainwin)
!   *  g_menuwin - The default window for menus (You may have as many
!       menu windows as you like; this window is the one to be used
!       by default)
!   *  g_imagewin - The default window in which to display images. This should
!       be derived from GImageWin.
!   *  name - a dictionary word used to uniquely identify the UI (ie., its name)
!             This is used by the GLoader Demo/Gallery program to allow switching
!             between UIs.  gltemplate.inf shows how you can use this
!             ability to give players the option of choosing which of
!             several installed UIs they will use.  Not providing a name will
!             hide that UI from this functionality.
!   *  before - This function should perform any initialization required
!               after the UI has been built but before the next turn begins.
!               You should use it to, for example, activate any
!               maps or menus which the interface uses.
!  * If your UI uses features not available on all interpreters, provide
!    the property g_ability.  Its value should be a bitmask of the following
!    constant values:
!       GWIN_MGOK       -  The UI requires the use of the mouse in
!                          a graphics window
!       GWIN_MGOK       -  The UI requires the use of the mouse in
!                          a textgrid window
!       GWIN_GWOK       -  The UI requires graphics capabilities
!       GWIN_DROK       -  The UI requires the ability to draw images in
!                          a graphics window.
!
! Failovers
!
!  If g_ability is set for a UI, GLoader will query Glk before attempting to
!  create the interface.  If any of the requested abilities are not available,
!  Gloader will (so long as GWL_FAIL_CLASSIC is set) switch to the classic
!  UI. If you want more nuanced behavior, you can use the "failover" capability
!
!  To do this, set g_failover on your UI to a different UI.  If the first UI
!  can not be created, GLoader will attempt to use the failover UI instead.
!  It will try the failover for each UI it tries to load until no failover is
!  specifed, at which point, if GWL_FAIL_CLASSIC is set, it will use the
!  classic UI.  If GWL_FAIL_CLASSIC is not set, the UI Load will fail.
!
!  DO NOT put a loop into the chain of failover UIs.  That would be bad.
!  Template writers may set a failover themselves, preferably to either
!  UI_Classic, or to a backup UI contained in the same template.
!  You can also set the failover at runtime.  This should be done in
!  InitGWindows(), before the call to GW_LoadUI.

system_file;
Default TEXTMENU_TX "Select one of the following options:^^";
Default GWL_FAIL_CLASSIC 1;
Include "gmodal";
Include "gmenu";
Include "GImage";


Class GWin_UI class WindowPair
 with g_load [;
               Active_UI=self;
               Main_GWindow=self.g_mainwin;
               if (self.g_inputwin)
               Input_GWindow=self.g_inputwin;
               else Input_GWindow=self.g_mainwin;
                ],
      g_ability 0,
      g_mainwin 0,
      g_inputwin 0,
      g_menuwin 0,
      g_imagewin 0,
      g_statuswin 0,
      g_failover 0;

Array GW_Loaderflags-->2;
! -->0 : Text mode modal Menu


[ GW_ShowImage x;
  if (Active_UI.g_imagewin)
  {
   if (Active_UI.g_imagewin ofclass GImageWin)
    {
     Active_UI.g_imagewin.image=x;
     GW_ForceRedraw(Active_UI.g_imagewin);
    }
   gwin_image_draw_auto(Active_UI.g_imagewin.winid,x,0,0,Active_UI.g_imagewin.width, Active_UI.g_imagewin.height);
   rtrue;
  }
  if (glk_gestalt(gestalt_DrawImage,wintype_TextBuffer))
  { gwin_image_drawf(Active_UI.g_mainwin.winid,x,imagealign_InlineUp,0); glk_window_flow_break(Active_UI.g_mainwin.winid);
  rtrue;}
  rfalse;
   
];
[ GW_ShowMenu m;
 if (Active_UI.g_menuwin) { (Active_UI.g_menuwin).activate(m); rtrue; }
 rfalse;
];
[ GW_ShowModalMenu m n x;
 if (Active_UI.g_menuwin) { (Active_UI.g_menuwin).activate(m); GoModal(Active_UI.g_menuwin); rtrue; }
 GW_Loaderflags-->0=1;
 while(GW_Loaderflags-->0==1)
        {
         print (string) TEXTMENU_TX; 
         n=1;
         objectloop(x in m)
         {
          print n, ". ", (name) x, "^";
          n++;
         }
         x=0; n--;
         while(x < 1 || x > n)
         {
          print "^[1-", n, "] >>";
          keyboardprimitive(buffer,parse);
          x=tryNumber(1);
         }
         scion(m,x).select();
        }
];
[ GW_EndMenu;
 if (Active_UI.g_menuwin) (Active_UI.g_menuwin).deactivate();
];
[ GW_EndModalMenu;
 if (Active_UI.g_menuwin) { (Active_UI.g_menuwin).deactivate(); EndModal(); }
 GW_Loaderflags-->0=0;
];


[ GW_LoadUI x y;
  if (~~(x ofclass GWin_UI)) rfalse;
   while (~~y)
   {
    if (((x.g_ability & GWIN_MGOK) && ~~glk_gestalt(gestalt_MouseInput,wintype_Graphics)) ||
        ((x.g_ability & GWIN_MTOK) && ~~glk_gestalt(gestalt_MouseInput,wintype_TextGrid)) ||
        ((x.g_ability & GWIN_GWOK) && ~~glk_gestalt(gestalt_Graphics,0)) ||
        ((x.g_ability & GWIN_DROK) && ~~glk_gestalt(gestalt_DrawImage,wintype_Graphics)))
         { x=x.g_failover; if (~~x) {
         if (GWL_FAIL_CLASSIC) y=UI_Classic;
         else 
         rfalse;
         } }
    else y=x;
    
   }
 y.g_load();
 rtrue;
];

[ GW_ChangeUI x y;
 y=Active_UI;
 GW_loadUI(x);
 if (Active_UI==y) rfalse;
 RestartGWindows();
 if (Active_UI provides before) Active_UI.before();
 return Active_UI;
];

#Iftrue GWL_FAIL_CLASSIC==1;
include "Classic.h";
#Endif;


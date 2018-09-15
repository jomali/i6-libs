! GWindows      Beta .9
! Screen API for glulx
! By L. Ross Raszewski

! This version contains numerous small fixes, a few new features, a lot
! of new widgets, and several new examples.

! gwindows.h -- library replacements
! Include this file *after* parser

! Setting up GWindows
!
! Gwindows consists of 3 primary include files.
! Include "gwindefs" *BEFORE* parser
! Include "gwincls" *After* the parser
! Include "gwindows" after gwincls
!
! GWindows eats most of the Glk entry points, and gives you its own:
! GWindowsGlkEvent  - Equivalent to HandleGlkEvent. Only called
!                     if GWindows's mechanisms don't want the event
!                     Specifically, you won't receive redraw or arrange
!                     events. You won't recieve mouseinput or charinput
!                     events for windows which use GWindows's mouse and
!                     character mechanisms
! GWindowsGlkIdentify - Equivalent to IdentifyGlkObject. Ignore its input
!                       for windows, as GWindows will recreate the window
!                       system for you
!  InitGWindows - Called whenever the game starts, restarts, or restores.
!                 Equivalent to InitGlkWindows(0).
!                 You are *required* to create this function, which is where
!                 you set up the variables for GWindows. Namely:

!                 Active_UI - The windowpair object for the current window
!                             tree.
!                 Main_GWindow - the window which will act in place of
!                                gg_mainwin
!                 Input_GWindow - the window where library string input
!                                should be done. Usually, this should
!                                be the same as Main_GWindow, but
!                                if you want a separate input window,
!                                put it here
!                 
!
!
! The Window Model and How to use it
!
! Glk's window creation mechanism is not complicated, and has a number
! of advantages on the technical side. However, it is very easy to
! get confused. I really can't explain how it works very well, so
! this section will be heavy on examples. The best way to learn
! glk window structures is to look at them written out until you
! get a feel for them. It may be a good idea to design your window
! system on paper first as a tree diagram.
!
! Since windows only split one way, you group windows based on a
! common split direction.
! consider:
! +-----------+
! | A         |
! +-----+-----+
! | B   | C   |
! +--+--+--+--+
! |D |E |F | G|
! +--+--+--+--+
! There are a number of ways to split this.
! Since 'A' is only touching windows on one side, it makes sense to
! make the highest-level pair into 'a' and 'not a'. Since 'not a' consists
! of many windows, we know that pair 1 will consist of A and a another pair:
! Pair 1 (a vertical split):
!  A (1/3 of the screen)
!  Pair 2 (2/3 of the screen)
! Now, there are two ways to split up pair 2; we can make the next split
! (B,D,E) and (C,F,G) (making a vertical split) or we can make it (B,C) and
! (D,E,F,G) (a horizontal split). Since we've already done one
! horizontal split, we'll try the vertical one now (There are also speed
! advantages in having the windows evenly distributed, but these are not
! usually signifigant)
! Pair 2: (a vertical split)
!  Pair 3 (B,D,E; 1/2 of Pair 2)
!  Pair 4 (C,F,G; 1/2 of Pair 2)
! Now, for pairs 3 and 4, there's only one way to split (since a split can
! only go in one direction, you have to split along lines which go all the
! way across the pair. We split B off from (D,E) (And we do the same thing
! for pair 4)
! Pair 3: (a horizontal split)
! B (1/2 of pair 3)
! Pair 5 (D,E; 1/2 of pair 3)
! (Pair 6 is similarly created from Pair4, and contains F and G)
! Finally, we split the remaining pairs, which have two windows each:
! Pair 5: (a vertical split)
! D (1/2)
! E (1/2)
!
! Life would be very simple if that was all there was to it.
! But it's not.
!
! Glk creates new windows by splitting old ones (except for the first
! window, which is initially given the entire area of the screen).
! When a new window A is split off from an old window B, the region
! formerly occupied by B is given to a "Pair window". The Pair Window's
! space is filled by the windows A and B, according to the metrics of the
! split.
! All of this is very confusing, and most of the time, it's easier
! for the end-user to think of the Pair Window as having come first.
! But there's one time when it's important (in GWindows) to remember
! Glk's native window representation;
! When you define B, you simply say what percentage of its
! parent pair you want it to occupy. However, when you define A, A has
! to specify how much space *the pair* will occupy, and where it will be
! situated relative to other windowpairs on the screen.
!
! And, most confusing of all, order matters.
!
! In GWindows, you design the window hierarchy as objects.
! You declare the windows the way you want them,
! and GWindows uses this object structure to make sure that
! the proper glk calls happen in the correct order.
!
! There are two fundamental window classes in GWindows: Window and WindowPair
! 'Window' corresponds to the actual windows you see on the screen,
! and "WindowPair" corresponds to the invisible pair windows which
! Glk implicitly creates to manage the windows.
! A Window has no children, a WindowPair has two (only having one is not
! legal, since the pair window is only constructed when the second window
! of the pair is made. If you have more than two windows in a pair, only
! the first two are actually constructed).
!
! You can next windowpairs as deeply as you like, remembering that with
! each level, it becomes harder to keep track of which windows define
! which splits:
! WindowPair top
!  WindowPair A
!   WindowPair B
!    Window C
!    WindowPair D
!   WindowPair E
!    Window F
!    Window G
!  Window H
!
! In this example, 'C' is created first, and will recieve whatever space
! isn't
!
!
! A window-pair is constructed thus:
! First, the eldest child window is opened. Its split metrics
! become the metrics of the entire window pair:
!
! WindowPair top;
! Window -> A;
! WindowPair -> B;
!  Window -> -> C;
!  Window -> -> D;
!
! Window C "determines" the size of B -- C is initially created by
! splitting A, so if C's split-size is 50, B will eventually become
! 50% of the WindowPair 'top'.
!
! Next, the younger child is created. It is split from the elder child,
! Which creates B as a side effect.
! In the above example, D is created by splitting C. B now contains both C
! and D. If D's size was 25, D would occupy 25% of B, and C would occupy the
! remaining 75%
!
! Generally, you have to specify a split size for all of the "real" windows
! (textbuffer, textgrids, and graphics windows). There is one exception:
! The first window created will be automatically sized to the entire screen,
! slowly giving up space to all the other windows as they are created.
! Most of the time, you will want a large "main" window, and a number of
! smaller windows. The main window should be the first window created
! (If you draw the window hierarchy as a binary tree, the first window created
! is the leftmost leaf node. Generally, the first "real" window defined in the
! hierarchy will be the first window created.)
!
! Windows are opened when they receive the 'g_open(x)' message. The parameter
! 'x' is the ID of the window "from which" the new window will be split
! (in GLK terms, this is the 'from' parameter to glk_window_open.)
!
! You will almost never want to send a g_open message yourself;
! opening all the windows is done for you recursively by GWindows (so
! that if you open the root of a window tree, all the windows in that tree
! are opened in the proper order) (The proper order being the order
! that they occur in the source) at the beginning of the game.
!
! If you want to switch from one window heirarchy to another (for example,
! in a game like Suspended, you might want to have a unique interface for
! each robot), the easiest way to do this is to set Active_UI to the root
! of the new window tree and call InitGlkWindows(0);
! 
!
! The Window Class is the representation of a "real" window. It has several
! important properties:
!
! winid:  This is the Glk identifier for the window. If you want to call
!         a glk function for window X, pass 'X.winid' as the 'ref' parameter.
!         This value is generated by GWindows when the window is opened.
!         Don't mess with it. (WindowPairs also have a winid, but GWindows
!         already does everything that you'd need to do to a WindowPair
!         directly
! split: This is the size of the window. For the elder child of a pair,
!        this is really the size of the pair itself. For the younger child,
!        it is the size of the window itself.
! split_dir: This is the direction of the split.
!            It can be any of the winmethod_ directions defined in infglk.h
!            Like 'split', which window this direction is in relation to is
!            determined by the window's placement within the pair.
!       AN Example:
!       WindowPair top;
!       Window -> A;
!       WindowPair -> B;
!        Window -> -> C
!        with split 25,
!             split_dir winmethod_Left;
!        Window -> -> D
!       with split 50,
!            split_dir winmethod_Below;
!
!       In this example, 'top' is the whole screen. 'B' is the
!       leftmost quarter of the screen, which is divided equally between
!       C and D, with C on the top. A is "all the space that's left"
!       
!       WindowPair top;
!       Window -> A;
!       WindowPair -> B;
!        Window -> -> D
!       with split 50,
!            split_dir winmethod_Below;
!        Window -> -> C
!        with split 25,
!             split_dir winmethod_Left;
!
!       Consider how this differs: C and D are reversed. WHat does this cause?
!       Well, now it's D's metrics which determine B.  In this version,
!       B is the bottom half of the screen, and A is the top half.
!       C occupies the left quarter of B, and D the right three quarters.
!
!       wintype: wintype_TextBuffer, wintype_TextGrid or wintype_Graphics
!                Classes exist for each type (TextBuffer, TextGrid, and
!                GraphWin), so you shouldn't have to set this yourself.
!
!       rock: the "rock" or "magic identifying number" of the window.
!             GWindows doesn't really use this, but you might need to
!       redraw: If provided, this function is used to regenerate the contents
!               of a window. It will be called in response to a
!               window arrange or redraw event.  Additionally,
!               whenever the windows are updated, it will be called if
!               the 'general' attribute is set.
!               For something like your main story window, this should be
!               omitted. For a graphics window, it should redraw the
!               graphics, and it should re-create the contents for other
!               special-purpose windows
!       update: If provided, this function is called at least once per turn.
!               (It's called whenever the library thinks that the statusline
!               shoudl be drawn).  This is the place to put the code to update
!               a window whose appearance is heavily dependent on the game
!               state, such as a status line or an graphic window that shows
!               a picture of the current location
!               (This is for things that change a lot. If, say, you
!               have a window that changes its graphic only when something very
!               specific happens, you might want to put the code in redraw,
!               and just set the window 'general' when the time comes.
!               For example, if you have a graphics window that shows a
!               different graphic for each location, you might put the code
!               to draw the image border in redraw, and the code to draw the image
!               itself in update.) Note that update will also be called whenever
!               the image is redrawn
!       width, height: These contain the size of the window in whatever units
!               are apropriate for the window (characters or pixels). It is
!               updated whenever the window is redrawn.
!       click_event(x,y): If provided, this function will be called when
!               the window is clicked. Note that some window types do not
!               support clicks.  By providing this function, you
!               also inform GWindows that it should request mouse clicks
!               for this window.
!       char_event(x): If provided, and the object is set "on", this function
!               is called when a character event is requested.
!               GWindows will request char events from such windows when the game
!               begins or is restored.
! The following attributes are also meaningful:
!  abssplit - If this is set, the split size is "absolute" -- that is, it gives
!             the requested window size in pixels or characters. If this is
!             unset, the split size is taken to be proportional
!  general - "needs to be redrawn" -- the redraw function for this window will
!            be called when the screen is next updated
!  on - On windows providing a char_event routine, this indicates that GWindows
!       should request character events when the game is started or restored
!       Note that this DOES NOT take effect except when the system is started or
!       restored! If you want to *start* gettign character events,
!       set the object on, then call glk_request_char_event. Likewise,
!       you have to cancel the char event manually when you unset this flag.
!
!
! Other GWindows Features:
!
!
! "command override"
! If cmd_override is set to a nonzero value, the pending line of input will
! be cancelled and the text of cmd_override will be inserted instead
! (This is done using PrintAnything, so cmd_override can be set to anything
! which PrintAnything can handle)
! For example, if you wanted an icon for "look", you could draw it in a graph
! window, then have the click_event for that window execute
! cmd_override="LOOK";
! It will be exactly as if the user had typed "LOOK" at the input line and
! pressed return.
!
! "command line appending"
! The function streamword(x) will insert the textual expansion of x (that is,
! whatevr PrintAnything(x) would print) at the end of the current line of
! input. Thus, you could have the click-event on, say a graphic of
! a car execute streamword("car");
! If the player had typed "EXAMINE ", then clicked on the car, his input
! would become "EXAMINE car"
!
! "Input window echoing"
! If you wish to use a separate window for input, set Input_GWindow to the
! window object which will take input.
! By default, the input is copied into the main window when the line is read.
! (so that it will appear in the game transcript) If this behavior is
! not desired, Define GW_INPUT_ECHO to 0 before including gwindefs.h
! 
! Because this may affect how the prompt should look, here is a proposed
! method:
! alter the library message for 'Prompt' to omit the '>' indicator.
! Have the message instead execute
! set_prompt=1;
! When the text is echoed to the main window, it will be prefaced by
! the string GW_Echo_Prompt (default is ">")
!
! Included with this library are several sample derived classes. See
! their documentation for details.
!
!--------------------------------------------------------------------------
!
! NOTA DE ELIUK BLAU: Correcciones... (buscar comentarios con "Eliuk")
!
! 1) No se muestra el mensaje de la libreria para el proceso de
!    lectura de un archivo de transcripcion de ordenes del jugador
!    [rutina KeyboardPrimitive()], porque causa un comportamiento
!    extraño en el prompt luego de re-ejecutar las ordenes; lo anterior
!    podria ser arreglado con un minimo esfuerzo, pero en la Lib. 6/11
!    la rutina KeyboardPrimitive() tampoco muestra ese mensaje de la
!    libreria, por lo que aqui he decidido imitar el comportamiento
!    por defecto de la Lib. Inform 6/11.
!
! 2) Las unicas dos apariciones de la rutina 'glk_window_close()' en
!    este archivo producian un error con INFGLK v0.7.0 (08/31/2006)
!    puesto que el autor asumia el argumento final cero en llamadas
!    al estilo 'glk_window_close(win)', pero como ahora InfGlk.h usa
!    '_vararg_count' para guardar los argumentos que se le pasan a las
!    rutinas Glk que implementa, este valor no puede asumirse porque
!    entonces simplemente 'no existe argumento'. Se corrige colocando
!    el cero que faltaba al estilo 'glk_window_close(win,0)'. Este
!    error debe haber sido un posible despiste del autor... pero en
!    las llamadas a Glk nunca debe 'asumirse' un argumento, incluso
!    si este tiene valor cero.
!
!--------------------------------------------------------------------------

ifndef GW_GWINDOWS_H;
Constant GW_GWINDOWS_H;
! to suppress warnings...
ifdef GW_GWINDOWS_H;
endif;
include "gcore";
! Dummy GConsole
#ifndef USE_GCONSOLE;
Object GConsole
with winid 0, number 0, penon [; @setiosys 0 0;], penoff [; @setiosys 2 0;],
     write [s; s=0; ];
#endif;

[ ScriptOnSub o;
  if (gg_scriptstr ~= 0)
    return L__M(##ScriptOn,1);

  if (gg_scriptfref == 0) {
    ! fileref_create_by_prompt
    gg_scriptfref = glk($0062, $102, $05, GG_SCRIPTFREF_ROCK); 
    if (gg_scriptfref == 0) 
      jump S1Failed;
  }
  ! stream_open_file
  gg_scriptstr = glk($0042, gg_scriptfref, $05, GG_SCRIPTSTR_ROCK); 
  if (gg_scriptstr == 0)
    jump S1Failed;

!  glk($002D, gg_mainwin, gg_scriptstr); ! window_set_echo_stream
  objectloop(o ofclass GWindow && IndirectlyContains(active_UI,o))
   if (o has scripted || o==Main_GWindow) glk_window_set_echo_stream(o.winid,gg_scriptstr);
  L__M(##ScriptOn,2);
  VersionSub();
  return;

.S1Failed;
  L__M(##ScriptOn,3);  
];

[ KeyboardPrimitive  a_buffer a_table done ix i;
#IFDEF DEBUG;
  if (gg_commandstr ~= 0 && gg_command_reading ~= false) {
    ! get_line_stream
    done = glk($0091, gg_commandstr, a_buffer+WORDSIZE,
      (INPUT_BUFFER_LEN-WORDSIZE)-1);
    if (done == 0) {
      glk($0044, gg_commandstr, 0); ! stream_close
      gg_commandstr = 0;
      gg_command_reading = false;
      ! CORREGIDO POR ELIUK BLAU
      ! L__M(##CommandsRead, 5); would come after prompt
      ! fall through to normal user input.
    }
    else {
      ! Trim the trailing newline
      if ((a_buffer+WORDSIZE)->(done-1) == 10)
        done = done-1;
      a_buffer-->0 = done;
      glk($0086, 8); ! set input style
      glk($0084, a_buffer+WORDSIZE, done); ! put_buffer
      glk($0086, 0); ! set normal style
      print "^";
      jump KPContinue;
    }
  }
#ENDIF;
  done = false;
   if (Input_GWindow~=Main_GWindow)
    glk_window_clear(Input_GWindow.winid);
   glk($00D0, Input_GWindow.winid, a_buffer+WORDSIZE, INPUT_BUFFER_LEN-WORDSIZE,
    0); ! request_line_event
  while (~~done) {
    glk($00C0, gg_event); ! select
    switch (gg_event-->0) {
      5: ! evtype_Arrange
        DrawStatusLine();
      3: ! evtype_LineInput
         if (gg_event-->1 == Input_GWindow.winid) {
          a_buffer-->0 = gg_event-->2;
          done = true;
        }
    }
    ix = HandleGlkEvent(gg_event, 0, a_buffer);
    if (ix == 2) {
      done = true;

    }
    else if (ix == -1) {
      done = false;
    }
  }
 if (Main_GWindow ~= Input_GWindow && GW_INPUT_ECHO)
 {
  if (set_prompt)
   PrintAnything(GW_Echo_Prompt);
  set_prompt=0;
  glk_set_style(style_Input);
  for(i=0:i<a_buffer-->0:i++)
  print (char) a_buffer->(WORDSIZE+i);
  new_line;
  glk_set_style(style_Normal);
 }
  
#IFDEF DEBUG;
  if (gg_commandstr ~= 0 && gg_command_reading == false) {
    ! put_buffer_stream
    glk($0085, gg_commandstr, a_buffer+WORDSIZE, a_buffer-->0); 
    glk($0081, gg_commandstr, 10); ! put_char_stream (newline)
  }
#ENDIF;
.KPContinue;
#ifdef GW_PRETOKENIZE;
 if (~~__Pretokenize(a_buffer, a_table)) Tokenise__(a_buffer, a_table);
#ifnot;
  Tokenise__(a_buffer,a_table);
#endif;
  ! It's time to close any quote window we've got going.
  if (gg_quotewin) {
    glk($0024, gg_quotewin, 0); ! close_window
    gg_quotewin = 0;
  }
];


GWin_Module "GWindows" with number GW_VERSION,
init [x i g hold hh o oo io;
#ifdef USE_GCONSOLE;
GConsole.write("[GWindows]: Initializing GWindows.^
                [GWindows]: Testing the gestalt.^");
#endif;

  if (x==0)
  {
   if (glk_gestalt(gestalt_MouseInput,wintype_Graphics))
    GW_Abilities=GWIN_MGOK;
   if (glk_gestalt(gestalt_MouseInput,wintype_TextGrid))
    GW_Abilities=GW_Abilities | GWIN_MTOK;
   if (glk_gestalt(gestalt_Graphics,0) && ~~(GW_Override & GWIN_GWOK))
    GW_Abilities=GW_Abilities | GWIN_GWOK;
   if (glk_gestalt(gestalt_DrawImage,wintype_Graphics) && ~~(GW_Override & GWIN_DROK))
    GW_Abilities=GW_Abilities | GWIN_DROK;
   InitGWindows();
   if (~~Input_GWindow) Input_GWindow=Main_GWindow;



! BEGIN CLOSING WINDOWS

   i=glk_window_get_root();

#ifdef USE_GCONSOLE;
   if (GConsole.winid) i=glk_window_get_sibling(GConsole.winid);
#endif;
if (GWIn_Core.init_reason==INIT_REASON_SYSSTART || ~~gw_restore_layout())
{
#ifdef USE_GCONSOLE;
    GConsole.penon();
    print "[GWindows]: Could not match current Glk layout to the active UI. Rebuilding screen.^";
    GConsole.penoff();
#endif;     

  if (i)
   {
   hh = GW_Find_First_Window(Active_UI);
   GW_Persistant_win=0;
   hold=0;
   if (hh ofclass GPersistantWin) {
           o = glk_window_iterate(0,GG_ARGUMENTS);
           while(o)
           {
            if (GG_Arguments-->0 == GW_PERSISTANT_ROCK)
            {
                hold=o;
                break;
            }
          o=glk_window_iterate(o,GG_ARGUMENTS);
          }
          }
     if (hold)
     {
      ! Do not close the hold window.
      ! Set the new persistant window.
      o = glk_window_iterate(0,gg_arguments);
      while(o)
       {
        io=gg_arguments-->0;        
        oo=glk_window_iterate(o,gg_arguments);
        if (io ~= 0 && o~=GConsole.winid && o~= hold) {
                glk_window_close(o,0); ! CORREGIDO POR ELIUK BLAU (faltaba el cero)
                oo = glk_window_iterate(0,gg_arguments);
                }
        o=oo;
       }

      hh.winid=hold;

      if (GW_Persistant_win provides char_event &&
          (~~hh provides char_event)) glk_cancel_char_event(hold);
      GW_Persistant_win=hh;
      give hh open ~absent;
     }
     else
     {
     glk_window_close(i,0); ! CORREGIDO POR ELIUK BLAU (faltaba el cero)
     }

 }


! ALL WINDOWS CLOSED

! Try
   g=GW_Massive_Error;
   @catch GW_Massive_Error ?ignoerr;
   GWindowsErrorHandler(GW_Massive_Error);
   GW_Massive_Error=g;
   .ignoerr;
i=0;
#ifdef USE_GCONSOLE;
if (GConsole.winid)
 i=GConsole.winid;
else
{
 GConsole.winid=glk_window_open(0,0,0,wintype_TextBuffer,GConsole);
 i=GConsole.winid;
 GConsole.write("[GWindows]: GConsole activated.^");
}
 GConsole.write("[GWindows]: Initializing the user interface.^");
#endif;

   Active_UI.g_open(i);
   }
#ifdef USE_GCONSOLE;
 GConsole.write("[GWindows]: Setting Up the Main Window^");
#endif;

   gg_mainwin=Main_GWindow.winid;
   glk_set_window(gg_mainwin);
#ifdef USE_GCONSOLE;
 GConsole.write("[GWindows]: UI is open. Beginning redraw^");
#endif;

   Active_UI.deep_redraw();
#ifdef USE_GCONSOLE;
GConsole.write("[GWindows]: Initializing all event handlers and setting up transcripting.^");
#endif;

   io=Glk_window_iterate(0,GG_Arguments);
   while(io)
   {
    if (gg_arguments-->0 == GW_PERSISTANT_ROCK) i=GW_Persistant_Win;
    else i=gg_arguments-->0;
    if (indirectlycontains(active_ui,i))
!   objectloop(i ofclass GWindow  && indirectlycontains(active_ui,i))
   {
     if (i provides init) i.init();        
     if (i provides click_event && i has on)
     if ((i.wintype==wintype_Textgrid && GW_Abilities & GWIN_MTOK)||
          (i.wintype==wintype_Graphics && GW_Abilities & GWIN_MGOK))
     GWindows_request_mouse_event(i);
     if (i provides char_event && i has on)
      gwindows_request_char_event(i);
     if (gg_scriptstr && (i has scripted || i==Main_GWindow))
      glk_window_set_echo_stream(i.winid,gg_scriptstr);
   }
   io = glk_window_iterate(io,gg_arguments);
  }
   rtrue;
  }
rfalse;
],
identify [phase type ref rock;
if (phase==0 && Active_UI && Active_UI has open)
 InitGlkWIndow(0);
return GwindowsGlkIdentify(phase,type,ref,rock);
],
event_handler
[ev x abortres handled g;
 g=GW_Massive_Error;
 @catch GW_Massive_Error ?evhne;
 GWindowsErrorHandler(GW_Massive_Error);
 GW_Massive_Error=g;
 return;
 .evhne;
 switch(ev-->0)
 {
  evtype_Redraw, evtype_Arrange:
#ifdef USE_GCONSOLE;
    GConsole.write("[GWindows]: Redraw/Arrange event received. Forcing redraw of user interface.^");
#endif;
    Active_UI.deep_redraw();
    handled=1;
  evtype_MouseInput:
#ifdef USE_GCONSOLE;
    GConsole.penon();
    print "[GWindows]: Mouse event received in window ", ev-->1, ".
        event value is (", ev-->2, (char) ',', ev-->3, ").^";
    GConsole.penoff();
#endif;
    x=FindWindowByWinid(ev-->1);
    if (x && x provides click_event)
    {
    gwindows_request_mouse_event(x);
#ifdef USE_GCONSOLE;
    GConsole.penon();
    print "[GWindows]: Calling mouse event handler on window ~", (name) x, "~.^";
    GConsole.penoff();
#endif;     
     x.click_event(ev-->2,ev-->3);
    handled=1;
    }
    else {
#ifdef USE_GCONSOLE;
    GConsole.write("[GWindows]: Unable to forward mouse event to a GWindow.^");
#endif;
 }
  evtype_CharInput:
#ifdef USE_GCONSOLE;
    GConsole.penon();
    print "[GWindows]: Character event received in window ", ev-->1, ".
        event value is ", ev-->2;
    if ((ev-->2 <= 126 && ev-->2 >= 32) ||(ev-->2 >=160 && ev-->2<=255))  
    print  " ('", (char) ev-->2, "').^";
    else print " (unprintable).^";
    GConsole.penoff();
#endif;
  x=FindWIndowByWinid(ev-->1);
  if (x && x provides char_event && x has on)
  {
#ifdef USE_GCONSOLE;
    GConsole.penon();
    print "[GWindows]: Calling character event handler on window ~", (name) x, "~.^";
    GConsole.penoff();
#endif;
   gwindows_request_char_event(x);
   x.char_event(ev-->2);
    handled=1;
  }
 }
 if (cmd_override)
 {
  glk_cancel_line_event(Input_GWindow.winid,0);
#ifdef GW_ECHO_OVERRIDE;
  glk_set_style(style_Input);
  PrintAnything(cmd_override);
  new_line;
  glk_set_style(style_Normal);
#endif;
  x=PrintAnyToArray(abortres+WORDSIZE,INPUT_BUFFER_LEN-WORDSIZE,cmd_override);
  cmd_override=0;
  abortres-->0=x;
  return 2;
 }
#ifndef GW_NO_AUTOLOAD;
if (~~handled) return GWindowsGlkEvent(ev,x,abortres);
#endif;
],
update
[g;
 g=gw_massive_error;
 @catch GW_Massive_Error ?dslnoerr;
 GWindowsErrorHandler(GW_Massive_Error);
 gw_massive_error=g;
 return;
 .dslnoerr;
 GW_Action_Reason=GW_REASON_UPDATE;
 Active_UI.checkredraw();
 Active_UI.deep_update();
];



[ GWindows_open_window from st split type rock;
#ifdef USE_GCONSOLE;
if (from==GConsole.winid)
! if (split==0)
 { st=winmethod_Above | winmethod_Proportional;
   split=75;
 }

if (GConsole.winid)
{
 GConsole.penon();
 print "[GWindows]: Opening new window from window #", from, ". Split method is ",
 st, "; window type ", type, "; split size ", split, ".^";
 GConsole.penoff();
}
#endif;
return glk_window_open(from,st,split,type,rock);
];

[ GWindows_request_char_event x;
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GWindows]: Requesting character event for window ~", (name) x, "~.^";
GConsole.penoff();
#endif;
glk_request_char_event(x.winid);
];

[ GWindows_request_mouse_event x;
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GWindows]: Requesting mouse event for window ~", (name) x, "~.^";
GConsole.penoff();
#endif;
glk_request_mouse_event(x.winid);
];
[ GW_Invalidate_layout x o;
 give x absent;
 objectloop(o in x)
  if (o ofclass GWindow || o ofclass WindowPair) GW_Invalidate_layout(o);
];
[ GW_Revalidate_layout x o;
 objectloop(o in x)
  {
   if (o ofclass WindowPair) GW_Revalidate_layout(o);
   if (o has absent)
        return;
  }
 give x ~absent;
 x.winid=glk_window_get_parent(child(x).winid);
];
[ GW_Check_layout x o;
 if (x has absent) return false;
 objectloop(o in x)
 {
  if ((o ofclass GWindow || o ofclass WindowPair) && ~~GW_Check_layout(o)) return false;
 }
 return true;
];
[ GW_finalize_layout x o;
 if (x provides validate && x.validate()) return false;
 if (x ofclass WindowPair)
 objectloop(o in x)
  if (~~GW_finalize_layout(o)) return false;
 return true;
];
[ GW_Restore_Layout o io;
  GW_Invalidate_layout(Active_UI);
  o=glk_window_iterate(0,GG_ARGUMENTS);
#ifdef USE_GCONSOLE;
    GConsole.penon();
    print "[GWindows]: Attempting to restore screen layout.^
        [GWindows]: Matching existing glk windows to current GWindows UI^";
    GConsole.penoff();
#endif;     
  
  while(o)
  { if (GG_ARGUMENTS-->0==GW_PERSISTANT_ROCK) io=GW_Persistant_Win; else io=GG_ARGUMENTS-->0;
   if (IndirectlyContains(Active_UI,io))
    {
     io.winid=o;
     give io ~absent;
    }
   else if (gg_arguments-->0==GConsole) GConsole.winid=o;
   else if (gg_arguments-->0 ~=0)
    return false;
  o=glk_window_iterate(o,GG_ARGUMENTS);
  }
#ifdef USE_GCONSOLE;
    GConsole.penon();
    print "[GWindows]: Validating pair windows.^";
    GConsole.penoff();
#endif;     

  GW_Revalidate_layout(Active_UI);
#ifdef USE_GCONSOLE;
    GConsole.penon();
    print "[GWindows]: Checking that the new UI is valid and finalizing.^";
    GConsole.penoff();
#endif;     

  return gw_check_layout(active_ui) && gw_finalize_layout(active_ui);
];


[ GW_Find_First_Window w;
 while (w && w ofclass WindowPair)
  w=child(w);
 return w;
];

![ GW_Find_Window w t x;
! if (w==0) return 0;
! if (t(w)) return w;
! x=GW_Find_Window(child(w),t);
! if (x) return x;
!
! x=sibling(child(w));
!#ifndef GW_NO_TAILCALL;
! @copy t sp;
! @copy x sp;
! @tailcall GW_Find_Window  2;
!#ifnot;
! return GW_Find_Window(x,t);
!#endif;
!];
![ GW_Is_Persistant x;
! if (x ofclass GPersistantWin) rtrue;
! rfalse;
!];

Stub GWindowsGlkEvent 3;
Stub GWindowsGlkIdentify 4;
Stub GWindowsHandleError 1;
endif;

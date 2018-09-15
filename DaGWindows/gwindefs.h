! GWindows      1.0
! Screen API for glulx
! By L. Ross Raszewski

! gwindefs.h - Global declarations, defaults, etc
! include this file *before* parser
ifndef GW_GWINDEFS_H;
include "gcdefs.h";
system_file;
Constant GW_GWINDEFS_H;
Attribute abssplit;
Attribute scripted;
Attribute aspected;
Replace KeyboardPrimitive;
Replace ScriptOnSub;
Global Active_UI;
Global Main_GWindow;
Global Input_GWindow;
Global Set_Prompt=0;
Global cmd_override=0;
Global GW_Massive_Error=0;
Global GW_Persistant_Win;
Default GW_INPUT_ECHO 1;
Default GW_Echo_Prompt ">";
Constant GW_VERSION "1.0";

Constant GWIN_GWOK 1;
Constant GWIN_DROK 2;
Constant GWIN_MGOK 4;
Constant GWIN_MTOK 8;

Constant GW_REASON_UPDATE 1;
Constant GW_REASON_REDRAW 2;

Global GW_Abilities=0;
Global GW_Action_Reason=0;
Global GW_Override=0;
Constant GW_ERR_ABS_GRAPH "Attempt to coerce a window of absolute size into a blank window.";
Constant GW_ERR_NO_OPEN "Attempt to open a window failed.";
Constant GW_ERR_RED_NO_WIN "Attempt to redraw a window which is not open.";

Default GW_BUFFER_SIZE 128;

Constant GW_PERSISTANT_ROCK 42;
endif;

! GAutoMenu     - GWindows Automatically-sized column menu widget
!
! usage: as GColumnMenu
!
! This is a column menu which automatically sizes its columns based on
! the menu data.
!
! Inherits from: GColumnMenu

ifndef GW_AUTOMEN_H;
system_file;
Constant GW_AUTOMEN_H;
include "gcolmen";

Class GAutoMenu
 class GColumnMenu,
 private junk,
 with   redraw [o x m;
        m=2;
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GAutoMenu]: Window ", (name) self, " finding needed size for
        contents of ", (name) self.current_menu, ".^";
GConsole.penoff();
#endif;

        objectloop(o in self.current_menu)
        {
         ! The Game Author's Guide says that the length and array can be
         ! zero here, but WinGlk at least doesn't like it.
         x=PrintAnyToArray(self.&junk,WORDSIZE,o);
         if (x>m) m=x+1;
        }
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GAutoMenu]: Window ", (name) self, " calculated column width is ", m, ".^";
GConsole.penoff();
#endif;
        
        self.columnwidth=m;
        self.GColumnMenu::redraw();
        ];
endif;

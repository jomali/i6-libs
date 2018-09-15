! Gstatus.h -- Status window module for GWindows
!
! GStatusWin is a class which emulates the standard inform statusline.
! Simply insert a GStatusWin object into your tree with the size and position
! desired, and it will fill itself with a normal inform statusline.
! The window is created with its text in reverse, by default, emulating
! Z-code inform rather than Glulx Inform.
! Also, this version uses different screen metrics to determine how to draw
! the statusline; a default statusline is drawn if the window is over 56
! characters in width, and reduced statuslines are drawn down to 35
! characters (The library draws the default status line down to 66 characters,
! and the reduced one down to 53 characters)
!
! Inherits from: TextGrid 
!
!--------------------------------------------------------------------------
!
! NOTA DE ELIUK BLAU: Correcciones... (buscar comentarios con "Eliuk")
!
! 1) Se actualiza correctamente la StatusLine cuando se redibujan
!    las ventanas Glk.
!
! 2) Se manejan correctamente las variaciones de la StatusLine de la
!    misma forma que en la Lib. 6/11.
!
!--------------------------------------------------------------------------

Ifndef GW_GSTATUS_H;
system_file;
Constant GW_GSTATUS_H;
Class GStatusWin
 class TextGrid,
 with
 redraw [; self.update(); ], ! CORREGIDO POR ELIUK BLAU
 update [ posa posb;
    if (location == 0 || player == 0 || parent(player) == 0)
      return;
    glk_set_window(self.winid);
    posa=self.width-26;
    posb=self.width-13;
    glk_window_clear(self.winid);
    glk_window_move_cursor(self.winid,1,0);
    if (location == thedark) {
        print (name) location;
    }
    else {
        FindVisibilityLevels();
        if (visibility_ceiling == location)
            print (name) location;
        else 
            print (The) visibility_ceiling;
    }
    
    !===============================================================================
    ! CORREGIDO POR ELIUK BLAU: aqui se copia (con minimas modificaciones) la forma
    ! de gestionar la linea de estado que tiene la propia libreria Inform 6/11 para
    ! que maneje correctamente: 1) cuando se muestra el tiempo; 2) cuando no hay
    ! puntuacion; 3) cuando debe reducir los textos mostrados en una linea de
    ! estado de tamaño muy pequeño [se conserva tratamiento GStatusWin del tamaño]
    !-------------------------------------------------------------------------------
    ! COMIENZO DE LA CORRECCION
    !-------------------------------------------------------------------------------
    if (sys_statusline_flag && self.width > 56) {
      glk($002B, self.winid, posa-1, 0); ! window_move_cursor
      print (string) TIME__TX;
      LanguageTimeOfDay(sline1, sline2);
    }
    else {
      if (self.width > 56) {
        #ifndef NO_SCORE;
          glk($002B, self.winid, posa-1, 0); ! window_move_cursor
          print (string) SCORE__TX, sline1;
        #endif;
          glk($002B, self.winid, posb-1, 0); ! window_move_cursor
          print (string) MOVES__TX, sline2;
      }
      #ifndef NO_SCORE;
        if (self.width > 43 && self.width <= 56) {
          glk($002B, self.winid, posb-1, 0); ! window_move_cursor
          print sline1, "/", sline2;
        }
        if (self.width > 35 && self.width <= 43) {
          glk_window_move_cursor(self.winid,self.width-10,0);
          print (char) ' ', sline1, (char) '/', sline2;
        }
      #endif;
    }
    !-------------------------------------------------------------------------------
    ! FIN DE LA CORRECCION
    !===============================================================================
 ],
 split 1,
 split_dir winmethod_Above,
 stylehints
  style_Normal stylehint_Reversecolor 1,
 has abssplit;

Endif;

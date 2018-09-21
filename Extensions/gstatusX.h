

!!==============================================================================
!!
!!	GSTATUSX WINDOW
!!	Módulo de ventana de estado para GWindows
!!
!!==============================================================================
!!
!!	Archivo:		gstatusX.h
!!	Autor(es):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!	Idioma:			ES (Español)
!!	Sistema:		Inform-INFSP 6
!!	Plataforma:		Glulx
!!	Versión:		1.3
!!	Fecha:			2018/09/21
!!
!!------------------------------------------------------------------------------
!!
!!	Copyright (c) 2014, 2018, J. Francisco Martín
!!
!!	Este programa es software libre: usted puede redistribuirlo y/o
!!	modificarlo bajo los términos de la Licencia Pública General GNU
!!	publicada por la Fundación para el Software Libre, ya sea la versión
!!	3 de la Licencia, o (a su elección) cualquier versión posterior.
!!
!!	Este programa se distribuye con la esperanza de que sea útil, pero
!!	SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita MERCANTIL o
!!	de APTITUD PARA UN PROPÓSITO DETERMINADO. Consulte los detalles de
!!	la Licencia Pública General GNU para más información.
!!
!!	Debería haber recibido una copia de la Licencia Pública General GNU
!!	junto a este programa. En caso contrario, consulte
!!	<http://www.gnu.org/licenses/>.
!!
!!------------------------------------------------------------------------------
!!
!!	HISTORIAL DE VERSIONES
!!
!!	1.3: 2018/09/21	Modificada la codificación de caracteres de ISO 8859-15 a
!!					UTF-8 (requiere la versión 6.34 o superior del compilador).
!!	1.2: 2018/03/05	Constante de la extensión renombrada a GW_GSTATUSX.
!!					Pequeñas modificaciones sobre la documentación
!!	1.1: 2014/10/20	Modificado el vector utilizado para tratar los contenidos
!!					de la barra de estado, la rutina para imprimir el nombre de
!!					la localidad en que se encuentra el personaje controlado
!!					por el usuario, y la propiedad GStatusXWin.update.
!!	1.0: 2014/06/06	Versión inicial
!!
!!------------------------------------------------------------------------------
!!
!!	'GStatusXWin' es un módulo para la librería GWindows de L. Ross Raszewski.
!!	Añade un tipo de ventana de estado en la que se imprime el nombre, centrado
!!	en la ventana, de la localidad actual del PC (player character, o personaje
!!	controlado por el usuario).
!!
!!------------------------------------------------------------------------------
System_file;

#Ifndef GW_GSTATUSX;
Constant GW_GSTATUSX;

Default GSTATUSX_JUSTIFIED 0; ! 0=left 1=center 2=right

!! Vector auxiliar para manejar los contenidos de la barra de estado:
#Ifdef VN_1630;	! compilador 6.30 o superior
Array _gstatusx_buffer buffer 160; ! 150 y algo caracteres deberían bastar
#Ifnot;			! compiladores anteriores
Array _gstatusx_buffer -> 160 + WORDSIZE;
#Endif; ! VN_1630

!! Clase con la que se define la extensión de barra de estado:
Class	GStatusXWin
 class	TextGrid
 with	redraw [; self.update(); ],
		update [ pos i;
			if (location == 0 || player == 0 || parent(player) == 0) return;
			glk_set_window(self.winid);
			switch (GSTATUSX_JUSTIFIED) {
				0:
					pos = 0;
					PrintToBuffer(_gstatusx_buffer, 160, self.locationName);
				2:
					pos = self.width - PrintToBuffer(_gstatusx_buffer,
						160, self.locationName);
				default:
					pos = (self.width - PrintToBuffer(_gstatusx_buffer,
						160, self.locationName)) / 2;
			}
			glk_window_clear(self.winid);
			glk_window_move_cursor(self.winid, pos, 0);
			for (i=0 : i<_gstatusx_buffer-->0 : i++) {
				if (i ~= 0) print (char) _gstatusx_buffer->(i+WORDSIZE);
				else print (char) UpperCase(_gstatusx_buffer->(i+WORDSIZE));
			}
		],
		locationName [;
			if (location == thedark) print (name) location;
			else {
				FindVisibilityLevels();
				if (visibility_ceiling == location) print (name) location;
				else print (The) visibility_ceiling;
			}
		],
		split 1,
		split_dir winmethod_Above,
		stylehints style_Normal stylehint_Reversecolor 1,
 has	abssplit;

#Endif; ! GW_GSTATUSX;

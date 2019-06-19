

!!==============================================================================
!!
!!	GWINDOWS GUI
!!	Aproximación de interfaz gráfica adaptativa con GWindows
!!
!!==============================================================================
!!
!!	Archivo:		gWindowsGUI.h
!!	Autor(es):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!	Idioma:			ES (Español)
!!	Sistema:		Inform-INFSP 6
!!	Plataforma:		Glulx
!!	Versión:		1.1
!!	Fecha:			2018/09/21
!!
!!------------------------------------------------------------------------------
!!
!!	Copyright (c) 2018, J. Francisco Martín
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
!!	1.1: 2018/09/21	Modificada la codificación de caracteres de ISO 8859-15 a
!!					UTF-8 (requiere la versión 6.34 o superior del compilador).
!!	1.0: 2018/05/05	Versión inicial de la extensión.
!!
!!------------------------------------------------------------------------------
!!
!!	TABLA DE CONTENIDOS
!!
!!		INSTALACIÓN
!!	1)	Configuración de la interfaz
!!	2)	Librerías y extensiones
!!	3)	Definición de la interfaz
!!
!!------------------------------------------------------------------------------
!!
!!	INSTALACIÓN
!!
!!	TODO
!!
!!------------------------------------------------------------------------------


!!==============================================================================
!!
!!	1)	Configuración de la interfaz
!!
!!------------------------------------------------------------------------------

!! Objeto de datos.
#Ifndef GUIConfig;
Constant GUICONFIG_MARGIN_COLOR $FFFFFF;
Object	GUIConfig "(GUI Configuration)"
 with	!!----------------------------------------------------------------------
		graphic_window_flag true,	! estado de las ventanas gráficas
		status_bar_height 1,		! altura de la barra de estado (en filas)
		!!----------------------------------------------------------------------
		!! Configuración por defecto A. Ancho de ventana >= threshold_A
		graphic_width_A 0 0,	! (px)
		margin_A 0 0,			! (%)
		padding_A 0 0 8 0,		! (px)
		threshold_A 0,			! (px)
		!! Configuración por defecto B. Ancho de ventana >= threshold_B
		graphic_width_B 0 0,	! (px)
		margin_B 0 6,			! (%)
		padding_B 0 0 8 0,		! (px)
		threshold_B 460,		! (px)
		!! Configuración por defecto C. Ancho de ventana >= threshold_C
		graphic_width_C 0 0,	! (px)
		margin_C 0 12,			! (%)
		padding_C 0 0 8 0,		! (px)
		threshold_C 660,		! (px)
		!! Configuración por defecto D. Ancho de ventana >= threshold_D
		graphic_width_D 0 0,	! (px)
		margin_D 0 18,			! (%)
		padding_D 0 0 8 0,		! (px)
		threshold_D 900,		! (px)
		!! Configuración por defecto E. Ancho de ventana >= threshold_E
		graphic_width_E 0 0,	! (px)
		margin_E 0 22,			! (%)
		padding_E 0 0 8 0,		! (px)
		threshold_E 1050,		! (px)
		!! Configuración por defecto F. Ancho de ventana >= threshold_F
		graphic_width_F 0 0,	! (px)
		margin_F 0 25,			! (%)
		padding_F 0 0 8 0,		! (px)
		threshold_F 1224,		! (px)
		!! Configuración por defecto G. Ancho de ventana >= threshold_G
		graphic_width_G 0 0,	! (px)
		margin_G 0 30,			! (%)
		padding_G 0 0 8 0,		! (px)
		threshold_G 1400,		! (px)
;
#Endif;


!!==============================================================================
!!
!!	2)	Librerías y extensiones
!!
!!------------------------------------------------------------------------------

Include "gimage.h";				! GWindows: Image Window Widget
Include "gstatusX.h";			! GWindows: Modified Status Window Widget
Include "gtile.h";				! GWindows: Tiled Image Window Widget


!!==============================================================================
!!
!!	3)	Definición de la interfaz
!!
!!------------------------------------------------------------------------------
!!
!!	+---------------------------------------+	> A: textWindow
!!	|					K					|	> B: statusBar
!!	+---+---+-----------------------+---+---+	> C: paddingLeft
!!	|	|	|			E			|	|	|	> D: paddingRight
!!	|	|	+---+---------------+---+	|	|	> E: paddingTop
!!	|	|	|	|		B		|	|	|	|	> F: paddingBottom
!!	|	|	|	+---------------+   |	|	|	> G: graphicWindowLeft
!!	|	|	|	|				|	|	|	|	> H: graphicWindowRight
!!	|	|	|	|				|	|	|	|	> I: marginLeft
!!	|	|	|	|				|	|	|	|	> J: marginRight
!!	|	|	|	|				|	|	|	|	> K: marginTop
!!	| I | G | C |		A		| D	| H | J |	> L: marginBottom
!!	|	|	|	|				|	|	|	|
!!	|	|	|	|				|	|	|	|
!!	|	|	|	|				|	|	|	|
!!	|	|	|	|				|	|	|	|
!!	|	|	+---+---------------+---+	|	|
!!	|	|	|			F			|	|	|
!!	+---+---+-----------------------+---+---+
!!	|					L					|
!!	+---------------------------------------+
!!
!!------------------------------------------------------------------------------

WindowPair RootUI;
WindowPair -> SecondaryAreaA;
WindowPair -> -> SecondaryAreaB;
WindowPair -> -> -> SecondaryAreaC;
WindowPair -> -> -> -> SecondaryAreaD;
WindowPair -> -> -> -> -> SecondaryAreaE;
WindowPair -> -> -> -> -> -> SecondaryAreaF;
WindowPair -> -> -> -> -> -> -> SecondaryAreaG;
WindowPair -> -> -> -> -> -> -> -> SecondaryAreaH;
WindowPair -> -> -> -> -> -> -> -> -> SecondaryAreaI;
WindowPair -> -> -> -> -> -> -> -> -> -> SecondaryAreaJ;

TextBuffer -> -> -> -> -> -> -> -> -> -> -> TextWindow;

GStatusXWin -> -> -> -> -> -> -> -> -> -> -> StatusBar
 with	split 0,
		split_dir winmethod_Above;

GraphWin -> -> -> -> -> -> -> -> -> -> PaddingRight
 with	split 0,
		split_dir winmethod_Right,
 has	abssplit;

GraphWin -> -> -> -> -> -> -> -> -> PaddingLeft
 with	split 0,
		split_dir winmethod_Left,
 has	abssplit;

GraphWin -> -> -> -> -> -> -> -> PaddingTop
 with	split 0,
		split_dir winmethod_Above,
 has	abssplit;

GraphWin -> -> -> -> -> -> -> PaddingBottom
 with	split 0,
		split_dir winmethod_Below,
 has	abssplit;

GImageWin -> -> -> -> -> -> GraphicWindowRight
 with	split 0,
		split_dir winmethod_Right,
		col GUICONFIG_MARGIN_COLOR,
		click_event [; cmd_override="mirar"; ],
 has	abssplit on;

GImageWin -> -> -> -> -> GraphicWindowLeft
 with	split 0,
		split_dir winmethod_Left,
		col GUICONFIG_MARGIN_COLOR,
		click_event [; cmd_override="mirar"; ],
 has	abssplit on;

GImageWin -> -> -> -> MarginRight
 with	split 0,
		col GUICONFIG_MARGIN_COLOR,
		split_dir winmethod_Right;

GImageWin -> -> -> MarginLeft
 with	split 0,
		col GUICONFIG_MARGIN_COLOR,
		split_dir winmethod_Left;

GImageWin -> -> MarginTop
  with	split 0,
		col GUICONFIG_MARGIN_COLOR,
		split_dir winmethod_Above;

GImageWin -> MarginBottom
  with	split 0,
		col GUICONFIG_MARGIN_COLOR,
		split_dir winmethod_Below,
		redraw [
			graphic_left graphic_right margin_top margin_right margin_bottom
			margin_left padding_top padding_right padding_bottom padding_left;
			if (self.width > GUIConfig.threshold_G) {
				graphic_right	= GUIConfig.&graphic_width_G-->0;
				graphic_left	= GUIConfig.&graphic_width_G-->1;
				margin_top		= (GUIConfig.&margin_G-->0 * self.height) / 100;
				margin_right	= (GUIConfig.&margin_G-->1 * self.width) / 100;
				if ((GUIConfig.#margin_G / WORDSIZE) == 2) {
					margin_bottom = (GUIConfig.&margin_G-->0*self.height)/100;
					margin_left = (GUIConfig.&margin_G-->1*self.width)/100;
				} else {
					margin_bottom = (GUIConfig.&margin_G-->2*self.height)/100;
					margin_left = (GUIConfig.&margin_G-->3*self.width)/100;
				}
				padding_top		= GUIConfig.&padding_G-->0;
				padding_right	= GUIConfig.&padding_G-->1;
				if ((GUIConfig.#padding_G / WORDSIZE) == 2) {
					padding_bottom	= GUIConfig.&padding_G-->0;
					padding_left	= GUIConfig.&padding_G-->1;
				} else {
					padding_bottom	= GUIConfig.&padding_G-->2;
					padding_left	= GUIConfig.&padding_G-->3;
				}
			} else if (self.width > GUIConfig.threshold_F) {
				graphic_right	= GUIConfig.&graphic_width_F-->0;
				graphic_left	= GUIConfig.&graphic_width_F-->1;
				margin_top		= (GUIConfig.&margin_F-->0 * self.height) / 100;
				margin_right	= (GUIConfig.&margin_F-->1 * self.width) / 100;
				if ((GUIConfig.#margin_F / WORDSIZE) == 2) {
					margin_bottom = (GUIConfig.&margin_F-->0*self.height)/100;
					margin_left = (GUIConfig.&margin_F-->1*self.width)/100;
				} else {
					margin_bottom = (GUIConfig.&margin_F-->2*self.height)/100;
					margin_left = (GUIConfig.&margin_F-->3*self.width)/100;
				}
				padding_top		= GUIConfig.&padding_F-->0;
				padding_right	= GUIConfig.&padding_F-->1;
				if ((GUIConfig.#padding_F / WORDSIZE) == 2) {
					padding_bottom	= GUIConfig.&padding_F-->0;
					padding_left	= GUIConfig.&padding_F-->1;
				} else {
					padding_bottom	= GUIConfig.&padding_F-->2;
					padding_left	= GUIConfig.&padding_F-->3;
				}
			} else if (self.width > GUIConfig.threshold_E) {
				graphic_right	= GUIConfig.&graphic_width_E-->0;
				graphic_left	= GUIConfig.&graphic_width_E-->1;
				margin_top		= (GUIConfig.&margin_E-->0 * self.height) / 100;
				margin_right	= (GUIConfig.&margin_E-->1 * self.width) / 100;
				if ((GUIConfig.#margin_E / WORDSIZE) == 2) {
					margin_bottom = (GUIConfig.&margin_E-->0*self.height)/100;
					margin_left = (GUIConfig.&margin_E-->1*self.width)/100;
				} else {
					margin_bottom = (GUIConfig.&margin_E-->2*self.height)/100;
					margin_left = (GUIConfig.&margin_E-->3*self.width)/100;
				}
				padding_top		= GUIConfig.&padding_E-->0;
				padding_right	= GUIConfig.&padding_E-->1;
				if ((GUIConfig.#padding_E / WORDSIZE) == 2) {
					padding_bottom	= GUIConfig.&padding_E-->0;
					padding_left	= GUIConfig.&padding_E-->1;
				} else {
					padding_bottom	= GUIConfig.&padding_E-->2;
					padding_left	= GUIConfig.&padding_E-->3;
				}
			} else if (self.width > GUIConfig.threshold_D) {
				graphic_right	= GUIConfig.&graphic_width_D-->0;
				graphic_left	= GUIConfig.&graphic_width_D-->1;
				margin_top		= (GUIConfig.&margin_D-->0 * self.height) / 100;
				margin_right	= (GUIConfig.&margin_D-->1 * self.width) / 100;
				if ((GUIConfig.#margin_D / WORDSIZE) == 2) {
					margin_bottom = (GUIConfig.&margin_D-->0*self.height)/100;
					margin_left = (GUIConfig.&margin_D-->1*self.width)/100;
				} else {
					margin_bottom = (GUIConfig.&margin_D-->2*self.height)/100;
					margin_left = (GUIConfig.&margin_D-->3*self.width)/100;
				}
				padding_top		= GUIConfig.&padding_D-->0;
				padding_right	= GUIConfig.&padding_D-->1;
				if ((GUIConfig.#padding_D / WORDSIZE) == 2) {
					padding_bottom	= GUIConfig.&padding_D-->0;
					padding_left	= GUIConfig.&padding_D-->1;
				} else {
					padding_bottom	= GUIConfig.&padding_D-->2;
					padding_left	= GUIConfig.&padding_D-->3;
				}
			} else if (self.width > GUIConfig.threshold_C) {
				graphic_right	= GUIConfig.&graphic_width_C-->0;
				graphic_left	= GUIConfig.&graphic_width_C-->1;
				margin_top		= (GUIConfig.&margin_C-->0 * self.height) / 100;
				margin_right	= (GUIConfig.&margin_C-->1 * self.width) / 100;
				if ((GUIConfig.#margin_C / WORDSIZE) == 2) {
					margin_bottom = (GUIConfig.&margin_C-->0*self.height)/100;
					margin_left = (GUIConfig.&margin_C-->1*self.width)/100;
				} else {
					margin_bottom = (GUIConfig.&margin_C-->2*self.height)/100;
					margin_left = (GUIConfig.&margin_C-->3*self.width)/100;
				}
				padding_top		= GUIConfig.&padding_C-->0;
				padding_right	= GUIConfig.&padding_C-->1;
				if ((GUIConfig.#padding_C / WORDSIZE) == 2) {
					padding_bottom	= GUIConfig.&padding_C-->0;
					padding_left	= GUIConfig.&padding_C-->1;
				} else {
					padding_bottom	= GUIConfig.&padding_C-->2;
					padding_left	= GUIConfig.&padding_C-->3;
				}
			} else if (self.width > GUIConfig.threshold_B) {
				graphic_right	= GUIConfig.&graphic_width_B-->0;
				graphic_left	= GUIConfig.&graphic_width_B-->1;
				margin_top		= (GUIConfig.&margin_B-->0 * self.height) / 100;
				margin_right	= (GUIConfig.&margin_B-->1 * self.width) / 100;
				if ((GUIConfig.#margin_B / WORDSIZE) == 2) {
					margin_bottom = (GUIConfig.&margin_B-->0*self.height)/100;
					margin_left = (GUIConfig.&margin_B-->1*self.width)/100;
				} else {
					margin_bottom = (GUIConfig.&margin_B-->2*self.height)/100;
					margin_left = (GUIConfig.&margin_B-->3*self.width)/100;
				}
				padding_top		= GUIConfig.&padding_B-->0;
				padding_right	= GUIConfig.&padding_B-->1;
				if ((GUIConfig.#padding_B / WORDSIZE) == 2) {
					padding_bottom	= GUIConfig.&padding_B-->0;
					padding_left	= GUIConfig.&padding_B-->1;
				} else {
					padding_bottom	= GUIConfig.&padding_B-->2;
					padding_left	= GUIConfig.&padding_B-->3;
				}
			} else {
				graphic_right	= GUIConfig.&graphic_width_A-->0;
				graphic_left	= GUIConfig.&graphic_width_A-->1;
				margin_top		= (GUIConfig.&margin_A-->0 * self.height) / 100;
				margin_right	= (GUIConfig.&margin_A-->1 * self.width) / 100;
				if ((GUIConfig.#margin_A / WORDSIZE) == 2) {
					margin_bottom = (GUIConfig.&margin_A-->0*self.height)/100;
					margin_left = (GUIConfig.&margin_A-->1*self.width)/100;
				} else {
					margin_bottom = (GUIConfig.&margin_A-->2*self.height)/100;
					margin_left = (GUIConfig.&margin_A-->3*self.width)/100;
				}
				padding_top		= GUIConfig.&padding_A-->0;
				padding_right	= GUIConfig.&padding_A-->1;
				if ((GUIConfig.#padding_A / WORDSIZE) == 2) {
					padding_bottom	= GUIConfig.&padding_A-->0;
					padding_left	= GUIConfig.&padding_A-->1;
				} else {
					padding_bottom	= GUIConfig.&padding_A-->2;
					padding_left	= GUIConfig.&padding_A-->3;
				}
			}
			self.rearrange_window_configuration(graphic_left, graphic_right,
				margin_top, margin_right, margin_bottom, margin_left,
 				padding_top, padding_right, padding_bottom, padding_left);
			glk_window_get_size(StatusBar.winid,
				StatusBar.&width,
				StatusBar.&height);
			GW_ForceRedraw(StatusBar);
			GW_ForceRedraw(GraphicWindowLeft);
			GW_ForceRedraw(GraphicWindowRight);
		],
 private
		rearrange_window_configuration [ graphic_left_width graphic_right_width
 			margin_top_width margin_right_width margin_bottom_width
			margin_left_width padding_top_width padding_right_width
			padding_bottom_width padding_left_width;
			!! Comprueba si las ventanas gráficas están activadas:
			if (~~GUIConfig.graphic_window_flag()) {
				graphic_left_width = 0;
				graphic_right_width = 0;
			}
			!! Redimensiona la barra de estado:
			glk_window_set_arrangement(parent(statusBar).winid,
				winmethod_Above | winmethod_Fixed,
				GUIConfig.status_bar_height(),
				statusBar.winid);
			statusBar.split = GUIConfig.status_bar_height();
			!! Redimensiona el padding izquierdo:
			glk_window_set_arrangement(parent(paddingLeft).winid,
				winmethod_Left | winmethod_Fixed,
				padding_left_width,
				paddingLeft.winid);
			paddingLeft.split = padding_left_width;
			!! Redimensiona el padding derecho:
			glk_window_set_arrangement(parent(paddingRight).winid,
				winmethod_Right | winmethod_Fixed,
				padding_right_width,
				paddingRight.winid);
			paddingRight.split = padding_right_width;
			!! Redimensiona el padding superior:
			glk_window_set_arrangement(parent(paddingTop).winid,
				winmethod_Above | winmethod_Fixed,
				padding_top_width,
				paddingTop.winid);
			paddingTop.split = padding_top_width;
			!! Redimensiona el padding inferior:
			glk_window_set_arrangement(parent(paddingBottom).winid,
				winmethod_Below | winmethod_Fixed,
				padding_bottom_width,
				paddingBottom.winid);
			paddingBottom.split = padding_bottom_width;
			!! Redimensiona la ventana gráfica izquierda:
			glk_window_set_arrangement(parent(graphicWindowLeft).winid,
				winmethod_Left | winmethod_Fixed,
				graphic_left_width,
				graphicWindowLeft.winid);
			graphicWindowLeft.split = graphic_left_width;
			!! Redimensiona la ventana gráfica derecha:
			glk_window_set_arrangement(parent(graphicWindowRight).winid,
				winmethod_Right | winmethod_Fixed,
				graphic_right_width,
				graphicWindowRight.winid);
			graphicWindowRight.split = graphic_right_width;
			!! Redimensiona el margen izquierdo
			glk_window_set_arrangement(parent(marginLeft).winid,
				winmethod_Left | winmethod_Fixed,
				margin_left_width,
				marginLeft.winid);
			marginLeft.split = margin_left_width;
			!! Redimensiona el margen derecho
			glk_window_set_arrangement(parent(marginRight).winid,
				winmethod_Right | winmethod_Fixed,
				margin_right_width,
				marginRight.winid);
			marginRight.split = margin_right_width;
			!! Redimensiona el margen superior:
			glk_window_set_arrangement(parent(marginTop).winid,
				winmethod_Above | winmethod_Fixed,
				margin_top_width,
				marginTop.winid);
			marginTop.split = margin_top_width;
			!! Redimensiona el margen inferior:
			glk_window_set_arrangement(parent(marginBottom).winid,
				winmethod_Below | winmethod_Fixed,
				margin_bottom_width,
				marginBottom.winid);
			marginBottom.split = margin_bottom_width;
		],
;

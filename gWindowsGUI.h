

!!==============================================================================
!!
!!	GWINDOWS GUI
!!	Aproximaci�n de interfaz gr�fica adaptativa con GWindows
!!
!!==============================================================================
!!
!!	Archivo:		gWindowsGUI.h
!!	Autor(es):		J. Francisco Mart�n <jfm.lisaso@gmail.com>
!!	Idioma:			ES (Espa�ol)
!!	Sistema:		Inform-INFSP 6
!!	Plataforma:		Glulx
!!	Versi�n:		0.0
!!	Fecha:			2018/03/XX
!!
!!------------------------------------------------------------------------------
!!
!!	Copyright (c) 2018, J. Francisco Mart�n
!!
!!	Este programa es software libre: usted puede redistribuirlo y/o
!!	modificarlo bajo los t�rminos de la Licencia P�blica General GNU
!!	publicada por la Fundaci�n para el Software Libre, ya sea la versi�n
!!	3 de la Licencia, o (a su elecci�n) cualquier versi�n posterior.
!!
!!	Este programa se distribuye con la esperanza de que sea �til, pero
!!	SIN GARANT�A ALGUNA; ni siquiera la garant�a impl�cita MERCANTIL o
!!	de APTITUD PARA UN PROP�SITO DETERMINADO. Consulte los detalles de
!!	la Licencia P�blica General GNU para m�s informaci�n.
!!
!!	Deber�a haber recibido una copia de la Licencia P�blica General GNU
!!	junto a este programa. En caso contrario, consulte
!!	<http://www.gnu.org/licenses/>.
!!
!!------------------------------------------------------------------------------
!!
!!	HISTORIAL DE VERSIONES
!!
!!	1.0: 2018/03/XX	Versi�n inicial de la extensi�n.
!!
!!------------------------------------------------------------------------------
!!
!!	TABLA DE CONTENIDOS
!!
!!		INSTALACI�N
!!	1)	Configuraci�n de la interfaz
!!	2)	Librer�as y extensiones
!!	3)	Definici�n de la interfaz
!!
!!------------------------------------------------------------------------------
!!
!!	INSTALACI�N
!!
!!	TODO
!!
!!------------------------------------------------------------------------------


!!==============================================================================
!!
!!	1)	Configuraci�n de la interfaz
!!
!!------------------------------------------------------------------------------

!! Objeto de datos.
Object	GUIConfig "(GUI Configuration)"
 with	!!----------------------------------------------------------------------
		!! Valores generales
		!!----------------------------------------------------------------------
		graphic_win_flag true,	! estado de la ventana gr�fica
		margin_bottom_height 0,	! altura del margen inferior (en px)
		margin_top_height 0,	! altura del margen superior (en px)
		padding_bottom_height 2, ! altura del padding inferior (en px)
		status_bar_height 1,	! altura de la barra de estado (en filas)
		!!----------------------------------------------------------------------
		!! Las ventanas internas de la interfaz pueden variar su tama�o en
		!! funci�n del ancho de la ventana principal de la aplicaci�n. Existen
		!! en total 7 configuraciones de tama�os modificables. La configuraci�n
		!! concreta que se utiliza en un momento dado se selecciona comparando
		!! el ancho actual de la ventana principal con el ancho prefijado de
		!! cada configuraci�n, de mayor a menor ---desde la configuraci�n 7
		!! hasta la 1---, de tal forma que si la ventana tiene un ancho
		!! superior al l�mite de la configuraci�n 7, la utiliza; en caso
		!! contrario, compara el ancho con el l�mite de la configuraci�n 6, y
		!! as� sucesivamente. De esta forma, aunque los valores de
		!! configuraci�n pueden ser modificados libremente, para que la
		!! interfaz se comporte correctamente conviene establecer siempre los
		!! l�mites de mayor a menor. Es decir; l�m.7 > l�m.6 > ... > l�m.1. Tal
		!! y como se hace con los valores por defecto.
		!!----------------------------------------------------------------------
		!! Configuraci�n por defecto 7. Ancho de ventana: >= 1400px
		!!----------------------------------------------------------------------
		configuration_limit_7 1400,
		graphic_window_width_7 225,
		margin_7 46 0,
		padding_7 0 20,
		!!----------------------------------------------------------------------
		!! Configuraci�n 6. Ancho de ventana: (1400, 1224]px
		!!----------------------------------------------------------------------
		configuration_limit_6 1224,
		graphic_window_width_6 225,
		margin_6 36 0,
		padding_6 0 20,
		!!----------------------------------------------------------------------
		!! Configuraci�n 5. Ancho de ventana: (1224, 1050]px
		!!----------------------------------------------------------------------
		configuration_limit_5 1050,
		graphic_window_width_5 225,
		margin_5 28 0,
		padding_5 0 20,
		!!----------------------------------------------------------------------
		!! Configuraci�n 4. Ancho de ventana: (1050, 900]px
		!!----------------------------------------------------------------------
		configuration_limit_4 900,
		graphic_window_width_4 225,
		margin_4 18 0,
		padding_4 0 20,
		!!----------------------------------------------------------------------
		!! Configuraci�n 3. Ancho de ventana: (900, 660]px
		!!----------------------------------------------------------------------
		configuration_limit_3 660,
		graphic_window_width_3 225,
		margin_3 6 0,
		padding_3 0 20,
		!!----------------------------------------------------------------------
		!! Configuraci�n 2. Ancho de ventana: (660, 460]px
		!!----------------------------------------------------------------------
		configuration_limit_2 460,
		graphic_window_width_2 0,
		margin_2 6 6,
		padding_2 0 0,
		!!----------------------------------------------------------------------
		!! Configuraci�n 1. Ancho de ventana: (460, 0]px
		!!----------------------------------------------------------------------
		configuration_limit_1 0,
		graphic_window_width_1 0,
		margin_1 0 0,
		padding_1 0 0,
;


!!==============================================================================
!!
!!	2)	Librer�as y extensiones
!!
!!------------------------------------------------------------------------------

Include "gimage.h";				! GWindows: Image Window Widget
Include "gstatusX.h";			! GWindows: Modified Status Window Widget
Include "gtile.h";				! GWindows: Tiled Image Window Widget


!!==============================================================================
!!
!!	3)	Definici�n de la interfaz
!!
!!------------------------------------------------------------------------------
!!
!!	+---------------------------------------+	> A: textWindow
!!	|					I					|	> B: paddingLeft
!!	+---+---------------------------+---+---+	> C: paddingRight
!!	|   |			  D				|	|   |	> D: statusBar
!!	|   +---------------------------+	|   |	> E: paddingBottom
!!	|   |   |					|   |   |   |	> F: graphicWindow
!!	|   |   |					|	|   |   |	> G: marginLeft
!!	|   |   |					|	|   |   |	> H: marginRight
!!	|   |   |					|	|   |   |	> I: marginTop
!!	| G | B |		  A 		| C | F | H |	> J: marginBottom
!!	|   |   |					|	|   |   |
!!	|   |   |					|	|   |   |
!!	|   |   |					|	|   |   |
!!	|   |   |					|	|   |   |
!!	|	|---+-----------------------+	|	|
!!	|   |   		  E				|	|   |
!!	+---+---------------------------+---+---+
!!	|					J					|
!!	+---------------------------------------+
!!
!!------------------------------------------------------------------------------

WindowPair rootUI;
WindowPair -> secondaryAreaA;
WindowPair -> -> secondaryAreaB;
WindowPair -> -> -> secondaryAreaC;
WindowPair -> -> -> -> secondaryAreaD;
WindowPair -> -> -> -> -> secondaryAreaE;
WindowPair -> -> -> -> -> -> secondaryAreaF;
WindowPair -> -> -> -> -> -> -> secondaryAreaG;
WindowPair -> -> -> -> -> -> -> -> secondaryAreaH;

TextBuffer -> -> -> -> -> -> -> -> -> textWindow;

GraphWin -> -> -> -> -> -> -> -> -> paddingLeft
 with	split 0,
 		split_dir winmethod_Left,
 has	abssplit;

GraphWin -> -> -> -> -> -> -> -> paddingRight
  with	split 0,
		split_dir winmethod_Right,
  has	abssplit;

GStatusXWin -> -> -> -> -> -> -> statusBar
  with	split 0,
		split_dir winmethod_Above;

GraphWin -> -> -> -> -> -> paddingBottom
  with	split 0,
		split_dir winmethod_Below;

GImageWin -> -> -> -> -> graphicWindow
  with	split 0,
		split_dir winmethod_Right,
		col $222222,
		click_event [; cmd_override="mirar"; ],
  has	abssplit on;

GraphWin -> -> -> -> marginLeft
  with	split 0,
		split_dir winmethod_Left;

GraphWin -> -> -> marginRight
  with	split 0,
		split_dir winmethod_Right;

GraphWin -> -> marginTop
  with	split 0,
		split_dir winmethod_Above;

GraphWin -> marginBottom
  with	split 0,
		split_dir winmethod_Below,
		redraw [
			graph_width mleft_width mright_width pleft_width pright_width;
			if (self.width > GUIConfig.configuration_limit_7) {
				graph_width = GUIConfig.graphic_window_width_7;
				mleft_width = GUIConfig.&margin_7-->0;
				mright_width = GUIConfig.&margin_7-->1;
				pleft_width = GUIConfig.&padding_7-->0;
				pright_width = GUIConfig.&padding_7-->1;
			} else if (self.width > GUIConfig.configuration_limit_6) {
				graph_width = GUIConfig.graphic_window_width_6;
				mleft_width = GUIConfig.&margin_6-->0;
				mright_width = GUIConfig.&margin_6-->1;
				pleft_width = GUIConfig.&padding_6-->0;
				pright_width = GUIConfig.&padding_6-->1;
			} else if (self.width > GUIConfig.configuration_limit_5) {
				graph_width = GUIConfig.graphic_window_width_5;
				mleft_width = GUIConfig.&margin_5-->0;
				mright_width = GUIConfig.&margin_5-->1;
				pleft_width = GUIConfig.&padding_5-->0;
				pright_width = GUIConfig.&padding_5-->1;
			} else if (self.width > GUIConfig.configuration_limit_4) {
				graph_width = GUIConfig.graphic_window_width_4;
				mleft_width = GUIConfig.&margin_4-->0;
				mright_width = GUIConfig.&margin_4-->1;
				pleft_width = GUIConfig.&padding_4-->0;
				pright_width = GUIConfig.&padding_4-->1;
			} else if (self.width > GUIConfig.configuration_limit_3) {
				graph_width = GUIConfig.graphic_window_width_3;
				mleft_width = GUIConfig.&margin_3-->0;
				mright_width = GUIConfig.&margin_3-->1;
				pleft_width = GUIConfig.&padding_3-->0;
				pright_width = GUIConfig.&padding_3-->1;
			} else if (self.width > GUIConfig.configuration_limit_2) {
				graph_width = GUIConfig.graphic_window_width_2;
				mleft_width = GUIConfig.&margin_2-->0;
				mright_width = GUIConfig.&margin_2-->1;
				pleft_width = GUIConfig.&padding_2-->0;
				pright_width = GUIConfig.&padding_2-->1;
			} else {
				graph_width = GUIConfig.graphic_window_width_1;
				mleft_width = GUIConfig.&margin_1-->0;
				mright_width = GUIConfig.&margin_1-->1;
				pleft_width = GUIConfig.&padding_1-->0;
				pright_width = GUIConfig.&padding_1-->1;
			}
			self.rearrange_window_configuration(mleft_width, mright_width,
				pleft_width, pright_width, graph_width);
			glk_window_get_size(statusBar.winid,
				statusBar.&width,
				statusBar.&height);
			statusBar.update();
		],
 private
		rearrange_window_configuration [ marginLeftValue marginRightValue
			paddingLeftValue paddingRightValue graphicWindowWidth;
			!! Comprueba que la ventana gr�fica est� activada:
			if (~~GUIConfig.graphic_win_flag()) {
				graphicWindowWidth = 0;
				paddingLeftValue = 0;
				paddingRightValue = 0;
			}
			!! Redimensiona el padding interior izquierdo:
			glk_window_set_arrangement(parent(paddingLeft).winid,
				winmethod_Left | winmethod_Fixed,
				paddingLeftValue,
				paddingLeft.winid);
			paddingLeft.split = paddingLeftValue;
			!! Redimensiona el padding interior derecho:
			glk_window_set_arrangement(parent(paddingRight).winid,
				winmethod_Right | winmethod_Fixed,
				paddingRightValue,
				paddingRight.winid);
			paddingRight.split = paddingRightValue;
			!! Redimensiona el padding interior inferior:
			glk_window_set_arrangement(parent(paddingBottom).winid,
				winmethod_Below | winmethod_Proportional,
				GUIConfig.padding_bottom_height(),
				paddingBottom.winid);
			paddingBottom.split = GUIConfig.padding_bottom_height();
			!! Redimensiona la barra de estado:
			glk_window_set_arrangement(parent(statusBar).winid,
				winmethod_Above | winmethod_Fixed,
				GUIConfig.status_bar_height(),
				statusBar.winid);
			statusBar.split = GUIConfig.status_bar_height();
			!! Redimensiona la ventana gr�fica:
			glk_window_set_arrangement(parent(graphicWindow).winid,
				winmethod_Right | winmethod_Fixed,
				graphicWindowWidth,
				graphicWindow.winid);
			graphicWindow.split = graphicWindowWidth;
			!! Redimensiona el margen izquierdo
			glk_window_set_arrangement(parent(marginLeft).winid,
				winmethod_Left | winmethod_Proportional,
				marginLeftValue,
				marginLeft.winid);
			marginLeft.split = marginLeftValue;
			!! Redimensiona el margen derecho
			glk_window_set_arrangement(parent(marginRight).winid,
				winmethod_Right | winmethod_Proportional,
				marginRightValue,
				marginRight.winid);
			marginRight.split = marginRightValue;
			!! Redimensiona el margen superior:
			glk_window_set_arrangement(parent(marginTop).winid,
				winmethod_Above | winmethod_Proportional,
				GUIConfig.margin_top_height(),
				marginTop.winid);
			marginTop.split = GUIConfig.margin_top_height();
			!! Redimensiona el margen inferior:
			glk_window_set_arrangement(parent(marginBottom).winid,
				winmethod_Below | winmethod_Proportional,
				GUIConfig.margin_bottom_height(),
				marginBottom.winid);
			marginBottom.split = GUIConfig.margin_bottom_height();
		],
;
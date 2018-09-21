

!!==============================================================================
!!
!!	TEXT STYLES
!!	Interfaz biplataforma para la selección de estilos de texto
!!
!!==============================================================================
!!
!!	Archivo:		textStyles.h
!!	Autor(es):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!	Idioma:			ES (Español)
!!	Sistema:		Inform-INFSP 6
!!	Plataforma:		Máquina-Z/Glulx
!!	Versión:		2.1
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
!!	2.1: 2018/09/21	Modificada la codificación de caracteres de ISO 8859-15 a
!!					UTF-8 (requiere la versión 6.34 o superior del compilador).
!!	2.0: 2018/03/07	Modificación del enfoque basado en el uso de un objeto
!!					gestor TextFormatter con estado interno, por un enfoque
!!					basado en rutinas independientes y variables globales. Por
!!					reducir la carga de la pila al encadenar llamadas a
!!					rutinas (especialmente cuando se utilizan directivas de
!!					depuración: 'acciones', 'mensajes'..., que pueden
!!					desencadenar errores de tipo "Stack overflow in callstub").
!!					La regla de impresión 'emphasis' se reemplaza por su
!!					sinónimo 'emph', para evitar incompatibilidades con la
!!					extensión 'utility.h' de L. Ross Raszewski
!!	1.1: 2018/03/05	Corrección en las instrucciones de instalación.
!!	1.0: 2018/02/28	Versión inicial.
!!
!!------------------------------------------------------------------------------
!!
!!	TABLA DE CONTENIDOS
!!
!!	1)	Definición de constantes y variables
!!	2)	Rutinas de selección del estilo de texto
!!	3)	Reglas de impresión normales
!!	4)	Reglas de impresión contextuales
!!
!!------------------------------------------------------------------------------
!!
!!	INSTALACIÓN
!!
!!	Para utilizar la extensión basta con añadir la siguiente línea en el
!!	fichero principal de la aplicación, inmediatamente después de la línea
!!	'Include "Parser";
!!
!!		Include "textStyles";
!!
!!	Opcionalmente en Glulx, además, es posible inicializar algunas sugerencias
!!	sobre el aspecto de los distintos estilos de texto de la extensión. Desde
!!	el propio sistema Inform no puede determinarse la apariencia final de los
!!	estilos de texto puesto que esta responsabilidad recae exclusivamente en el
!!	programa intérprete, pero sí es posible definir un conjunto de sugerencias
!!	que pueden ser tenidas en cuenta por él. Es necesario realizar estas
!!	sugerencias antes de la creación de la ventana principal de la obra;
!!	habitualmente se recomienda utilizar el punto de entrada Glk
!!	'InitGlkWindow(winrock)', invocado cada vez que la librería se encarga de
!!	establecer una de las ventanas estándar de la aplicación [PLO02]:
!!
!!		#Ifdef TARGET_GLULX;
!!		[ InitGlkWindow winrock;
!!		    !! Sugerencias de aspecto de 'textStyles':
!!		    InitialiseStyleHints(winrock);
!!		    !! Espacio para sugerencias de aspecto del autor y
!!		    !! para el resto de contenidos de InitGlkWindow:
!!		    [...]
!!		    !! Se continúa con el proceso normal de la librería:
!!		    return false;
!!		];
!!		#Endif; ! TARGET_GLULX;
!!
!!	[PLO02] Plotkin, Andrew (2002) 'The Game Author's Guide to Glulx Inform'.
!!	<https://www.eblong.com/zarf/glulx/inform-guide.txt>
!!
!!------------------------------------------------------------------------------
System_file;

#Ifndef TEXT_STYLES;
Constant TEXT_STYLES;


!!==============================================================================
!!
!!	1)	Definición de constantes y variables
!!
!!------------------------------------------------------------------------------

Constant TEXT_STYLE_UPRIGHT		= 0;	! Estilo: Recto (Upright)
Constant TEXT_STYLE_STRESSED	= 1;	! Estilo: Enfático (Stressed)
Constant TEXT_STYLE_IMPORTANT	= 2;	! Estilo: Importante (Important)
Constant TEXT_STYLE_MONOSPACED	= 3;	! Estilo: Monoespaciada (Monospaced)
Constant TEXT_STYLE_REVERSED	= 4;	! Estilo: Invertido (Reversed)
Constant TEXT_STYLE_HEADER		= 5;	! Estilo: Encabezado (Header)
Constant TEXT_STYLE_NOTE		= 6;	! Estilo: Nota (Note)
Constant TEXT_STYLE_QUOTE		= 7;	! Estilo: Cita (Quote)
Constant TEXT_STYLE_INPUT		= 8;	! Estilo: Entrada (Input)
Constant TEXT_STYLE_USER1		= 9;	! Estilo: Usuario 1 (User 1)
Constant TEXT_STYLE_USER2		= 10;	! Estilo: Usuario 2 (User 2)

!! Código del estilo de texto utilizado por los mensajes del sistema:
Default TEXT_STYLE_PARSER = TEXT_STYLE_UPRIGHT;

!! Prefijo de los mensajes del sistema:
Default TEXT_STYLE_PARSER_PREFIX = "";

!! Sufijo de los mensajes del sistema:
Default TEXT_STYLE_PARSER_SUFIX = "";

!! Código numérico entero que representa el último estilo de texto establecido
!! por la extensión. Es importante tener en cuenta que si la última vez que se
!! ha modificado el estilo de texto ha sido por medios distintos a los
!! ofrecidos por 'textStyles' ---utilizando directamente los códigos de
!! operación de las máquinas virtuales, por ejemplo---, este valor puede NO
!! CORRESPONDERSE en realidad con el estilo de texto utilizado actualmente en
!! la obra:
Global _current_text_style = TEXT_STYLE_UPRIGHT;


!!==============================================================================
!!
!!	2)	Rutinas de selección del estilo de texto
!!
!!------------------------------------------------------------------------------

!!------------------------------------------------------------------------------
!! (SÓLO PARA GLULX. NO TIENE NINGÚN EFECTO EN MÁQUINA-Z). Establece las
!! propuestas de aspecto por defecto para los estilos definidos por la
!! extensión. No garantiza el aspecto real con que se visualizará cada estilo
!! puesto que al final es siempre decisión del intérprete ignorar o reescribir
!! esta información. Debe invocarse antes de crear las ventanas gráficas, por
!! ejemplo en el punto de entrada 'InitGlkWindow(winrock)'.
!!
!!	@param {integer} winrock - Código con que se indica en qué fase se ha
!!		invocado al punto de entrada 'InitGlkWindow()'. Si la rutina se utiliza
!!		desde un sitio diferente a este punto de entrada es necesario hacer que
!!		el parámetro tome el valor GG_MAINWIN_ROCK para que la operaión se siga
!!		llevando a cabo efectivamente
!!	@returns {boolean} Verdadero si 'winrock == GG_MAINWIN_ROCK' y las
!!		sugerencias se establecen correctamente. Falso en caso
!!		contrario
!!------------------------------------------------------------------------------
[ InitialiseStyleHints winrock;
	#Ifdef TARGET_GLULX;
	if (winrock ~= GG_MAINWIN_ROCK) return false;
	!! Indicaciones de aspecto: estilo Header:
	glk($00B0, 3, 3, 4, 1); ! Header, weight, 1 (heavy)
	glk($00B0, 3, 3, 5, 0); ! Header, oblique, 0 (false)
	!! Indicaciones de aspecto: estilo Important:
	glk($00B0, 3, 4, 4, 1); ! Subheader, weight, 1 (heavy)
	glk($00B0, 3, 4, 5, 0); ! Subheader, oblique, 0 (false)
	!! Indicaciones de aspecto: estilo Reversed
	glk($00B0, 3, 5, 5, 0); ! Alert, oblique, 0 (false)
	glk($00B0, 3, 5, 9, 1); ! Alert, ReverseColor, 1 (reverse)
	!! Indicaciones de aspecto: estilo Note:
	glk($00B0, 3, 6, 4, 1); ! Note, weight, 1 (heavy)
	glk($00B0, 3, 6, 5, 1); ! Note, oblique, 1 (true)
	!! Indicaciones de aspecto: estilo Quote:
	glk($00B0, 3, 7, 6, 0); ! BlockQuote, Proportional, 0 (false)
	!! Indicaciones de aspecto: estilo	 User1:
	glk($00B0, 3, 9, 8, $FFFF00); ! User1, background, #FFFF00
	!! Indicaciones de aspecto: estilo User2:
	glk($00B0, 3, 10, 7, $808080); ! User2, foreground, #808080
	#Endif; ! TARGET_GLULX;
	winrock++; ! (por evitar alertas del compilador en Máquina-Z)
	return true;
];

!!------------------------------------------------------------------------------
!! Establece el estilo que se corresponde con el código numérico pasado como
!! parámetro.
!!
!!	@param {integer} st - Código numérico del estilo que se desea utilizar
!!		en la obra. Si el código no se corresponde con un valor válido, no se
!!		produce ningún efecto
!!	@returns {integer} Código del estilo de texto registrado anteriormente por
!!		la extensión
!!------------------------------------------------------------------------------
[ UseTextStyle st
	is_proportional is_bold is_underline is_reverse glulx_code result;
	result = _current_text_style;
	switch (st) {
		TEXT_STYLE_HEADER:
			_current_text_style	= st;
			is_proportional	= false;
			is_bold			= true;
			is_underline	= false;
			is_reverse		= false;
			glulx_code		= 3; ! style_Header
		TEXT_STYLE_IMPORTANT:
			_current_text_style	= st;
			is_proportional	= false;
			is_bold			= true;
			is_underline	= false;
			is_reverse		= false;
			glulx_code		= 4; ! style_Subheader
		TEXT_STYLE_INPUT:
			_current_text_style	= st;
			is_proportional	= false;
			is_bold			= true;
			is_underline	= false;
			is_reverse		= false;
			glulx_code		= 8; ! style_Input
		TEXT_STYLE_MONOSPACED:
			_current_text_style	= st;
			is_proportional	= true;
			is_bold			= false;
			is_underline	= false;
			is_reverse		= false;
			glulx_code		= 2; ! style_Preformatted
		TEXT_STYLE_NOTE:
			_current_text_style	= st;
			is_proportional	= false;
			is_bold			= true;
			is_underline	= true;
			is_reverse		= false;
			glulx_code		= 6; ! style_Note
		TEXT_STYLE_QUOTE:
			_current_text_style	= st;
			is_proportional	= true;
			is_bold			= false;
			is_underline	= false;
			is_reverse		= false;
			glulx_code		= 7; ! style_BlockQuote
		TEXT_STYLE_REVERSED:
			_current_text_style	= st;
			is_proportional	= false;
			is_bold			= false;
			is_underline	= false;
			is_reverse		= true;
			glulx_code		= 5; ! style_Alert
		TEXT_STYLE_STRESSED:
			_current_text_style	= st;
			is_proportional	= false;
			is_bold			= false;
			is_underline	= true;
			is_reverse		= false;
			glulx_code		= 1; ! style_Emphasized
		TEXT_STYLE_UPRIGHT:
			_current_text_style	= st;
			is_proportional	= false;
			is_bold			= false;
			is_underline	= false;
			is_reverse		= false;
			glulx_code		= 0; ! style_Normal
		TEXT_STYLE_USER1:
			_current_text_style	= st;
			is_proportional	= false;
			is_bold			= false;
			is_underline	= false;
			is_reverse		= false;
			glulx_code		= 9; ! style_User1
		TEXT_STYLE_USER2:
			_current_text_style	= st;
			is_proportional	= false;
			is_bold			= false;
			is_underline	= false;
			is_reverse		= false;
			glulx_code		= 10; ! style_User2
	}
	if (result ~= _current_text_style) {
		#Ifdef TARGET_ZCODE;
		!! Se reinicia el estilo para evitar combinaciones indeseadas:
		font on; style roman;
		!! Se aplican los estilos según corresponda:
		if (is_proportional) font off;
		if (is_bold) style bold;
		if (is_underline) style underline;
		if (is_reverse) style reverse;
		#Ifnot; ! TARGET_GLULX;
		glk($0086, glulx_code);
		#Endif; ! TARGET_
	}
	return result;
];


!!==============================================================================
!!
!!	3)	Reglas de impresión
!!
!!------------------------------------------------------------------------------

!!------------------------------------------------------------------------------
!! Regla de impresión que utiliza el estilo 'Header'; para introducir secciones
!! principales de la obra como su propio título o títulos de posibles
!! capítulos, por ejemplo.
!!
!!	@param {String} text - Texto a imprimir
!!	@returns {boolean} Verdadero si el texto se imprime con éxito. Falso si el
!!		parámetro 'text' no es una cadena de caracteres
!!------------------------------------------------------------------------------
[ header text
	previous_style;
	if (metaclass(text) ~= String) return false;
	previous_style = _current_text_style;
	UseTextStyle(TEXT_STYLE_HEADER);
	print (string) text;
	UseTextStyle(previous_style);
	return true;
];

!!------------------------------------------------------------------------------
!! Regla de impresión que utiliza el estilo 'Important'; para indicar una
!! importancia destacada, un asunto serio, o urgencia en un texto. Es análogo a
!! las etiquetas <strong> en HTML5. Los intérpretes suelen imprimir este estilo
!! en negrita.
!!
!!	@param {String} text - Texto a imprimir
!!	@returns {boolean} Verdadero si el texto se imprime con éxito. Falso si el
!!		parámetro 'text' no es una cadena de caracteres
!!------------------------------------------------------------------------------
[ important text
	previous_style;
	if (metaclass(text) ~= String) return false;
	previous_style = _current_text_style;
	UseTextStyle(TEXT_STYLE_IMPORTANT);
	print (string) text;
	UseTextStyle(previous_style);
	return true;
];

!!------------------------------------------------------------------------------
!! Regla de impresión que utiliza el estilo 'Input'; para la entrada de
!! usuario. No se recomienda su utilización salvo en casos excepcionales.
!!
!!	@param {String} text - Texto a imprimir
!!	@returns {boolean} Verdadero si el texto se imprime con éxito. Falso si el
!!		parámetro 'text' no es una cadena de caracteres
!!------------------------------------------------------------------------------
[ input text
	previous_style;
	if (metaclass(text) ~= String) return false;
	previous_style = _current_text_style;
	UseTextStyle(TEXT_STYLE_INPUT);
	print (string) text;
	UseTextStyle(previous_style);
	return true;
];

!!------------------------------------------------------------------------------
!! Regla de impresión que utiliza el estilo 'Monospaced'. En un intérprete bien
!! configurado este estilo usa siempre una fuente de letra de ancho fijo.
!!
!!	@param {String} text - Texto a imprimir
!!	@returns {boolean} Verdadero si el texto se imprime con éxito. Falso si el
!!		parámetro 'text' no es una cadena de caracteres
!!------------------------------------------------------------------------------
[ monospaced text
	previous_style;
	if (metaclass(text) ~= String) return false;
	previous_style = _current_text_style;
	UseTextStyle(TEXT_STYLE_MONOSPACED);
	print (string) text;
	UseTextStyle(previous_style);
	return true;
];

!!------------------------------------------------------------------------------
!! Regla de impresión que utiliza el estilo Note'; para notificaciones
!! especiales, como cambios en la puntuación del usuario. Está ideado como
!! alternativa de aspecto para el estilo 'Important'.
!!
!!	@param {String} text - Texto a imprimir
!!	@returns {boolean} Verdadero si el texto se imprime con éxito. Falso si el
!!		parámetro 'text' no es una cadena de caracteres
!!------------------------------------------------------------------------------
[ note text
	previous_style;
	if (metaclass(text) ~= String) return false;
	previous_style = _current_text_style;
	UseTextStyle(TEXT_STYLE_NOTE);
	print (string) text;
	UseTextStyle(previous_style);
	return true;
];

!!------------------------------------------------------------------------------
!! Regla de impresión que utiliza el estilo 'Parser'; para mensajes del
!! sistema. En realidad funciona a modo envoltorio de otro estilo diferente
!! determinado por la constante TEXT_STYLE_PARSER. La regla imprime además el
!! prefijo y el sufijo definidos en las constantes TEXT_STYLE_PARSER_PREFIX y
!! TEXT_STYLE_PARSER_SUFIX, respectivamente.
!!
!!	@param {String} text - Texto a imprimir
!!	@returns {boolean} Verdadero si el texto se imprime con éxito. Falso si el
!!		parámetro 'text' no es una cadena de caracteres
!!------------------------------------------------------------------------------
[ parser text
	previous_style;
	if (metaclass(text) ~= String) return false;
	previous_style = _current_text_style;
	UseTextStyle(TEXT_STYLE_PARSER);
	print (string) TEXT_STYLE_PARSER_PREFIX;
	print (string) text;
	print (string) TEXT_STYLE_PARSER_SUFIX;
	UseTextStyle(previous_style);
	return true;
];

!!------------------------------------------------------------------------------
!! Regla de impresión que utiliza el estilo 'Quote'; para citas u otros textos
!! especiales.
!!
!!	@param {String} text - Texto a imprimir
!!	@returns {boolean} Verdadero si el texto se imprime con éxito. Falso si el
!!		parámetro 'text' no es una cadena de caracteres
!!------------------------------------------------------------------------------
[ quote text
	previous_style;
	if (metaclass(text) ~= String) return false;
	previous_style = _current_text_style;
	UseTextStyle(TEXT_STYLE_QUOTE);
	print (string) text;
	UseTextStyle(previous_style);
	return true;
];

!!------------------------------------------------------------------------------
!! Regla de impresión que utiliza el estilo 'Reversed'; intercambia los colores
!! frontal y de fondo de la configuración por defecto. Para utilizarlo
!! adecuadamente en Glulx es necesario invocar a la función
!! 'InitialiseStyleHints()' antes de crear las ventanas de la interfaz gráfica.
!!
!!	@param {String} text - Texto a imprimir
!!	@returns {boolean} Verdadero si el texto se imprime con éxito. Falso si el
!!		parámetro 'text' no es una cadena de caracteres
!!------------------------------------------------------------------------------
[ reversed text
	previous_style;
	if (metaclass(text) ~= String) return false;
	previous_style = _current_text_style;
	UseTextStyle(TEXT_STYLE_REVERSED);
	print (string) text;
	UseTextStyle(previous_style);
	return true;
];

!!------------------------------------------------------------------------------
!! Regla de impresión que utiliza el estilo 'Stressed'; para indicar una
!! acentuación enfatizada de un texto. Es análogo a las etiquetas <em> en
!! HTML5. Los intérpretes suelen imprimir este estilo en itálica.
!!
!!	@param {String} text - Texto a imprimir
!!	@returns {boolean} Verdadero si el texto se imprime con éxito. Falso si el
!!		parámetro 'text' no es una cadena de caracteres
!!------------------------------------------------------------------------------
[ stressed text
	previous_style;
	if (metaclass(text) ~= String) return false;
	previous_style = _current_text_style;
	UseTextStyle(TEXT_STYLE_STRESSED);
	print (string) text;
	UseTextStyle(previous_style);
	return true;
];

!!------------------------------------------------------------------------------
!! Regla de impresión que utiliza el estilo 'Upright'; usado por el cuerpo de
!! texto normal. Es siempre el estilo de inicio de la aplicación.
!!
!!	@param {String} text - Texto a imprimir
!!	@returns {boolean} Verdadero si el texto se imprime con éxito. Falso si el
!!		parámetro 'text' no es una cadena de caracteres
!!------------------------------------------------------------------------------
[ upright text
	previous_style;
	if (metaclass(text) ~= String) return false;
	previous_style = _current_text_style;
	UseTextStyle(TEXT_STYLE_UPRIGHT);
	print (string) text;
	UseTextStyle(previous_style);
	return true;
];

!!------------------------------------------------------------------------------
!! Regla de impresión que utiliza el estilo 'User1'; ideado junto con 'User2'
!! para ser redefinido libremente por el autor.
!!
!!	@param {String} text - Texto a imprimir
!!	@returns {boolean} Verdadero si el texto se imprime con éxito. Falso si el
!!		parámetro 'text' no es una cadena de caracteres
!!------------------------------------------------------------------------------
[ user1 text
	previous_style;
	if (metaclass(text) ~= String) return false;
	previous_style = _current_text_style;
	UseTextStyle(TEXT_STYLE_USER1);
	print (string) text;
	UseTextStyle(previous_style);
	return true;
];

!!------------------------------------------------------------------------------
!! Regla de impresión que utiliza el estilo 'User2'; ideado junto con 'User1'
!! para ser redefinido libremente por el autor.
!!
!!	@param {String} text - Texto a imprimir
!!	@returns {boolean} Verdadero si el texto se imprime con éxito. Falso si el
!!		parámetro 'text' no es una cadena de caracteres
!!------------------------------------------------------------------------------
[ user2 text
	previous_style;
	if (metaclass(text) ~= String) return false;
	previous_style = _current_text_style;
	UseTextStyle(TEXT_STYLE_USER2);
	print (string) text;
	UseTextStyle(previous_style);
	return true;
];

!! Reglas de impresión contextuales:

!!------------------------------------------------------------------------------
!! Regla de impresión contextual. Imprime el texto con un estilo enfatizado
!! con respecto al estilo utilizado actualmente.
!!
!!	@param {String} text - Texto a imprimir
!!	@returns {boolean} Verdadero si el texto se imprime con estilo enfatizado.
!!		Falso si el parámetro 'text' no es una cadena de caracteres y no puede
!!		imprimirse, o si el texto se imprime sin modificar el estilo
!!------------------------------------------------------------------------------
[ emph text;
	switch (_current_text_style) {
		TEXT_STYLE_HEADER:
			return note(text);
		TEXT_STYLE_IMPORTANT:
			return note(text);
		TEXT_STYLE_NOTE:
			return important(text);
		TEXT_STYLE_QUOTE:
			return stressed(text);
		TEXT_STYLE_STRESSED:
			return upright(text);
		TEXT_STYLE_UPRIGHT:
			return stressed(text);
		default:
			if (metaclass(text) == String) print (string) text;
			return false;
	}
];

!!------------------------------------------------------------------------------
!! Regla de impresión contextual. Imprime el texto con un estilo destacado
!! con respecto al estilo utilizado actualmente.
!!------------------------------------------------------------------------------
[ strong text;
	switch (_current_text_style) {
		TEXT_STYLE_HEADER:
			return upright(text);
		TEXT_STYLE_IMPORTANT:
			return upright(text);
		TEXT_STYLE_NOTE:
			return stressed(text);
		TEXT_STYLE_QUOTE:
			return important(text);
		TEXT_STYLE_STRESSED:
			return note(text);
		TEXT_STYLE_UPRIGHT:
			return important(text);
		default:
			if (metaclass(text) == String) print (string) text;
			return false;
	}
];

!! Alias:

!!------------------------------------------------------------------------------
!! Sinónimo para la regla de impresión 'emph'.
!!
!!	@param {String} text - Texto a imprimir
!!	@returns {boolean} Verdadero si el texto se imprime con estilo enfatizado.
!!		Falso si el parámetro 'text' no es una cadena de caracteres y no puede
!!		imprimirse, o si el texto se imprime sin modificar el estilo
!!------------------------------------------------------------------------------
[ em text; return emph(text); ];

#Endif; ! TEXT_STYLES;



!!==============================================================================
!!
!!	TYPES
!!	Rutinas biplataforma (Z/GLULX) para imprimir texto con diferentes estilos
!!
!!==============================================================================
!!
!!	File:			types.h
!!	Author(s):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!	Language:		ES (Castellano)
!!	System:			Inform-INFSP 6
!!	Platform:		Máquina-Z / GLULX
!!	Version:		5.2
!!	Released:		2017/08/04
!!
!!------------------------------------------------------------------------------
!!
!!	# HISTORIAL DE VERSIONES
!!
!!	5.2: 2017/08/04	Revisión y formateo de comentarios de la extensión.
!!	5.1: 2016/09/30	Actualización de valores de los códigos de estilo. Las
!!					rutinas que cambian el estilo de texto ahora retornan el
!!					valor de estilo utilizado hasta ese momento. Añadidas las
!!					funciones User1Style() y User2Style(). SetStyle()
!!					renombrada a SetTextStyle().
!!	5.0: 2016/06/25	Añadidas las siguientes funciones: SetStyle(),
!!					PrintParserPrefix(), PrintParserSufix() y HorizontalRule().
!!					Añadidas constantes adicionales para referenciar los
!!					estilos personalizados de usuario en glk: _1ST_ y _2ST_.
!!					Eliminadas las funciones StartParserStyle() y
!!					EndParserStyle(). Extendida documentación de la extensión.
!!	4.5: 2014/09/21	Modificada definición del estilo del 'parser' para
!!					diferenciar claramente que se trata de una variable que
!!					puede ser modificada en tiempo de ejecución, y no de una
!!					constante.
!!	4.4: 2014/07/28	Adoptado el estilo CamelCase para los nombres de las
!!					rutinas.
!!	4.3: 2014/06/12	Añadida constante TYPES para permitir comprobar si la
!!					extensión ha sido incluida.
!!	(No se guarda registro de versiones anteriores)
!!
!!------------------------------------------------------------------------------
!!
!!	Copyright (c) 2013, 2016, J. Francisco Martín
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
!!	# INTRODUCCIÓN
!!
!!	La extensión ofrece una interfaz a través de la que seleccionar los cuatro
!!	estilos de texto básicos: romana (roman), itálica (italic), negrita (bold)
!!	y monoespaciada (monospaced); con independencia de la plataforma sobre la
!!	que estemos trabajando (Máquina-Z/GLULX).
!!
!!	Define además cuatro estilos abstractos de texto: enfático
!!	(emphatic/emph/em), fuerte (strong), código (code) y parser; que se
!!	imprimirán con un aspecto u otro en función del estilo base actual o, en el
!!	caso del estilo 'parser', en función de la configuración de la extensión.
!!
!!
!!	# FUNCIONES DE SELECCIÓN DE ESTILO DE TEXTO BÁSICOS
!!
!!	-	RomanStyle()
!!	-	ItalicStyle()
!!	-	BoldStyle()
!!	-	MonospacedStyle()
!!	-	User1Style()
!!	-	User2Style()
!!	-	SetTextStyle()
!!
!!
!!	# FUNCIONES DE SELECCIÓN DE ESTILO DE TEXTO ABSTRACTOS
!!
!!	-	emphatic() / emph() / em()
!!	-	strong()
!!	-	code()
!!	-	parser()
!!
!!
!!	# OTRAS FUNCIONES
!!
!!	-	PrintParserPrefix()
!!	-	PrintParserSufix()
!!	-	HorizontalRule()
!!
!!------------------------------------------------------------------------------
System_file;

#Ifndef _TYPES_;
Constant _TYPES_;

Constant _RST_	= 1;			! Estilo romana (roman)
Constant _IST_	= 2;			! Estilo itálica (italic)
Constant _BST_	= 3;			! Estilo negrita (bold)
Constant _MST_	= 4;			! Estilo monoespaciada (monospaced)
Constant _1ST_	= 5;			! Estilo de usuario 1
Constant _2ST_	= 6;			! Estilo de usuario 2

Default	PARSER_PREFIX	"";
Default PARSER_SUFIX	"";
Default _parser_style	_RST_;
Global _current_style = _RST_;

!!==============================================================================
!!	Funciones de selección de estilo de texto básicos
!!------------------------------------------------------------------------------

[ RomanStyle
	st;
	st = _current_style;
	#Ifdef	TARGET_ZCODE;
	font on; style roman;
	#Ifnot;	! TARGET_GLULX;
	glk($0086, 0);
	#Endif;	! TARGET_
	_current_style = _RST_;
	return st;
];

[ ItalicStyle
	st;
	st = _current_style;
	#Ifdef	TARGET_ZCODE;
	font on; style underline;
	#Ifnot;	! TARGET_GLULX;
	glk($0086, 1);
	#Endif;	! TARGET_
	_current_style = _IST_;
	return st;
];

[ BoldStyle
	st;
	st = _current_style;
	#Ifdef	TARGET_ZCODE;
	font on; style bold;
	#Ifnot;	! TARGET_GLULX;
	glk($0086, 3);
	#Endif;	! TARGET_
	_current_style = _BST_;
	return st;
];

[ MonospacedStyle
	st;
	st = _current_style;
	#Ifdef	TARGET_ZCODE;
	font off;
	#Ifnot;	! TARGET_GLULX;
	glk($0086, 2);
	#Endif;	! TARGET_
	_current_style = _MST_;
	return st;
];

[ User1Style
	st;
	st = _current_style;
	#Ifdef	TARGET_GLULX;
	glk_set_style(style_User1);
	_current_style = _1ST_;
	#Endif; ! TARGET_GLULX;
	return st;
];

[ User2Style
	st;
	st = _current_style;
	#Ifdef	TARGET_GLULX;
	glk_set_style(style_User2);
	_current_style = _2ST_;
	#Endif; ! TARGET_GLULX;
	return st;
];

[ SetTextStyle style
	st;
	st = _current_style;
	switch (style) {
		_RST_:	RomanStyle();
		_IST_:	ItalicStyle();
		_BST_:	BoldStyle();
		_MST_:	MonospacedStyle();
		_1ST_:	User1Style();
		_2ST_:	User2Style();
	}
	return st;
];


!!==============================================================================
!!	Funciones de selección de estilo de texto abstractos
!!------------------------------------------------------------------------------

[ emphatic text
	st;
	if (text == 0) return false;
	st = _current_style;
	switch (_current_style) {
		_RST_:	ItalicStyle();
		_IST_:	RomanStyle();
		_BST_:	RomanStyle();
		_MST_:	ItalicStyle();
	}
	print (string) text;
	SetTextStyle(st);
	return true;
];

[ strong text
	st;
	if (text == 0) return false;
	st = _current_style;
	switch (_current_style) {
		_RST_:	BoldStyle();
		_IST_:	BoldStyle();
		_BST_:	ItalicStyle();
		_MST_:	BoldStyle();
	}
	print (string) text;
	SetTextStyle(st);
	return true;
];

[ code text
	st;
	if (text == 0) return false;
	st = _current_style;
	switch (_current_style) {
		_RST_:	MonospacedStyle();
		_IST_:	MonospacedStyle();
		_BST_:	MonospacedStyle();
		_MST_:	ItalicStyle();
	}
	print (string) text;
	SetTextStyle(st);
	return true;
];

[ parser text
	st;
	if (text == 0) return false;
	st = PrintParserPrefix();
	print (string) text;
	PrintParserSufix(st);
	return true;
];

!! Alias:

[ emph text; return emphatic (text); ];
[ em text; return emphatic (text); ];

!!==============================================================================
!!	Otras funciones
!!------------------------------------------------------------------------------

!!------------------------------------------------------------------------------
!! Imprime una regla horizontal centrada en pantalla.
!!
!!	@returns {boolean} Verdadero
!!------------------------------------------------------------------------------
[ HorizontalRule
	st;
	st = MonospacedStyle();
	spaces (ScreenWidth()-1-7) / 2; ! 7 -> longitud de "*  *  *"
	print "*  *  *";
	SetTextStyle(st);
	new_line;
	return true;
];

!!------------------------------------------------------------------------------
!! Inicia el estilo de texto definido para los mensajes por defecto de la
!! librería e imprime el prefijo.
!!
!!	@returns {integer} [1-6] Código del estilo de texto utilizado antes de
!!		llamar a la rutina
!!------------------------------------------------------------------------------
[ PrintParserPrefix
	st;
	st = SetTextStyle(_parser_style);
	if (PARSER_PREFIX ~= 0)
		print (string) PARSER_PREFIX;
	return st;
];

!!------------------------------------------------------------------------------
!! Imprime el sufijo definido para los mensajes por defecto de la librería y
!! cambia el estilo del texto.
!!
!!	@param {integer} [st] - [1-6] Código del nuevo estilo de texto a utilizar
!!		tras imprimir el sufijo
!!------------------------------------------------------------------------------
[ PrintParserSufix st;
	if (PARSER_SUFIX ~= 0)
		print (string) PARSER_SUFIX;
	if (st >= 1 && st <= 6) SetTextStyle(st);
	else SetTextStyle(_RST_);
];

#Endif; ! _TYPES_;

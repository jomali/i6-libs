

!!==============================================================================
!!
!!	HYPERLINKS
!!	Rutinas para facilitar la interacción por hipervínculos
!!
!!==============================================================================
!!
!!	Archivo:		hyperlinks.inf
!!	Autor(es):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!	Idioma:			ES (Español)
!!	Sistema:		Inform-INFSP 6
!!	Plataforma:		Glulx
!!	Versión:		1.0
!!	Fecha:			2018/03/05
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
!!	1.0: 2018/03/05	Versión inicial de la extensión.
!!
!!------------------------------------------------------------------------------
!!
!!	INSTALACIÓN
!!
!!	Para utilizar la extensión hay que añadir la siguiente línea en el fichero
!!	principal de la obra, inmediatamente después de la línea
!!	'Include "Parser";':
!!
!!		Include "hyperlinks";
!!
!!	Son necesarias, además, otras dos consideraciones: por una parte, debe
!!	activarse la escucha de eventos glk de selección de hipervínculos en las
!!	ventanas principales de la aplicación. Para hacer esto se deben incluir las
!!	siguientes declaraciones dentro del punto de entrada 'Initialise()' ---el
!!	ejemplo utiliza directivas de compilación condicionales para permitir la
!!	compilación biplataforma---:
!!
!! 		[ Initialise;
!! 			#Ifdef TARGET_GLULX;
!! 			!! Escucha de hipervínculos en la ventana princiapl:
!! 			glk($0102, gg_mainwin); ! glk_request_hyperlink_event();
!!			!! Escucha de hipervínculos en la ventana de estado:
!!			glk($0102, gg_statuswin); ! glk_request_hyperlink_event();
!! 			#Endif; ! TARGET_GLULX;
!!
!! 			!! Resto de contenidos del punto de entrada:
!! 			[...]
!! 		];
!!
!!	Por último, hay que introducir la lógica encargada de capturar y responder
!!	a esos eventos Glk de tipo hipervínculo. Esta lógica debe encontrarse
!!	dentro del punto de entrada Glulx 'HandleGlkEvent()' ---crearlo si no
!!	existe---:
!!
!! 		#Ifdef TARGET_GLULX;
!! 		[ HandleGlkEvent ev context abortres;
!! 			if (HandleHyperlinkEvent(ev, context, abortres)) return 2;
!! 		];
!! 		#Endif; ! TARGET_GLULX;
!!
!!------------------------------------------------------------------------------
System_file;

#Ifndef HYPERLINKS;
Constant HYPERLINKS;

Default HYPERLINKS_COMMAND = "examina";
Array _hyperlinks_temp_array -> INPUT_BUFFER_LEN/WORDSIZE*2;

#Ifdef TARGET_GLULX;
!!------------------------------------------------------------------------------
!! Gestiona la respuesta a los eventos Glk de tipo hipervínculo. Ideada para
!! ser invocada desde el punto de entrada 'HandleGlkEvent()'.
!!
!!	@param {array} ev - Array de 4 palabras que describe el evento. ev-->0
!!		registra un código numérico con que se determina el tipo de evento. La
!!		rutina sólo actúa si se trata de un evento de tipo hipervínculo
!!		(ev-->0 == 8); ev-->1 indica la ventana sobre la que se ha producido el
!!		evento; ev-->2 el objeto o cadena de caracteres sobre el que se ha
!!		creado el hipervínculo; ev-->3, reservado para información adicional,
!!		no se utiliza
!!	@param {integer} context - 0 si el evento se ha producido durante una
!!		entrada de línea (comandos normales u otros usos de la función de la
!!		librería 'KeyboardPrimitive()'). 1 si el evento se ha producido durante
!!		una entrada de caracter (función de la librería 'KeyCharPrimitive()')
!!	@param {array} abortres - Utilizado para cancelar la entrada de texto y
!!		forzar una entrada particular. La longitud de la nueva entrada se
!!		registra en 'abortres-->0'. Si es diferente de 0, los caracteres del
!!		comando deben escribirse en el array secuencialmente desde la posición
!!		'abortres->WORDSIZE' hasta 'abortres->(WORDSIZE+length)' (no
!!		inclusive). No pueden superarse los 256 caracteres
!!	@returns {boolean} Verdadero para indicar que la entrada de usuario debe
!!		ser ignorada y finalizar el turno con la nueva entrada indicada en el
!!		parámetro 'abortres'.
!!------------------------------------------------------------------------------
[ HandleHyperlinkEvent ev context abortres
	length i;
	if (ev-->0 == 8) { ! evtype_Hyperlink
		!! Tras capturar con éxito el evento de selección de un hipervínculo la
		!! aplicación deja de esperar nuevos eventos de este tipo, de modo que
		!! es necesario activar de nuevo su escucha. Para poder capturar uno de
 		!! estos eventos por primera vez es necesario activar su escucha
		!! también al inicio de la obra (en el punto de entrada 'Initialise()',
		!! por ejemplo):
		glk($0102, gg_mainwin);		! glk_request_hyperlink_event
		glk($0102, gg_statuswin);	! glk_request_hyperlink_event
		!! Se cancelan los inputs de teclado:
		glk($00D3, gg_mainwin);		! glk_cancel_char_event
		glk($00D1, gg_mainwin, 0);	! glk_cancel_line_event
		!! 1) Si el hipervínculo se ha creado sobre un objeto, la entrada de
		!! usuario se genera como la combinación de la orden registrada en el
		!! string HYPERLINKS_COMMAND, el símbolo espacio ' ', y el nombre del
		!! objeto:
		if (metaclass(ev-->2) == Object) {
			if (metaclass(HYPERLINK_COMMAND) == String) {
				PrintToBuffer(abortres, INPUT_BUFFER_LEN, HYPERLINKS_COMMAND);
				#Ifdef DEBUG_HYPERLINKS;
				print "** Acción del hipervínculo: ";
				for (i = WORDSIZE : i < (abortres-->0) + WORDSIZE : i++) {
					print (char) abortres->i;
				}
				print " **^";
				#Endif; ! DEBUG_HYPERLINKS;
				length = abortres->(WORDSIZE-1);
				if (length >= 1) {
					abortres->(WORDSIZE+length) = ' ';
					(abortres->(WORDSIZE-1))++;
					length = abortres->(WORDSIZE-1);
				}
			}
			PrintToBuffer(_hyperlinks_temp_array,
				INPUT_BUFFER_LEN/WORDSIZE * 2, ev-->2);
			for (i=WORDSIZE : i<(_hyperlinks_temp_array-->0)+WORDSIZE : i++) {
				abortres->(length+i) = _hyperlinks_temp_array->i;
				(abortres->(WORDSIZE-1))++;
			}
			#Ifdef DEBUG_HYPERLINKS;
			print "** Comando completo del hipervínculo: ";
			for (i = WORDSIZE : i < (abortres-->0) + WORDSIZE : i++) {
				print (char) abortres-->i;
			}
			print " **^";
			#Endif; ! DEBUG_HYPERLINKS;
			return true;
		}
		!! 2) Si el hipervínculo se ha creado sobre un string, la entrada de
		!! usuario es él mismo:
		if (metaclass(ev-->2) == String) {
			PrintToBuffer(abortres, INPUT_BUFFER_LEN, ev-->2);
			#Ifdef DEBUG_HYPERLINKS;
			print "** Comando completo del hipervínculo: ";
			for (i = WORDSIZE : i < (abortres-->0) + WORDSIZE : i++) {
				print (char) abortres-->i;
			}
			print " **^";
			#Endif; ! DEBUG_HYPERLINKS;
			return true;
		}
	}
	context++; ! (por evitar alertas del compilador)
	return false;
];
#Endif; ! TARGET_GLULX;

!!------------------------------------------------------------------------------
!! Genera un hipervínculo de tipo texto a partir del objeto o la cadena de
!! caracteres pasado como parámetro, de forma que el texto impreso del
!! hipervínculo es el nombre del objeto o la propia cadena de caracteres.
!! Admite dos parámetros opcionales; en primer lugar una cadena de caracteres
!! con un texto alternativo que se imprime en lugar del nombre del objeto o de
!! la cadena, y un valor numérico que se identifica con el estilo de texto
!! utilizado para imprimir el hipervínculo.
!!
!!	@param {Object|String} item - Objeto o cadena de caracteres sobre la que se
!!		genera el hipervínculo. Si es un objeto, la entrada que se genera al
!!		seleccionarlo es un comando con el verbo definido en HYPERLINKS_COMMAND
!!		y el objeto. Si es una cadena de caracteres, la entrada que se genera
!!		es ella misma
!!	@param {String} [alternative] - Texto alternativo con que se imprime el
!!		hipervínculo. Si no se indica ninguno, como texto del hipervínculo se
!!		utiliza el nombre del objeto o la cadena de caracteres del parámetro
!!		'item'
!!	@param {integer} [highlight = 0] - Código numérico indicando el estilo de
!!		texto con que se imprime el hipervínculo
!!	@returns {boolean} Verdadero
!!------------------------------------------------------------------------------
[ Hyperlink item alternative highlight
	auxiliary;
	if (metaclass(item) ~= String or Object) return false;
	!! Establece el inicio del hipervínculo:
	#Ifdef TARGET_GLULX;
	glk($0100, item); ! glk_set_hyperlink();
	#Endif; ! TARGET_GLULX;
	!! Selecciona el estilo de texto del hipervínculo:
	auxiliary = HyperlinkSetStyle(highlight, item);
	!! Imprime el texto del hipervínculo:
	if (metaclass(alternative) == String) item = alternative;
	switch (metaclass(item)) {
		String:
			print (string) item;
		Object:
			if (indef_mode && item.&short_name_indef ~= 0
				&& PrintOrRun(item, short_name_indef, 1) ~= 0)
				jump hyperlinkTextPrinted;
			if (item.&short_name ~= 0 && PrintOrRun(item, short_name, 1) ~= 0)
				jump hyperlinkTextPrinted;
			print (object) item;
	}
	.hyperlinkTextPrinted;
	!! Reestablece el estilo de texto de la obra:
	HyperlinkSetStyle(auxiliary, item);
	!! Establece el final del hipervínculo:
	#Ifdef TARGET_GLULX;
	glk($0100, 0); ! glk_set_hyperlink
	#Endif; ! TARGET_GLULX;
];

!!------------------------------------------------------------------------------
!! Selecciona el estilo de texto utilizado por la rutina para crear
!! hipervínculos. Puede ser sobreescrita por el autor desde el fichero original
!! (por medio de una sentencia 'Replace HyperlinkSetStyle'), para definir un
!! comportamiento más complejo ---utilizar el tipo de objeto pasado como
!! parámetro para determinar el estilo de texto aplicado en el hipervínculo,
!! por ejemplo---.
!!
!!	@param {integer} highlight - Código numérico para identificar el estilo de
!!		texto a utilizar, utilizando como referencia los estilos de texto de
!!		Máquina-Z: 0) normal, 1) subrayado, 2) negrita y 3) ancho-fijo
!!	@param {Object|String} item - Objeto o cadena de caracteres sobre el que se
!!		genera el hipervínculo. Originalmente no se utiliza, pero puede ser
!!		interesante si el autor decide sobreescribir la rutina y tener en
!!		cuenta este 'item' para seleccionar el estilo de texto utilizado
!!	@returns {integer} Código numérico que identifica los estilos de texto. La
!!		rutina se invoca 2 veces, antes y después de imprimir el texto del
!!		hipervínculo, de tal forma que el resultado de la primera llamada se
!!		pasa como parámetro en la segunda. Así es posible inicar, desde la
!!		llamada 1, el estilo final del texto una vez impreso el hipervínculo
!!------------------------------------------------------------------------------
[ HyperlinkSetStyle highlight item;
	item++; ! (por evitar alertas del compilador)
	switch (highlight) {
		1:	! Subrayado
			#Ifdef TARGET_ZCODE;
			font on; style roman;
			style underline;
			#Ifnot; ! TARGET_GLULX;
			glk($0086, 1); ! style_Emphasized
			#Endif; ! TARGET_
		2:	! Negrita
			#Ifdef TARGET_ZCODE;
			font on; style roman;
			style bold;
			#Ifnot; ! TARGET_GLULX;
			glk($0086, 4); ! style_Subheader
			#Endif; ! TARGET_
		3:	! Ancho-fijo
			#Ifdef TARGET_ZCODE;
			font on; style roman;
			font off;
			#Ifnot; ! TARGET_GLULX;
			glk($0086, 2); ! style_Preformatted
			#Endif; ! TARGET_
		default: ! Normal
			#Ifdef TARGET_ZCODE;
			font on; style roman;
			#Ifnot; ! TARGET_GLULX;
			glk($0086, 0); ! style_Normal
			#Endif; ! TARGET_
	}
	!! Garantiza que tras el hipervínculo se utilice el estilo Normal:
	return 0;
];

#Endif; ! HYPERLINKS;

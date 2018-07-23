

!!==============================================================================
!!
!!	HYPERLINKS
!!	Rutinas para facilitar la interacción por hipervínculos
!!
!!==============================================================================
!!
!!	Archivo:		hyperlinks.h
!!	Autor(es):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!	Idioma:			ES (Español)
!!	Sistema:		Inform-INFSP 6
!!	Plataforma:		Máquina-Z/Glulx
!!	Versión:		1.3
!!	Fecha:			2018/07/23
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
!!	1.3: 2018/07/23 Añadido nuevo modo de funcionamiento de los hipervínculos
!!					generados con una cadena de texto alternativa. Consultar el
!!					apartado COMPORTAMIENTO AL UTILIZAR CADENAS DE TEXTO
!!					ALTERNATIVAS de la documentación para más información.
!!	1.2: 2018/06/12	Añadida opción de desactivar los hipervínculos,
!!					configurable por el usuario a través de la redefinición de
!!					la nueva rutina 'HyperlinkStatus()'.
!!	1.1: 2018/06/06	Nueva función 'ListenHyperlinkEvents()' para activar la
!!					escucha de eventos de tipo pulsación de hipervínculo.
!!					Añadidas comprobaciones de las capacidades del intérprete
!!					antes de definir un hipervínculo en 'Hyperlink()'. Añadido
!!					'eco' a la entrada de usuario al utilizar hipervínculos.
!!	1.0: 2018/03/05	Versión inicial de la extensión.
!!
!!------------------------------------------------------------------------------
!!
!!	INSTALACIÓN
!!
!!	Es importante tener en cuenta que la utilización de hipervínculos sólo está
!!	soportada por la máquina virtual Glulx, y que no todos los intérpretes de
!!	Glulx implementan esta funcionalidad. Aún así, la extensión puede
!!	utilizarse tanto en Glulx como en Máquina-Z (en esta segunda ---o en
!!	aquellos intérpretes Glulx que no soporten hipervínculos--- simplemente
!!	no es posible utilizar la funcionalidad). Para hacerlo hay que añadir la
!!	siguiente línea en el fichero principal de la obra, inmediatamente después
!!	de la línea 'Include "Parser";':
!!
!!		Include "hyperlinks";
!!
!!	Son necesarias, además, otras dos consideraciones: Por una parte, 1) debe
!!	activarse la escucha de eventos glk de selección de hipervínculos en las
!!	ventanas principales de la aplicación. Para ello, basta con invocar a la
!!	función 'ListenHyperlinkEvents()' en el punto de entrada 'Initialise()':
!!
!! 		[ Initialise;
!!			ListenHyperlinkEvents();
!!
!! 			!! Resto de contenidos del punto de entrada:
!! 			[...]
!! 		];
!!
!!	Por último, 2) hay que introducir la lógica encargada de capturar y
!!	responder a esos eventos Glk de tipo hipervínculo. Esta lógica debe
!!	encontrarse dentro del punto de entrada Glulx 'HandleGlkEvent()' ---crearlo
!!	si no existe---:
!!
!! 		#Ifdef TARGET_GLULX;
!! 		[ HandleGlkEvent ev context abortres;
!! 			if (HandleHyperlinkEvent(ev, context, abortres)) return 2;
!! 		];
!! 		#Endif; ! TARGET_GLULX;
!!
!!	NOTA: Destacar la utilización de directivas de compilación condicionales
!!	en el último ejemplo para permitir la compilación biplataforma.
!!
!!
!!	COMPORTAMIENTO AL UTILIZAR CADENAS DE TEXTO ALTERNATIVAS
!!
!!	Al generar un hipervínculo con la rutina 'Hyperlink()' se puede incluir una
!!	cadena de texto alternativa además del elemento (objeto o cadena de texto)
!!	sobre el que se genera el hipervínculo. Esta cadena de texto alternativa se
!!	imprimirá en el lugar del elemento a la hora de crear el hipervínculo. Hay,
!!	además, dos modos de funcionamiento posibles al seleccionar un hipervínculo
!!	creado utilizando una cadena de texto alternativa:
!!
!!	1)	Por defecto, al seleccionar el hipervínculo se lanza el comando
!!		guardado en la variable '_hyperlinks_command', sobre la cadena de texto
!!		alternativa. Se entiende que esta cadena de texto debe ser un sinónimo
!!		del nombre del elemento. Así, si se crea un hipervínculo sobre un
!!		hipotético objeto de nombre 'piedra' de la siguiente manera:
!!
!!			Hyperlink(piedra, "roca");
!!
!!		En pantalla se imprimirá la cadena alternativa "roca", y al seleccionar
!!		dicho hipervínculo se lanzará el comando "<_hyperlinks_command> ROCA".
!!		Debe asegurarse que el objeto 'piedra' esté definido con el sinónimo
!!		'roca'. De lo contrario el comando no reconocerá ningún objeto.
!!
!!	2)	Para evitar este último comportamiento, es posible utilizar un segundo
!!		modo de funcionamiento definiendo la constante 'HYPERLINKS_ALT_MODE'
!!		como verdadera. Así, el hipervínculo del ejemplo anterior se imprimirá
!!		en pantalla igualmente con la cadena alternativa "roca" pero, al
!!		seleccionarlo, se lanzaría en cambio el comando:
!!		"<_hyperlinks_command> PIEDRA". Este modo de funcionamiento garantiza
!!		que no se generen comandos que no sean reconocidos por la falta de
!!		definición de algún sinónimo (también rompe ligeramente cierta
!!		coherencia de la interfaz).
!!
!!------------------------------------------------------------------------------
!!
!!	TABLA DE CONTENIDOS
!!
!!	<>	HandleHyperlinkEvent()
!!	<>	Hyperlink()
!!	<>	HyperlinkSetStyle()
!!	<>	HyperlinkStatus()
!!	<>	ListenHyperlinkEvents()
!!
!!------------------------------------------------------------------------------
System_file;

#Ifndef HYPERLINKS;
Constant HYPERLINKS;

!! Comportamiento de los hipervínculos generados con un texto alternativo:
Default HYPERLINKS_ALT_MODE = false;

!! Comando por defecto al seleccionar un hipervínculo:
Default _hyperlinks_command = "examina";

!! Array de apoyo para la gestión de los eventos de selección de hipervínculos:
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
!!		librería 'KeyboardPrimitive()'); la aplicación debe esperar a que el
!!		usuario pulse INTRO antes de dar respuesta para la entrada. 1 si el
!!		evento se ha producido durante una entrada de caracter (función de la
!!		librería 'KeyCharPrimitive()'); la aplicación responde ante cada
!!		pulsación de tecla, como en los menús, por ejemplo
!!	@param {array} abortres - Utilizado para cancelar la entrada de texto y
!!		forzar una entrada particular. La longitud de la nueva entrada se
!!		registra en 'abortres-->0'. Si es diferente de 0, los caracteres del
!!		comando deben escribirse en el array secuencialmente desde la posición
!!		'abortres->WORDSIZE' hasta 'abortres->(WORDSIZE+length)' (no
!!		inclusive). No pueden superarse los 256 caracteres
!!	@returns {boolean} Verdadero para indicar que la entrada de usuario debe
!!		ser ignorada y finalizar el turno con la nueva entrada indicada en el
!!		parámetro 'abortres'
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
		ListenHyperlinkEvents();
		!! Se cancelan los inputs de teclado:
		glk($00D3, gg_mainwin);		! glk_cancel_char_event
		glk($00D1, gg_mainwin, 0);	! glk_cancel_line_event
		!! 1) Si el hipervínculo se ha creado sobre un objeto, la entrada de
		!! usuario se genera como la combinación de la orden registrada en el
		!! string _hyperlinks_command, el símbolo espacio ' ', y el nombre del
		!! objeto:
		if (metaclass(ev-->2) == Object) {
			if (metaclass(_hyperlinks_command) == String) {
				PrintToBuffer(abortres, INPUT_BUFFER_LEN, _hyperlinks_command);
				#Ifdef DEBUG_HYPERLINKS;
				print "** Acción del hipervínculo: ";
				print "(tam = ", (abortres-->0), ") ";
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
			print "(tam = ", (abortres-->0), ") ";
			for (i = WORDSIZE : i < (abortres-->0) + WORDSIZE : i++) {
				print (char) abortres->i;
			}
			print " **^";
			#Endif; ! DEBUG_HYPERLINKS;
			!! Imprime el eco de la entrada de texto:
			glk($0086, 8); ! style_Input
			glk($0084, buffer+WORDSIZE, buffer-->0);
			glk($0086, 0); ! style_Normal
			new_line;
			return true;
		}
		!! 2) Si el hipervínculo se ha creado sobre un string, la entrada de
		!! usuario es él mismo:
		if (metaclass(ev-->2) == String) {
			PrintToBuffer(abortres, INPUT_BUFFER_LEN, ev-->2);
			#Ifdef DEBUG_HYPERLINKS;
			print "** Comando completo del hipervínculo: ";
			print "(tam = ", (abortres-->0), ") ";
			for (i = WORDSIZE : i < (abortres-->0) + WORDSIZE : i++) {
				print (char) abortres->i;
			}
			print " **^";
			#Endif; ! DEBUG_HYPERLINKS;
			!! Imprime el eco de la entrada de texto:
			glk($0086, 8); ! style_Input
			glk($0084, buffer+WORDSIZE, buffer-->0);
			glk($0086, 0); ! style_Normal
			new_line;
			return true;
		}
	}
	if (ev-->0 == 3) { ! evtype_LineInput
		!! Imprime el eco de la entrada de texto:
		glk($0086, 8); ! style_Input
		glk($0084, buffer+WORDSIZE, buffer-->0);
		glk($0086, 0); ! style_Normal
		new_line;
		return true;
	}
	context++; ! (por evitar alertas del compilador)
	return false;
];
#Endif; ! TARGET_GLULX;

!!------------------------------------------------------------------------------
!! Crea un hipervínculo a partir del objeto o la cadena de caracteres pasado
!! como parámetro, de forma que el texto impreso del hipervínculo es el nombre
!! corto del objeto o la propia cadena de caracteres. Admite dos parámetros
!! opcionales; 1) una cadena de caracteres con un texto alternativo que se
!! imprime en lugar del nombre corto del objeto o de la cadena, 2) un parámetro
!! extra que puede ser utilizado libremente en las rutinas: 'HyperlinkStatus()'
!! e 'HyperlinkSetStyle()'.
!!
!!	@param {Object|String} item - Objeto o cadena de caracteres sobre la que se
!!		genera el hipervínculo. Si es un objeto, la entrada que se ejecuta al
!!		seleccionar el hipervínculo es un comando con el verbo definido en
!!		'_hyperlinks_command' y el objeto. Si es una cadena de caracteres, la
!!		entrada que se ejecuta es ella misma
!!	@param {String} [alternative] - Texto alternativo con que se imprime el
!!		hipervínculo. Si no se indica ninguno, como texto del hipervínculo se
!!		utiliza el nombre del objeto o la cadena de caracteres del parámetro
!!		'item'
!!	@param extra1 - Parámetro libre para controlar la lógica de la rutina
!!		'HyperlinkSetStyle()'
!!	@param extra2 - Parámetro libre para controlar la lógica de la rutina
!!		'HyperlinkStatus()'
!!	@returns {boolean} Verdadero
!!------------------------------------------------------------------------------
[ Hyperlink item alternative extra1 extra2
	previous_style hyperlink_active;
	if (metaclass(item) ~= string or Object) return false;
	!! Establece el estilo del hipervínculo:
	previous_style = HyperlinkSetStyle(item, extra1);
	!! Determina si el hipervínculo se debe desactivar o no:
	hyperlink_active = HyperlinkStatus(item, extra2);
	#Ifdef TARGET_GLULX;
	!! Establece el inicio del hipervínculo:
	if (hyperlink_active && glk($0004, 11, 0)) {
		if (HYPERLINKS_ALT_MODE == false && metaclass(alternative) == string) {
			glk($0100, alternative); ! glk_set_hyperlink();
		} else {
			glk($0100, item); ! glk_set_hyperlink();
		}
	}
	#Endif; ! TARGET_GLULX;
	!! Imprime el texto del hipervínculo:
	if (metaclass(alternative) == string) item = alternative;
	switch (metaclass(item)) {
		string:
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
	#Ifdef TARGET_GLULX;
	!! Establece el final del hipervínculo:
	if (hyperlink_active && glk($0004, 11, 0)) {
		glk($0100, 0); ! glk_set_hyperlink();
	}
	#Endif; ! TARGET_GLULX;
	!! Reestablece el estilo de texto normal:
	HyperlinkSetStyle(0, previous_style);
	return true;
];

!!------------------------------------------------------------------------------
!! Selecciona el estilo de texto utilizado por los hipervínculos. Por defecto
!! utiliza los mismos estilos de texto presentes en Máquina-Z, pero puede ser
!! reescrita para definir un comportamiento más complejo o aumentar el número
!! de estilos disponibles utilizando una sentencia 'Replace HyperlinkSetStyle;'
!! antes de incluir la extensión.'Hyperlink()' invoca a esta rutina 2 veces:
!!
!!	1)	Antes de crear el hipervínculo, para establecer el estilo con el que
!!		se imprime. En esta etapa el valor del parámetro 'item' es distinto de
!!		0 (item ~= 0).
!!	2)	Tras la creación del hipervínculo, para reestablecer el estilo normal
!!		de la obra. En esta estapa el valor de 'item' es siempre 0 (item == 0).
!!
!!	@param {Object|String} item - En la etapa (1) contiene al objeto o la
!!		cadena de caracteres sobre la que se va a generar el hipervínculo. En
!!		la etapa (2) siempre es 0
!!	@param {integer} style - Código numérico para identificar el estilo de
!!		texto a utilizar, en base a los estilos de texto de Máquina-Z:
!!		0) normal, 1) subrayado, 2) negrita y 3) ancho-fijo
!!	@returns {integer} Código numérico que identifica el estilo de texto
!!		utilizado antes de invocar a la rutina. El resultado retornado durante
!!		la etapa (1) se pasa como parámetro en la etapa (2) para reestablecer
!!		el estilo de texto que había en la obra antes de imprimir el
!!		hipervínculo
!!------------------------------------------------------------------------------
[ HyperlinkSetStyle item style;
	item = style; ! (por evitar alertas del compilador)
	switch (style) {
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
	!! Retorna 0 para reestablecer el estilo de texto normal en la etapa (2):
	return 0;
];

!!------------------------------------------------------------------------------
!! Determina si el próximo hipervínculo está o no activado. Por defecto siempre
!! retorna verdadero ---los hipervínculos están siempre activados---, pero
!! puede ser reescrita utilizando una sentencia 'Replace HyperlinkStatus;'
!! antes de incluir la extensión.
!!
!!	@param {Object|String} item - Contiene al objeto o la cadena de caracteres
!!		sobre la que se va a generar el hipervínculo
!!	@param extra - Parámetro libre para controlar la lógica de la rutina
!!	@returns {boolean} Verdadero para indicar que el hipervínculo está
!!		activado. Falso en caso contrario
!!------------------------------------------------------------------------------
[ HyperlinkStatus item extra;
	item = extra; ! (por evitar alertas del compilador)
	return true;
];

!!------------------------------------------------------------------------------
!! Si el intérprete utilizado los soporta, activa la escucha de eventos glk
!! para la selección de hipervínculos en las ventanas principal de la
!! aplicación.
!!
!!	@returns {boolean} Verdadero
!!------------------------------------------------------------------------------
[ ListenHyperlinkEvents;
	#Ifdef TARGET_GLULX;
	if (glk($0004, 11, 0)) { ! glk_gestalt(gestalt_Hyperlinks, 0)
		!! Activa escucha de hipervínculos en la ventana principal:
		glk($0102, gg_mainwin); ! glk_request_hyperlink_event
		!! Activa escucha de hipervínculos en la ventana de estado:
		glk($0102, gg_statuswin); ! glk_request_hyperlink_event
		!! Desactiva el eco automático de la entrada en la ventana principal:
		glk($0150, gg_mainwin, 0); ! glk_set_echo_line_event
	}
	#Endif; ! TARGET_GLULX;
];

#Endif; ! HYPERLINKS;

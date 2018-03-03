

!!==============================================================================
!!
!!	HYPERLINKS
!!	Marco para facilitar la interacción por hipervínculos
!!
!!==============================================================================
!!
!!	Archivo:		hyperlinks.inf
!!	Autor(es):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!	Idioma:			ES (Español)
!!	Sistema:		Inform-INFSP 6
!!	Plataforma:		Glulx
!!	Versión:		0.0 - En desarrollo
!!	Fecha:			2018/03/03
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
!!	1.0: 2018/03/XX	TODO
!!
!!------------------------------------------------------------------------------
System_file;

#Ifndef HYPERLINKS;
Constant HYPERLINKS;

Constant HYPERLINKS_DEFAULT_COMMAND = "examina";
Global _hyperlinks_command = HYPERLINKS_DEFAULT_COMMAND;
Array _hyperlinks_temp_array -> INPUT_BUFFER_LEN/WORDSIZE*2;

#Ifdef TARGET_GLULX;
[ HandleHyperlinkEvent ev context abortres
	length i;
	if (ev-->0 == 8) { ! evtype_Hyperlink
		!! Tras reconocer y reaccionar con éxito a la selección de un
		!! hipervínculo, la aplicación deja de esperar nuevos eventos de este
		!! tipo. De modo que hay que activar otra vez su escucha. (Para poder
		!! recibir por primera vez un evento de selección de hipervínculo se
		!! debe activar su escucha también al inicio de la obra, en la rutina
		!! 'Initialise()', por ejemplo):
		glk($0102, gg_mainwin);		! glk_request_hyperlink_event
		!! Se cancelan los inputs de teclado:
		glk($00D3, gg_mainwin);		! glk_cancel_char_event
		glk($00D1, gg_mainwin, 0);	! glk_cancel_line_event
		!! 'ev-->2' puede almacenar un objeto o un string (sobre el que se ha
		!! creado el hipervínculo). Para crear el comando que se va a utilizar
		!! como input, deben volcarse sus contenidos sobre el array 'abortres'.
		!! Aquí existen dos posibilidades: 1) si el hipervínculo se ha creado
		!! sobre un objeto, el comando se construye como la concatenación del
		!! valor registrado en la variable '_hyperlinks_command' y el objeto.
		!! 2) si el hipervínculo se ha creado sobre un string, el propio string
		!! es el comando:
		if (metaclass(ev-->2) == Object) {
			if (metaclass(_hyperlinks_command) == String) {
				PrintToBuffer(abortres, INPUT_BUFFER_LEN, _hyperlinks_command);
			} else {
				PrintToBuffer(abortres, INPUT_BUFFER_LEN,
					HYPERLINKS_DEFAULT_COMMAND);
			}
			#Ifdef DEBUG_HYPERLINKS;
			print " ** Contenidos de abortres ** ";
			Debug_printCharacterArray(abortres);
			new_line;
			#Endif; ! DEBUG_HYPERLINKS;
			length = abortres->(WORDSIZE-1);
			abortres->(WORDSIZE+length) = ' ';
			(abortres->(WORDSIZE-1))++;
			length = abortres->(WORDSIZE-1);
			PrintToBuffer(_hyperlinks_temp_array, INPUT_BUFFER_LEN/WORDSIZE*2, ev-->2);
			for (i = 0 : i < _hyperlinks_temp_array->(WORDSIZE-1) : i++) {
				abortres->(WORDSIZE+length+i) =
					_hyperlinks_temp_array->(WORDSIZE+i);
				(abortres->(WORDSIZE-1))++;
			}
			#Ifdef DEBUG_HYPERLINKS;
			print " ** Contenidos de abortres ** ";
			Debug_printCharacterArray(abortres);
			new_line;
			#Endif; ! DEBUG_HYPERLINKS;
			return true;
		}
		if (metaclass(ev-->2) == String) {
			PrintToBuffer(abortres, INPUT_BUFFER_LEN, ev-->2);
			#Ifdef DEBUG_HYPERLINKS;
			print " ** Contenidos de abortres ** ";
			Debug_printCharacterArray(abortres);
			new_line;
			#Endif; ! DEBUG_HYPERLINKS;
			return true;
		}
	}
	context++; ! por evitar alertas del compilador
	return false;
];
#Endif; ! TARGET_GLULX;

[ Hyperlink item alternative;
	if (metaclass(item) ~= String or Object) return false;
	!! Establece el inicio del hipervínculo:
	#Ifdef TARGET_GLULX;
	glk($0100, item); ! glk_set_hyperlink();
	#Endif; ! TARGET_GLULX;
	!! Selecciona el estilo de texto del hipervínculo:
	!! TODO
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
	!! TODO
	!! Establece el final del hipervínculo:
	#Ifdef TARGET_GLULX;
	glk($0100, 0); ! glk_set_hyperlink
	#Endif; ! TARGET_GLULX;
];

!! Imprime un array de caracteres, caracter a caracter
#Ifdef DEBUG_HYPERLINKS;
[ Debug_printCharacterArray character_array
	i;
	for (i = WORDSIZE : i < (character_array-->0) + WORDSIZE : i++) {
		print (char) character_array->i;
	}
];
#Endif; ! DEBUG_HYPERLINKS;

#Endif; ! HYPERLINKS;



!!==============================================================================
!!
!!	ARRAYS
!!	Rutinas de utilidad para manipular arrays de caracteres
!!
!!==============================================================================
!!
!!	Archivo:		arrays.h
!!	Autor(es):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!	Idioma:			ES (Español)
!!	Sistema:		Inform-INFSP 6
!!	Plataforma:		Máquina-Z/Glulx
!!	Versión:		1.2
!!	Fecha:			2019/02/25
!!
!!------------------------------------------------------------------------------
!!
!!	Copyright (c) 2019, J. Francisco Martín
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
!!	1.2: 2019/02/25	Incluye rutinas para imprimir un array de caracteres todas
!!					en mayúsculas o todas en minúsculas.
!!	1.1: 2018/09/21	Modificada la codificación de caracteres de ISO 8859-15 a
!!					UTF-8 (requiere la versión 6.34 o superior del compilador).
!!	1.0: 2018/06/19	Versión inicial de la extensión.
!!
!!------------------------------------------------------------------------------
System_file;

#Ifndef ARRAYS;
Constant ARRAYS;

Array temp_array -> INPUT_BUFFER_LEN; ! hasta 160 caracteres

!!------------------------------------------------------------------------------
!! Dado un array de caracteres, capitaliza la primera letra de cada palabra de
!! éste ---útil por ejemplo si el array almacena el nombre de una persona
!! (Paul O'Brian, Jean-Paul Sartre,...) o de una localidad (Weston-Super-Mare,
!! Los Angeles,...)---.
!!
!!	@param {Array} character_array - El array de caracteres sobre el que se
!!		realizará la capitalización
!!	@returns {boolean} Verdadero
!!	@version 1.0
!!------------------------------------------------------------------------------
[ CapitaliseCharacterArray character_array
	i c flg;
	for (i = 0, flg = true : i < character_array-->0 : i++) {
		c = character_array->(i+WORDSIZE);
		if (c >= 'a' && c <= 'z') {
			if (flg) character_array->(i+WORDSIZE) = UpperCase(c);
			flg = false;
 		} else flg = true;
	}
	return true;
];

!!------------------------------------------------------------------------------
!! Dados dos arrays de caracteres: 'array_a' y 'array_b', modifica el primero
!! de forma que se convierte en la concatenación de los dos. Puede
!! especificarse además un caracter extra opcional que será introducido como
!! delimitador entre los dos arrays (si no se especifica este caracter extra,
!! el segundo array se añade inmediatamente a continuación del primero).
!!
!!	@param {Array} array_a - Primer array de caracteres; sobre el que queda el
!!		resultado de la concatenación
!!	@param {Array} array_b - Segundo array de caracteres; el que se concatena
!!		a continuación de 'array_a'
!!	@param {char} [c=false] - Caracter opcional que puede introducirse como
!!		delimitador de los dos arrays
!!	@returns {boolean} Verdadero
!!	@version 1.0
!!------------------------------------------------------------------------------
[ ConcatenateArrays array_a array_b c
	len i;
	len = array_a-->0;
	if (c ~= 0 || metaclass(c) ~= nothing) {
		array_a->(WORDSIZE+len) = c;
		(array_a->(WORDSIZE-1))++;
		len = array_a-->0;
	}
	for (i = 0 : i < array_b->(WORDSIZE-1) : i++) {
		array_a->(WORDSIZE+len+i) = array_b->(WORDSIZE+i);
		(array_a->(WORDSIZE-1))++;
	}
	return true;
];

!!------------------------------------------------------------------------------
!! Imprime en pantalla un array de caracteres, caracter a caracter.
!!
!!	@param {array} character_array - Array de caracteres a imprimir
!!	@returns {boolean} Verdadero
!!	@version 1.0
!!------------------------------------------------------------------------------
[ PrintCharacterArray character_array
	i;
	for (i = 0 : i < character_array->(WORDSIZE-1) : i++) {
		print (char) character_array->(WORDSIZE+i);
	}
	return true;
];

!!------------------------------------------------------------------------------
!! Imprime en pantalla un array de caracteres, caracter a caracter, todos en
!! mayúsculas
!!
!!	@param {array} character_array - Array de caracteres a imprimir
!!	@returns {boolean} Verdadero
!!	@version 1.0
!!------------------------------------------------------------------------------
[ PrintCharacterArrayUpperCase character_array
	i c;
	for (i = 0 : i < character_array->(WORDSIZE-1) : i++) {
		c = character_array->(WORDSIZE+i);
		if (c >= 'a' && c <= 'z') {
			c = UpperCase(c);
		}
		print (char) c;
	}
	return true;
];

!!------------------------------------------------------------------------------
!! Imprime en pantalla un array de caracteres, caracter a caracter, todos en
!! minúsculas
!!
!!	@param {array} character_array - Array de caracteres a imprimir
!!	@returns {boolean} Verdadero
!!	@version 1.0
!!------------------------------------------------------------------------------
[ PrintCharacterArrayLowerCase character_array
	i c;
	for (i = 0 : i < character_array->(WORDSIZE-1) : i++) {
		c = character_array->(WORDSIZE+i);
		if (c >= 'A' && c <= 'Z') {
			c = LowerCase(c);
		}
		print (char) c;
	}
	return true;
];

#Endif; ! ARRAYS;

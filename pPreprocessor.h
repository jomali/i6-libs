

!!==============================================================================
!!
!!	PARSING PREPROCESSOR
!!
!!==============================================================================
!!
!!	File:			pPreprocessor.h
!!	Author(s):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!	Language:		ES (Castellano)
!!	System:			Inform-INFSP 6
!!	Platform:		Z-Machine / Glulx
!!	Version:		1.3
!!	Released:		2017/09/18
!!
!!------------------------------------------------------------------------------
!!
!!	# HISTORIAL DE VERSIONES
!!
!!	1.3: 2017/09/18	Actualización de la rutina 'CompareWord' a la versión 1.2.
!!	1.2: 2017/08/04	Revisión y formateo de comentarios de la extensión.
!!	1.1: 2014/07/29	Ante objetos con el mismo índice de coincidencia, ahora se
!!					da preferencia a aquellos que se encuentren en el foco del
!!					jugador.
!!	1.0: 2014/05/29	Versión preliminar.
!!
!!------------------------------------------------------------------------------
!!
!!	This program is free software; you can redistribute it and/or modify
!!	it under the terms of the GNU General Public License as published by
!!	the Free Software Foundation; either version 2 of the License, or
!!	(at your option) any later version.
!!
!!	This program is distributed in the hope that it will be useful,
!!	but WITHOUT ANY WARRANTY; without even the implied warranty of
!!	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
!!	GNU General Public License for more details.
!!
!!	You should have received a copy of the GNU General Public License along
!!	with this program; if not, write to the Free Software Foundation, Inc.,
!!	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. Or see
!!	<http://www.gnu.org/licenses/>.
!!
!!	Copyright (C) 2014, 2017, J. Francisco Martín
!!
!!------------------------------------------------------------------------------
System_file;

!! Descomentar para obtener info. de depuración del preprocesador:
!Constant DEBUG_PARSING_PREPROCESSOR;

!! Descomentar para obtener info. de depuración de la rutina CompareWord():
!Constant DEBUG_COMPARE_WORD_ROUTINE;

#Ifndef _COMPARE_WORD_ROUTINE_;
Constant _COMPARE_WORD_ROUTINE_;
!! Array para guardar palabras temporalmente:
Array compare_word_tmp_text -> 64;
!!==============================================================================
!! Compara una palabra de la entrada del usuario con una de las palabras de
!! diccionario. La palabra de entrada se pasa a la función a través de
!! 'num_word_prompt', un número que indica el orden de la palabra en el vector
!! de entrada, y la palabra de diccionario se pasa a través de 'dictword'
!! (hay que volcarla en un vector antes de hacer la comprobación).
!!
!!	@param {integer} num_word_prompt - Indica el orden de la palabra en el
!!		vector de entrada
!!	@param {string} dictword - Palabra de diccionario
!!	@returns {integer} 1 si las palabras son iguales, 0 si son diferentes
!!	@version 1.2
!!------------------------------------------------------------------------------
[ CompareWord num_word_prompt dictword
	i length;

	!! A) Se vuelca la palabra de diccionario a un array:

	#Ifdef TARGET_ZCODE;
	@output_stream 3 compare_word_tmp_text;
	print (address) dictword;
	@output_stream -3;
	#Ifnot;	! TARGET_GLULX;
	compare_word_tmp_text->(WORDSIZE-1) =
		PrintAnyToArray(compare_word_tmp_text + WORDSIZE, 60, dictword);
	#Endif; ! TARGET_

	length = compare_word_tmp_text->(WORDSIZE-1);

	!! B) Si el ultimo carácter es una coma, se elimina para evitar conflictos
	!! con la conversión de infinitivos y los diccionarios en informATE --> NO
	!! DEBE HABER NUNCA PALABRAS EN INFINITIVO EN EL DICCIONARIO. No vale para
	!! palabras que antes de ponerles la coma tengan 9 o más caracteres
	!! (limitación de Inform):

	if (compare_word_tmp_text->(length+WORDSIZE-1) == ',') {
		!! Se elimina el caracter del buffer:
		compare_word_tmp_text->(length+WORDSIZE-1) = 0;
		!! Se reducen las dimensiones:
		(compare_word_tmp_text->(WORDSIZE-1))--;
		!! Se actualiza el valor de 'length':
		length = compare_word_tmp_text->(WORDSIZE-1);
	}

	#Ifdef DEBUG_COMPARE_WORD_ROUTINE;
	print "Comparando prompt: <", (PrintPromptWord) num_word_prompt,
	"> con palabra de diccionario:<", (PrintStringArray) compare_word_tmp_text,
	">^";
	#Endif; ! DEBUG_COMPARE_WORD_ROUTINE;

	!! Si la longitud de las palabras no es igual, se retorna NO coincidente.
	!! (NOTA: Hay que contemplar el caso especial de palabras de más de 9
	!! caracteres por las limitaciones de Inform):
	if (WordLength(num_word_prompt) ~= length &&
			~~(WordLength(num_word_prompt) > 9 && length == 9)) {
		return 0;
	}

	!! Si las palabras tienen la misma longitud, se comparan carácter a
	!! carácter y se retorna NO coincidente si se encuentra una diferencia:
	for (i = 0: i < length: i++) {
		if (WordAddress(num_word_prompt)->i ~=
				compare_word_tmp_text->(i+WORDSIZE)) {
			return 0;
		}
	}

	!! Las palabras son iguales:
	return 1;
];

#Ifdef DEBUG_COMPARE_WORD_ROUTINE;
!!==============================================================================
!!	Funciones de depuración
!!------------------------------------------------------------------------------
!! Función para pintar un String Array
[ PrintStringArray the_array i;
	print "(", the_array-->0, ")";
	for (i = WORDSIZE : i < (the_array-->0) + WORDSIZE : i++)
		print (char) the_array->i;
];
!! Función para pintar una palabra del Prompt de entrada del jugador
[ PrintPromptWord num_word dir i;
	dir = WordAddress(num_word);
	for (i = 0 : i < WordLength(num_word) : i++)
		print (char) dir->i;
];
#Endif; ! DEBUG_COMPARE_WORD_ROUTINE;
#Endif; ! _COMPARE_WORD_ROUTINE_;


!!==============================================================================
!! Preprocesador de la entrada de usuario. Implementa la siguiente interfaz:
!!
!!	 -	get_selected_object(): Retorna objeto
!!	 -	run()
!!------------------------------------------------------------------------------
Object	ParsingPreprocessor "(Parsing preprocessor)"
 with	!!----------------------------------------------------------------------
		!!	@returns {Object} Último objeto reconocido por el preprocesador en
		!!		la entrada del usuario
 		!!----------------------------------------------------------------------
 		get_selected_object [;
			return self.selected_object;
		],
		!!----------------------------------------------------------------------
		!! Comprueba la entrada del usuario y trata de reconocer patrones en
		!! ella mediante análisis no estricto para identificar si puede
		!! referirse a alguno de los objetos definidos en el modelo del mundo.
		!!----------------------------------------------------------------------
		run [
			obj i j n m valid hits max_hits;

			!! A) Inicializaciones del método:
			self.selected_object = 0;

			!! B) Da un repaso a los objetos presentes en el relato,
			!! comprobando si alguno encaja con la entrada de usuario:
			objectloop (obj ofclass Object) {
				n = m = 0;
				valid = false;

				if (obj.adjectives ~= 0) {
					for (i = 0 : i < (obj.#adjectives)/WORDSIZE : i++) {
						for (j = 1 : j <= num_words : j++) {
							if (CompareWord(j, obj.&adjectives-->i)) {
								if (j == 1) valid = true;
								m++;
							}
						}
					}
				}
				if (obj.name_f ~= 0) {
					for (i = 0 : i < (obj.#name_f)/WORDSIZE : i++) {
						for (j = 1 : j <= num_words : j++) {
							if (CompareWord(j, obj.&name_f-->i)) {
								if (j == 1) valid = true;
								n++;
							}
						}
					}
				}
				if (obj.name_fp ~= 0) {
					for (i = 0 : i < (obj.#name_fp)/WORDSIZE : i++) {
						for (j = 1 : j <= num_words : j++) {
							if (CompareWord(j, obj.&name_fp-->i)) {
								if (j == 1) valid = true;
								n++;
							}
						}
					}
				}
				if (obj.name_m ~= 0) {
					for (i = 0 : i < (obj.#name_m)/WORDSIZE : i++) {
						for (j = 1 : j <= num_words : j++) {
							if (CompareWord(j, obj.&name_m-->i)) {
								if (j == 1) valid = true;
								n++;
							}
						}
					}
				}
				if (obj.name_mp ~= 0) {
					for (i = 0 : i < (obj.#name_mp)/WORDSIZE : i++) {
						for (j = 1 : j <= num_words : j++) {
							if (CompareWord(j, obj.&name_mp-->i)) {
								if (j == 1) valid = true;
								n++;
							}
						}
					}
				}
				if (n ~= 0) n = n+m;

				!! Se calcula el número de coincidencias del objeto actual en
				!! relación al total de palabras (%):
				hits = (n*100) / num_words;

				!! Si el objeto actual tiene más coincidencias que el mejor
				!! candidato hasta ahora lo sustituye:
				if ((valid) && (hits > max_hits)) {
					self.selected_object = obj;
					max_hits = hits;
				}
				!! Si el objeto actual y el mejor candidato hasta ahora tienen
				!! el mismo número de coincidencias, comprueba si el actual se
				!! encuentra en el foco del jugador y si es así se lo
				!! selecciona como candidato:
				else if ((valid) && (hits == max_hits)) {
					if (TestScope(obj, player)) {
						self.selected_object = obj;
					}
				}
			}

			#Ifdef DEBUG_PARSING_PREPROCESSOR;
			if (self.selected_object ~= 0) {
				print "** PARSING PREPROCESSOR **^", "Coincidencia: ",
				(name) self.selected_object, ", ", max_hits, "%.^";
			}
			else {
				print "** PARSING PREPROCESSOR **^", "No hay coincidencias.^";
			}
			#Endif; ! DEBUG_PARSING_PREPROCESSOR;

		],
 private
		selected_object 0;

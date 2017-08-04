

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
!!	Version:		1.2
!!	Released:		2017/08/04
!!
!!------------------------------------------------------------------------------
!!
!!	# HISTORIAL DE VERSIONES
!!
!!	1.2: 2017/08/04	Revisión y formateo de comentarios de la extensión.
!!	1.1: 2014/07/29	Ante objetos con el mismo índice de coincidencia, ahora se
!!					da preferencia a aquellos que se encuentren en el foco del
!!					jugador.
!!	1.0: 2014/05/29	Versión preliminar.
!!
!!------------------------------------------------------------------------------
!!
!!	Copyright (c) 2014, 2017, J. Francisco Martín
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
System_file;

!! Descomentar para obtener info. de depuración del preprocesador:
!Constant DEBUG_PARSING_PREPROCESSOR;

!! Descomentar para obtener info. de depuración de la rutina CompareWord():
!Constant DEBUG_COMPARE_WORD_ROUTINE;

#Ifndef COMPARE_WORD_ROUTINE;
Constant COMPARE_WORD_ROUTINE;
!!==============================================================================
!! Compara una palabra de la entrada del usuario con una de las palabras de
!! diccionario. La palabra de entrada se pasa a la función a través de
!! *num_word_prompt*, un número que indica el orden de la palabra en el vector
!! de entrada, y la palabra de diccionario se pasa a través de *dictword*
!! (hay que volcarla en un vector antes de hacer la comprobación).
!!
!!	@param {integer} num_word_prompt - Indica el orden de la palabra en el
!!		vector de entrada
!!	@param {string} dictword - Palabra de diccionario
!!	@returns {integer} 1 si las palabras son iguales, 0 si son diferentes
!!------------------------------------------------------------------------------
!! Vector para guardar palabras temporalmente:
Array tmp_text -> 64;
[ CompareWord num_word_prompt dictword
	i len;

	!! A) Se vuelca la palabra de diccionario a un array:

	#Ifdef TARGET_ZCODE;
	@output_stream 3 tmp_text;
	print (address) dictword;
	@output_stream -3;
	#Ifnot;	! TARGET_GLULX;
	tmp_text->(WORDSIZE-1) = PrintAnyToArray(tmp_text+WORDSIZE, 60, dictword);
	#Endif; ! TARGET_

	len = tmp_text->(WORDSIZE-1);

	!! B) Si el ultimo carácter es una coma, se elimina para evitar conflictos
	!! con la conversión de infitivos y los diccionarios en informATE --> NO
	!! DEBE HABER NUNCA PALABRAS EN INFINITIVO EN EL DICCIONARIO. No vale para
	!! palabras que antes de ponerles la coma tengan 9 o más caracteres
	!! (limitación de Inform):

	if (tmp_text->(len+WORDSIZE-1) == ',') {
		tmp_text->(len+WORDSIZE-1) = 0;	! Se elimina el caracter del buffer
		(tmp_text->(WORDSIZE-1))--;		! Se reducen las dimensiones
		len = tmp_text->(WORDSIZE-1);	! Se actualiza el valor de 'len'
	}

	#Ifdef DEBUG_COMPARE_WORD_ROUTINE;
	print "Comparando prompt: <", (PrintPromptWord) num_word_prompt,
	"> con palabra de diccionario:<", (PrintStringArray) tmp_text, ">^";
	#Endif; ! DEBUG_COMPARE_WORD_ROUTINE;

	!! Si la longitud de las palabras no es igual, se retorna NO coincidente.
	!! (NOTA: Hay que contemplar el caso especial de palabras de más de 9
	!! caracteres por las limitaciones de Inform):
	if (WordLength(num_word_prompt) ~= len &&
			~~(WordLength(num_word_prompt) > 9 && len == 9))
		return 0;

	!! Si las palabras tienen la misma longitud, se comparan caracter a
	!! caracter y se retorna NO coincidente si se encuentra una diferencia:
	for (i = 0: i < len: i++) {
		if (WordAddress(num_word_prompt)->i ~= tmp_text->(i+WORDSIZE))
			return 0;
	}

	!! Las palabras son iguales:
	return 1;
];

#Ifdef DEBUG_COMPARE_WORD_ROUTINE;
!!==============================================================================
!! Función de depuración para imprimir en pantalla un vector de caracteres.
!!
!!	@param {Array} the_array
!!------------------------------------------------------------------------------
[ PrintStringArray the_array
	i;
	print "(", the_array-->0, ")";
	for (i = WORDSIZE : i < (the_array-->0) + WORDSIZE : i++)
		print (char) the_array->i;
];

!!==============================================================================
!! Función de depuración para imprimir en pantalla una palabra de la entrada
!! del usuario.
!!
!!	@param {integer} num_word
!!------------------------------------------------------------------------------
[ PrintPromptWord num_word dir i;
	dir = WordAddress(num_word);
	for (i = 0 : i < WordLength(num_word) : i++)
		print (char) dir->i;
];
#Endif; ! DEBUG_COMPARE_WORD_ROUTINE;
#Endif; ! COMPARE_WORD_ROUTINE;


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

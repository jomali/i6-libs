

!!==============================================================================
!!
!!	CHOICE SET
!!	Sistema para hacer selecciones entre un conjunto de opciones
!!
!!==============================================================================
!!
!!	File:			choiceSet.h
!!	Author(s):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!					Mastodon
!!	Language:		ES (Castellano)
!!	System:			Inform-INFSP 6
!!	Platform:		Z-Machine / Glulx
!!	Version:		1.0
!!	Released:		2017/09/18
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
!!	Copyright (c) 2009, Mastodon
!!	Copyright (C) 2017, J. Francisco Martín
!!
!!------------------------------------------------------------------------------
!!
!!	# HISTORIAL DE VERSIONES
!!
!!	1.1: 2017/12/28	Corrección en el cambio de estilo de texto en Máquina-Z
!!	1.0: 2017/09/21	Versión inicial.
!!	0.0: 2016/07/24	Inicio de la adaptación de la extensión 'topicInventory'
!!					v2.2 para generalizar el sistema de conversación con
!!					inventario de temas.
!!
!!------------------------------------------------------------------------------
!!
!!	# INTRODUCCIÓN
!!
!!	La extensión CHOICE SET permite implementar sistemas de conversación con
!!	inventario de temas ---y, en general, cualquier otro sistema que utilice
!!	un mecanismo de selección de opciones de entre un conjunto dado---
!!	utilizando análisis no estricto de la entrada de usuario para el
!!	reconocimiento de patrones. Está basada en las notas de Eric Eve sobre
!!	sistemas de conversación: <http://www.tads.org/howto/convbkg.htm>, y
!!	construída sobre las extensiones NPC_Conversacion v1.0 de Mastodon, y
!!	TOPIC INVENTORY v2.1 ---CHOICE SET es una generalización actualizada de
!!	sobre ésta última---. Permite interacciones del tipo:
!!
!!		Te detienes un momento a pensar en qué hacer esta tarde...
!!		(Puedes escoger entre escribir documentación, salir a tomar algo o ver
!!		una película.)
!!
!!		> lo de la peli
!!
!!
!!	# APLICACIONES
!!
!!	CHOICE SET permite listar ante el usuario un conjunto de opciones de entre
!!	las que puede seleccionar una introduciendo alguna de las palabras clave de
!!	la opción; una funcionalidad que facilita, por ejemplo, la construcción de
!!	CONVERSACIONES utilizando un sistema de INVENTARIO DE TEMAS. Estos sistemas
!!	de conversación están ideados con el objetivo de esquivar los problemas que
!!	suelen presentar los sistemas de conversación más habituales en los relatos
!!	interactivos; dificultades para adivinar la palabra clave en sistemas
!!	basados en acciones ASK/TELL, simplificación excesiva en sistemas basados
!!	en la acción TALK TO, o falta de libertad y ruptura de la interfaz textual
!!	en sistemas de menús.
!!
!!	Al utilizar un inventario de temas, en esencia, se presenta al usuario una
!!	lista de temas de conversación sugeridos basándose en el conocimiento del
!!	personaje protagonista. De esta forma, el usuario puede hacer referencia a
!!	los temas que quiera lanzar utilizando una interfaz similar a la de los
!!	sistemas ASK/TELL, pero sin necesidad de tener que adivinar por sí mismo la
!!	palabra clave que lanza el tema.
!!
!!	En concreto, el sistema se podría presentar de una forma similar a la
!!	del siguiente ejemplo (las diferentes opciones posibles se ordenan
!!	aleatoriamente con cada listado):
!!
!!		> hablar con el programador
!!		---Disculpe...
!!		El programador levanta la vista de la pantalla de su ordenador y se
!!		quita las gafas. ---¿Si?
!!
!!		(Puedes preguntar por sus aficiones, hablarle del proyecto en que
!!		trabaja o hablar del tema que nunca se acaba.)
!!
!!		> hablar del proyecto
!!		---He oído que llevas un tiempo trabajando en el proyecto de un relato
!!		interactivo... ---empiezas.
!!		El hombre se pone muy nervioso de pronto. ---¿Quién te ha hablado de
!!		eso? Ese proyecto está aparcado desde hace años. Después de aquel... de
!!		aquel asunto.
!!
!!		> hablar al programador
!!		Simula limpiarse las gafas, inquieto.
!!
!!		(Puedes hablar del tema que nunca se acaba, preguntar por el asunto o
!!		preguntar por sus aficiones.)
!!
!!		> asunto
!!		---¿A qué asunto te refieres?
!!		Él se coloca las gafas y vuelve de nuevo su atención al ordenador,
!!		claramente agitado. ---T-tengo mucho trabajo que hacer. Si me
!!		disculpas...
!!
!!		(Puedes insistir en el asunto, preguntar por sus aficiones o hablar
!!		del tema que nunca se acaba.)
!!
!!		> tema interminable
!!		---Tío, ¿dónde está mi coche?
!!		---¿Y tu coche, tío?
!!
!!		(Puedes hablar del tema que nunca se acaba, preguntar por sus aficiones
!!		o insistir en el asunto.)
!!
!!	Además de para conversaciones, el sistema se puede utilizar en general para
!!	crear cualquier otra interacción similar con un objeto cualquiera. Por
!!	ejemplo:
!!
!!		> abrir nevera
!!		Abres la nevera buscando algo que comer.
!!
!!		(Puedes prepararte un sandwich o hacerte un cocido montañés.)
!!
!!		> cocido
!!		[...]
!!
!!
!!	# ANÁLISIS NO ESTRICTO
!!
!!	El reconocimiento de patrones entre la entrada de usuario y las palabras
!!	clave de cada elección se lleva a cabo por medio de análisis no estricto;
!!	si entre todas las palabras introducidas por el usuario se reconocen claves
!!	de una o más elecciones, se lanza aquella con más coincidencias, ignorando
!!	el resto de la entrada.
!!
!!
!!	# SOBRE EL FORMATO DE LOS MENSAJES
!!
!!	El formato con el que se imprime el listado de opciones se puede modificar.
!!	Para ello, el autor cuenta con 8 constantes diferentes que puede definir
!!	libremente:
!!
!!	 -	CSET_STYLE [0-3]: Define el estilo con el que se imprime el listado de
!!		opciones: 0 -> romana, 1 -> itálica, 2 -> negrita, 3 -> monoespaciada.
!!
!!	 -	CSET_PREFIX: Cadena de texto previa al listado de elecciones.
!!
!!	 -	CSET_SUFIX: Cadena de texto posterior al listado de elecciones.
!!
!!	 -	CSET_MSG1: Antecede al conjunto de elecciones cuando son listadas.
!!
!!	 -	CSET_MSG2: Si hay más de una elección en el conjunto, se imprime entre
!!		CSET_MSG1 y el conjunto de elecciones cuando son listadas.
!!
!!	 -	CSET_COMMA: Separador general de las elecciones del conjunto cuando son
!!		listadas.
!!
!!	 -	CSET_OR: Separador de las dos últimas elecciones del conjunto cuando
!!		son listadas.
!!
!!	 -	CSET_NO_MSG: Mensaje cuando se hace un listado si no hay elecciones en
!!		el conjunto.
!!
!!	La configuración por defecto de estas constantes: CSET_STYLE=1,
!!	CSET_PREFIX="(", CSET_SUFIX=".)", CSET_MSG1="Puedes ", CSET_MSG2="escoger
!!	entre ", CSET_COMMA=", ", CSET_OR=" o ", CSET_NO_MSG="Listado de opciones
!!	vacío", imprime listados en estilo romana del tipo*:
!!
!!		(Puedes escoger entre la opción 1, la opción 2 o la opción 3.)
!!
!!	*.- El último separador en la configuración por defecto es la cadena " o ".
!!	Cabe señalar que ante opciones que empiecen igualmente por 'o', el
!!	separador debería ser " u ", en lugar de " o ". Aunque hacer esto
!!	automáticamente es técnicamente posible, la manipulación de cadenas de
!!	caracteres en Inform resulta muy engorrosa y requeriría transformar cada
!!	una de las opciones del listado en vectores de caracteres primero, y luego
!!	realizar las comprobaciones oportunas antes de imprimir el separador
!!	correcto. En lugar de todo esto, se insta al autor a no utilizar opciones
!!	que empiecen por la letra 'o' si utiliza ese " o " por defecto como
!!	separador final del listado. (En el listado del ejemplo, en lugar de
!!	"opción 1", "opción 2", etc, se ha utilizado: "LA opción 1", "LA opción
!!	2"... No así en el próximo ejemplo, más abajo).
!!
!!	Se podría, por ejemplo, cambiar por la siguiente configuración alternativa:
!!	CSET_STYLE=1, CSET_PREFIX="[", CSET_SUFIX="]", CSET_MSG1="Escoge: ",
!!	CSET_MSG2="", CSET_COMMA=" / ", CSET_OR=" / ", CSET_NO_MSG="Listado de
!!	opciones vacío", para imprimir listados en cursiva con el siguiente formato:
!!
!!		[Escoge: opción 1 / opción 2 / opción 3]
!!
!!
!!	# UTILIZACIÓN
!!
!!	Para usar la librería únicamente hay que incluir la siguiente línea en la
!!	rutina BeforeParsing (crearla si no existe):
!!
!!		[ BeforeParsing;
!!			ChoiceSetManager.run();
!!		];
!!
!!
!!	# LIMITACIONES Y POSIBLES MEJORAS
!!
!!	Podría ser interesante contemplar la posibilidad de crear elecciones
!!	ocultas ('concealed') que no aparezcan sugeridas automáticamente al
!!	imprimir el conjunto de elecciones disponibles. Permitiría implementar, por
!!	ejemplo, temas de conversación ocultos.
!!
!!------------------------------------------------------------------------------
System_file;
#Ifndef _CHOICE_SET_;
Constant _CHOICE_SET_;
Message "[Including <choiceSet>]";

!! Descomentar para obtener info. de depuración del controlador:
!Constant DEBUG_CHOICE_SET;

!! Descomentar para obtener info. de depuración de la rutina 'CompareWord()'':
!Constant DEBUG_COMPARE_WORD_ROUTINE;

!! Descomentar y compilar para probar la extensión:
!Constant TEST_CHOICE_SET;

!! Estilo y textos por defecto de la extensión:
Default CSET_STYLE	1; ! [0-3]
Default CSET_PREFIX	"(";
Default CSET_SUFIX	".)";
Default CSET_MSG1	"Puedes ";
Default CSET_MSG2	"escoger entre ";
Default CSET_COMMA	", ";
Default CSET_OR		" o ";
Default CSET_NO_MSG	"Listado de opciones vacío";

!! Objeto de apoyo para reordenar los temas de una conversación:
Object	ChoiceBag "(ChoiceSet Bag)";


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
!!	Representa una elección que puede ser seleccionada por el usuario.
!!------------------------------------------------------------------------------
Class	ChoiceSetItem
 with	!!----------------------------------------------------------------------
		!! Determina el número de coincidencias entre la entrada del usuario y
		!! el ítem.
		!!----------------------------------------------------------------------
		compare_prompt [
			i j;
			self.hits = 0;
			if (self.keys ~= 0) {
				for (i = 0 : i < (self.#keys)/WORDSIZE : i++) {
					for (j = 1 : j <= num_words : j++) {
						if (CompareWord(j, self.&keys-->i)) {
							self.hits++;
						}
					}
				}
			}
		],
		!!----------------------------------------------------------------------
		!! Otras propiedades:
		!!----------------------------------------------------------------------
		!! Indica si el turno en que se trata este tema debe finalizar
		!! mostrando el inventario de temas restantes de la conversación de la
		!! que forma parte.
		append_choice_set false,
		!! Descripción del ítem. Es el texto que se imprime al mostrar el
		!! listado de elecciones de un conjunto:
		entry 0,
		!! Indica si el ítem pone fin a la selección:
		final_choice false,
   		!! Número de coincidencias de la entrada del usuario con el ítem:
   		hits 0,
		!! Palabras clave con las que el usuario puede hacer alusión al ítem:
		keys 0,
		!! Indica si el ítem es persistente. Cuando el gestor trata un ítem no
		!! persistente, automáticamente le da el atributo 'visited' para
		!! marcarlo como ítem ya seleccionado y luego lo elimina del conjunto
		!! (junto con todos sus parientes):
		persistent false,
		!! Rutina a ejecutar después de seleccionar el ítem:
		reaction 0,
		!! Array de ítems relacionados. Cuando éste se elimina, todos sus
		!! parientes se eliminan a su vez (y son marcados como tratados si éste
		!! ha sido marcado también):
		relatives 0,
		!! Rutina a ejecutar cuando se selecciona el ítem:
		reply 0,
		!! Array de ítems que se añaden al conjunto de elecciones tras tratar
		!! éste:
		subchoices 0,
;


!!==============================================================================
!!	Representa un conjunto de elecciones que pueden ser seleccionadas y
!!	exploradas por el usuario. Implementa la siguiente interfaz:
!!------------------------------------------------------------------------------
Class	ChoiceSet
 with	!!----------------------------------------------------------------------
		!! Añade un ítem al conjunto de elecciones (a menos que el ítem pasado
		!! como parámetro esté marcado como tratado ---atributo 'visited'---,
		!! en cuyo caso no hace nada). Los otros dos parámetros de la función
		!! son opcionales y permiten añadir ítems temporales. Si se invoca con
		!! 'temp_flag' como verdadero, el ítem formará parte del conjunto de
		!! elecciones únicamente durante una cantidad 'countdown' de turnos (si
		!! no se especifica un valor, se considera una cuenta atrás de 1).
		!!
		!!	@param {ChoiceSetItem} choice - Elección a añadir al conjunto
		!!	@param {boolean} [temp_flag=false] - Indica si la nueva elección es
		!!		temporal o no
		!!	@param {integer} [countdown=0} - Cantidad de turnos que ha de
		!!		permanecer la elección en el conjunto (en caso de tratarse de
		!!		una elección temporal)
		!!	@returns {boolean} Verdadero si la elección se añade correctamente
		!!		al conjunto. Falso en caso contrario
		!!----------------------------------------------------------------------
		add_choice [ choice temp_flag countdown;
			!! Se comprueba que el tema pasado sea válido:
			if (choice == 0) return false;
			if (~~(choice ofclass ChoiceSetItem)) return false;
			if (choice has visited) return false;
			!! Si es necesario se establece como tema temporal:
			if (temp_flag) {
				if (countdown < 1) countdown = 1;
				self.temporal_choice = choice;
				StopTimer(self);
				StartTimer(self, countdown);
			}
			!! Se añade a la conversación:
			move choice to self;
			return true;
		],
		!!----------------------------------------------------------------------
		!! Invoca a la función 'add_choice() para añadir un ítem temporal a
		!! partir de los parámetros dados.
		!!
		!!	@param {ChoiceSetItem} choice - Elección a añadir al conjunto como
		!!		elección temporal
		!!	@param {integer} [countdown=1] - Cantidad de turnos que ha de
		!!		permanecer la elección en el conjunto
		!!	@returns {boolean} Verdadero si la elección se añade correctamente
		!!		al conjunto como elección temporal. Falso en caso contrario
		!!----------------------------------------------------------------------
		add_temporal_choice [ choice countdown;
			return self.add_choice(choice, true, countdown);
		],
		!!----------------------------------------------------------------------
		!! Añade al conjunto las sub-elecciones (si tiene alguna) de aquella
		!! pasada como parámetro.
		!!
		!!	@param {ChoiceSetItem} choice - Se añaden las sub-elecciones
		!!		definidas para 'choice'
		!!	@returns {boolean} Verdadero si los sub-ítems se añaden con éxito.
		!!		Falso en caso contrario
		!!----------------------------------------------------------------------
		add_subchoices [ choice
			i;
			if ((choice == 0) || ~~(choice provides subchoices)) return false;
			if (choice.subchoices ~= 0) {
				for (i=0 : i<(choice.#subchoices)/WORDSIZE : i++) {
					self.add_choice(choice.&subchoices-->i);
				}
			}
			return true;
		],
		!!----------------------------------------------------------------------
		!! Marca un conjunto de elecciones como agotado. (Para hacerlo se
		!! utiliza el atributo 'general' contemplado por la librería Inform.)
		!!
		!!	@returns {boolean} Verdadero para indicar que el conjunto se ha
		!!		marcado como agotado con éxito
		!!----------------------------------------------------------------------
		end [;
			give self general;
			return true;
		],
		!!----------------------------------------------------------------------
		!! Indica si el conjunto de elecciones está o no agotado.
		!!
		!!	@returns {boolean} Verdadero si el conjunto está agotado. Falso en
		!!		caso contrario
		!!----------------------------------------------------------------------
		has_ended [;
			return (self has general);
		],
		!!----------------------------------------------------------------------
		!! Indica si el conjunto de elecciones tiene la elección concreta
		!! pasada como parámetro.
		!!
		!!	@param {ChoiceSetItem} choice
		!!	@returns {boolean} Verdadero si el conjunto tiene la elección dada.
		!!		Falso en caso contrario
		!!----------------------------------------------------------------------
		has_choice [ choice;
			return parent(choice) == self;
		],
		!!----------------------------------------------------------------------
		!! Elimina un ítem del conjunto de elecciones. Si se invoca con
		!! 'visited_flag' verdadero, se fuerza además que el ítem quede marcado
		!! como tratado aunque no haya llegado a mostrarse al usuario en
		!! realidad.
		!!
		!!	@returns {boolean} Verdadero si la elección se elimina con éxito
		!!		del conjunto. Falso en caso contrario
		!!----------------------------------------------------------------------
		remove_choice [ choice visited_flag
			obj i x;
			if ((choice == 0) || (parent(choice) ~= self)) return false;
			if (visited_flag) give choice visited;
			!! Se marca a los parientes de la elección como tratados (si
			!! procede), y se eliminan del conjunto (si están en él):
			if (choice.relatives ~= 0) {
				for (i=0 : i<(choice.#relatives)/WORDSIZE : i++) {
					x = choice.&relatives-->i;
					if (choice has visited) give x visited;
					for (obj=child(self) : obj~=nothing : obj=sibling(obj)) {
						if (obj == x) {
							remove x;
							break;
						}
					}
				}
			}
			!! Se elimina la elección:
			remove choice;
			return true;
		],
		!!----------------------------------------------------------------------
		!! Si hay alguna elección temporal en el conjunto, la elimina.
		!!
		!!	@returns {boolean} Verdadero si elimina la elección temporal del
		!!		conjunto correctamente. Falso en caso contrario
		!!----------------------------------------------------------------------
		remove_temporal_choice [
			x;
			if (self.temporal_choice ~= 0) {
				x = self.temporal_choice;
				self.temporal_choice = 0;
				StopTimer(self);
				self.time_left = -1;
				self.remove_choice(x);
				return true;
			}
			return false;
		],
		!!----------------------------------------------------------------------
		!! Retorna el número de elecciones del conjunto.
		!!
		!!	@returns {integer} Número de elecciones del conjunto
		!!----------------------------------------------------------------------
		get_size [
			choice size;
			choice = 0; ! para evitar un desconcertante warning del compilador
			objectloop(choice in self) size++;
			return size;
		],
		!!----------------------------------------------------------------------
		!! Ordena aleatoriamente e imprime un listado con el conjunto de
		!! elecciones. Si la entidad tiene definida la propiedad 'title', ésta
		!! se imprime antes de mostrar el resto del listado.
		!!----------------------------------------------------------------------
		show_choice_set [
			choice size i n;
			!! XXX - Puesto que el temporizador comprueba si se deben eliminar
			!! las elecciones temporales al finalizar el turno (es decir, justo
			!! después de mostrar el conjunto de elecciones), puede ocurrir que
			!! algunas de las elecciones del listado no estén en realidad
			!! disponibles. Por ello, antes de imprimir el listado, si procede
			!! se eliminan las elecciones temporales.
			if (self.time_left == 0) self.remove_temporal_choice();

			!! Si el conjunto tiene una propiedad 'title' definida, se imprime:
			if (self.title ~= 0) {
				switch (metaclass(self.title)) {
					Object:		print (The) self.title;
					String:		print (string) self.title;
					Routine:	indirect(self.title);
				}
				print ": ";
			}

			!! Se calcula el número de temas de la conversación:
			size = self.get_size();

			!! Se imprimen los mensajes previos al inventario:
			if ((size == 0) && (CSET_NO_MSG ~= 0))
				print (string) CSET_NO_MSG;
			if ((size > 0) && (CSET_MSG1 ~= 0))
				print (string) CSET_MSG1;
			if ((size > 1) && (CSET_MSG2 ~= 0))
				print (string) CSET_MSG2;

			!! Se recolocan los temas en la conversación de forma aleatoria:
			for (i = size : i > 0 : i--) {
				n = random(i);
				choice = child(self);
				while (n > 1) {
					choice = sibling(choice);
					n--;
				}
				move choice to ChoiceBag;
			}
			while (child(ChoiceBag)) move child(ChoiceBag) to self;

			!! Por último se imprime el listado de ítems:
			for (choice = child(self) : choice~=nothing
					: choice = sibling(choice)) {
				PrintOrRun(choice, entry, true);
				if (sibling(choice) ~= nothing) {
					if (sibling(sibling(choice)) == nothing) {
						if (CSET_OR ~= 0) {
							print (string) CSET_OR;
						}
					} else {
						if (CSET_COMMA ~= 0) {
							print (string) CSET_COMMA;
						}
					}
				}
			}
			return true;
		],
		!!----------------------------------------------------------------------
		!! Otras propiedades:
		!!----------------------------------------------------------------------
		!! Acción al intentar activar un conjunto de elecciones agotado:
		final_action 0,
		!! Acción al activar un conjunto de elecciones:
		initial_action 0,
		!! Acción al intentar activar un conjunto de elecciones ya activado:
		inter_action 0,
		!! Permite indicar un título para el conjunto que se imprimirá junto
		!! con el listado de elecciones:
		title 0,
		!! La siguiente propiedad ofrece soporte para bloquear el conjunto, de
		!! forma que mientras un conjunto se encuentre bloqueado se fuerce al
		!! usuario a seleccionar una de las elecciones sin posibilidad de
		!! hacer ninguna otra interacción. Para implementar esta funcionalidad
		!! se debe incluir incluir una rutina 'react_before' en el objeto que
		!! lanza el sistema CHOICE SET. (Consultar TEST para ver un ejemplo de
		!! uso de un conjunto bloqueado.)
		fixed false,
		!! Temporizadores:
		time_left -1,
		time_out [; self.remove_temporal_choice(); ],
 private
		!! Guarda el tema temporal.
		temporal_choice 0;


!!==============================================================================
!!	Objeto gestor que controla la lógica del sistema. Su función principal,
!!	run(), debe invocarse desde el punto de entrada *BeforeParsing()* (crear
!!	este punto de entrada si no existe):
!!
!!		[ BeforeParsing;
!!			ChoiceSetManager.run();
!!		];
!!------------------------------------------------------------------------------
Object ChoiceSetManager "(ChoiceSet Manager)"
 with	!!----------------------------------------------------------------------
		!! Retorna el valor de la propiedad 'choice_set_flag' utilizado por la
		!! acción 'CSETSelected' para determinar si debe listar o no el
		!! conjunto de elecciones activo.
		!!
		!!	@returns {boolean} Propiedad 'choice_set_flag' del objeto
		!!----------------------------------------------------------------------
		get_choice_set_flag [;
			return self.choice_set_flag;
		],
		!!----------------------------------------------------------------------
		!! Indica si el conjunto de elecciones pasado como parámetro está o no
		!! activado en el gestor. Si no se pasa ningún parámetro, indica si hay
		!! activado un conjunto de elecciones cualquiera.
		!!
		!!	@param {ChoiceSet} [choiceSet] - Si se especifica uno, la función
		!!		indica si el conjunto 'choiceSet' está activado en el gestor
		!!	@returns {boolean} Verdadero si el conjunto pasado como parámetro
		!!		está activo (si no se ha especificado uno, retorna verdadero en
		!!		caso de que haya un conjunto cualquiera activado en el gestor).
		!!		Falso en caso contrario
		!!----------------------------------------------------------------------
		is_running [ choiceSet;
			if (choiceSet ~= nothing) {
				return self.current_choice_set == choiceSet;
			} else return self.current_choice_set ~= nothing;
		],
		!!----------------------------------------------------------------------
		!! Función principal del gestor. Comprueba si la entrada de usuario se
		!! refiere a alguna de las elecciones disponibles en el conjunto
		!! activo y lanza la acción adecuada para tratarla si es así. Debe
		!! invocarse desde el punto de entrada 'BeforeParsing()'.
		!!
		!!	@returns {boolean} Falso, para que el flujo de ejecución del relato
		!!		interactivo continúe normalmente
		!!----------------------------------------------------------------------
		run [
			o o_tmp_hits;
			if (self.current_choice_set) {
				if (self.current_choice_set.has_ended()) return false;

				!! A) Inicializaciones del método:
				self.choice_set_flag = false;
				self.hits = 0;
				self.selected_choice = 0;

				!! B) Explora las elecciones del conjunto actual, comprobando
				!! si alguna encaja con la entrada de usuario:
				objectloop (o in self.current_choice_set) {
					#Ifdef DEBUG_CHOICE_SET;
					print "Probando: ", (string) o.entry, "... ";
					#Endif; ! DEBUG_CHOICE_SET;

					!! Se calcula el número de coincidencias de la elección en
					!! relación al total de palabras de la entrada (en %):
					o.compare_prompt();
					o_tmp_hits = (o.hits*100) / num_words;

					#Ifdef DEBUG_CHOICE_SET;
					print "Ajuste de ", o.hits, " sobre ",
					o.#keys / WORDSIZE, " palabras: ", o_tmp_hits, "%^";
					#Endif; ! DEBUG_CHOICE_SET;

					!! Si la elección coincide con más exactitud que la
					!! mejor provisional:
					if (o_tmp_hits > self.hits) {
						self.hits = o_tmp_hits;
						self.selected_choice = o;
					}
				}

				!! C) Si se ha seleccionado una elección, se ejecutan las
				!! acciones asociadas a ella, se elimina del conjunto (si
				!! procede), y se añaden las posibles sub-elecciones:
				if (self.hits) {
					#Ifdef DEBUG_CHOICE_SET;
					print "Tema seleccionado: ",
					(string) self.selected_choice.entry, "^";
					#Endif; ! DEBUG_CHOICE_SET;

					!! Si no es persistente, la elección queda marcada como
					!! tratada:
					if (~~(self.selected_choice.persistent)) {
						give self.selected_choice visited;
					}

					!! Acción al seleccionar la elección:
					if (self.selected_choice.reply ~= 0) {
						PrintOrRun(self.selected_choice, reply);
					}

					!! Se establece la propiedad 'choice_set_flag' del gestor
					!! en función de las propiedades de la elección:
					self.choice_set_flag
						= self.selected_choice.append_choice_set;

					!! La elección se elimina del conjunto si está agotada y
					!! se añaden todas sus sub-elecciones (si tiene alguna):
					if (self.selected_choice has visited) {
						self.current_choice_set.remove_choice(
							self.selected_choice);
					}
					self.current_choice_set.add_subchoices(
						self.selected_choice);

					!! Acción después de tratar la elección:
					if (self.selected_choice.reaction ~= 0) {
						PrintOrRun(self.selected_choice, reaction);
					}

					!! Si es un ítem final, termina la selección:
					if (self.selected_choice.final_choice) {
						self.current_choice_set.end();
					}

					!! Se modifica la entrada de usuario para que la librería
					!! lance la acción de apoyo ##CSETSelected (referenciada
					!! por el verbo de apoyo 'cset.selected'):
					parse-->1 = 'cset.selected';
					num_words = 1;
					!! A partir de este punto, la librería Inform lanzará la
					!! acción ##CSETSelected, encargada de listar el conjunto
					!! de elecciones (si es preciso).
				}
			}

			!! Retorna de la función y deja el flujo de ejecución de nuevo en
			!! manos de la librería, para que haga el tratamiento normal de la
			!! entrada del usuario:
			return false;
		],
		!!----------------------------------------------------------------------
		!! Lista el conjunto de elecciones activo.
		!!
		!!	@returns {boolean} Verdadero si el conjunto se lista correctamente.
		!!		Falso si no hay un conjunto de elecciones activo en el gestor
		!!----------------------------------------------------------------------
		show_choice_set [
			st;
			if (self.current_choice_set == 0) return false;
			#Ifdef _TYPES_;
			st = _current_style;
			#Ifnot;
			st = 0; ! Por evitar warnings del compilador
			#Endif; ! _TYPES_;
			switch (CSET_STYLE) {
			0:	!! Estilo: Romana
				#Ifdef TARGET_ZCODE;
				font on; style roman;
				#Ifnot; ! TARGET_GLULX;
				glk($0086, 0);
				#Endif;	! TARGET_
			1:	!! Estilo: Itálica
				#Ifdef	TARGET_ZCODE;
				font on; style underline;
				#Ifnot;	! TARGET_GLULX;
				glk($0086, 1);
				#Endif;	! TARGET_
			2:	!! Estilo: Negrita
				#Ifdef	TARGET_ZCODE;
				font on; style bold;
				#Ifnot;	! TARGET_GLULX;
				glk($0086, 3);
				#Endif;	! TARGET_
			3:	!! Estilo: Monoespaciada
				#Ifdef	TARGET_ZCODE;
				font off;
				#Ifnot;	! TARGET_GLULX;
				glk($0086, 2);
				#Endif;	! TARGET_
			}
			if (CSET_PREFIX ~= 0) print (string) CSET_PREFIX;
			self.current_choice_set.show_choice_set();
			if (CSET_SUFIX ~= 0) print (string) CSET_SUFIX;
			#Ifdef	TARGET_ZCODE;		!!
			font on; style roman;		!!
			#Ifnot;	! TARGET_GLULX;		!! Romana
			glk($0086, 0);				!!
			#Endif; ! TARGET_			!!
			#Ifdef _TYPES_;
			SetTextStyle(st);
			#Endif; ! _TYPES_;
			new_line;
			return true;
		],
		!!----------------------------------------------------------------------
		!! Inicia y deja activo en el gestor el conjunto de elecciones pasado
		!! como parámetro. Si además se invoca con 'no_action' verdadero, se
		!! evita la ejecución de las acciones asociadas a la activación (o
		!! reactivación) del conjunto.
		!!
		!!	@param {ChoiceSet} choice_set - Conjunto de elecciones que se
		!!		activa en el gestor
		!!	@param {boolean} [no_action=false] - Si se invoca como verdadero,
		!!		evita la ejecucción de las acciones asociadas con la activación
		!!		y reactivación del conjunto
		!!	@returns {boolean} Verdadero si el conjunto de elecciones se activa
		!!		(o reactiva) correctamente. Falso si el conjunto no es válido o
		!!		está marcado como agotado
		!!----------------------------------------------------------------------
		start [ choice_set no_action;
			!! Se comprueba que el conjunto pasado sea válido:
			if ((choice_set == 0) || ~~(choice_set ofclass ChoiceSet)) {
				#Ifdef DEBUG_CHOICE_SET;
				print "ERROR. El conjunto introducido no es válido.^";
				#Endif;
				return false;
			}
			!! Si el conjunto está agotado, se ejecuta su acción final (si hay
			!! una definida) y retorna:
			if (choice_set.has_ended()) {
				if ((choice_set.final_action ~= 0) && ~~(no_action)) {
					PrintOrRun(choice_set, final_action);
				}
				return false;
			}
			!! Si el conjunto ya está activado, ejecuta su acción de conjunto
			!! en ejecución (si hay una definida):
			if (self.is_running(choice_set)) {
				if ((choice_set.inter_action ~= 0) && ~~(no_action)) {
					PrintOrRun(choice_set, inter_action);
					new_line;
				}
			}
			!! Se ejecuta la acción inicial del conjunto (si hay una definida)
			!! y lo activa en el gestor:
			else {
				if ((choice_set.initial_action ~= 0) && ~~(no_action)) {
					PrintOrRun(choice_set, initial_action);
					new_line;
				}
				self.current_choice_set = choice_set;
			}
			!! Imprime el listado de elecciones del conjunto activo:
			self.show_choice_set();
			return true;
		],
		!!----------------------------------------------------------------------
		!! Quita del gestor el conjunto activo.
		!!
		!!	@returns {boolean} Verdadero
		!!----------------------------------------------------------------------
		stop [;
			self.current_choice_set = 0;
			return true;
		],
		!!----------------------------------------------------------------------
		!! Retorna el tamaño del conjunto de elecciones activo en el gestor.
		!!
		!!	@returns {integer} Número de elecciones del conjunto activo
		!!----------------------------------------------------------------------
		get_size [;
			if (self.is_running()) return self.current_choice_set.get_size();
			else return 0;
		],
 private
		 !! Indica si hay que mostrar el inventario de temas al terminar de
		 !! desarrollar uno de los temas de la conversación actual.
		 choice_set_flag false,
 		!! Conversación actual activa en el gestor.
 		current_choice_set 0,
		!! Número de coincidencias del tema con más coincidencias de la
		!! conversación (en tanto por 100 sobre el número de palabras clave).
		hits 0,

		!! Tema con mayor porcentaje de coincidencias hasta el momento.
		!! FIXME
		selected_choice 0,
;


!!==============================================================================
!!	Definición de la acción de apoyo (y su gramática) que se lanza si se
!!	reconoce en la entrada de usuario un intento de tratar alguna de las
!!	elecciones del conjunto activo en el gestor.
!!------------------------------------------------------------------------------
Verb	'cset.selected'
	*								-> CSETSelected
	* topic							-> CSETSelected
;

[ CSETSelectedSub;
	if (ChoiceSetManager.is_running()) {
		if (ChoiceSetManager.get_choice_set_flag()) {
			new_line;
			ChoiceSetManager.show_choice_set();
		}
	}
	return false;
];


!!------------------------------------------------------------------------------
!! FIXME
#Ifdef TEST_CHOICE_SET;
Constant Story "ChoiceSet Test";

Include "Parser";
Include "Verblib";

[ Initialise;
	location = Habitacion;
	lookmode = 2;
];

[ BeforeParsing;
	ChoiceSetManager.run();
];

Include "SpanishG.h";

Extend	'habla' replace
	* noun						-> TalkTo
	* 'a'/'con' noun			-> TalkTo
;

[ TalkToSub;
	if (noun == player) "Hablar con uno mismo es una locura.";
	if (noun hasnt animate) "Eso no podría contestarte.";
	print_ret (The) noun, " no parece", (n) noun, " interesad", (o) noun,
	" en hablar contigo.";
];

Object	Habitacion "Habitación"
 with	description
			"Hay una persona en la habitación. Teclea HABLAR CON PERSONA para
			iniciar una conversación con ella.",
 has	light;

Object	-> "persona"
 with	name 'persona' 'individuo' 'ser' 'hombre' 'pepe' 'pepito',
		react_before [;
			CSETSelected, TalkTo:
				return false;
			default:
				if (conversaction.fixed) <<TalkTo self>>;
		],
		before [;
			TalkTo:
				ChoiceSetManager.start(conversacion);
				return true;
			default:
				"Teclea HABLAR CON PERSONA para hablar con ella.";
			],
 has	animate concealed female;

ChoiceSet conversaction "(Conversación con la persona)"
 with	initial_action [;
			self.add_choice(cset_item_1);
			self.add_choice(cset_item_2);
			self.add_choice(cset_item_4);
			"---Hola.";
		],
		inter_action [;
			"El hombre te mira, curioso.";
		],
		final_action [;
			"No hay nada más que comentar.";
		];

ChoiceSetItem	cset_item_1
 with	entry	"preguntar nombre",
		keys	'preguntar' 'pregunta' 'nombre',
		reply [;
			"---Me presento,---le dices--- mi nombre es Don Pepito. ¿Puedo
			preguntarle el suyo?
			^^
			---Por supuesto Don Pepito, faltaría más. Encantado de conocerle,
			yo soy Don José. Don José Villaescusa Lacio.";
		],
		subchoices cset_item_12,
		append_choice_set true;

ChoiceSetItem	cset_item_12
 with	entry	"interesarte por sus apellidos",
		keys	'apellidos' 'apellido',
		reply [;
			"---Apellidos curiosos, ¿de dónde vienen, si me permite la
			indiscreción?
			^^
			---Se la permito, por supuesto. Se va a sorprender usted; vienen de
			mi padre, uno, y de mi madre el segundo. Curioso, ¿no es así?";
		],
		reaction [;
			!! Alternativo a utilizar la propiedad *subchoices*:
			conversacion.add_topic(cset_item_3);
		],
		append_choice_set true;

ChoiceSetItem	cset_item_2
 with	entry	"investigar en qué trabaja",
		keys	'trabaja' 'trabajo',
		reply [;
			"---¿Tendría la bondad de explicarme su trabajo?
			^^
			---Mi querido amigo, yo hago de todo, pero digamos que
			principalmente me dedico al ramo de los viajes.";
		],
		subchoices cset_item_21 cset_item_22,
		append_choice_set true;

ChoiceSetItem	cset_item_21
 with	entry	"preguntar sobre los viajes"
		keys	'viajes',
		reply [;
			"---Oh, viajes. ¡Me encanta viajar! Claro que como turista. Supongo
			que dedicarse a ello debe resultar cansado.
			^^
			---Cansado y aburrido. No imagina usted lo tedioso que es explicar
			las mismas cosas sobre la Torre Eiffel una y otra vez. Un
			auténtico tostón... perdone el exabrupto.";
		],
		append_choice_set false;

ChoiceSetItem	cset_item_22
 with	entry	"pedir que te aclare qué quiere decir con ~de todo~",
		keys	'aclarar' 'aclare' 'decir' 'todo',
		reply [;
			"---Perdone, Don José. ¿De todo? ¿A qué se refiere?
			^^
			---Oh, pues exactamente a eso, Don Pepito. Un poco a todo tipo de
			negocio; apuestas, inversiones en bolsa, compra-venta de activos,
			robo de bancos... cualquier cosa que usted imagine. ---Sonríe.
			---No ponga esa cara, hombre. Era broma, por supuesto.";
		]
		append_choice_set false;

ChoiceSetItem	cset_item_3
 with	entry	"insultarle",
		keys	'insultar' 'insulta' 'insultarle' 'insultale'
		reply [;
			"---Me parece usted un borde.
			^^
			---¿Cómo dice? Retire eso, por favor.";
		],
		append_choice_set true;

ChoiceSetItem	cset_item_31
 with	entry	"negarse",
		keys	'negarse' 'negate' 'negar' 'negarte',
		reply [;
			"---¡Jamás! Es usted un borde. ¡Un borde!
			^^
			---Amigo mío, estoy ya ha pasado de castaño oscuro. No pienso
			tolerar más insultos. Zanjo aquí nuestra conversación. Que tenga
			usted buen día.";
		],
		append_choice_set false;

ChoiceSetItem	cset_item_32
 with	entry	"retirar el insulto"
		keys	'retirar' 'retira' 'insulto',
		reply [;
			"---Discúlpeme. Reconozco que ha sido una descortesía. Y era una
			afirmación infundada, además.
			^^
			---No hay nada que disculpar. Olvidemos esta absurda disgresión
			de nuestra agradable conversación.";
		],
		append_choice_set true;

ChoiceSetItem	cset_item_4
 with	entry	"saludarle con el sombrero"
		keys	'saludar' 'saluda' 'saludarle' 'saludale' 'sombrero',
		reply [;
			"Inclinas el ala de tu sombrero en un gesto amistoso, y él te
			responde con un gesto idéntico.";
		],
		append_choice_set true,
		permanent true;

#Endif; ! TEST_CHOICE_SET;
!!------------------------------------------------------------------------------

#Endif; ! _CHOICE_SET_;

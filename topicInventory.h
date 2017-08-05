

!!==============================================================================
!!
!!	TOPIC INVENTORY
!!	Sistema de conversación con inventario de temas
!!
!!==============================================================================
!!
!!	File:			topicInventory.h
!!	Author(s):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!					Mastodon
!!	Language:		ES (Castellano)
!!	System:			Inform-INFSP 6
!!	Platform:		Z-Machine / Glulx
!!	Version:		2.1
!!	Released:		2014/06/12
!!
!!------------------------------------------------------------------------------
!!
!!	# HISTORIAL DE VERSIONES
!!
!!	2.1: 2014/06/12	Modificaciones en la propiedad *show_topic_inventory* del 
!!					objeto gestor. Nueva constante CONVERSATION_COMMA.
!!	2.0: 2014/04/03	Mejora la gestión del cambio de distintas conversaciones y 
!!					añade temas con presencia temporizada, temas relacionados 
!!					(análogos a los subtopics, pero a la inversa; se eliminan 
!!					al eliminar un tema), y otras pequeñas modificaciones. 
!!					Envuelve la rutina *CompareWord(num_word_prompt, dictword)* 
!!					entre #Ifdefs; para evitar que se incluya si ya se ha 
!!					definido previamente en algún archivo externo.
!!	1.8: 2014/02/05	Cambiado el nombre de la clase *ConversationEntry* por 
!!					*ConversationTopic* y otras pequeñas correcciones.
!!	1.7: 2014/01/29	Cambiados los nombres de las clases y pequeñas correcciones.
!!	1.4: 2013/04/13	Modificación de la propiedad *show_topic_inventory* del 
!!					objeto gestor.
!!	1.3: 2013/04/01 Añadidas nuevas propiedades a la clase *ConversationTopic* 
!!					y modificación de la rutina *NPCTalkSub()*.
!!	1.2: 2013/03/30	Añadidos a la documentación.
!!	1.1: 2013/03/30 Añadidas nuevas propiedades al objeto *ConversationManager* 
!!					y modificación de la rutina *NPCTalkSub()*.
!!	1.0: 2013/03/30	Primera versión de la extensión.
!!	0.1: 2013/03/28	Versión preliminar.
!!
!!------------------------------------------------------------------------------
!!
!!	Copyright (c) 2009, Mastodon
!!	Copyright (c) 2013, 2014, J. Francisco Martín
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
!!	*TOPIC INVENTORY* es una extensión para implementar sistemas de 
!!	conversación utilizando inventario de temas y análisis no estricto de la 
!!	entrada de usuario para el reconocimiento de patrones. Está basada en las 
!!	notas de Eric Eve sobre sistemas de conversación:
!!	<http://www.tads.org/howto/convbkg.htm>, y construida sobre la extensión 
!!	*NPC_Conversacion* v1.0 de Mastodon.
!!
!!
!!	# CONVERSACIONES CON INVENTARIO DE TEMAS
!!
!!	El sistema de conversación con invantario de temas está ideado con el 
!!	objetivo de esquivar los problemas que suelen presentar los sistemas de 
!!	conversación más habituales en los relatos interactivos; dificultades para 
!!	adivinar la palabra clave en sistemas basados en acciones ASK/TELL, 
!!	simplificación excesiva en sistemas basados en la acción TALK TO, o falta 
!!	de libertad y ruptura de la interfaz textual en sistemas de menús. 
!!
!!	Al utilizar un inventario de temas, en esencia, se presenta al usuario una 
!!	lista de temas de conversación sugeridos basándose en el conocimiento del 
!!	personaje protagonista. De esta forma, el usuario puede hacer referencia a 
!!	los temas que quiera lanzar utilizando una interfaz similar a la de los 
!!	sistemas ASK/TELL, pero sin necesidad de tener que adivinar por sí mismo la 
!!	palabra clave que lanza el tema.
!!
!!	En concreto, el sistema se presentaría de forma similar a la siguiente:
!!
!!		> hablar con Bob
!!		---Disculpe...
!!		Bob levanta la vista de su libro y se quita las gafas- ---¿Si?
!!
!!		(Puedes preguntar por la antena, hablarle sobre el faro o hablarle 
!!		del tema que nunca se acaba.)
!!
!!		> hablar sobre el faro
!!		---He pasado junto al faro esta mañana ---empiezas.
!!		Bob se pone muy nervioso de pronto. ---¿De qué estás hablando? Esa cosa 
!!		se vino abajo hace años. Después de aquel... asunto.
!!
!!		> hablar con Bob
!!		Bob simula limpiar las gafas, inquieto. 
!!
!!		(Puedes preguntar por la antena, preguntar por el asunto o hablarle 
!!		del tema que nunca se acaba.)
!!
!!		> asunto
!!		---¿A qué "asunto" te refieres?
!!		Bob se coloca las gafas y vuelve de nuevo su atención al libro, 
!!		claramente agitado. ---T-Tengo mucho trabajo que hacer. Si me 
!!		disculpas...
!!
!!		(Puedes insistir con el "asunto", preguntar por la antena o hablarle 
!!		del tema que nunca se acaba.)
!!
!!		> tema interminable
!!		---Tío, ¿dónde está mi coche?
!!		---¿Y tu coche, tío?
!!
!!		(Puedes insistir con el "asunto", preguntar por la antena o hablarle 
!!		del tema que nunca se acaba.)
!!
!!	El reconocimiento de patrones entre la entrada de usuario y las claves de 
!!	cada tema se lleva a cabo por medio de análisis no estricto; si entre todas 
!!	las palabras introducidas se reconocen claves de uno o más temas, se lanza 
!!	aquel tema con más coincidencias ignorando el resto de la entrada.
!!
!!
!!	# SOBRE LOS MENSAJES
!!
!!	El autor puede definir hasta 8 constantes para modificar los textos por 
!!	defecto de la extensión:
!!
!!	 *	TINV_STYLE: (0-3) Define el estilo con el que se imprimen los textos de 
!!		la extensión: 0-romana, 1-itálica, 2-negrita, 3-monoespaciada.
!!
!!	 *	TINV_PREFIX: Cadena de texto previa a cualquier otro mensaje.
!!
!!	 *	TINV_SUFIX: Cadena de texto posterior a cualquier otro mensaje.
!!
!!	 *	TINV_MSG1: Antecede a la lista de temas del inventario.
!!
!!	 *	TINV_MSG2: Si hay más de un tema en el inventario, se imprime entre 
!!		TINV_MSG1 y la lista de temas.
!!
!!	 *	TINV_COMMA: Separador de los temas del inventario.
!!
!!	 *	TINV_OR: Separador de los dos últimos temas del inventario.
!!
!!	 *	TINV_NO_MSG: Mensaje cuando no hay temas en el inventario.
!!
!!
!!	# UTILIZACIÓN
!!
!!	Para usar la librería únicamente hay que incluir la siguiente línea en la 
!!	rutina BeforeParsing (crearla si no existe):
!!
!!		[ BeforeParsing;
!!			ConversationManager.run();
!!		];
!!
!!
!!	# LIMITACIONES Y POSIBLES MEJORAS
!!
!!	Podría ser interesante contemplar la posibilidad de crear temas ocultos que 
!!	no aparezcan sugeridos automáticamente al imprimir el inventario de temas 
!!	disponibles.
!!
!!------------------------------------------------------------------------------
System_file;

!! Descomentar para obtener info. de depuración del controlador:
!Constant DEBUG_TOPICINVENTORY;

!! Descomentar para obtener info. de depuración de la rutina CompareWord():
!Constant DEBUG_COMPARE_WORD_ROUTINE;

!! Estilo y textos por defecto de la extensión:
Default TINV_STYLE	1; ! (0-3)
Default TINV_PREFIX	"(";
Default TINV_SUFIX	".)";
Default TINV_MSG1	"Puedes ";
Default TINV_MSG2	"escoger entre ";
Default TINV_COMMA	", ";
Default TINV_OR		" o ";
Default TINV_NO_MSG	"No hay temas que tratar";

!! Objeto de apoyo para reordenar los temas de una conversación:
Object	TopicBag "(Topic Bag)";


#Ifndef COMPARE_WORD_ROUTINE;
Constant COMPARE_WORD_ROUTINE;
!!==============================================================================
!!	Compara una palabra de la entrada del usuario con una de las palabras de 
!!	diccionario. La palabra de entrada se pasa a la función a través de 
!!	*num_word_prompt*, un número que indica el orden de la palabra en el vector 
!!	de entrada, y la palabra de diccionario se pasa a través de *dictword* 
!!	(hay que volcarla en un vector antes de hacer la comprobación).
!!
!!	Se retorna 1 si las palabras son iguales, o 0 si son diferentes.
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
#Endif; ! COMPARE_WORD_ROUTINE;


!!==============================================================================
!!	Representa un tema sobre el que se puede hablar en una conversación.
!!------------------------------------------------------------------------------

Class	ConversationTopic
 with	!! Determina el número de coincidencias entre la entrada del usuario y 
		!! el tema.
		compare_prompt [i j;
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
		!! Número de coincidencias de la entrada del usuario con el tema.
		hits 0,
		!! Descripción del tema. Es el texto que se imprime al mostrar el 
		!! inventario de temas de una conversación.
		entry 0,
		!! Palabras clave con las que el usuario puede hacer alusión al tema.
		keys 0,
		!! Rutina a ejecutar cuando se selecciona el tema.
		reply 0,
		!! Rutina a ejecutar después de tratar el tema.
		reaction 0,
		!! Vector de temas relacionados. Cuando éste se elimina, todos sus 
		!! parientes se eliminan a la vez (y se marcan además como tratados si 
		!! lo está también él).
		relatives 0,
		!! Vector de temas que se añaden a la conversación tras tratar éste.
		subtopics 0,
		!! Indica si el turno en que se trata este tema debe finalizar 
		!! mostrando el inventario de temas restantes de la conversación de la 
		!! que forma parte.
		append_topic_inventory true,
		!! Indica si el tema es persistente. Cuando el gestor trata un tema no 
		!! persistente, automáticamente le da el atributo *visited* para 
		!! marcarlo como tema tratado y luego lo elimina de la conversación.
		persistent false;

!!==============================================================================
!!	Representa una conversación con una lista de temas que pueden ser tratados 
!!	a elección del usuario. Implementa las siguientes funciones:
!!
!!	 *	add_topic(topic:ConversationTopic, temp_flag:boolean, period:integer) - 
!!		Añade un tema a la conversación (a menos que el tema pasado como 
!!		parámetro esté marcado como ya tratado). Los otros dos parámetros son 
!!		opcionales y permiten añadir temas temporales. Si se invoca con 
!!		*temp_flag* como verdadero, el tema formará parte de la conversación 
!!		únicamente durante una cantidad *period* de turnos (si no se indica un 
!!		valor, por defecto se considera periodo de 1).
!!
!!	 *	add_temporal_topic(topic:ConversationTopic, period:integer) - Invoca a 
!!		la función add_topic para añadir un tema temporal a partir de los 
!!		parámetros dados.
!!
!!	 *	add_subtopics(topic:ConversationTopic) - Añade a la conversación los 
!!		subtemas del tema pasado como parámetro (si tiene alguno).
!!
!!	 *	end() - Marca la conversación como finalizada.
!!
!!	 *	has_ended() - Indica si la conversación ha finalizado o no.
!!
!!	 *	remove_topic(topic:ConversationTopic, visited_flag:boolean) - Elimina 
!!		un tema de la conversación. Si se invoca con *visited_flag* verdadero, 
!!		además se fuerza que el tema quede marcado como tratado aunque no haya 
!!		llegado a mostrarse al jugador en realidad.
!!
!!	 *	remove_temporal_topic() - Si hay algún tema temporal en la conversación 
!!		lo elimina.
!!
!!	 *	topic_inventory_size() - Retorna el número de temas de la conversación.
!!
!!	 *	show_topic_inventory(flag:boolean) - Ordena aleatoriamente e imprime el 
!!		inventario de temas. Si se invoca con *flag* verdadero y la 
!!		conversación tiene definida la propiedad *talker*, ésta se imprime 
!!		antes de imprimir el inventario.
!!------------------------------------------------------------------------------

Class	Conversation
 with	add_topic [ topic temp_flag period;
			!! Se comprueba que el tema pasado sea válido:
			if (topic == 0) return false;
			if (~~(topic ofclass ConversationTopic)) return false;
			if (topic has visited) return false;
			!! Si es necesario se establece como tema temporal:
			if (temp_flag) {
				if (period < 1) period = 1;
				self.temporal_topic = topic;
				StopTimer(self);
				StartTimer(self, period);
			}
			!! Se añade a la conversación:
			move topic to self;
			return true;
		],
		add_temporal_topic [ topic period;
			return self.add_topic(topic, true, period);
		],
		add_subtopics [ topic i;
			if ((topic == 0) || ~~(topic provides subtopics)) return false;
			if (topic.subtopics ~= 0) {
				for (i=0 : i<(topic.#subtopics)/WORDSIZE : i++) {
					self.add_topic(topic.&subtopics-->i);
				}
			}
			return true;
		],
		end [;
			give self general;
		],
		has_ended [;
			if (self has general) return true;
			else return false;
		],
		remove_topic [ topic visited_flag obj i x;
			if (parent(topic) ~= self) return false;
			if (visited_flag) give topic visited;
			!! Se marca a los parientes del tema como tratados (si procede), y 
			!! se eliminan de la conversación (si están en ella):
			if (topic.relatives ~= 0) {
				for (i=0 : i<(topic.#relatives)/WORDSIZE : i++) {
					x = topic.&relatives-->i;
					if (topic has visited) give x visited;
					for (obj=child(self) : obj~=nothing : obj=sibling(obj)) {
						if (obj == x) {
							remove x;
							break;
						}
					}
				}
			}
			!! Se elimina el tema:
			remove topic;
			return true;
		], 
		remove_temporal_topic [;
			self.remove_topic(self.temporal_topic);
			StopTimer(self);
			self.time_left = -1;
			self.temporal_topic = 0;
		],
		topic_inventory_size [ topic size;
			topic = 0; ! para evitar un desconcertante warning del compilador
			objectloop(topic in self) size++;
			return size;
		],
		show_topic_inventory [ flag		topic size i n;
			!! XXX - Puesto que el temporizador comprueba si se deben eliminar 
			!! los temas temporales al finalizar el turno (es decir, después de 
			!! de mostrar el inventario de temas), puede ocurrir que algunos de 
			!! los temas del listado no estén en realidad disponibles. Por 
			!! ello, antes de imprimir el inventario, si procede se eliminan 
			!! los temas temporales.
			if (self.time_left == 0) self.remove_temporal_topic();

			!! Si la función se invoca con *flag* activado y la conversación 
			!! tiene el parámetro *talker* definido, se imprime:
			if ((flag) && (self.talker ~= 0)) {
				switch (metaclass(self.talker)) {
					Object:		print (The) self.talker;
					String:		print (string) self.talker;
					Routine:	indirect(self.talker);
				}
				print ": ";
			}

			!! Se calcula el número de temas de la conversación:
			size = self.topic_inventory_size();

			!! Se imprimen los mensajes previos al inventario:
			if ((size == 0) && (TINV_NO_MSG ~= 0))
				print (string) TINV_NO_MSG;
			if ((size > 0) && (TINV_MSG1 ~= 0))
				print (string) TINV_MSG1;
			if ((size > 1) && (TINV_MSG2 ~= 0))
				print (string) TINV_MSG2;

			!! Se recolocan los temas en la conversación de forma aleatoria:
			for (i=size : i>0 : i--) {
				n = random(i);
				topic = child(self);
				while (n>1) {
					topic = sibling(topic);
					n--;
				}
				move topic to TopicBag;
			}
			while (child(TopicBag)) move child(TopicBag) to self;

			!! Por último se imprime el listado de temas:
			for (topic=child(self) : topic~=nothing : topic=sibling(topic)) {
				PrintOrRun(topic, entry, true);
				if (sibling(topic) ~= nothing) {
					if (sibling(sibling(topic)) == nothing) {
						if (TINV_OR ~= 0) {
							print (string) TINV_OR;
						}
					} else {
						if (TINV_COMMA ~= 0) {
							print (string) TINV_COMMA;
						}
					}
				}
			}
			return true;
		],
		!! Permite indicar con quién se lleva a cabo la conversación. Puede ser 
		!! un objeto, un string o una rutina.
		talker 0,
		!! Acción al activar una conversación.
		initial_action 0,
		!! Acción al intentar iniciar una conversación ya activada.
		inter_action 0,
		!! Acción al intentar iniciar una conversación agotada.
		final_action 0,
		!! Temporizadores.
		time_left -1,
		time_out [; self.remove_temporal_topic(); ],
 private
		!! Guarda el tema temporal.
		temporal_topic 0;

!!==============================================================================
!!	Objeto gestor del sistema de conversación. Cuenta con el siguiente conjunto 
!!	de funciones que pueden ser utilizadas por un autor de relatos interactivos 
!!	para manejar conversaciones:
!!
!!	 *	get_topic_inventory_flag() - Retorna el valor del atributo 
!!		*inventory_flag* (booleano).
!!
!!	 *	is_running(conv:Conversation) - Retorna verdadero si la conversación 
!!		pasada como parámetro está activada en el gestor. Si no se pasan 
!!		parámetros, retorna verdadero si hay una conversación cualquiera 
!!		activada. Retorna falso en otro caso.
!!
!!	 *	run() - Función principal del gestor. Comprueba si la entrada de 
!!		usuario se refiere a alguno de los temas disponibles en la conversación 
!!		activa  y lanza la acción adecuada para tratarlo si es así. Debe 
!!		invocarse desde el punto de entrada *BeforeParsing()*.
!!
!!	 *	show_topic_inventory(flag:boolean) - Invoca la función 
!!		*show_topic_inventory(flag)* de la conversación activa para imprimir el 
!!		inventario de temas.
!!
!!	 *	start(conv:Conversation, no_action:boolean) - Inicia y deja activa en 
!!		el gestor la conversación pasada como parámetro. Si además se invoca 
!!		con *no_action* verdadero, se evita la ejecución de las acciones 
!!		previas a la activación de la conversación. Retorna verdadero si la 
!!		conversación se activa correctamente, falso si la conversación no es 
!!		válida o está marcada como finalizada.
!!
!!	 *	stop() - Quita del gestor la conversación activa.
!!
!!	 *	topic_inventory_size() - Retorna el número de temas de la conversación 
!!		activa.
!!------------------------------------------------------------------------------

Object ConversationManager "(Conversation Manager)"
 with	get_topic_inventory_flag [;
			return self.topic_inventory_flag;
		],
		is_running [ conv;
			if (conv ~= nothing) return self.current_conversation == conv;
			else return self.current_conversation ~= nothing;
		],
		run [ o o_tmp_hits;
			if (self.current_conversation) {

				!! A) Inicializaciones del método:
				self.topic_inventory_flag = false; 
				self.hits = 0;
				self.topic = 0;

				!! B) Da un repaso a los temas actuales comprobando si alguno 
				!! encaja con la entrada de usuario:
				objectloop (o in self.current_conversation) {
					#Ifdef DEBUG_TOPICINVENTORY;
					print "Probando: ", (string) o.entry, "... ";
					#Endif; ! DEBUG_TOPICINVENTORY;

					!! Se calcula el número de coincidencias del tema en 
					!! relación al total de palabras (%):
					o.compare_prompt();
					o_tmp_hits = (o.hits*100) / num_words; 
					
					#Ifdef DEBUG_TOPICINVENTORY;
					print "Ajuste de ", o.hits, " sobre ", 
					o.#keys / WORDSIZE, " palabras: ", o_tmp_hits, "%^";
					#Endif; ! DEBUG_TOPICINVENTORY;

					!! Si coincide más que el máximo actual:
					if (o_tmp_hits > self.hits) {
						self.hits = o_tmp_hits;
						self.topic = o;
					}
				}

				!! C) Si se ha seleccionado un tema, se ejecutan las acciones 
				!! del tema, se elimina de la conversación (si procede), y se 
				!! añaden los posibles subtemas:
				if (self.hits) {
					#Ifdef DEBUG_TOPICINVENTORY;
					print "Tema seleccionado: ", (string) self.topic.entry;
					new_line;
					#Endif; ! DEBUG_TOPICINVENTORY;

					!! Si no es persistente, el tema queda marcado como tratado:
					if (~~(self.topic.persistent)) give self.topic visited;

					!! Acción al tratar el tema:
					if (self.topic.reply ~= 0)
						PrintOrRun(self.topic, reply);

					!! Se establece la propiedad *topic_inventory_flag* del 
					!! gestor en función de las propiedades del tema:
					self.topic_inventory_flag
						= self.topic.append_topic_inventory;

					!! Se elimina el tema seleccionado si está agotado y se 
					!! añaden a la conversación todos sus subtemas, si los hay:
					if (self.topic has visited)
						self.current_conversation.remove_topic(self.topic);
					self.current_conversation.add_subtopics(self.topic);

					!! Acción después de tratar el tema:
					if (self.topic.reaction ~= 0)
						PrintOrRun(self.topic, reaction);

					!! Se modifica la entrada de usuario para que la librería 
					!! lance la acción de apoyo ##NPCTalk (referenciada con la 
					!! palabra clave 'npc.talk'):

					parse-->1 = 'npc.talk';
					num_words = 1;

					!! A partir de este punto, la librería lanzará la acción 
					!! ##NPCTalk, que imprimirá el inventario de temas 
					!! disponibles (si es preciso) o pondrá fin a la 
					!! conversación actual
				}
			}

			!! Retorna de la función sin hacer nada -> tratamiento normal de 
			!! la entrada del usuario:
			return false;
		],
		show_topic_inventory [ flag;
			if (self.current_conversation == 0) return false;
			switch (TINV_STYLE) {
			0:	!! Estilo: Romana
				#Ifdef _TYPES_;
				RomanStyle();
				#Ifnot;
				#Ifdef TARGET_ZCODE;
				font_on; style roman;
				#Ifnot; ! TARGET_GLULX;
				glk($0086, 0);
				#Endif;	! TARGET_
				#Endif; ! _TYPES_;
			1:	!! Estilo: Itálica
				#Ifdef _TYPES_;
				ItalicStyle();
				#Ifnot;
				#Ifdef	TARGET_ZCODE;
				font on; style underline;
				#Ifnot;	! TARGET_GLULX;
				glk($0086, 1);
				#Endif;	! TARGET_
				#Endif; ! _TYPES_;
			2:	!! Estilo: Negrita
				#Ifdef _TYPES_;
				BoldStyle();
				#Ifnot;
				#Ifdef	TARGET_ZCODE;
				font on; style bold;
				#Ifnot;	! TARGET_GLULX;
				glk($0086, 3);
				#Endif;	! TARGET_
				#Endif; ! _TYPES_;
			3:	!! Estilo: Monoespaciada
				#Ifdef _TYPES_;
				MonospacedStyle();
				#Ifnot;
				#Ifdef	TARGET_ZCODE;
				font off;
				#Ifnot;	! TARGET_GLULX;
				glk($0086, 2);
				#Endif;	! TARGET_
				#Endif; ! _TYPES_;
			}
			if (TINV_PREFIX ~= 0)
				print (string) TINV_PREFIX;
			self.current_conversation.show_topic_inventory(flag);
			if (TINV_SUFIX ~= 0)
				print (string) TINV_SUFIX;
			#Ifdef _TYPES_;				!!
			RomanStyle();				!!
			#Ifnot;						!!
			#Ifdef	TARGET_ZCODE;		!!
			font on; style roman;		!! Romana
			#Ifnot;	! TARGET_GLULX;		!!
			glk($0086, 0);				!!
			#Endif; ! TARGET_			!!
			#Endif; ! _TYPES_;			!!
			new_line;
			return true;
		],
		start [ conv no_action;
			!! Se comprueba que la conversación pasada sea válida:
			if ((conv == 0) || ~~(conv ofclass Conversation)) {
				#Ifdef DEBUG_TOPICINVENTORY;
				print "ERROR. La conversación introducida no es válida.^";
				#Endif;
				return false;
			}
			!! Si la conversación ha finalizado, ejecuta la acción de final de 
			!! conversación (si está definida) y retorna:
			if (conv.has_ended()) {
				if ((conv.final_action ~= 0) && ~~(no_action)) {
					PrintOrRun(conv, final_action);
				}
				return false;
			}
			!! Si la conversación ya está activada, ejecuta la acción de 
			!! conversación en ejecución (si está definida):
			if (self.is_running(conv)) {
				if ((conv.inter_action ~= 0) && ~~(no_action)) {
					PrintOrRun(conv, inter_action);
					new_line;
				}
			}
			!! Se ejecuta la acción de inicio de conversación (si está 
			!! definida) y activa la conversación en el gestor:
			else {
				if ((conv.initial_action ~= 0) && ~~(no_action)) {
					PrintOrRun(conv, initial_action);
					new_line;
				}
				self.current_conversation = conv;
			}
			!! Imprime el inventario de temas de la conversación activa:
			self.show_topic_inventory();
			return true;
		],
		stop [;
			self.current_conversation = 0;
			return true;
		],
		topic_inventory_size [;
			return self.current_conversation.topic_inventory_size();
		],
 private
		!! Tema con mayor porcentaje de coincidencias hasta el momento.
		topic 0,
		!! Número de coincidencias del tema con más coincidencias de la 
		!! conversación (en tanto por 100 sobre el número de palabras clave).
		hits 0, 
		!! Conversación actual activa en el gestor.
		current_conversation 0, 
		!! Indica si hay que mostrar el inventario de temas al terminar de 
		!! desarrollar uno de los temas de la conversación actual.
		topic_inventory_flag false;

!!==============================================================================
!!	Definición de la acción de apoyo (y su gramática) que se lanza si se 
!!	reconoce en la entrada de usuario un intento de seguir con alguno de los 
!!	temas de la conversación activa en el gestor.
!!------------------------------------------------------------------------------

Verb	'npc.talk'
	*								-> NPCTalk
	* topic							-> NPCTalk
;

[ NPCTalkSub;
	if (ConversationManager.is_running()) {
		if (ConversationManager.get_topic_inventory_flag()) {
			new_line;
			ConversationManager.show_topic_inventory();
		}
	}
	return false;
];



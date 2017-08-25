

!!==============================================================================
!!
!!	OPTION LIST
!!	Listados de opciones seleccionables por el usuario
!!
!!==============================================================================
!!
!!	File:			optionList.h
!!	Author(s):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!					Mastodon
!!	Language:		ES (Castellano)
!!	System:			Inform-INFSP 6
!!	Platform:		Z-Machine / GLULX
!!	Version:		1.0
!!	Release:		2014/10/01
!!
!!------------------------------------------------------------------------------
!!
!!	# HISTORIAL DE VERSIONES
!!
!!	1.0: 2014/10/01	Primera versión de la extensión, construida sobre 
!!					'topicInventory.h0 v2.1.
!!
!!------------------------------------------------------------------------------
!!
!!	Copyright (c) 2009, Mastodon
!!	Copyright (c) 2014, J. Francisco Martín
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
!!	Esta extensión a la librería 'Inform6' implementa un sistema para hacer 
!!	listados de opciones seleccionables por el usuario, utilizando análisis no 
!!	estricto de la entrada de teclado para el reconocimiento de patrones. 
!!	Permite interacciones del tipo:
!!
!!		Te detienes un momento a pensar qué hacer esta tarde...
!!		(Puedes escoger entre escribir documentación, salir a tomar algo o 
!!		ver una película.)
!!
!!		> peli
!!
!!	Está basada en las notas de Eric Eve sobre sistemas de conversación 
!!	(<http://www.tads.org/howto/convbkg.htm>), y construida a partir de la 
!!	extensión 'topicInventory' v2.1 (que, a su vez, se basaba en la extensión 
!!	'NPC_Conversacion' v1.0, de Mastodon).
!!
!!
!!	# CONVERSACIONES CON INVENTARIO DE TEMAS
!!
!!	Una de las aplicaciones más interesantes de la extensión es la creación de 
!!	conversaciones empleando INVENTARIO DE TEMAS. Este tipo de conversación 
!!	está ideado con el objetivo de esquivar los problemas que suelen presentar 
!!	los sistemas de conversación más habituales en los relatos interactivos; 
!!	dificultades para adivinar la palabra clave en sistemas basados en acciones 
!!	ASK/TELL, simplificación excesiva en sistemas basados en la acción TALK TO, 
!!	o falta de libertad y ruptura de la interfaz textual en sistemas de menús.
!!
!!	Al utilizar inventario de temas, en esencia, se presenta al usuario una 
!!	lista de temas de conversación sugeridos por el autor. De esta forma, el 
!!	usuario puede hacer referencia a los temas que quiera tratar utilizando una 
!!	interfaz similar a la de los sistemas ASK/TELL, pero sin necesidad de tener 
!!	que adivinar por sí mismo la palabra clave que lanza el tema (con lo que se 
!!	evita el famoso "síndrome de la palabra" exacta y posibles frustraciones 
!!	del usuario).
!!
!!	El sistema se presentaría de forma similar a la siguiente:
!!
!!		> hablar con Bob
!!		---Disculpe...
!!		Bob levanta la vista de su libro y se quita las gafas ---¿Si?
!!		(Puedes escoger entre preguntar por la antena, hablar sobre el faro o 
!!		hablar del tema que nunca se acaba.)
!!
!!		> hablar sobre el faro
!!		---He pasado junto al faro esta mañana ---empiezas.
!!		Bob se pone muy nervioso de pronto. ---¿De qué estás hablando? Esa cosa 
!!		se vino abajo hace años. Después de aquel... asunto.
!!
!!		> hablar con Bob
!!		Bob simula limpiar las gafas, inquieto.
!!		(Puedes escoger entre hablar del tema que nunca se acaba, preguntar por 
!!		el asunto o preguntar por la antena.)
!!
!!		> asunto
!!		---¿A qué "asunto" te refieres?
!!		Bob se coloca las gafas y vuelve de nuevo su atención al libro, 
!!		claramente agitado. ---T-tengo mucho trabajo que hacer. Si me 
!!		disculpas...
!!		(Puedes escoger entre insistir sobre el "asunto", hablar del tema que 
!!		nunca se acaba o preguntar por la antena.)
!!
!!		> tema interminable
!!		---Tío, ¿dónde está mi coche?
!!		---¿Y tu coche, tío?
!!		(Puedes escoger entre preguntar por la antena, hablar del tema que 
!!		nunca se acaba o insistir sobre el "asunto".)
!!
!!	El reconocimiento de patrones entre la entrada de usuario y los enlaces de 
!!	cada opción se lleva a cabo por medio de análisis no estricto; si entre 
!!	todas las palabras introducidas se reconocen claves de una o más opciones, 
!!	se trata aquella con más coincidencias ignorando el resto de la entrada.
!!
!!
!!	# CONFIRMACIÓN DE ACCIONES
!!
!!	Además de la creación de conversaciones utilizando inventario de temas, 
!!	otra aplicación interesante de la extensión es la CONFIRMACIÓN DE ACCIONES. 
!!	Ante una instrucción del usuario que pueda tener implicaciones importantes 
!!	en el resto de la narración, se pueden presentar dudas en el personaje y 
!!	hacer que el usuario tenga que confirmar la acción antes de llevarla a cabo 
!!	efectivamente. Por ejemplo, ante una acción que pueda provocar la muerte 
!!	del personaje:
!!
!!		> ataca al orco
!!		Miras al orco con miedo, dudando si lanzarte al ataque o no...
!!		[Si / No]
!!
!!		> si
!!		Agarras la espada y atacas al orco con todas tus fuerzas, pero la hoja 
!!		rebota contra la gruesa piel del bicho. Bosteza. Y después te mata.
!!
!!
!!	# SOBRE EL FORMATO DE LOS MENSAJES
!!
!!	El formato con el que se imprime el listado de opciones se puede modificar. 
!!	Para ello, el autor cuenta con 8 constantes diferentes que puede definir 
!!	libremente:
!!
!!	 -	OL_STYLE -- Define el estilo con el que se imprime el listado de 
!!		mensajes: 0 -> romana, 1 -> itálica, 2 -> negrita, 3 -> monoespaciada. 
!!		Por defecto tiene el valor 1.
!!
!!	 -	OL_PREFIX -- Cadena de texto que hace de prefijo a los mensajes. Por 
!!		defecto "(".
!!
!!	 -	OL_SUFIX -- Cadena de texto que hace de sufijo a los mensajes. Por 
!!		defecto ".)".
!!
!!	 -	OL_MSG1 -- Antecede a la lista de opciones de la lista. Por defecto 
!!		"Puedes ".
!!
!!	 -	OL_MSG2 -- Si hay más de una opción en la lista, se imprime entre 
!!		OL_MSG1 y la lista de opciones. Por defecto "escoger entre ".
!!
!!	 -	OL_COMMA -- Separador general de las opciones del listado. Por defecto 
!!		", ".
!!
!!	 -	OL_OR -- Separador de las dos últimas opciones del listado. Por defecto 
!!		" o ".
!!
!!	 -	OL_NO_MSG – Mensaje que se muestra cuando no hay opciones en el 
!!		listado. Por defecto es "Listado de opciones vacío".
!!
!!	Con la configuración por defecto, la extensión imprime listados de la 
!!	forma: "(Puedes escoger entre opción 1, opción 2 o opción* 3.)". A 
!!	continuación se muestra una configuración para listados de la forma: 
!!	"[Opción 1 / Opción 2 / Opción 3]":
!!
!!	OL_STYLE -> 1, OL_PREFIX -> "[", OL_SUFIX -> "]", OL_MSG1 -> "", 
!!	OL_MSG2 -> "", OL_COMMA -> " / " y OL_OR -> " / ".
!!
!!	*.- En este caso el separador debería ser 'u', puesto que la palabra 
!!	siguiente empieza igualmente por 'o'. Aunque hacer esto automáticamente 
!!	sería posible técnicamente, la manipulación de cadenas de caracteres en 
!!	Inform resulta muy engorrosa y requeriría transformar cada una de las 
!!	opciones del listado en vectores de caracteres primero, y luego realizar 
!!	las comprobaciones oportunas antes de imprimir el separador correcto. En 
!!	lugar de todo esto, se anima al autor a que procure que ninguna opción del 
!!	listado empiece por la letra 'o'. En el caso del ejemplo podría hacer: 
!!	"(Puede escoger entre LA opción 1, LA opción 2 o LA opción 3.)". O, si no, 
!!	simplemente que intente pasar por alto la pequeña errata.
!!
!!
!!	# UTILIZACIÓN
!!
!!	Para usar la extensión únicamente hay que incluir la siguiente línea en el 
!!	punto de entrada 'BeforeParsing' de la obra (crearlo si no existe):
!!
!!		[ BeforeParsing;
!!			OL_OptionListManager.run();
!!		];
!!
!!
!!	# LIMITACIONES Y POSIBLES MEJORAS
!!
!!	Podría ser interesante contemplar la posibilidad de crear opciones ocultas 
!!	('concealed') que no aparezcan sugeridas automáticamente al imprimir la 
!!	lista de opciones disponibles, pero a las que el usuario pudiese referirse 
!!	igualmente.
!!
!!------------------------------------------------------------------------------
System_file;


!! Estilo y textos por defecto de la extensión:
Default OL_STYLE	1;
Default OL_PREFIX	"(";
Default OL_SUFIX	".)";
Default OL_MSG1		"Puedes ";
Default OL_MSG2		"escoger entre ";
Default OL_COMMA	", ";
Default OL_OR		" o ";
Default OL_NO_MSG	"Listado de opciones vacío";

!! Objeto de apoyo para reordenar las opciones de un listado:
Object	OL_OptionBag "(OL: Option Bag)";


!!==============================================================================
Class	OL_Option
 with	!!----------------------------------------------------------------------
		compare_prompt [;
		],
		!!----------------------------------------------------------------------
		entry 0,
		!!----------------------------------------------------------------------
		keywords 0,
		!!----------------------------------------------------------------------
		reply 0,
		!!----------------------------------------------------------------------
		reaction 0,
		!!----------------------------------------------------------------------
		relatives 0,
		!!----------------------------------------------------------------------
		suboptions 0,
		!!----------------------------------------------------------------------
		append_option list true,
		!!----------------------------------------------------------------------
		persistent false;

!!==============================================================================
Class	OL_OptionList
 with	!!----------------------------------------------------------------------
		add_option [ opt temp_flag period;
		],
		!!----------------------------------------------------------------------
		add_temporal_option [ opt period;
			return self.add_option(opt, true, period);
		],
		!!----------------------------------------------------------------------
		add_suboptions [ opt
			i;
		],
		!!----------------------------------------------------------------------
		end [ flag;
		],
		!!----------------------------------------------------------------------
		has_ended [;
		],
		!!----------------------------------------------------------------------
		remove_option [ opt visited_flag
			obj i x;
		],
		!!----------------------------------------------------------------------
		remove_temporal_option [;
		],
		!!----------------------------------------------------------------------
		option_list_size [
			opt size;
		],
		!!----------------------------------------------------------------------
		show_option_list [ flag
			opt size i n;
		],
		!!----------------------------------------------------------------------
		trigger 0,
		!!----------------------------------------------------------------------
		initial_action 0,
		!!----------------------------------------------------------------------
		inter_action 0,
		!!----------------------------------------------------------------------
		final_action 0,
		!!----------------------------------------------------------------------
		time_left -1,
		time_out [; self.remove_temporal_option(); ],
		!!----------------------------------------------------------------------
		temporal_option 0;

!!==============================================================================
Object	OL_OptionListManager "(OL: Option List Manager)"
 with	!!----------------------------------------------------------------------
		get_avoid_impression_flag [;
			return self.avoid_impression_flag;
		],
		!!----------------------------------------------------------------------
		is_running [ list;
		],
		!!----------------------------------------------------------------------
		option_list_size [;
		],
		!!----------------------------------------------------------------------
		run [
			o o_tmp_hits;
		],
		!!----------------------------------------------------------------------
		show_option_list [ avoid_trigger;
		],
		!!----------------------------------------------------------------------
		start [ list avoid_action;
		];
		!!----------------------------------------------------------------------
		stop [;
		],
		!!----------------------------------------------------------------------
		opt 0,
		!!----------------------------------------------------------------------
		hits 0,
		!!----------------------------------------------------------------------
		current_list 0,
		!!----------------------------------------------------------------------
		avoid_list_impression_flag false;

!!==============================================================================

Verb	'ol.selected.option'
	*								-> OL_SelectedOption
	* topic							-> OL_SelectedOption
;

[ OL_SelectedOptionSub;
	if (OL_OptionListManager.is_running()) {
		if (~~(OL_OptionListManager.avoid_list_impression())) {
			new_line;
			OL_OptionListManager.show_option_list();
		}
	}
	return false;
];



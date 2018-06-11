

!!==============================================================================
!!
!!	MENSAJES DE LA LIBRERÍA EN ESPAÑOL
!!
!!==============================================================================
!!
!!	Archivo:		SpanishLM.inf
!!	Autor(es):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!	Idioma:			ES (Español)
!!	Sistema:		Inform-INFSP 6
!!	Plataforma:		Máquina-Z/Glulx
!!	Versión:		0.0
!!	Fecha:			2018/03/04
!!
!!------------------------------------------------------------------------------
!!
!!	HISTORIAL DE VERSIONES
!!
!!	0.0: 2017/08/03	Versión en desarrollo de la extensión.
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
!!	NOTAS
!!
!!	Implementa el conjunto de mensajes por defecto de la librería Inform-INFSP,
!!	incluyendo la posibilidad de modificar en tiempo de ejecución tanto el
!!	tiempo verbal (presente, pasado, futuro) y la persona (primera, segunda,
!!	tercera), como el género (masculino, femenino) el número (singular,
!!	plural) ---estos últimos, en función de la definición del objeto 'player'
!!	controlado por el usuario---. Los mensajes están basados en gran medida en
!!	los de 'Spanish.h'.
!!
!!	Incluye además una nueva meta-acción de depuración (sólo está definida
!!	si la obra se compila con la opción DEBUG activada); 'gramatica [opción]',
!!	que  permite consultar la flexión gramatical actual de los mensajes de la
!!	librería (cuando se invoca sin indicar ninguna opción), o si se especifica
!!	una opción [1-9], modifica la flexión gramatical utilizada.
!!
!!
!!	UTILIZACIÓN
!!
!!	A continuación se detallan los 3 pasos que deben seguirse para instalar la
!!	extensión:
!!
!!	1)	Declarar la constante SIN_MENSAJES para omitir los mensajes por defecto
!!		de la librería Inform (antes de incluir librerías y extensiones):
!!
!!			Constant SIN_MENSAJES;
!!
!!	2)	Declarar el siguiente conjunto de variables (antes de incluir librerías
!!		y extensiones):
!!
!!			Global FORMER__TX	= "tu antiguo ~yo~";
!!			Global YOURSELF__TX	= "ti mismo";
!!			Global CANTGO__TX	= "No puedes ir por ahí.";
!!			Global IS__TX		= " ves";
!!			Global ARE__TX		= " ves";
!!			Global IS2__TX		= "ves ";
!!			Global ARE2__TX		= "ves ";
!!			Global YOU__TX		= "Tú";
!!			Global PARTICULA_TE	= "te";
!!
!!	3)	Declarar el reemplazo de la rutina 'ChangePlayer' definida en
!!		'parserm.h' (antes de incluir librerías y extensiones):
!!
!!			Replace ChangePlayer;
!!
!!		Como se ha apuntado anteriormente, 'SpanishLM.h' utiliza un mecanismo
!!		que permite modificar la flexión gramatical de los mensajes de la
!!		librería en tiempo de ejecución ---permitiendo mensajes en primera,
!!		segunda y tercera persona; presente, pasado y futuro; singular y
!!		plurar; masculino y femenino--- en función, en parte, de los atributos
!!		del personaje controlado por el usuario. Así, al cambiar de personaje,
!!		se hace necesario actualizar el estado de la librería Inform.
!!
!!	Una vez instalada, se puede modificar la flexión gramatical utilizada en
!!	los mensajes por defecto invocando a la rutina
!!	'SetGrammaticalInflection()'. Por ejemplo, para pasar a utilizar un
!!	narrador en pasado y tercera persona:
!!
!!		SetGrammaticalInflection(THIRD_PERSON_PAST);
!!
!!------------------------------------------------------------------------------


!!------------------------------------------------------------------------------
!! Definición de constantes, variables y propiedades
!!------------------------------------------------------------------------------

Default PS1 = "^> ";

Constant FIRST_PERSON_PRESENT	= 1;
Constant SECOND_PERSON_PRESENT	= 2;
Constant THIRD_PERSON_PRESENT	= 3;
Constant FIRST_PERSON_PAST		= 4;
Constant SECOND_PERSON_PAST		= 5;
Constant THIRD_PERSON_PAST		= 6;
Constant FIRST_PERSON_FUTURE	= 7;
Constant SECOND_PERSON_FUTURE	= 8;
Constant THIRD_PERSON_FUTURE	= 9;

Global _grammatical_inflection = SECOND_PERSON_PRESENT;

!!==============================================================================
!! La propiedad 'clarification' está ideada para aquellos objetos que no son
!! localidades y que permiten al personaje controlado por el usuario (PC)
!! entrar en ellos (objetos con el atributo 'enterable'). Cuando un PJ se
!! encuentra dentro de uno de estos objetos 'enterables', al imprimir la
!! descripción de la localidad como resultado de la acción ##Look, se imprime
!! el título de la localidad con un pequeño apéndice del tipo ", en el
!! <objeto enterable>" o ", sobre el <objeto enterable>". La propiedad
!! 'clarification' permite personalizar los mensajes de este apéndice. Por
!! ejemplo, en una localidad "DORMITORIO" podemos definir un objeto 'enterable'
!! cama con la propiedad:
!!
!!		clarification "sentado en la cama",
!!
!! para conseguir títulos del tipo: "DORMITORIO, sentado en la cama", en lugar
!! del: "DORMITORIO, en la cama" por defecto.
!!------------------------------------------------------------------------------
Property clarification; ! string

!!==============================================================================
!! La propiedad 'inhibit_object_list' está ideada para ser utilizada por los
!! objetos de tipo localidad. Se se define una localidad con la propiedad
!! 'inhibit_object_list' como verdadera, al imprimir su descripción como
!! resultado de la acción ##Look se omitirá el listado automático de objetos
!! presentes en esa localidad.
!!------------------------------------------------------------------------------
Property inhibit_object_list; ! boolean


!!------------------------------------------------------------------------------
!! Funciones
!!------------------------------------------------------------------------------

!!==============================================================================
!! Imprime la construcción correcta (en forma amalgamada o no) formada por la
!! preposición 'con' y el pronombre o segmento pronominal que se corresponda
!! con la flexión gramatical del narrador y el objeto pasado como parámetro.
!!
!!	@param {Object} obj
!!------------------------------------------------------------------------------
[ contigo obj;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT,
		FIRST_PERSON_PAST,
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) {
				if (IsFemaleNoun(obj)) print "con nosotras";
				else print "con nosotros";
			} else print "conmigo";
		SECOND_PERSON_PRESENT,
		SECOND_PERSON_PAST,
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(obj)) {
				if (IsFemaleNoun(obj)) print "con vosotras";
				else print "con vosotros";
			} else print "contigo";
		THIRD_PERSON_PRESENT,
		THIRD_PERSON_PAST,
		THIRD_PERSON_FUTURE:
			if (IsPluralNoun(obj)) {
				if (IsFemaleNoun(obj)) print "con ellas";
				else print "con ellos";
			} else {
				if (IsFemaleNoun(obj)) print "con ella";
				else print "con él";
			}
	}
];

!!==============================================================================
!! Intercambia el objeto controlado por el usuario por otro objeto dado.
!!
!!	@param {Object} obj
!!	@param {boolean} [flag]
!!	@overrides parserm.h
!!------------------------------------------------------------------------------
[ ChangePlayer obj flag
	i;
	if (actor == player) actor=obj;
    give player ~transparent ~concealed;
    i = obj; while (parent(i) ~= 0) {
        if (i has animate) give i transparent;
        i = parent(i);
    }

	!! XXX - Modificación sobre la rutina original
	SetGrammaticalInflection(_grammatical_inflection, obj);
	!! XXX - Fin de la modificación

    if (player == selfobj) player.short_name = FORMER__TX;

    player = obj;

    if (player == selfobj) player.short_name = NULL;
    give player transparent concealed animate proper;
    i = player; while (parent(i) ~= 0) i = parent(i);
    location = i; real_location = location;
    if (parent(player) == 0) return RunTimeError(10);
    MoveFloatingObjects();
    lightflag = OffersLight(parent(player));
    if (lightflag == 0) location = thedark;
    print_player_flag = flag;
];


!!==============================================================================
!! Determina si un objeto está definido como nombre femenino o no. En la
!! práctica, en la extensión se considera que todos los objetos con nombre no
!! femenino ('~~IsFemaleNoun()') tienen nombre masculino ---aunque en realidad,
!! el inverso del conjunto de GNA femenino: {1, 4, 7, 10}, comprende a un
!! tiempo los conjuntos de GNA masculino: {0, 3, 6, 9}, y GNA neutro:
!! {2, 6, 8, 11}---.
!!
!!	@param {Object} obj
!!	@returns {boolean} Verdadero si el objeto está definido como nombre
!!		femenino. Falso en caso contrario
!!------------------------------------------------------------------------------
[ IsFemaleNoun obj
	result;
	if (obj provides gender) result = (obj.gender == 2 or 4);
	else result = (GetGNAOfObject(obj) == 1 or 4 or 7 or 10);
	return result;
];


!!==============================================================================
!! Determina si un objeto está definido como nombre plural o no. En la
!! práctica, en la extensión se considera que todos los objetos con nombre no
!! plural ('~~IsPluralNoun()') tienen nombre singular ---ciertamente, el
!! inverso del conjunto de GNA plural: {3, 4, 5, 9, 10, 11}, se corresponde con
!! el conjunto de GNA singular: {0, 1, 2, 6, 7, 8}---.
!!
!!	@param {Object} obj
!!	@returns {boolean} Verdadero si el objeto está definido como nombre
!!		plural. Falso en caso contrario
!!------------------------------------------------------------------------------
[ IsPluralNoun obj
	result;
	if (obj provides gender) result = (obj.gender == 3 or 4);
	else result = (GetGNAOfObject(obj) == 3 or 4 or 5 or 9 or 10 or 11);
	return result;
];


!!==============================================================================
!! Establece la flexión gramatical de los mensajes de la librería, actualizando
!! su estado. Para ello, utiliza la definición ---para determinar su género y
!! número--- de un objeto dado (si no se especifica uno, por defecto el objeto
!! 'player' controlado por el usuario).
!!
!!	@param {int} [gi=SECOND_PERSON_PRESENT] - Nueva flexión gramatical a
!!		utilizar en los mensajes de la librería. Si no se especifica un valor o
!!		el valor especificado es erróneo, se establece por defecto la segunda
!!		persona del presente: SECOND_PERSON_PRESENT.
!!	@param {Object} [obj=player] - Objeto del que se cosultan los atributos
!!		referidos a género y número utilizados para actualizar el estado de la
!!		librería.
!!------------------------------------------------------------------------------
[ SetGrammaticalInflection gi obj;
	if ((obj == 0) || (metaclass(obj) == nothing)) obj = player;
	switch (gi) {
		FIRST_PERSON_PRESENT:
			_grammatical_inflection = FIRST_PERSON_PRESENT;
			if (IsPluralNoun(obj)) {
				ARE__TX			= " vemos";
				ARE2__TX		= "vemos ";
				CANTGO__TX		= "No podemos ir por ahí.";
				IS__TX			= " vemos";
				IS2__TX			= "vemos ";
				PARTICULA_TE	= "nos";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "nuestra antigua ~yo~";
					YOU__TX			= "Nosotras";
					YOURSELF__TX	= "nosotras mismas";
				} else {
					FORMER__TX		= "nuestro antiguo ~yo~";
					YOU__TX			= "Nosotros";
					YOURSELF__TX	= "nosotros mismos";
				}
			} else {
				ARE__TX			= " veo";
				ARE2__TX		= "veo ";
				CANTGO__TX		= "No puedo ir por ahí.";
				IS__TX			= " veo";
				IS2__TX			= "veo ";
				PARTICULA_TE	= "me";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "mi antigua ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "mí misma";
				} else {
					FORMER__TX		= "mi mi antiguo ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "mí mismo";
				}
			}
		SECOND_PERSON_PRESENT:
			.defaultInflection;
			_grammatical_inflection = SECOND_PERSON_PRESENT;
			if (IsPluralNoun(obj)) {
				ARE__TX			= " veis";
				ARE2__TX		= "veis ";
				CANTGO__TX		= "No podéis ir por ahí.";
				IS__TX			= " veis";
				IS2__TX			= "veis ";
				PARTICULA_TE	= "os";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "vuestra antigua ~yo~";
					YOU__TX			= "Vosotras";
					YOURSELF__TX	= "vosotras mismas";
				} else {
					FORMER__TX		= "vuestro antiguo ~yo~";
					YOU__TX			= "Vosotros";
					YOURSELF__TX	= "vosotros mismos";
				}
			} else {
				ARE__TX			= " ves";
				ARE2__TX		= "ves ";
				CANTGO__TX		= "No puedes ir por ahí.";
				IS__TX			= " ves";
				IS2__TX			= "ves ";
				PARTICULA_TE	= "te";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "tu antigua ~yo~";
					YOU__TX			= "Tú";
					YOURSELF__TX	= "tí misma";
				} else {
					FORMER__TX		= "tu antiguo ~yo~";
					YOU__TX			= "Tú";
					YOURSELF__TX	= "tí mismo";
				}
			}
		THIRD_PERSON_PRESENT:
			_grammatical_inflection = THIRD_PERSON_PRESENT;
			if (IsPluralNoun(obj)) {
				ARE__TX			= " ven";
				ARE2__TX		= "ven ";
				CANTGO__TX		= "No pueden ir por ahí.";
				IS__TX			= " ven";
				IS2__TX			= "ven ";
				PARTICULA_TE	= "se";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "su antigua ~yo~";
					YOU__TX			= "Ellas";
					YOURSELF__TX	= "ellas mismas";
				} else {
					FORMER__TX		= "su antiguo ~yo~";
					YOU__TX			= "Ellos";
					YOURSELF__TX	= "ellos mismos";
				}
			} else {
				ARE__TX			= " ve";
				ARE2__TX		= "ve ";
				CANTGO__TX		= "No puede ir por ahí.";
				IS__TX			= " ve";
				IS2__TX			= "ve ";
				PARTICULA_TE	= "se";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "su antigua ~yo~";
					YOU__TX			= "Ella";
					YOURSELF__TX	= "sí misma";
				} else {
					FORMER__TX		= "su antiguo ~yo~";
					YOU__TX			= "Él";
					YOURSELF__TX	= "sí mismo";
				}
			}
		FIRST_PERSON_PAST:
			_grammatical_inflection = FIRST_PERSON_PAST;
			if (IsPluralNoun(obj)) {
				ARE__TX			= " veíamos";
				ARE2__TX		= "veíamos ";
				CANTGO__TX		= "No podíamos ir por ahí.";
				IS__TX			= " veíamos";
				IS2__TX			= "veíamos ";
				PARTICULA_TE	= "nos";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "nuestra antigua ~yo~";
					YOU__TX			= "Nosotras";
					YOURSELF__TX	= "nosotras mismas";
				} else {
					FORMER__TX		= "nuestro antiguo ~yo~";
					YOU__TX			= "Nosotros";
					YOURSELF__TX	= "nosotros mismos";
				}
			} else {
				ARE__TX			= " veía";
				ARE2__TX		= "veía ";
				CANTGO__TX		= "No podía ir por ahí.";
				IS__TX			= " veía";
				IS2__TX			= "veía ";
				PARTICULA_TE	= "me";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "mi antigua ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "mí misma";
				} else {
					FORMER__TX		= "mi antiguo ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "mí mismo";
				}
			}
		SECOND_PERSON_PAST:
			_grammatical_inflection = SECOND_PERSON_PAST;
			if (IsPluralNoun(obj)) {
				ARE__TX			= " veíais";
				ARE2__TX		= "veíais ";
				CANTGO__TX		= "No podíais ir por ahí.";
				IS__TX			= " veíais";
				IS2__TX			= "veíais ";
				PARTICULA_TE	= "os";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "vuestra antigua ~yo~";
					YOU__TX			= "Vosotras";
					YOURSELF__TX	= "vosotras mismas";
				} else {
					FORMER__TX		= "vuestro antiguo ~yo~";
					YOU__TX			= "Vosotros";
					YOURSELF__TX	= "vosotros mismos";
				}
			} else {
				ARE__TX			= " veías";
				ARE2__TX		= "veías ";
				CANTGO__TX		= "No podías ir por ahí.";
				IS__TX			= " veías";
				IS2__TX			= "veías ";
				PARTICULA_TE	= "te";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "tu antigua ~yo~";
					YOU__TX			= "Tú";
					YOURSELF__TX	= "tí misma";
				} else {
					FORMER__TX		= "tu antiguo ~yo~";
					YOU__TX			= "Tú";
					YOURSELF__TX	= "tí mismo";
				}
			}
		THIRD_PERSON_PAST:
			_grammatical_inflection = THIRD_PERSON_PAST;
			if (IsPluralNoun(obj)) {
				ARE__TX			= " veían";
				ARE2__TX		= "veían ";
				CANTGO__TX		= "No podían ir por ahí.";
				IS__TX			= " veían";
				IS2__TX			= "veían ";
				PARTICULA_TE	= "se";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "su antigua ~yo~";
					YOU__TX			= "Ellas";
					YOURSELF__TX	= "ellas mismas";
				} else {
					FORMER__TX		= "su antiguo ~yo~";
					YOU__TX			= "Ellos";
					YOURSELF__TX	= "ellos mismos";
				}
			} else {
				ARE__TX			= " veía";
				ARE2__TX		= "veía ";
				CANTGO__TX		= "No podía ir por ahí.";
				IS__TX			= " veía";
				IS2__TX			= "veía ";
				PARTICULA_TE	= "se";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "su antigua ~yo~";
					YOU__TX			= "Ella";
					YOURSELF__TX	= "sí misma";
				} else {
					FORMER__TX		= "su antiguo ~yo~";
					YOU__TX			= "Él";
					YOURSELF__TX	= "sí mismo";
				}
			}
		FIRST_PERSON_FUTURE:
			_grammatical_inflection = FIRST_PERSON_FUTURE;
			if (IsPluralNoun(obj)) {
				ARE__TX			= " veremos";
				ARE2__TX		= "veremos ";
				CANTGO__TX		= "No podremos ir por ahí.";
				IS__TX			= " veremos";
				IS2__TX			= "veremos ";
				PARTICULA_TE	= "nos";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "nuestra antigua ~yo~";
					YOU__TX			= "Nosotras";
					YOURSELF__TX	= "nosotras mismas";
				} else {
					FORMER__TX		= "nuestro antiguo ~yo~";
					YOU__TX			= "Nosotros";
					YOURSELF__TX	= "nosotros mismos";
				}
			} else {
				ARE__TX			= " veré";
				ARE2__TX		= "veré ";
				CANTGO__TX		= "No podré ir por ahí.";
				IS__TX			= " veré";
				IS2__TX			= "veré ";
				PARTICULA_TE	= "me";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "mi antigua ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "mí misma";
				} else {
					FORMER__TX		= "mi antiguo ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "mí mismo";
				}
			}
		SECOND_PERSON_FUTURE:
			_grammatical_inflection = SECOND_PERSON_FUTURE;
			if (IsPluralNoun(obj)) {
				ARE__TX			= " veréis";
				ARE2__TX		= "veréis ";
				CANTGO__TX		= "No podréis ir por ahí.";
				IS__TX			= " veréis";
				IS2__TX			= "veréis ";
				PARTICULA_TE	= "os";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "vuestra antigua ~yo~";
					YOU__TX			= "Vosotras";
					YOURSELF__TX	= "vosotras mismas";
				} else {
					FORMER__TX		= "vuestro antiguo ~yo~";
					YOU__TX			= "Vosotros";
					YOURSELF__TX	= "vosotros mismos";
				}
			} else {
				ARE__TX				= " verás";
				ARE2__TX			= "verás ";
				CANTGO__TX			= "No podrás ir por ahí.";
				IS__TX				= " verás";
				IS2__TX				= "verás ";
				PARTICULA_TE		= "te";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "tu antigua ~yo~";
					YOU__TX			= "Tú";
					YOURSELF__TX	= "tí misma";
				} else {
					FORMER__TX		= "tu antiguo ~yo~";
					YOU__TX			= "Tú";
					YOURSELF__TX	= "tí mismo";
				}
			}
		THIRD_PERSON_FUTURE:
			_grammatical_inflection = THIRD_PERSON_FUTURE;
			if (IsPluralNoun(obj)) {
				ARE__TX			= " verán";
				ARE2__TX		= "verán ";
				CANTGO__TX		= "No podrán ir por ahí.";
				IS__TX			= " verán";
				IS2__TX			= "verán ";
				PARTICULA_TE	= "se";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "su antigua ~yo~";
					YOU__TX			= "Ellas";
					YOURSELF__TX	= "ellas mismas";
				} else {
					FORMER__TX		= "su antiguo ~yo~";
					YOU__TX			= "Ellos";
					YOURSELF__TX	= "ellos mismos";
				}
			} else {
				ARE__TX			= " verá";
				ARE2__TX		= "verá ";
				CANTGO__TX		= "No podrá ir por ahí.";
				IS__TX			= " verá";
				IS2__TX			= "verá ";
				PARTICULA_TE	= "se";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "su antigua ~yo~";
					YOU__TX			= "Ella";
					YOURSELF__TX	= "sí misma";
				} else {
					FORMER__TX		= "su antiguo ~yo~";
					YOU__TX			= "Él";
					YOURSELF__TX	= "sí mismo";
				}
			}
		default:
			jump defaultInflection;
	}
	ChangeDefault(cant_go, CANTGO__TX);
];

#Ifdef	DEBUG;
Verb	meta 'gramatica' 'grammar'
	*								-> Grammar
	* number						-> Grammar
;

[ GrammarSub;
	switch (noun) {
		1:	SetGrammaticalInflection(FIRST_PERSON_PRESENT);
		2:	SetGrammaticalInflection(SECOND_PERSON_PRESENT);
		3:	SetGrammaticalInflection(THIRD_PERSON_PRESENT);
		4:	SetGrammaticalInflection(FIRST_PERSON_PAST);
		5:	SetGrammaticalInflection(SECOND_PERSON_PAST);
		6:	SetGrammaticalInflection(THIRD_PERSON_PAST);
		7:	SetGrammaticalInflection(FIRST_PERSON_FUTURE);
		8:	SetGrammaticalInflection(SECOND_PERSON_FUTURE);
		9:	SetGrammaticalInflection(THIRD_PERSON_FUTURE);
		default:
			"Flexión gramatical actual: ", _grammatical_inflection,
			"^ARE__TX: ", (string) ARE__TX,
			"^ARE2__TX: ", (string) ARE2__TX,
			"^CANTGO__TX: ", (string) CANTGO__TX,
			"^IS__TX: ", (string) IS__TX,
			"^IS2__TX: ", (string) IS2__TX,
			"^PARTICULA_TE: ", (string) PARTICULA_TE,
			"^FORMER__TX: ", (string) FORMER__TX,
			"^YOU__TX: ", (string) YOU__TX,
			"^YOURSELF__TX: ", (string) YOURSELF__TX;
	}
	print "Cambio de flexión gramatical: ";
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			print "(1) presente 1a persona";
		SECOND_PERSON_PRESENT:
			print "(2) presente 2a persona";
		THIRD_PERSON_PRESENT:
			print "(3) presente 3a persona";
		FIRST_PERSON_PAST:
			print "(4) pasado 1a persona";
		SECOND_PERSON_PAST:
			print "(5) pasado 2a persona";
		THIRD_PERSON_PAST:
			print "(6) pasado 3a persona";
		FIRST_PERSON_FUTURE:
			print "(7) futuro 1a persona";
		SECOND_PERSON_FUTURE:
			print "(8) futuro 2a persona";
		THIRD_PERSON_FUTURE:
			print "(9) futuro 3a persona";
	}
	".";
];
#Endif; ! DEBUG;




Include "sp1present.h";
Include "sp2present.h";
Include "sp3present.h";
Include "sp1past.h";
Include "sp2past.h";
Include "sp3past.h";
Include "sp1future.h";
Include "sp2future.h";
Include "sp3future.h";

!!==============================================================================
[ LanguageLM n x1;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			FirstPersonPresent_ES(n, x1);
		SECOND_PERSON_PRESENT:
			SecondPersonPresent_ES(n, x1);
		THIRD_PERSON_PRESENT:
			ThirdPersonPresent_ES(n, x1);
		FIRST_PERSON_PAST:
			FirstPersonPast_ES(n, x1);
		SECOND_PERSON_PAST:
			SecondPersonPast_ES(n, x1);
		THIRD_PERSON_PAST:
			!! Librería de mensajes principal. Es la única librería completa,
			!! el resto de librerías la invocan para reutilizar algunos de sus
			!! mensajes:
			ThirdPersonPast_ES(n, x1);
		FIRST_PERSON_FUTURE:
			FirstPersonFuture_ES(n, x1);
		SECOND_PERSON_FUTURE:
			SecondPersonFuture_ES(n, x1);
		THIRD_PERSON_FUTURE:
			ThirdPersonFuture_ES(n, x1);
	}
];



!!==============================================================================
!!
!!	MENSAJES DE LA LIBRERÍA EN ESPAÑOL
!!
!!==============================================================================
!!
!!	File:			SpanishLM.inf
!!	Author(s):		INFSP Task Team
!!					J. Francisco Martín <jfm.lisaso@gmail.com>
!!	Language:		ES (Castellano)
!!	System:			Inform-INFSP 6
!!	Platform:		Máquina-Z / GLULX
!!	Version:		0.0
!!	Released:		2017/08/03
!!
!!------------------------------------------------------------------------------
!!
!!	# HISTORIAL DE VERSIONES
!!
!!	0.0: 2017/08/03	Versión en desarrollo de la extensión.
!!
!!------------------------------------------------------------------------------
!!
!!	Copyright (c) 2017, J. Francisco Martín
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
!!	# UTILIZACIÓN
!!
!!	A continuación se detallan los pasos que deben seguirse para usar la
!!	librería.
!!
!!	1)	Declarar la constante SIN_MENSAJES para omitir los mensajes por defecto
!!		de la librería Inform:
!!
!!		Constant SIN_MENSAJES; ! (antes de incluir librerías y extensiones)
!!
!!	2)	Declarar el reemplazo de la rutina *ChangePlayer* definida en
!!		*parserm.h*. *SpanishLM.h* utiliza un mecanismo que permite modificar
!!		la flexión gramatical de los mensajes de la librería en tiempo de
!!		ejecución ---permitiendo mensajes en primera, segunda y tercera
!!		persona; presente, pasado y futuro; singular y plurar; masculino y
!!		femenino--- en función, en parte, de los atributos del personaje
!!		controlado por el usuario. Así, al cambiar de personaje, se hace
!!		necesario actualizar el estado de la librería Inform.
!!
!!		Replace ChangePlayer; ! (antes de incluir librerías y extensiones)
!!
!!------------------------------------------------------------------------------


!!------------------------------------------------------------------------------
!! Definición de constantes y variables
!!------------------------------------------------------------------------------

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


!!------------------------------------------------------------------------------
!! Funciones
!!------------------------------------------------------------------------------

!!==============================================================================
!! Intercambia el objeto controlado por el usuario por otro objeto dado.
!! (Basado en *parserm.h*)
!!
!!	@param {Object} obj
!!	@param {boolean} [flag]
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
!! Establece la flexión gramatical de los mensajes de la librería, actualizando
!! su estado. Para ello, utiliza los atributos ---aquellos referidos al género
!! y número--- de un objeto dado (si no se especifica uno, por defecto el
!! objeto controlado por el usuario).
!!
!!	@param {int} [gi=SECOND_PERSON_PRESENT] - Nueva flexión gramatical a
!!		utilizar en los mensajes de la librería. Si no se especifica un valor o
!!		el valor especificado es erróneo, se establece por defecto la segunda
!!		persona del presente: SECOND_PERSON_PRESENT.
!!	@param {Object} [obj=player] - Objeto del que se cosultan los atributos
!!		referidos a género y número utilizados para actualizar el estado de la
!!		librería.
!!------------------------------------------------------------------------------
[ IsSingularNoun obj;
	return (GetGNAOfObject(obj) == 0 or 1 or 2 or 6 or 7 or 8);
];
[ IsMaleNoun obj;
	return (GetGNAOfObject(obj) == 0 or 3 or 6 or 9);
];
[ SetGrammaticalInflection gi obj;
	if ((obj == 0) || (metaclass(obj) == nothing)) obj = player;
	switch (gi) {
		FIRST_PERSON_PRESENT:
			_grammatical_inflection = FIRST_PERSON_PRESENT;
			if (IsSingularNoun(player)) {
				ARE__TX			= " veo";
				ARE2__TX		= "veo ";
				CANTGO__TX		= "No puedo ir por ahí.";
				IS__TX			= " veo";
				IS2__TX			= "veo ";
				PARTICULA_TE	= "me";
				if (IsMaleNoun(player)) {
					FORMER__TX		= "mi antiguo ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "mí mismo";
				} else {
					FORMER__TX		= "mi antigua ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "mí misma";
				}
			} else {
				ARE__TX			= " vemos";
				ARE2__TX		= "vemos ";
				CANTGO__TX		= "No podemos ir por ahí.";
				IS__TX			= " vemos";
				IS2__TX			= "vemos ";
				PARTICULA_TE	= "nos";
				if (IsMaleNoun(player)) {
					FORMER__TX		= "nuestro antiguo ~yo~";
					YOU__TX			= "Nosotros";
					YOURSELF__TX	= "nosotros mismos";
				} else {
					FORMER__TX		= "nuestra antigua ~yo~";
					YOU__TX			= "Nosotras";
					YOURSELF__TX	= "nosotras mismas";
				}
			}
		SECOND_PERSON_PRESENT:
			.defaultInflection;
			_grammatical_inflection = SECOND_PERSON_PRESENT;
			if (IsSingularNoun(obj)) {
				ARE__TX			= " ves";
				ARE2__TX		= "ves ";
				CANTGO__TX		= "No puedes ir por ahí.";
				IS__TX			= " ves";
				IS2__TX			= "ves ";
				PARTICULA_TE	= "te";
				if (IsMaleNoun(obj)) {
					FORMER__TX		= "tu antiguo ~yo~";
					YOU__TX			= "Tú";
					YOURSELF__TX	= "tí mismo";
				} else {
					FORMER__TX		= "tu antigua ~yo~";
					YOU__TX			= "Tú";
					YOURSELF__TX	= "tí misma";
				}
			} else {
				ARE__TX			= " veis";
				ARE2__TX		= "veis ";
				CANTGO__TX		= "No podéis ir por ahí.";
				IS__TX			= " veis";
				IS2__TX			= "veis ";
				PARTICULA_TE	= "os";
				if (IsMaleNoun(obj)) {
					FORMER__TX		= "vuestro antiguo ~yo~";
					YOU__TX			= "Vosotros";
					YOURSELF__TX	= "vosotros mismos";
				} else {
					FORMER__TX		= "vuestra antigua ~yo~";
					YOU__TX			= "Vosotras";
					YOURSELF__TX	= "vosotras mismas";
				}
			}
		THIRD_PERSON_PRESENT:
			_grammatical_inflection = THIRD_PERSON_PRESENT;
			if (IsSingularNoun(obj)) {
				ARE__TX			= " ve";
				ARE2__TX		= "ve ";
				CANTGO__TX		= "No puede ir por ahí.";
				IS__TX			= " ve";
				IS2__TX			= "ve ";
				PARTICULA_TE	= "se";
				if (IsMaleNoun(obj)) {
					FORMER__TX		= "su antiguo ~yo~";
					YOU__TX			= "Él";
					YOURSELF__TX	= "sí mismo";
				} else {
					FORMER__TX		= "su antigua ~yo~";
					YOU__TX			= "Ella";
					YOURSELF__TX	= "sí misma";
				}
			} else {
				ARE__TX			= " ven";
				ARE2__TX		= "ven ";
				CANTGO__TX		= "No pueden ir por ahí.";
				IS__TX			= " ven";
				IS2__TX			= "ven ";
				PARTICULA_TE	= "se";
				if (IsMaleNoun(obj)) {
					FORMER__TX		= "su antiguo ~yo~";
					YOU__TX			= "Ellos";
					YOURSELF__TX	= "ellos mismos";
				} else {
					FORMER__TX		= "su antigua ~yo~";
					YOU__TX			= "Ellas";
					YOURSELF__TX	= "ellas mismas";
				}
			}
		FIRST_PERSON_PAST:
			_grammatical_inflection = FIRST_PERSON_PAST;
			if (IsSingularNoun(obj)) {
				ARE__TX			= " veía";
				ARE2__TX		= "veía ";
				CANTGO__TX		= "No podía ir por ahí.";
				IS__TX			= " veía";
				IS2__TX			= "veía ";
				PARTICULA_TE	= "me";
				if (IsMaleNoun(obj)) {
					FORMER__TX		= "mi antiguo ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "mí mismo";
				} else {
					FORMER__TX		= "mi antigua ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "mí misma";
				}
			} else {
				ARE__TX			= " veíamos";
				ARE2__TX		= "veíamos ";
				CANTGO__TX		= "No podíamos ir por ahí.";
				IS__TX			= " veíamos";
				IS2__TX			= "veíamos ";
				PARTICULA_TE	= "nos";
				if (IsMaleNoun(obj)) {
					FORMER__TX		= "nuestro antiguo ~yo~";
					YOU__TX			= "Nosotros";
					YOURSELF__TX	= "nosotros mismos";
				} else {
					FORMER__TX		= "nuestra antigua ~yo~";
					YOU__TX			= "Nosotras";
					YOURSELF__TX	= "nosotras mismas";
				}
			}
		SECOND_PERSON_PAST:
			_grammatical_inflection = SECOND_PERSON_PAST;
			if (IsSingularNoun(obj)) {
				ARE__TX			= " veías";
				ARE2__TX		= "veías ";
				CANTGO__TX		= "No podías ir por ahí.";
				IS__TX			= " veías";
				IS2__TX			= "veías ";
				PARTICULA_TE	= "te";
				if (IsMaleNoun(obj)) {
					FORMER__TX		= "tu antiguo ~yo~";
					YOU__TX			= "Tú";
					YOURSELF__TX	= "tí mismo";
				} else {
					FORMER__TX		= "tu antigua ~yo~";
					YOU__TX			= "Tú";
					YOURSELF__TX	= "tí misma";
				}
			} else {
				ARE__TX			= " veíais";
				ARE2__TX		= "veíais ";
				CANTGO__TX		= "No podíais ir por ahí.";
				IS__TX			= " veíais";
				IS2__TX			= "veíais ";
				PARTICULA_TE	= "os";
				if (IsMaleNoun(obj)) {
					FORMER__TX		= "vuestro antiguo ~yo~";
					YOU__TX			= "Vosotros";
					YOURSELF__TX	= "vosotros mismos";
				} else {
					FORMER__TX		= "vuestra antigua ~yo~";
					YOU__TX			= "Vosotras";
					YOURSELF__TX	= "vosotras mismas";
				}
			}
		THIRD_PERSON_PAST:
			_grammatical_inflection = THIRD_PERSON_PAST;
			if (IsSingularNoun(obj)) {
				ARE__TX			= " veía";
				ARE2__TX		= "veía ";
				CANTGO__TX		= "No podía ir por ahí.";
				IS__TX			= " veía";
				IS2__TX			= "veía ";
				PARTICULA_TE	= "se";
				if (IsMaleNoun(obj)) {
					FORMER__TX		= "su antiguo ~yo~";
					YOU__TX			= "Él";
					YOURSELF__TX	= "sí mismo";
				} else {
					FORMER__TX		= "su antigua ~yo~";
					YOU__TX			= "Ella";
					YOURSELF__TX	= "sí misma";
				}
			} else {
				ARE__TX			= " veían";
				ARE2__TX		= "veían ";
				CANTGO__TX		= "No podían ir por ahí.";
				IS__TX			= " veían";
				IS2__TX			= "veían ";
				PARTICULA_TE	= "se";
				if (IsMaleNoun(obj)) {
					FORMER__TX		= "su antiguo ~yo~";
					YOU__TX			= "Ellos";
					YOURSELF__TX	= "ellos mismos";
				} else {
					FORMER__TX		= "su antigua ~yo~";
					YOU__TX			= "Ellas";
					YOURSELF__TX	= "ellas mismas";
				}
			}
		FIRST_PERSON_FUTURE:
			_grammatical_inflection = FIRST_PERSON_FUTURE;
			if (IsSingularNoun(obj)) {
				ARE__TX			= " veré";
				ARE2__TX		= "veré ";
				CANTGO__TX		= "No podré ir por ahí.";
				IS__TX			= " veré";
				IS2__TX			= "veré ";
				PARTICULA_TE	= "me";
				if (IsMaleNoun(obj)) {
					FORMER__TX		= "mi antiguo ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "mí mismo";
				} else {
					FORMER__TX		= "mi antigua ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "mí misma";
				}
			} else {
				ARE__TX			= " veremos";
				ARE2__TX		= "veremos ";
				CANTGO__TX		= "No podremos ir por ahí.";
				IS__TX			= " veremos";
				IS2__TX			= "veremos ";
				PARTICULA_TE	= "nos";
				if (IsMaleNoun(obj)) {
					FORMER__TX		= "nuestro antiguo ~yo~";
					YOU__TX			= "Nosotros";
					YOURSELF__TX	= "nosotros mismos";
				} else {
					FORMER__TX		= "nuestra antigua ~yo~";
					YOU__TX			= "Nosotras";
					YOURSELF__TX	= "nosotras mismas";
				}
			}
		SECOND_PERSON_FUTURE:
			_grammatical_inflection = SECOND_PERSON_FUTURE;
			if (IsSingularNoun(obj)) {
				ARE__TX				= " verás";
				ARE2__TX			= "verás ";
				CANTGO__TX			= "No podrás ir por ahí.";
				IS__TX				= " verás";
				IS2__TX				= "verás ";
				PARTICULA_TE		= "te";
				if (IsMaleNoun(obj)) {
					FORMER__TX		= "tu antiguo ~yo~";
					YOU__TX			= "Tú";
					YOURSELF__TX	= "tí mismo";
				} else {
					FORMER__TX		= "tu antigua ~yo~";
					YOU__TX			= "Tú";
					YOURSELF__TX	= "tí misma";
				}
			} else {
				ARE__TX			= " veréis";
				ARE2__TX		= "veréis ";
				CANTGO__TX		= "No podréis ir por ahí.";
				IS__TX			= " veréis";
				IS2__TX			= "veréis ";
				PARTICULA_TE	= "os";
				if (IsMaleNoun(obj)) {
					FORMER__TX		= "vuestro antiguo ~yo~";
					YOU__TX			= "Vosotros";
					YOURSELF__TX	= "vosotros mismos";
				} else {
					FORMER__TX		= "vuestra antigua ~yo~";
					YOU__TX			= "Vosotras";
					YOURSELF__TX	= "vosotras mismas";
				}
			}
		THIRD_PERSON_FUTURE:
			_grammatical_inflection = THIRD_PERSON_FUTURE;
			if (IsSingularNoun(obj)) {
				ARE__TX			= " verá";
				ARE2__TX		= "verá ";
				CANTGO__TX		= "No podrá ir por ahí.";
				IS__TX			= " verá";
				IS2__TX			= "verá ";
				PARTICULA_TE	= "se";
				if (IsMaleNoun(obj)) {
					FORMER__TX		= "su antiguo ~yo~";
					YOU__TX			= "Él";
					YOURSELF__TX	= "sí mismo";
				} else {
					FORMER__TX		= "su antigua ~yo~";
					YOU__TX			= "Ella";
					YOURSELF__TX	= "sí misma";
				}
			} else {
				ARE__TX			= " verán";
				ARE2__TX		= "verán ";
				CANTGO__TX		= "No podrán ir por ahí.";
				IS__TX			= " verán";
				IS2__TX			= "verán ";
				PARTICULA_TE	= "se";
				if (IsMaleNoun(obj)) {
					FORMER__TX		= "su antiguo ~yo~";
					YOU__TX			= "Ellos";
					YOURSELF__TX	= "ellos mismos";
				} else {
					FORMER__TX		= "su antigua ~yo~";
					YOU__TX			= "Ellas";
					YOURSELF__TX	= "ellas mismas";
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
	* number						-> Grammar;
[ GrammarSub;
	switch (noun) {
		1:	SetGrammaticalInflection(FIRST_PERSON_PRESENT);
			print "Cambio de flexión gramatical: ";
		2:	SetGrammaticalInflection(SECOND_PERSON_PRESENT);
			print "Cambio de flexión gramatical: ";
		3:	SetGrammaticalInflection(THIRD_PERSON_PRESENT);
			print "Cambio de flexión gramatical: ";
		4:	SetGrammaticalInflection(FIRST_PERSON_PAST);
			print "Cambio de flexión gramatical: ";
		5:	SetGrammaticalInflection(SECOND_PERSON_PAST);
			print "Cambio de flexión gramatical: ";
		6:	SetGrammaticalInflection(THIRD_PERSON_PAST);
			print "Cambio de flexión gramatical: ";
		default:
			print "Flexión gramatical actual: ";
	}
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:	print "(1) presente 1a persona";
		SECOND_PERSON_PRESENT:	print "(2) presente 2a persona";
		THIRD_PERSON_PRESENT:	print "(3) presente 3a persona";
		FIRST_PERSON_PAST:		print "(4) pasado 1a persona";
		SECOND_PERSON_PAST:		print "(5) pasado 2a persona";
		THIRD_PERSON_PAST:		print "(6) pasado 3a persona";
	}
	".";
];
#Endif; ! DEBUG;


!!==============================================================================
[ LanguageLM n x1
	gna;

	Answer, Ask, AskFor:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT, SECOND_PERSON_PRESENT, THIRD_PERSON_PRESENT:
				"No hay respuesta.";
			FIRST_PERSON_PAST, SECOND_PERSON_PAST, THIRD_PERSON_PAST:
				"No había respuesta.";
			FIRST_PERSON_FUTURE, SECOND_PERSON_FUTURE, THIRD_PERSON_FUTURE:
				"No habrá respuesta.";
		}

!!	Ask:	see Answer
!!	AskFor:	see Answer

	Attack:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT, SECOND_PERSON_PRESENT, THIRD_PERSON_PRESENT:
				print "es";
			FIRST_PERSON_PAST, SECOND_PERSON_PAST, THIRD_PERSON_PAST:
				print "era";
			FIRST_PERSON_FUTURE, SECOND_PERSON_FUTURE, THIRD_PERSON_FUTURE:
				print "será";
		}
		" necesario emprenderla a golpes con ", (the) x1, ".";

	Blow:
		gna = GetGNAOfObject(player, true);
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				switch (gna) {
					0,1,6,7: print "Mi";
					3,4,9,10: print "Nuestro";
				}
				print " soplido no produce";
			SECOND_PERSON_PRESENT:
				switch (gna) {
					0,1,6,7: print "Tú";
					3,4,9,10: print "Vuestro";
				}
				print " soplido no produce";
			THIRD_PERSON_PRESENT:
				print "Su soplido no produce";
			FIRST_PERSON_PAST:
				switch (gna) {
					0,1,6,7: print "Mi";
					3,4,9,10: print "Nuestro";
				}
				print " soplido no produjo";
			SECOND_PERSON_PAST:
				switch (gna) {
					0,1,6,7: print "Tu";
					3,4,9,10: print "Vuestro";
				}
				print " soplido no produjo";
			THIRD_PERSON_PAST:
				print "Su soplido no produjo";
			FIRST_PERSON_FUTURE:
				switch (gna) {
					0,1,6,7: print "Mi";
					3,4,9,10: print "Nuestro";
				}
				print " soplido no producirá";
			SECOND_PERSON_FUTURE:
				switch (gna) {
					0,1,6,7: print "Tu";
					3,4,9,10: print "Vuestro";
				}
				print " soplido no producirá";
			THIRD_PERSON_FUTURE:
				print "Su soplido no producirá";
		}
		" ningún efecto.";

!! TODO
	Burn:
		print "Con esa peligrosa acción no ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			FIRST_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "iba";
				else print "íbamos";
				" a lograr nada.";
			SECOND_PERSON_PRESENT,
			SECOND_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "ibas";
				else print "ibais";
				" a lograr nada.";
			THIRD_PERSON_PRESENT,
			THIRD_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "iba";
				else print "iban";
				" a lograr nada.";
			FIRST_PERSON_PAST:
				if (IsSingularNoun(player)) print "hubiese";
				else print "hubiésemos";
				" logrado nada.";
			SECOND_PERSON_PAST:
				if (IsSingularNoun(player)) print "hubieses";
				else print "hubieseis";
				" logrado nada.";
			THIRD_PERSON_PAST:
				if (IsSingularNoun(player)) print "hubiese";
				else print "hubiesen";
				" logrado nada.";
		}

!! TODO
	Buy:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				"No hay nada en venta.";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				"No había nada en venta.";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				"No habrá nada en venta.";
		}

!! TODO
	Climb:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsSingularNoun(player)) print "No creo que vaya";
				else print "No creemos que vayamos";
				" a lograr nada haciendo eso.";
			SECOND_PERSON_PRESENT:
				print "En realidad no";
				if (IsSingularNoun(player)) print " crees que vayas";
				else print " creeis que vayais";
				" a lograr nada haciendo eso.";
			THIRD_PERSON_PRESENT:
				print "En realidad no";
				if (IsSingularNoun(player)) print " cree que vaya";
				else print " creen que vayan";
				" a lograr nada haciendo eso.";
			FIRST_PERSON_PAST:
				if (IsSingularNoun(player)) print "No creo que hubiese";
				else print "No creemos que hubiésemos";
				" logrado nada haciendo aquello.";
			SECOND_PERSON_PAST:
				print "En realidad no";
				if (IsSingularNoun(player)) print " crees que hubieses";
				else print " creéis que hubieseis";
				" logrado nada haciendo aquello.";
			THIRD_PERSON_PAST:
				print "En realidad no";
				if (IsSingularNoun(player)) print " cree que hubiese";
				else print " creen que hubiesen";
				" logrado nada haciendo aquello.";
			FIRST_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "No iba";
				else print "No íbamos";
				" a lograr nada haciendo aquello.";
			SECOND_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "No ibas";
				else print "No ibais";
				" a lograr nada haciendo aquello.";
			THIRD_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "No iba";
				else print "No iban";
				" a lograr nada haciendo aquello.";
		}

!! TODO
	Close:
		!!	1:	Error. El objeto no es *openable*.
		!!	2:	Error. El objeto está cerrado.
		!!	3:	Mensaje cuando se cierra el objeto.
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						"No es algo que pueda cerrarse.";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						"No era algo que se pudiese cerrar.";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"No será algo que se pueda cerrar.";
				}
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						"Ya estaba", (n) x1, " cerrad", (o) x1, ".";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						"Ya estaba", (n) x1, " cerrad", (o) x1, ".";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"Ya estará", (n) x1, " cerrad", (o) x1, ".";
				}
			3:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "Cierro";
						else print "Cerramos";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "Cierras";
						else print "Cerráis";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "Cierra";
						else print "Cierran";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "Cerré";
						else print "Cerramos";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "Cerraste";
						else print "Cerrasteis";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "Cerró";
						else print "Cerraron";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "Cerraré";
						else print "Cerraremos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "Cerrarás";
						else print "Cerraréis";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "Cerrará";
						else print "Cerrarán";
				}
				" ", (the) x1, ".";
		}

!! TODO
	CommandsOff:
		switch (n) { ![6/11]
			1:	"[Grabación de órdenes finalizada.]";
			#Ifdef TARGET_GLULX;
			2:	"[La grabación de órdenes ya estaba finalizada.]";
			#Endif; ! TARGET_
		}

!! TODO
	CommandsOn:
		switch (n) { ![6/11]
			1:	"[Grabación de órdenes activada.]";
			#Ifdef TARGET_GLULX;
			2:	"[Órdenes relanzadas.]";
			3:	"[Grabación de órdenes ya activada.]";
			4:	"[Fallo en la grabación de órdenes.]";
			#Endif; ! TARGET_
		}

!! TODO
	CommandsRead:
		switch (n) { ![6/11]
			1:	"[Relanzando acciones.]";
			#Ifdef TARGET_GLULX;
			2:	"[Las órdenes ya están siendo relanzadas.]";
			3:	"[Fallo en la reejecución de órdenes: grabación en curso.]";
			4:	"[Fallo en la reejecución de órdenes.]";
			5:	"[Acciones ejecutadas: fin del proceso.]";
			#Endif; ! TARGET_
		}

!! TODO
	Consult:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsSingularNoun(player)) print "descubro";
				else print "descubrimos";
			SECOND_PERSON_PRESENT:
				if (IsSingularNoun(player)) print "descubres";
				else print "descubrís";
			THIRD_PERSON_PRESENT:
				if (IsSingularNoun(player)) print "descubre";
				else print "descubren";
			FIRST_PERSON_PAST:
				if (IsSingularNoun(player)) print "descubrí";
				else print "descubrimos";
			SECOND_PERSON_PAST:
				if (IsSingularNoun(player)) print "descubriste";
				else print "descubrieron";
			THIRD_PERSON_PAST:
				if (IsSingularNoun(player)) print "descubrió";
				else print "descubrieron";
			FIRST_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "descubriré";
				else print "descubriremos";
			SECOND_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "descubrirás";
				else print "descubriréis";
			THIRD_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "descubrirá";
				else print "descubrirán";
		}
		" nada interesante en ", (the) x1, " sobre ese tema.";

!! TODO
	Cut:
		print "Cortándo", (lo) x1, " no ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			FIRST_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "lograré";
				else print "lograremos";
			SECOND_PERSON_PRESENT,
			SECOND_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "lograrás";
				else print "lograréis";
			THIRD_PERSON_PRESENT,
			THIRD_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "logrará";
				else print "lograrán";
			FIRST_PERSON_PAST:
				if (IsSingularNoun(player)) print "hubiese logrado";
				else print "hubiésemos logrado";
			SECOND_PERSON_PAST:
				if (IsSingularNoun(player)) print "hubieses logrado";
				else print "hubieseis logrado";
			THIRD_PERSON_PAST:
				if (IsSingularNoun(player)) print "hubiese logrado";
				else print "hubiesen logrado";
		}
		" gran cosa.";

!! TODO
	Dig:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT:
			THIRD_PERSON_PRESENT:
				"Excavar no servirá de nada aquí.";
			FIRST_PERSON_PAST:
			SECOND_PERSON_PAST:
			THIRD_PERSON_PAST:
				"Excavar no hubiese servido de nada allí.";
			FIRST_PERSON_FUTURE:
			SECOND_PERSON_FUTURE:
			THIRD_PERSON_FUTURE:
				"Excavar no servirá de nada allí.";
		}

!! TODO
	Disrobe:
		!!	1:	Error. El protagonista no lleva el objeto puesto.
		!!	2:	Mensaje cuando el protagonista se quita el objeto.
		switch (n) {
			1:	print "No ", (lo) x1, " ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "llevo";
						else print "llevamos";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "llevas";
						else print "lleváis";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "lleva";
						else print "llevan";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "llevaba";
						else print "llevábamos";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "llevabas";
						else print "llevabais";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "llevaba";
						else print "llevaban";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "llevaré";
						else print "llevaremos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "llevarás";
						else print "llevaréis";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "llevará";
						else print "llevarán";
				}
				" puest", (o) x1, ".";
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "Me quito";
						else print "Nos quitamos";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "Te quitas";
						else print "Os quitáis";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "Se quita";
						else print "Se quitan";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "Me quité";
						else print "Nos quitamos";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "Te quitaste";
						else print "Os quitasteis";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "Se quitó";
						else print "Se quitaron";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "Me quitaré";
						else print "Nos quitaremos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "Te quitarás";
						else print "Os quitaréis";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "Se quitará";
						else print "Se quitarán";
				}
				" ", (the) x1, ".";
		}

!! TODO
	Drink:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT:
			THIRD_PERSON_PRESENT:
				"Eso no parece potable.";
			FIRST_PERSON_PAST:
			SECOND_PERSON_PAST:
			THIRD_PERSON_PAST:
				"Aquello no parecía potable.";
			FIRST_PERSON_FUTURE:
			SECOND_PERSON_FUTURE:
			THIRD_PERSON_FUTURE:
				"Aquello no parecerá potable.";
		}

!! TODO
	Drop:
		!!	1:	Error, el objeto dejado no está en poder del protagonista,
		!!		pero está en la localidad.
		!!	2:	Error, el objeto dejado no está en poder del protagonista ni en
		!!		la localidad,
		!!	3:	Aviso, el objeto era una prenda que el protagonista llevaba
		!!		puesta y la librería va a quitársela automáticamente para poder
		!!		dejarla.
		!!	4:	Éxito.
		switch (n) {
			1:	print "Para dejar ", (the) x1, " ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "debería";
						else print "deberíamos";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "deberías";
						else print "deberíais";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "debería";
						else print "deberían";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "hubiese debido";
						else print "hubiésemos debido";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "hubieses debido";
						else print "hubieseis debido";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "hubiese debido";
						else print "hubiesen debido";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "deberé";
						else print "deberemos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "deberás";
						else print "deberéis";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "deberá";
						else print "deberán";
				}
				" tener", (lo) x1, ".";
			2:	print "No ", (lo) x1, " ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) "tengo conmigo.";
						if (IsMaleNoun(player)) "tenemos con nosotros.";
						"tenemos con nosotras.";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) "tienes contigo.";
						if (IsMaleNoun(player)) "tenéis con vosotros.";
						"tenéis con vosotras.";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) "tiene consigo";
						if (IsMaleNoun(noun)) "tienen con ellos.";
						"tienen con ellas.";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) "tenía conmigo";
						if (IsMaleNoun(noun)) "teníamos con nosotros.";
						"teníamos con nosotras.";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) "tenías contigo";
						if (IsMaleNoun(noun)) "teníais con vosotros.";
						"teníais con vosotras.";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) "tenía consigo";
						if (IsMaleNoun(noun)) "tenían con ellos.";
						"tenían con ellas.";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) "tendré conmigo";
						if (IsMaleNoun(noun)) "tendremos con nosotros.";
						"tendremos con nosotras.";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) "tendrás contigo";
						if (IsMaleNoun(noun)) "tendréis con vosotros.";
						"tendréis con vosotras.";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) "tendrá consigo";
						if (IsMaleNoun(noun)) "tendrán con ellos.";
						"tendrán con ellas.";
				}
			3:	print "(Primero ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "me quito";
						else print "nos quitamos";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "te quitas";
						else print "os quitáis";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "se quita";
						else print "se quitan";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "me quité";
						else print "nos quitamos";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "te quitaste";
						else print "os quitasteis";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "se quitó";
						else print "se quitaron";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "me quitaré";
						else print "nos quitaremos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "te quitarás";
						else print "os quitaréis";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "se quitará";
						else print "se quitarán";
				}
				" ", (the) x1, ".)";
			4:	"Dejad", (o) x1, ".";
		}

!! TODO
	Eat:
		!!	1:	Error, el objeto no tiene el atributo "comestible".
		!!	2:	Éxito. [NOTA: la librería permite por defecto comerse
		!!		cualquier cosa que tenga el atributo "comestible", pero la
		!!		única acción que provoca esto es que el objeto en cuestión
		!!		desaparece del juego al ser comido.]
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT:
					THIRD_PERSON_PRESENT:
						"Eso no parece comestible.";
					FIRST_PERSON_PAST:
					SECOND_PERSON_PAST:
					THIRD_PERSON_PAST:
						"Aquello no parecía comestible.";
					FIRST_PERSON_FUTURE:
					SECOND_PERSON_FUTURE:
					THIRD_PERSON_FUTURE:
						"Aquello no parecerá comestible.";
				}
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "Me como";
						else print "Nos comemos";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "Te comes";
						else print "Os coméis";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "Se come";
						else print "Se comen";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "Me comí";
						else print "Nos comimos";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "Te comiste";
						else print "Os comisteis";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "Se comió";
						else print "Se comieron";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "Me comeré";
						else print "Nos comeremos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "Te comerás";
						else print "Os comeréis";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "Se comerá";
						else print "Se comerán";
				}
				" ", (the) x1, ".";
		}

!! TODO
	EmptyT:
		!!	1:	Error, el usuario intenta vaciar un objeto en otro que no es un
		!!		recipiente.
		!!	2:	Error, el usuario intenta vaciar un objeto sobre un recipiente
		!!		cerrado.
		!!	3:	Error, el usuario intenta vaciar un objeto que no tiene nada
		!!		dentro.
		!!	4:	Error, el usuario intenta vaciar un objeto sobre sí mismo.
		!!
		!! [NOTA: No hay mensajes de éxito para esta acción, ya que en caso
		!! de haber superado los test anteriores, la librería genera
		!! finalmente la acción ##Transfer, la cuál, a su vez, generará la
		!! acción ##PutOn o ##Insert, según el segundo objeto sea soporte o
		!! recipiente. Por tanto los mensajes de éxito serán los de las
		!! acciones ##PutOn o ##Insert.]
		switch (n) {
			1:	print (The) x1, " no ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "puede", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "podía", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "podrá", (n) x1;
				}
				" tener cosas dentro.";
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print (The) x1, " está", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print (The) x1, " estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print (The) x1, " estará", (n) x1;
				}
				" cerrad", (o) x1, ".";
			3:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print (The) x1, " ya está", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print (The) x1, " ya estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print (The) x1, " ya estará", (n) x1;
				}
				" vací", (o) x1, ".";
			4:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "puedo";
						else print "podemos";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "puedes";
						else print "podéis";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "puede";
						else print "pueden";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "podía";
						else print "podíamos";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "podías";
						else print "podíais";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "podía";
						else print "podían";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "podré";
						else print "podremos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "podrás";
						else print "podréis";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "podrá";
						else print "podrán";
				}
				" vaciar un objeto sobre sí mismo.";
		}

!! TODO
	Enter:
		! [infsp] GoIn (Meterse) se cambió por Enter.
		!! CUIDADO. La acción Meterse se genera en muy diversas
		!! circunstancias: VETE HACIA EL PUENTE, VETE AL PUENTE, VETE POR
		!! EL PUENTE, PASA POR EL PUENTE, ENTRA EN EL PUENTE, ENTRA AL
		!! PUENTE, CRUZA EL PUENTE, CRUZA POR EL PUENTE, METETE EN EL
		!! PUENTE, METETE POR EL PUENTE, ATRAVIESA EL PUENTE, BAJA POR EL
		!! PUENTE.  Todas ellas generarían la acción <Meterse Puente>
		!!
		!! Además, los intentos de entrar en un "entrable", también, como
		!! por ejemplo: SIENTATE EN EL BANCO, ECHATE EN EL BANCO, SUBETE AL
		!! BANCO, SUBETE EN EL BANCO, SUBE AL BANCO, SUBE POR EL BANCO,
		!! SALTA AL BANCO. Todas ellas generarían <Meterse Banco>
		!!
		!! Puesto que hay muchos verbos diferentes que dan lugar a la misma
		!! acción, es necesaria alguna forma de imprimir qué verbo concreto
		!! ha sido el que la ha desencadenado, para poder generar mensajes
		!! como "No puedes entrar ahi", "No puedes sentarte ahi", "No
		!! puedes subirte ahi", etc.. según el verbo usado. Para esto puede
		!! usarse una llamada a IdiomaVerbo(palabra_verbo). palabra_verbo
		!! contiene el verbo usado por el jugador (convertido en forma
		!! imperativa), y IdiomaVerbo lo que hace es imprimir la forma
		!! infinitiva.
		!!
		!! Mensajes que puede generar esta acción:
		!!	1:	Error, el protagonista ya está en/sobre el objeto.
		!!	2:	Error, el objeto al que intenta entrar/subirse el usuario
		!!		no tiene el atributo "enterable".
		!!	3:	Error, el objeto al que intenta entrar/subirse el usuario tiene
		!!		los atributos "container" y "enterable", pero está cerrado.
		!!	4:	Error, el objeto al que intenta entrar/subirse el usuario está
		!!		en poder del propio usuario.
		!!	5:	Éxito, el usuario entra/sube al objeto.
		!!	6:	Aviso, el usuario estaba en otro objeto, la lib. intentará la
		!!		acción SALIR automáticamente antes de reintentar entrar el
		!!		nuevo objeto.
		!!	7:	Aviso, el objeto al que intenta entrar/subirse el usuario está
		!!		dentro de otros objeto. La lib. intentará automáticamente meter
		!!		al jugador en el objeto desde el cual pueda acceder al que el
		!!		jugador le ha indicado.
		switch (n) {
			1:	print "Ya estoy "; ! FIXME
				if (x1 has supporter) print "sobre ";
				else print "en ";
				"", (the) x1, ".";
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player))
							print "No es algo donde pueda";
						else print "No es algo donde podamos";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player))
							print "No es algo donde puedas";
						else print "No es algo donde podáis";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player))
							print "No es algo donde pueda";
						else print "No es algo donde puedan";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player))
							print "No era algo donde pudiese";
						else print "No era algo donde pudiésemos";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player))
							print "No era algo donde pudieses";
						else print "No era algo donde pudieseis";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player))
							print "No era algo donde pudiese";
						else print "No era algo donde pudiesen";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player))
							print "No será algo donde podré";
						else print "No será algo donde podremos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player))
							print "No será algo donde podrás";
						else print "No será algo donde podréis";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player))
							print "No será algo donde podrá";
						else print "No será algo donde podrán";
				}
				LanguageVerb(verb_word); ".";
			3:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "puedo";
						else print "podemos";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "puedes";
						else print "podéis";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "puede";
						else print "pueden";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "podía";
						else print "podíamos";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "podías";
						else print "podíais";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "podía";
						else print "podían";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "podré";
						else print "podremos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "podrás";
						else print "podréis";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "podrá";
						else print "podrán";
				}
				LanguageVerb(verb_word);
				print " en ", (the) x1, " porque ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "está", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "estará", (n) x1;
				}
				" cerrad", (o) x1, ".";
			4:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "voy a poder";
						else print "vamos a poder";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "vas a poder";
						else print "vais a poder";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "va a poder";
						else print "van a poder";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "iba a poder";
						else print "íbamos a poder";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "ibas a poder";
						else print "ibais a poder";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "iba a poder";
						else print "iban a poder";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "podré";
						else print "podremos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "podrás";
						else print "podréis";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "podrá";
						else print "podrán";
				}
				LanguageVerb(verb_word);
				print " ahí mientras no ", (lo) x1, " ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "suelte";
						else print "soltemos";
					SECOND_PERSON_PRESENT,
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "sueltes";
						else print "soltéis";
					THIRD_PERSON_PRESENT,
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "suelte";
						else print "suelten";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "soltase";
						else print "soltásemos";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "soltases";
						else print "soltaseis";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "soltase";
						else print "soltasen";
				}
				".";
			5:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "Subo";
							else print "Subimos";
							print " ", (al_) x1;
						} else {
							if (IsSingularNoun(player)) print "Entro";
							else print "Entramos";
							print " en ", (the) x1;
						}
						".";
					SECOND_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "Subes";
							else print "Subís";
							print " ", (al_) x1;
						} else {
							if (IsSingularNoun(player)) print "Entras";
							else print "Entráis";
							print " en ", (the) x1;
						}
						".";
					THIRD_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "Sube";
							else print "Suben";
							print " ", (al_) x1;
						} else {
							if (IsSingularNoun(player)) print "Entra";
							else print "Entran";
							print " en ", (the) x1;
						}
						".";
					FIRST_PERSON_PAST:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "Subí";
							else print "Subimos";
							print " ", (al_) x1;
						} else {
							if (IsSingularNoun(player)) print "Entré";
							else print "Entramos";
							print " en ", (the) x1;
						}
						".";
					SECOND_PERSON_PAST:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "Subiste";
							else print "Subisteis";
							print " ", (al_) x1;
						} else {
							if (IsSingularNoun(player)) print "Entraste";
							else print "Entrasteis";
							print " en ", (the) x1;
						}
						".";
					THIRD_PERSON_PAST:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "Subió";
							else print "Subieron";
							print " ", (al_) x1;
						} else {
							if (IsSingularNoun(player)) print "Entró";
							else print "Entraron";
							print " en ", (the) x1;
						}
						".";
					FIRST_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "Subiré";
							else print "Subiremos";
							print " ", (al_) x1;
						} else {
							if (IsSingularNoun(player)) print "Entraré";
							else print "Entraremos";
							print " en ", (the) x1;
						}
						".";
					SECOND_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "Subirás";
							else print "Subiréis";
							print " ", (al_) x1;
						} else {
							if (IsSingularNoun(player)) print "Entrarás";
							else print "Entraréis";
							print " en ", (the) x1;
						}
						".";
					THIRD_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "Subirá";
							else print "Subirán";
							print " ", (al_) x1;
						} else {
							if (IsSingularNoun(player)) print "Entrará";
							else print "Entrarán";
							print " en ", (the) x1;
						}
						".";
				}
			6:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "(Me bajo";
							else print "(Nos bajamos";
						} else {
							if (IsSingularNoun(player)) print "(Salgo";
							else print "(Salimos";
						}
					SECOND_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "(Te bajas";
							else print "(Os bajáis";
						} else {
							if (IsSingularNoun(player)) print "(Sales";
							else print "(Salís";
						}
					THIRD_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "(Se baja";
							else print "(Se bajan";
						} else {
							if (IsSingularNoun(player)) print "(Sale";
							else print "(Salen";
						}
					FIRST_PERSON_PAST:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "(Me bajé";
							else print "(Nos bajamos";
						} else {
							if (IsSingularNoun(player)) print "(Salí";
							else print "(Salimos";
						}
					SECOND_PERSON_PAST:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "(Te bajaste";
							else print "(Os bajásteis";
						} else {
							if (IsSingularNoun(player)) print "(Saliste";
							else print "(Salisteis";
						}
					THIRD_PERSON_PAST:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "(Se bajó";
							else print "(Se bajaron";
						} else {
							if (IsSingularNoun(player)) print "(Salió";
							else print "(Salieron";
						}
					FIRST_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "(Me bajaré";
							else print "(Nos bajaremos";
						} else {
							if (IsSingularNoun(player)) print "(Saldré";
							else print "(Saldremos";
						}
					SECOND_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "(Te bajarás";
							else print "(Os bajaréis";
						} else {
							if (IsSingularNoun(player)) print "(Saldrás";
							else print "(Saldréis";
						}
					THIRD_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "(Se bajará";
							else print "(Se bajarán";
						} else {
							if (IsSingularNoun(player)) print "(Saldrá";
							else print "(Saldrán";
						}
				}
				" ", (del_) x1, ".)";
			7:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "(Me subo";
							else print "(Nos subimos";
							" ", (al_) x1, ".)^";
						} else if (x1 has container) {
							if (IsSingularNoun(player)) print "(Me meto";
							else print "(Nos metemos";
						} else {
							if (IsSingularNoun(player)) print "(Entro";
							else print "(Entramos";
						}
						" en ", (the) x1, ".)^";
					SECOND_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "(Te subes";
							else print "(Os subís";
							" ", (al_) x1, ".)^";
						} else if (x1 has container) {
							if (IsSingularNoun(player)) print "(Te metes";
							else print "(Os metéis";
						} else {
							if (IsSingularNoun(player)) print "(Entras";
							else print "(Entráis";
						}
						" en ", (the) x1, ".)^";
					THIRD_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "(Se sube";
							else print "(Se suben";
							" ", (al_) x1, ".)^";
						} else if (x1 has container) {
							if (IsSingularNoun(player)) print "(Se mete";
							else print "(Se meten";
						} else {
							if (IsSingularNoun(player)) print "(Entra";
							else print "(Entran";
						}
						" en ", (the) x1, ".)^";
					FIRST_PERSON_PAST:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "(Me subí";
							else print "(Nos subimos";
							" ", (al_) x1, ".)^";
						} else if (x1 has container) {
							if (IsSingularNoun(player)) print "(Me metí";
							else print "(Nos metimos";
						} else {
							if (IsSingularNoun(player)) print "(Entré";
							else print "(Entramos";
						}
						" en ", (the) x1, ".)^";
					SECOND_PERSON_PAST:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "(Te subiste";
							else print "(Os subisteis";
							" ", (al_) x1, ".)^";
						} else if (x1 has container) {
							if (IsSingularNoun(player)) print "(Te metiste";
							else print "(Os metisteis";
						} else {
							if (IsSingularNoun(player)) print "(Entraste";
							else print "(Entrasteis";
						}
						" en ", (the) x1, ".)^";
					THIRD_PERSON_PAST:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "(Se subió";
							else print "(Se subieron";
							" ", (al_) x1, ".)^";
						} else if (x1 has container) {
							if (IsSingularNoun(player)) print "(Se metió";
							else print "(Se metieron";
						} else {
							if (IsSingularNoun(player)) print "(Entró";
							else print "(Entraron";
						}
						" en ", (the) x1, ".)^";
					FIRST_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "(Me subiré";
							else print "(Nos subiremos";
							" ", (al_) x1, ".)^";
						} else if (x1 has container) {
							if (IsSingularNoun(player)) print "(Me meteré";
							else print "(Nos meteremos";
						} else {
							if (IsSingularNoun(player)) print "(Entraré";
							else print "(Entraremos";
						}
						" en ", (the) x1, ".)^";
					SECOND_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "(Te subirás";
							else print "(Os subiréis";
							" ", (al_) x1, ".)^";
						} else if (x1 has container) {
							if (IsSingularNoun(player)) print "(Te meterás";
							else print "(Os meteréis";
						} else {
							if (IsSingularNoun(player)) print "(Entrarás";
							else print "(Entraréis";
						}
						" en ", (the) x1, ".)^";
					THIRD_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "(Se subirá";
							else print "(Se subirán";
							" ", (al_) x1, ".)^";
						} else if (x1 has container) {
							if (IsSingularNoun(player)) print "(Se meterá";
							else print "(Se meterán";
						} else {
							if (IsSingularNoun(player)) print "(Entrará";
							else print "(Entrarán";
						}
						" en ", (the) x1, ".)^";
				}
		}

!! TODO
	Examine:
		!!	1:	Error, el usuario intenta examinar un objeto, pero está a
		!!		oscuras.
		!!	2:	Éxito, pero el objeto examinado no tiene descripcion
		!!	3:	Éxito, pero el objeto examinado no tiene descripcion, aunque
		!!		tiene el atributo conmutable, por lo que la librería genera
		!!		este mensaje para indicar si está apagado o encendido.
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "Está";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "Estaba";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "Estará";
				}
				print " demasiado oscuro. No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "puedo";
						else print "podemos";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "puedes";
						else print "podéis";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "puede";
						else print "pueden";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "podía";
						else print "podíamos";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "podías";
						else print "podíais";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "podía";
						else print "podían";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "podré";
						else print "podremos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "podrás";
						else print "podréis";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "podrá";
						else print "podrán";
				}
				" ver nada.";
			2:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "observo";
						else print "observamos";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "observas";
						else print "observáis";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "observa";
						else print "observan";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "observé";
						else print "observamos";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "observaste";
						else print "observasteis";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "observó";
						else print "observaron";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "observaré";
						else print "observaremos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "observarás";
						else print "observaréis";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "observará";
						else print "observarán";
				}
				" nada especial en ", (the) x1, ".";
			3:	switch (_grammatical_inflection) {
					1,2,3:	print (The) x1, " está", (n) x1;
					4,5,6:	print (The) x1, " estaba", (n) x1;
					7,8,9:	print (The) x1, " estará", (n) x1;
				}
				if (x1 has on) " encendid", (o) x1, ".";
				else " apagad", (o) x1,".";
		}

!! TODO
	Exit:
		!!	1:	Error, el usuario no está subido/sentado/metido en ningún
		!!		objeto. [Nota, si la localidad tiene la propiedad "afuera",
		!!		entonces la acción Salir lo sacará de la localidad. En caso
		!!		contrario es cuando se genera este error.]
		!!	2:	Error, el usuario está dentro de un recipiente cerrado.
		!!	3:	Éxito, el usuario sale/baja del objeto
		!!	4:	Error, más específico. [6/11]
		switch (n) {
			1:	print "No estoy en ningún sitio del que "; ! FIXME
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "deba";
						else print "debamos";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "debas";
						else print "debáis";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "deba";
						else print "deban";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "debiese";
						else print "debiésemos";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "debieses";
						else print "debieseis";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "debiese";
						else print "debiesen";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "debería";
						else print "deberíamos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "deberías";
						else print "deberíais";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "debería";
						else print "deberían";
				}
				LanguageVerb(verb_word); ".";
			2:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "puedo";
						else print "podemos";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "puedes";
						else print "podéis";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "puede";
						else print "pueden";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "podía";
						else print "podíamos";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "podías";
						else print "podíais";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "podía";
						else print "podían";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "podré";
						else print "podremos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "podrás";
						else print "podréis";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "podrá";
						else print "podrán";
				}
				print " salir ", (del_) x1, " porque ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "está", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "estará", (n) x1;
				}
				" cerrad", (o) x1, ".";
			3:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "Bajo";
							else print "Bajamos";
						} else {
							if (IsSingularNoun(player)) print "Salgo";
							else print "Salimos";
						}
					SECOND_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "Bajas";
							else print "Bajáis";
						} else {
							if (IsSingularNoun(player)) print "Sales";
							else print "Salís";
						}
					THIRD_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "Baja";
							else print "Bajan";
						} else {
							if (IsSingularNoun(player)) print "Sale";
							else print "Salen";
						}
					FIRST_PERSON_PAST:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "Bajé";
							else print "Bajamos";
						} else {
							if (IsSingularNoun(player)) print "Salí";
							else print "Salimos";
						}
					SECOND_PERSON_PAST:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "Bajaste";
							else print "Bajasteis";
						} else {
							if (IsSingularNoun(player)) print "Saliste";
							else print "Salisteis";
						}
					THIRD_PERSON_PAST:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "Bajó";
							else print "Bajaron";
						} else {
							if (IsSingularNoun(player)) print "Salió";
							else print "Salieron";
						}
					FIRST_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "Bajaré";
							else print "Bajaremos";
						} else {
							if (IsSingularNoun(player)) print "Saldré";
							else print "Saldremos";
						}
					SECOND_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "Bajarás";
							else print "Bajaréis";
						} else {
							if (IsSingularNoun(player)) print "Saldrás";
							else print "Saldréis";
						}
					THIRD_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsSingularNoun(player)) print "Bajará";
							else print "Bajarán";
						} else {
							if (IsSingularNoun(player)) print "Saldrá";
							else print "Saldrán";
						}
				}
				" ", (del_) x1, ".";
			4:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "puedo";
						else print "podemos";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "puedes";
						else print "podéis";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "puede";
						else print "pueden";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "podía";
						else print "podíamos";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "podías";
						else print "podíais";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "podía";
						else print "podían";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "podré";
						else print "podremos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "podrás";
						else print "podréis";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "podrá";
						else print "podrán";
				}
				print ". No estoy "; ! FIXME
				if (x1 has supporter) print "encima";
				else print "dentro";
				" ", (del_) x1, ".";
		}

!! TODO
	Fill:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsSingularNoun(player)) print "puedo";
				else print "podemos";
			SECOND_PERSON_PRESENT:
				if (IsSingularNoun(player)) print "puedes";
				else print "podéis";
			THIRD_PERSON_PRESENT:
				if (IsSingularNoun(player)) print "puede";
				else print "pueden";
			FIRST_PERSON_PAST:
				if (IsSingularNoun(player)) print "podía";
				else print "podíamos";
			SECOND_PERSON_PAST:
				if (IsSingularNoun(player)) print "podías";
				else print "podíais";
			THIRD_PERSON_PAST:
				if (IsSingularNoun(player)) print "podía";
				else print "podían";
			FIRST_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "podré";
				else print "podremos";
			SECOND_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "podrás";
				else print "podréis";
			THIRD_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "podrá";
				else print "podrán";
		}
		" llenar", (lo) x1, ".";

	FullScore:
		!! Puntuación en modo "explicativo". Puede activarse porque el
		!! usuario lo pida con el verbo "PUNTUACION LARGA" o porque el
		!! relato haya terminado (y la constante HAY_TAREAS esté definida).
		!!
		!!	1:	Texto introductorio al desglose de puntos
		!!	2:	Texto de objetos importantes (los que tienen el atributo
		!!		"valepuntos")
		!!	3:	Texto de lugares importantes (los que tienen el atributo
		!!		"valepuntos")
		!!	4:	Texto final, tras la suma total impresa por la librería
		switch (n) {
			1:	if (deadflag) print "La puntuación se desglosó ";
				else          print "La puntuación se desglosa ";
				"de la siguiente manera:^";
			2: "por encontrar objetos importantes";
			3: "por visitar lugares importantes";
			4: print "total (de ", MAX_SCORE ; ")";
		}

!! TODO
	GetOff:
		!! Esta acción se genera ante la frase SAL DEL ARMARIO o similares.
		!! Ante SAL a secas la acción es Salir. Si el jugador no está en el
		!! objeto indicado, se genera el siguiente mensaje de error. Si está,
		!! la librería generará una acción Salir, por lo que el mensaje de
		!! éxito será el de Salir.
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsSingularNoun(player)) print "puedo";
				else print "podemos";
			SECOND_PERSON_PRESENT:
				if (IsSingularNoun(player)) print "puedes";
				else print "podéis";
			THIRD_PERSON_PRESENT:
				if (IsSingularNoun(player)) print "puede";
				else print "pueden";
			FIRST_PERSON_PAST:
				if (IsSingularNoun(player)) print "podía";
				else print "podíamos";
			SECOND_PERSON_PAST:
				if (IsSingularNoun(player)) print "podías";
				else print "podíais";
			THIRD_PERSON_PAST:
				if (IsSingularNoun(player)) print "podía";
				else print "podían";
			FIRST_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "podré";
				else print "podremos";
			SECOND_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "podrás";
				else print "podréis";
			THIRD_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "podrá";
				else print "podrán";
		}
		". No estoy en ", (the) x1, "."; ! FIXME

!! TODO
	Give:
		!!	1:	Error, el jugador intenta dar un objeto que no tiene.
		!!	2:	Error, el jugador se da el objeto a sí mismo.
		!!	3:	Aviso, se ha enviado la acción Dar al PNJ, pero este no ha
		!!		respondido. En este caso x1 apunta al PNJ y no al objeto
		!!		que le hemos dado.
		!!
		!! [Observar que por defecto el objeto sigue en poder del
		!! jugador. Si queremos que el PNJ lo acepte, hay que programarlo
		!! como parte de su rutina Vida.]
		switch (n) {
			1:	switch (_grammatical_inflection) {
				1:	"No tengo ", (the) x1, ".";
				2:	"No tienes ", (the) x1, ".";
				3:	"No tiene ", (the) x1, ".";
				4:	"No tenía ", (the) x1, ".";
				5:	"No tenías ", (the) x1, ".";
				6:	"No tenía ", (the) x1, ".";
				7:	"No tendré ", (the) x1, ".";
				8:	"No tendrás ", (the) x1, ".";
				9:	"No tendrá ", (the) x1, ".";
				}
			2:	switch (_grammatical_inflection) {
				1:	print "Manoseo ", (the) x1;
				2:	print "Manoseas ", (the) x1;
				3:	print "Manosea ", (the) x1;
				4:	print "Manoseé ", (the) x1;
				5:	print "Manoseaste ", (the) x1;
				6:	print "Manoseó ", (the) x1;
				7:	print "Manosearé ", (the) x1;
				8:	print "Manosearás ", (the) x1;
				9:	print "Manoseará ", (the) x1;
				} " durante unos momentos, sin conseguir nada.";
			3:	switch (_grammatical_inflection) {
				1,2,3:	print_ret (The) x1, " no parece", (n) x1,
						" interesad", (o) x1, ".";
				4,5,6:	print_ret (The) x1, " no parecía", (n) x1,
						" interesad", (o) x1, ".";
				7,8,9:	print_ret (The) x1, " no parecerá", (n) x1,
						" interesad", (o) x1, ".";
				}
		}

!! TODO
	Go:
		!!	1:	Error, el jugador está dentro/subido en un objeto del que
		!!		tiene que salir antes.
		!!	2:	Error, la localidad no tiene salida en esa dirección (y tampoco
		!!		tiene la propiedad "cant_go", ya que en este caso se habría
		!!		impreso el valor de esa propiedad.
		!!	3:	Error, el jugador ha intentado ir hacia arriba, pero allí hay
		!!		una puerta cerrada.
		!!	4:	Error, el jugador ha intentado ir hacia abajo, pero allí hay
		!!		una puerta cerrada.
		!!	5:	Error, en la dirección que ha dicho el jugador hay una
		!!		puerta cerrada.
		!!	6:	Error, en la dirección que ha dicho el jugador hay una puerta,
		!!		pero ésta no tiene una propiedad "door_to" (probablemente un
		!!		error de programación del juego).
		switch (n) {
			1:	switch (_grammatical_inflection) {
				1:	print "Tengo que ";
					if (x1 has supporter) print "bajarme ";
					else print "salir ";
				2:	print "Tienes que ";
					if (x1 has supporter) print "bajarte ";
					else print "salir ";
				3:	print "Tiene que ";
					if (x1 has supporter) print "bajarse ";
					else print "salir ";
				4:	print "Tenía que ";
					if (x1 has supporter) print "bajarme ";
					else print "salir ";
				5:	print "Tenías que ";
					if (x1 has supporter) print "bajarte ";
					else print "salir ";
				6:	print "Tenía que ";
					if (x1 has supporter) print "bajarse ";
					else print "salir ";
				7:	print "Tendré que ";
					if (x1 has supporter) print "bajarme ";
					else print "salir ";
				8:	print "Tendrás que ";
					if (x1 has supporter) print "bajarte ";
					else print "salir ";
				9:	print "Tendrá que ";
					if (x1 has supporter) print "bajarse ";
					else print "salir ";
				}
				print_ret (del_) x1, " antes.";
			2:	switch (_grammatical_inflection) {
				1:	"No puedo ir por ahí.";
				2:	"No puedes ir por ahí.";
				3:	"No puede ir por ahí.";
				4:	"No podía ir por ahí.";
				5:	"No podías ir por ahí.";
				6:	"No podía ir por ahí.";
				7:	"No podré ir por ahí.";
				8:	"No podrás ir por ahí.";
				9:	"No podrá ir por ahí.";
				}
			3:	switch (_grammatical_inflection) {
				1:	"Soy incapaz de trepar por ", (the) x1, ".";
				2:	"Eres incapaz de trepar por ", (the) x1, ".";
				3:	"Es incapaz de trepar por ", (the) x1, ".";
				4:	"Era incapaz de trepar por ", (the) x1, ".";
				5:	"Eras incapaz de trepar por ", (the) x1, ".";
				6:	"Era incapaz de trepar por ", (the) x1, ".";
				7:	"Seré incapaz de trepar por ", (the) x1, ".";
				8:	"Serás incapaz de trepar por ", (the) x1, ".";
				9:	"Será incapaz de trepar por ", (the) x1, ".";
				}
			4:	switch (_grammatical_inflection) {
				1:	"Soy incapaz de bajar por ", (the) x1, ".";
				2:	"Eres incapaz de bajar por ", (the) x1, ".";
				3:	"Es incapaz de bajar por ", (the) x1, ".";
				4:	"Era incapaz de bajar por ", (the) x1, ".";
				5:	"Eras incapaz de bajar por ", (the) x1, ".";
				6:	"Era incapaz de bajar por ", (the) x1, ".";
				7:	"Seré incapaz de bajar por ", (the) x1, ".";
				8:	"Serás incapaz de bajar por ", (the) x1, ".";
				9:	"Será incpaz de bajar por ", (the) x1, ".";
				}
			5:	switch (_grammatical_inflection) {
				1:	"No puedo pasar a través ", (del_) x1, ".";
				2:	"No puedes pasar a través ", (del_) x1, ".";
				3:	"No puede pasar a través ", (del_) x1, ".";
				4:	"No podía pasar a través ", (del_) x1, ".";
				5:	"No podías pasar a través ", (del_) x1, ".";
				6:	"No podía pasar a través ", (del_) x1, ".";
				7:	"No podré pasar a través ", (del_) x1, ".";
				8:	"No podrás pasar a través ", (del_) x1, ".";
				9:	"No podrá pasar a través ", (del_) x1, ".";
				}
			6:	switch (_grammatical_inflection) {
				1:	"No puedo ir porque ", (the) x1, " no lleva", (n) x1,
					" a ningún sitio.";
				2:	"No puedes ir porque ", (the) x1, " no lleva", (n) x1,
					" a ningún sitio.";
				3:	"No puede ir porque ", (the) x1, " no lleva", (n) x1,
					" a ningún sitio.";
				4:	"No podía ir porque ", (the) x1, " no llevaba", (n) x1,
					" a ningún sitio.";
				5:	"No podías ir porque ", (the) x1, " no llevaba", (n) x1,
					" a ningún sitio.";
				6:	"No podía ir porque ", (the) x1, " no llevaba", (n) x1,
					" a ningún sitio.";
				7:	"No podré ir porque ", (the) x1, " no llevará", (n) x1,
					" a ningún sitio.";
				8:	"No podrás ir porque ", (the) x1, " no llevará", (n) x1,
					" a ningún sitio.";
				9:	"No podrá ir porque ", (the) x1, " no llevará", (n) x1,
					" a ningún sitio.";
				}
		}

!! TODO
	Insert:
		!!	1:	Error, el objeto no está en poder del jugador. [Nota, conviene
		!!		mirar en este caso si el objeto es animado o no, para generar
		!!		un mensaje más adecuado].
		!!	2:	Error, el jugador intenta meter el objeto en otro que no tiene
		!!		el atributo "container".
		!!	3:	Error, el jugador intenta meter el objeto en un recipiente
		!!		cerrado.
		!!	4:	Error, el objeto es una prenda que el jugador lleva puesta.
		!!		[ESTE MENSAJE NO SE GENERA NUNCA, PARECE UN BUG DE LA LIBRERÍA.
		!!		Véase en su lugar el mensaje 6].
		!!	5:	Error, se intenta poner un objeto dentro de sí mismo.
		!!	6:	Aviso, el objeto es una prenda puesta, la librería va a
		!!		quitársela de forma automática antes de reintentar Insert.
		!!	7:	Error, no queda sitio en el recipiente (el número de objetos
		!!		que un recipiente puede contener se indica en su propiedad
		!!		"capacity").
		!!	8:	Éxito. Mensaje a mostrar para cada objeto metido cuando se
		!!		meten muchos (ej: METE TODO EN LA BOLSA).
		!!	9:	Éxito. Mensaje a mostrar cuando se mete un solo objeto dentro
		!!		de otro.
		switch (n) {
			1:	switch (_grammatical_inflection) {
				1:	if (x1 has animate)
						"Antes tendría que ", (coge)"rl", (o) x1, " y no sé
						si se dejará", (n) x1, ".";
					else
						"Necesito tener ", (the) x1, " para poder meter",
						(lo) x1, " donde sea.";
				2:	if (x1 has animate)
						"Antes tendrías que ", (coge)"rl", (o) x1, " y no sabes
						si se dejará", (n) x1, ".";
					else
						"Necesitas tener ", (the) x1, " para poder meter",
						(lo) x1, " donde sea.";
				3:	if (x1 has animate)
						"Antes tendría que ", (coge)"rl", (o) x1, " y no sabe
						si se dejará", (n) x1, ".";
					else
						"Necesita tener ", (the) x1, " para poder meter",
						(lo) x1, " donde sea.";
				4:	if (x1 has animate)
						"Antes tendría que haber", (lo) x1, " cogido, y no
						sé si ", (the) x1, " se hubiese", (n) x1,
						" dejado.";
					else
						"Hubiese necesitado tener ", (the) x1, " para poder
						meter", (lo) x1, " donde fuese.";
				5:	if (x1 has animate)
						"Antes tendrías que haber", (lo) x1, " cogido, y no
						sabes si ", (the) x1, " se hubiese", (n) x1,
						" dejado.";
					else
						"Hubieses necesitado tener ", (the) x1, " para poder
						meter", (lo) x1, " donde fuese.";
				6:	if (x1 has animate)
						"Antes tendría que haber", (lo) x1, " cogido, y no
						sabe si ", (the) x1, " se hubiese", (n) x1,
						" dejado.";
					else
						"Hubiese necesitado tener ", (the) x1, " para poder
						meter", (lo) x1, " donde fuese.";
				7:	if (x1 has animate)
						"Antes tendré que haber", (lo) x1, " cogido, y no
						sabré si ", (the) x1, " se habría", (n) x1,
						" dejado.";
					else
					 	"Necesitaré tener ", (the) x1, " para poder
						meter", (lo) x1, " donde sea.";
				8:	if (x1 has animate)
						"Antes tendrás que haber", (lo) x1, " cogido, y no
						sabrás si ", (the) x1, " se habría", (n) x1,
						" dejado.";
					else
						"Necesitarás tener ", (the) x1, " para poder
						meter", (lo) x1, " donde sea.";
				9:	if (x1 has animate)
						"Antes tendrá que haber", (lo) x1, " cogido, y no
						sabrá si ", (the) x1, " se habría", (n) x1,
						" dejado.";
					else
						"Necesitará tener ", (the) x1, " para poder
						meter", (lo) x1, " donde sea.";
				}
			2:	switch (_grammatical_inflection) {
				1,2,3:	"No se pueden meter cosas dentro ", (del_) x1, ".";
				4,5,6:	"No se podían meter cosas dentro ", (del_) x1, ".";
				7,8,9:	"No se podrán meter cosas dentro ", (del_) x1, ".";
				}
			3:	switch (_grammatical_inflection) {
					1,2,3:	print (The) x1, " está", (n) x1;
					4,5,6:	print (The) x1, " estaba", (n) x1;
					7,8,9:	print (The) x1, " estará", (n) x1;
				}
				" cerrad", (o) x1, ".";
			4:	switch (_grammatical_inflection) {
				1:	"Tengo que quitárme", (lo) x1, " antes.";
				2:	"Tienes que quitárte", (lo) x1, " antes.";
				3:	"Tiene que quitárse", (lo) x1, " antes.";
				4:	"Tenía que quitárme", (lo) x1, " antes.";
				5:	"Tenías que quitárte", (lo) x1, " antes.";
				6:	"Tenía que quitárse", (lo) x1, " antes.";
				7:	"Tendré que quitárme", (lo) x1, " antes.";
				8:	"Tendrás que quitárte", (lo) x1, " antes.";
				9:	"Tendrá que quitárse", (lo) x1, " antes.";
				}
			5:	switch (_grammatical_inflection) {
				1:	print "No puedo";
				2:	print "No puedes";
				3:	print "No puede";
				4:	print "No podía";
				5:	print "No podías";
				6:	print "No podía";
				7:	print "No podré";
				8:	print "No podrás";
				9:	print "No podrá";
				}
				" poner un objeto dentro de sí mismo.";
			6:	switch (_grammatical_inflection) {
				1:	"(Primero me ", (lo) x1, " quito.)^";
				2:	"(Primero te ", (lo) x1, " quitas.)^";
				3:	"(Primero se ", (lo) x1, " quita.)^";
				4:	"(Primero me ", (lo) x1, " quité.)^";
				5:	"(Primero te ", (lo) x1, " quitaste.)^";
				6:	"(Primero se ", (lo) x1, " quitó.)^";
				7:	"(Primero me ", (lo) x1, " quitaré.)^";
				8:	"(Primero te ", (lo) x1, " quitarás.)^";
				9:	"(Primero se ", (lo) x1, " quitará.)^";
				}
			7:	switch (_grammatical_inflection) {
				1,2,3:	"No queda sitio en ", (the) x1, ".";
				4,5,6:	"No quedaba sitio en ", (the) x1, ".";
				7,8,9:	"No quedará sitio en ", (the) x1, ".";
				}
			8:	"Hecho.";
			9:	switch (_grammatical_inflection) {
				1:	print "Meto ";
				2:	print "Metes ";
				3:	print "Mete ";
				4:	print "Metí ";
				5:	print "Metiste ";
				6:	print "Metió ";
				7:	print "Meteré ";
				8:	print "Meterás ";
				9:	print "Meterá ";
				}
				print_ret (the) x1, " dentro ", (del_) second, ".";
		}

!! TODO
	Inv:
		!!	1:	Mensaje si el inventario está vacío
		!!	2:	Encabezado del inventario, antes de la lista de objetos
		!!		generada por la librería
		!!	3 y 4: [6/11]
		switch (n) {
			1:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "llevo";
						else print "llevamos";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "llevas";
						else print "lleváis";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "lleva";
						else print "llevan";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "llevaba";
						else print "llevábamos";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "llevabas";
						else print "llevabais";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "llevaba";
						else print "llevaban";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "llevaré";
						else print "llevaremos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "llevarás";
						else print "llevaréis";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "llevará";
						else print "llevarán";
				}
				" nada.";
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "Llevo";
						else print "Llevamos";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "Llevas";
						else print "Lleváis";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "Lleva";
						else print "Llevan";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "Llevaba";
						else print "Llevábamos";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "Llevabas";
						else print "Llevabais";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "Llevaba";
						else print "Llevaban";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "Llevaré";
						else print "Llevaremos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "Llevarás";
						else print "Llevaréis";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "Llevará";
						else print "Llevarán";
				}
			3:	print ":^";
			4:	print ".^";
		}

!! TODO
	Jump:
		switch (_grammatical_inflection) {
				FIRST_PERSON_PRESENT:
					if (IsSingularNoun(player)) print "Salto";
					else print "Saltamos";
				SECOND_PERSON_PRESENT:
					if (IsSingularNoun(player)) print "Saltas";
					else print "Saltáis";
				THIRD_PERSON_PRESENT:
					if (IsSingularNoun(player)) print "Salta";
					else print "Saltan";
				FIRST_PERSON_PAST:
					if (IsSingularNoun(player)) print "Salté";
					else print "Saltamos";
				SECOND_PERSON_PAST:
					if (IsSingularNoun(player)) print "Saltaste";
					else print "Saltasteis";
				THIRD_PERSON_PAST:
					if (IsSingularNoun(player)) print "Saltó";
					else print "Saltaron";
				FIRST_PERSON_FUTURE:
					if (IsSingularNoun(player)) print "Saltaré";
					else print "Saltaremos";
				SECOND_PERSON_FUTURE:
					if (IsSingularNoun(player)) print "Saltarás";
					else print "Saltaréis";
				THIRD_PERSON_FUTURE:
					if (IsSingularNoun(player)) print "Saltará";
					else print "Saltarán";
		}
		" en el sitio, sin ningún resultado.";

!! TODO
	JumpOver, Tie:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			FIRST_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "lograré";
				else print "lograremos";
			SECOND_PERSON_PRESENT,
			SECOND_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "lograrás";
				else print "lograréis";
			THIRD_PERSON_PRESENT,
			THIRD_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "logrará";
				else print "lograrán";
			FIRST_PERSON_PAST:
				if (IsSingularNoun(player)) print "hubiese logrado";
				else print "hubiésemos logrado";
			SECOND_PERSON_PAST:
				if (IsSingularNoun(player)) print "hubieses logrado";
				else print "hubieseis logrado";
			THIRD_PERSON_PAST:
				if (IsSingularNoun(player)) print "hubiese logrado";
				else print "hubiesen logrado";
		}
		" nada así.";

!! TODO
	Kiss:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsSingularNoun(player))
					"No creo que deba.";
				else "En realidad no deberíamos.";
			SECOND_PERSON_PRESENT:
				if (IsSingularNoun(player))
				 	"En realidad no crees que debas.";
				else "En realidad no deberíais.";
			THIRD_PERSON_PRESENT:
				if (IsSingularNoun(player))
					"No cree que deba.";
				else "En realidad no deberían.";
			FIRST_PERSON_PAST:
				if (IsSingularNoun(player)) print "No se me ocurrió";
				else print "No se nos ocurrió";
				" hacer algo así en aquel momento.";
			SECOND_PERSON_PAST:
				if (IsSingularNoun(player)) print "No se te ocurrió";
				else print "No se os ocurrió";
				" hacer algo así en aquel momento.";
			THIRD_PERSON_PAST:
				if (IsSingularNoun(player)) print "No se le ocurrió";
				else print "No se les ocurrió";
				" hacer algo así en aquel momento.";
			FIRST_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "No se me ocurrirá";
				else print "No se nos ocurrirá";
				" hacer algo así en ese momento.";
			SECOND_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "No se te ocurrirá";
				else print "No se os ocurrirá";
				" hacer algo así en ese momento.";
			THIRD_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "No se le ocurrirá";
				else print "No se les ocurrirá";
				" hacer algo así en ese momento.";
		}

!! TODO
	Listen:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsSingularNoun(player)) print "No escucho";
				else print "No escuchamos";
			SECOND_PERSON_PRESENT:
				if (IsSingularNoun(player)) print "No escuchas";
				else "No escucháis";
			THIRD_PERSON_PRESENT:
				if (IsSingularNoun(player)) print "No escucha";
				else "No escuchan";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "No se escuchaba";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "No se escuchará";
		}
		" nada fuera de lo común.";

!! TODO
	ListMiscellany:
		!! Los siguientes mensajes se muestran como aclaraciones cuando se está
		!! listando el inventario del jugador, o los objetos que hay en una
		!! localidad. Junto a cada mensaje se comenta qué condiciones deben
		!! darse en ese objeto para que se muestre ese mensaje aclaratorio.
		switch (n) {
			1:	print " (alumbrando)";
			!! El objeto tiene "luz" y la localidad no
			2:	switch (_grammatical_inflection) {
				1,2,3:	print " (que ", (esta) x1, " cerrad", (o) x1, ")";
				4,5,6:	print " (que estaba", (n) x1, " cerrad", (o) x1, ")";
				7,8,9:	print " (que estará", (n) x1, " cerrad", (o) x1, ")";
				}
			!! El objeto tiene "recipiente" pero no "abierto"
			3:	print " (cerrad", (o) x1, " y alumbrando)";
			!! Casos 2 y 1 juntos
			4:	switch (_grammatical_inflection) {
				1,2,3:	print " (que ", (esta) x1, " vací", (o) x1, ")";
				4,5,6:	print " (que estaba", (n) x1, " vací", (o) x1, ")";
				7,8,9:	print " (que estará", (n) x1, " vací", (o) x1, ")";
				}
			!! El objeto es un recipiente abierto (o transparente) y no
			!!! tiene nada en su interior
			5:	print " (vací", (o) x1, " y alumbrando)";
			!! Casos 1 y 4 juntos
			6:	switch (_grammatical_inflection) {
				1,2,3:	print " (que ", (esta) x1, " cerrad", (o) x1,
						" y vací", (o) x1, ")";
				4,5,6:	print " (que estaba", (n) x1, " cerrad", (o) x1,
						" y vací", (o) x1, ")";
				7,8,9:	print " (que estará", (n) x1, " cerrad", (o) x1,
						" y vací", (o) x1, ")";
				}
			!! El objeto tiene "recipiente", no "abierto", pero sí
			!! "transparente"
			7:	print " (cerrad", (o) x1, ", vací", (o) x1, " y
				alumbrando)";
			!! Casos 1 y 6 juntos

			!! Los casos siguientes son similares, pero se muestran cuando se
			!! solicita a la rutina EscribirListaDesde la opción INFOTOTAL. La
			!! librería puede combinar varios de estos mensajes, por eso no
			!! deben llevar el cerrado de paréntesis al final, que lo añade la
			!! propia librería. *** NO SE ACONSEJA CAMBIAR ESTOS ***

			8:	switch (_grammatical_inflection) {
				1:	print " (alumbrando y que llevo puest", (o) x1;
				2:	print " (alumbrando y que llevas puest", (o) x1;
				3:	print " (alumbrando y que lleva puest", (o) x1;
				4:	print " (alumbrando y que llevaba puest", (o) x1;
				5:	print " (alumbrando y que llevabas puest", (o) x1;
				6:	print " (alumbrando y que llevaba puest", (o) x1;
				7:	print " (alumbrando y que llevaré puest", (o) x1;
				8:	print " (alumbrando y que llevarás puest", (o) x1;
				9:	print " (alumbrando y que llevará puest", (o) x1;
				}
			!! El objeto tiene "luz" y "puesto"
			9: print " (alumbrando";
			!! El objeto tiene "luz" pero no "puesto"
			10:	switch (_grammatical_inflection) {
				1:	print " (que llevo puest", (o) x1;
				2:	print " (que llevas puest", (o) x1;
				3:	print " (que lleva puest", (o) x1;
				4:	print " (que llevaba puest", (o) x1;
				5:	print " (que llevabas puest", (o) x1;
				6:	print " (que llevaba puest", (o) x1;
				7:	print " (que llevaré puest", (o) x1;
				8:	print " (que llevarás puest", (o) x1;
				9:	print " (que llevará puest", (o) x1;
				}
			!! El objeto tiene "puesto" pero no "luz"
			11:	switch (_grammatical_inflection) {
				1,2,3:	print " (que ", (esta) x1, " ";
				4,5,6:	print " (que estaba", (n) x1;
				7,8,9:	print " (que estará", (n) x1;
				}
			!! Mensaje introductorio para decir "que está
			!! abierto/cerrado/vacio"...
			12:	print "abiert", (o) x1;
			!! Objeto tiene "recipiente", "abrible" y "abierto" (y cosas dentro)
			13:	print "abiert", (o) x1, ", pero vací", (o) x1;
			!! Objeto tiene "recipiente", "abrible" y "abierto (pero vacio)
			14:	print "cerrad", (o) x1;
			!! Objeto tiene "recipiente", "abrible" y no "abierto"
			15: print "cerrad", (o) x1, " con llave";
			!! Objeto tiene "recipiente", "abrible" y "cerrojoechado" o
			!! "cerrojo"
			16:	print " vací", (o) x1;
			!! Objeto tiene "recipiente", no "abrible" y "transparente"
			17:	switch (_grammatical_inflection) {
				1,2,3:	print " (que ", (esta) x1, " vací", (o) x1, ")";
				4,5,6:	print " (que estaba", (n) x1, " vací", (o) x1, ")";
				7,8,9:	print " (que estará", (n) x1, " vací", (o) x1, ")";
				}
			!! Como el caso anterior, pero mensaje más "largo" (que se activa
			!! si EscribirListaDesde es llamada sin el modo BREVE_BIT)
			18:	switch (_grammatical_inflection) {
				1,2,3:	print " que contiene", (n) x1, " ";
				4,5,6:	print " que contenía", (n) x1, " ";
				7,8,9:	print " que contendrá", (n) x1, " ";
			}
			!! encabezado a la lista de lo que hay dentro del objeto
			19: print " (sobre ", (el_) x1;
			!! Si el objeto tiene "soporte", la librería va a listar sus
			!! contenidos. Este es el encabezado de la lista
			20: print ", encima ", (del_) x1;
			!! Como e l9, pero en otra modalidad (que se activa si
			!! EscribirListaDesde es llamada sin el modo BREVE_BIT)
			21: print " (en ", (el_) x1;
			!! Si el contenido tiene "recipiente" y puede verse su interior
			!! y hay cosas, la librería va a mostrar sus contenidos. Este
			!! es el encabezado de la lista
			22: print ", dentro ", (del_) x1;
			!! Como el 21, pero en otra modalidad (que se activa si
			!! EscribirListaDesde es llamada sin el modo BREVE_BIT)
		}

 	LMode1:
	    !! La acción LMode1 se genera ante el comando BREVE (o NORMAL). La
	    !! librería imprime la constante Historia y a continuación este
	    !! mensaje.
	    " está ahora en su modo normal ~breve~, que da sólo descripciones
	    largas de los lugares la primera vez que son visitadas, y
	    descripciones cortas en otro caso.";

	LMode2:
    	!! La acción LMode2 se genera ante el comando LARGO. La librería
		!! imprime la constante Historia y a continuación este mensaje.
		" está ahora en su modo ~largo~, que siempre da descripciones
    	largas de los lugares (incluso si ya habías estado antes).";

	LMode3:
    	!! La acción LMode3 se genera ante el comando SUPERBREVE. La librería
		!! imprime la constante Historia y a continuación este mensaje.
		" está ahora en su modo ~superbreve~, que siempre da descripciones
    	cortas de los lugares (incluso si nunca habías estado antes).";

!! TODO
	Lock:
		!! Lock se genera con CIERRA <objeto> CON <objeto2>, o
		!! también ante ECHA CERROJO A <objeto> (sin especificar un
		!! segundo objeto en este caso).
		!!
		!!	1:	Error, el objeto al que se intenta echar el cerrojo no tiene la
		!!		propiedad "lockable".
		!!	2:	Error, el objeto al que se intenta echar el cerrojo tiene la
		!!		propiedad "lockable", pero ya tiene también "locked".
		!!	3:	Error, el objeto tiene las propiedades "lockable" y "open". No
		!!		se le puede echar el cerrojo hasta que no se cierre.
		!!	4:	Error, el <objeto2> especificado no coincide con el que el
		!!		objeto indica en su propiedad "with_key".
		!!	5:	Éxito, se echa el cerrojo al objeto (con el <objeto2> si éste
		!!		es especificado y se puede encontrar en la variable "second").
		switch (n) {
			1:	switch (_grammatical_inflection) {
				1,2,3:	"No parece", (n) x1, " tener ningún tipo de cerrojo.";
				4,5,6:	"No parecía", (n) x1," tener ningún tipo de cerrojo.";
				7,8,9:	"No parecerá", (n) x1, " tener ningún tipo de cerrojo.";
				}
			2:	if (x1 provides with_key) {
					switch (_grammatical_inflection) {
						1,2,3:	print (The) x1, " ya estaba", (n) x1;
						4,5,6:	print (The) x1, " ya estaba", (n) x1;
						7,8,9:	print (The) x1, " ya estará", (n) x1;
					}
					" cerrad", (o) x1, " con llave.";
				}
				else {
					switch (_grammatical_inflection) {
					1,2,3:	print (The) x1, " ya tiene", (n) x1;
					4,5,6:	print (The) x1, " ya tenía", (n) x1;
					7,8,9:	print (The) x1, " ya tendrá", (n) x1;
					}
					" echado el cerrojo.";
				}
			3:	switch (_grammatical_inflection) {
				1:	"Primero tengo que cerrar ", (the) x1, ".";
				2:	"Primero tienes que cerrar ", (the) x1, ".";
				3:	"Primero tiene que cerrar ", (the) x1, ".";
				4:	"Primero tenía que cerrar ", (the) x1, ".";
				5:	"Primero tenías que cerrar ", (the) x1, ".";
				6:	"Primero tenía que cerrar ", (the) x1, ".";
				7:	"Primero tendré que cerrar ", (the) x1, ".";
				8:	"Primero tendrás que cerrar ", (the) x1, ".";
				9:	"Primero tendrá que cerrar ", (the) x1, ".";
				}
			4:	if (second) switch (_grammatical_inflection) {
				1,2,3:	"No parece", (n) x1, " encajar en la cerradura.";
				4,5,6:	"No parecía", (n) x1, " encajar en la cerradura.";
				7,8,9:	"No parecerá", (n) x1, " encajar en la cerradura.";
				}
				switch (_grammatical_inflection) {
				1:	print "Necesito";
				2:	print "Necesitas";
				3:	print "Necesita";
				4:	print "Necesitaba";
				5:	print "Necesitabas";
				6:	print "Necesitaba";
				7:	print "Necesitaré";
				8:	print "Necesitarás";
				9:	print "Necesitará";
				}
				" algún tipo de llave.";
			5:	switch (_grammatical_inflection) {
				1:	if (second) "Cierro ", (the) x1, " con ", (the) second, ".";
					else "Echo el cerrojo ", (al_) x1, ".";
				2:	if (second) "Cierras ", (the) x1, " con ", (the) second,".";
					else "Echas el cerrojo ", (al_) x1, ".";
				3:	if (second) "Cierra ", (the) x1, " con ", (the) second, ".";
					else "Echa el cerrojo ", (al_) x1, ".";
				4:	if (second) "Cerré ", (the) x1, " con ", (the) second, ".";
					else "Eché el cerrojo ", (al_) x1, ".";
				5:	if (second) "Cerraste ", (the) x1," con ", (the) second,".";
					else "Echaste el cerrojo ", (al_) x1, ".";
				6:	if (second) "Cerró ", (the) x1, " con ", (the) second, ".";
					else "Echó el cerrojo ", (al_) x1, ".";
				7:	if (second) "Cerraré ", (the) x1, " con ", (the) second,".";
					else "Echaré el cerrojo ", (al_) x1, ".";
				8:	if (second) "Cerrarás ", (the) x1," con ", (the) second,".";
					else "Echarás el cerrojo ", (al_) x1, ".";
				9:	if (second) "Cerrará ", (the) x1, " con ", (the) second,".";
					else "Echará el cerrojo ", (al_) x1, ".";
				}
		}

!! TODO
	Look:
		!! La acción Look se genera cuando el jugador pone MIRAR, pero también
		!! de forma automática al entrar en una localidad nueva, o cuando el
		!! jugador sale/se baja de un objeto en el que estaba.
		!!
		!! Algunos de los mensajes que se definen aquí aparecen en el "título"
		!! de la localidad (lo que aparece en negrita antes de la descripción
		!! de la localidad).
		!!
		!!	1:	Aclaración a añadir tras el título si el jugador está subido
		!!		en un objeto.
		!!	2:	Aclaración a añadir tras el título si el jugador está dentro
		!!		de un objeto.
		!!	3:	Aclaración a añadir tras el título si el jugador ha sido
		!!		transformado en otro personaje mediante una llamada a
		!!		ChangePlayer(nuevo, 1); (sin el 1, la librería no intentará
		!!		mostrar este mensaje).
		!!	4:	Una vez que la librería ha mostrado la descripción de la
		!!		localidad, si el jugador estaba encima de un supporter, la
		!!		librería generará este mensaje 4 para mostrar qué más cosas
		!!		hay sobre el supporter.
		!!	Restante: 5,6 [6/11] antes 'default'
		!!		Son usados por la librería para listar los objetos "simples"
		!!		que hay en la localidad. Son objetos "simples" los que no
		!!		dan su propia auto-descrcipcion a través de la propiedad
		!!		"describe" o "initial".
		!!	7:	Respuesta estandar para MirarHacia [6/11]
		switch (n) {
			1:	print ", ";
				!! XXX: Se puede usar un mensaje de aclaración completamente
				!! personalizado definiendo la propiedad "clarification" en un
				!! objeto ("clarification" tiene que devolver un string o una
				!! rutina encargada de imprimir un string). Ej: SALA DE ESTAR,
				!! sentado en el sofá
				if ( x1 provides clarification ) {
					if (x1.clarification ofclass string)
						print (string) x1.clarification;
					else if (x1.clarification ofclass routine)
						indirect(x1.clarification);
				}
				else print "sobre ", (the) x1;
			2:	print ", ";
				!! XXX: Ver comportamiento de Look con n == 1
				if ( x1 provides clarification ) {
					if (x1.clarification ofclass string)
						print (string) x1.clarification;
					else if (x1.clarification ofclass routine)
						indirect( x1.clarification);
				}
				else print ", en ", (the) x1;
			3:	print " (como ", (object) x1 , ")";
			4:	print "^Sobre ", (the) x1;
				WriteListFrom(child(x1),
						ENGLISH_BIT + RECURSE_BIT + PARTINV_BIT
						+ TERSE_BIT + ISARE_BIT + CONCEAL_BIT);
				".";
			5,	!! XXX: Si la localidad actual tiene definida la propiedad
			6:	!! "inhibit_object_list" y está establecida como verdadero, se
				!! evita que se imprima el listado automático de objetos
				!! simples junto con la descripción de la localidad
				if (real_location provides inhibit_object_list)
					if (real_location.inhibit_object_list)
						return true;

				new_line;
				if (x1~=location) {
					if (x1 has supporter) print "Sobre "; else print "En ";
					print (the) x1;
					switch (_grammatical_inflection) {
					1:	print " puedo ver ";
					2:	print " puedes ver ";
					3:	print " puede ver ";
					4:	print " podía ver ";
					5:	print " podías ver ";
					6:	print " podía ver ";
					7:	print " podré ver ";
					8:	print " podrás ver ";
					9:	print " podrá ver ";
					}
				}
				else switch (_grammatical_inflection) {
				1:	print "Puedo ver ";
				2:	print "Puedes ver ";
				3:	print "Puede ver ";
				4:	print "Podía ver ";
				5:	print "Podías ver ";
				6:	print "Podía ver ";
				7:	print "Podré ver ";
				8:	print "Podrás ver ";
				9:	print "Podrá ver ";
				}
				if (n==5) print "también ";
				WriteListFrom(child(x1),
					ENGLISH_BIT + WORKFLAG_BIT + RECURSE_BIT
					+ PARTINV_BIT + TERSE_BIT + CONCEAL_BIT);
				".";
			7:	switch (_grammatical_inflection) {
				1:	print "No observo";
				2:	print "No observas";
				3:	print "No observa";
				4:	print "No observé";
				5:	print "No observaste";
				6:	print "No observó";
				7:	print "No observaré";
				8:	print "No observarás";
				9:	print "No observará";
				}
				" nada digno de mención al mirar hacia ", (the) x1, ".";
			8:	if (x1 has supporter) print " (sobre "; else print " (en ";
				print (the) x1, ")";
		}

!! TODO
	LookUnder:
		!!	1:	Error, estamos a oscuras.
		!!	2:	Éxito, mensaje por defecto.
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "Está";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "Estaba";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "Estará";
				}
				" demasiado oscuro como para ver algo.";
			2:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "veo";
						else print "vemos";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "ves";
						else print "veis";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "ve";
						else print "ven";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "vi";
						else print "vimos";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "viste";
						else print "visteis";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "vio";
						else print "vieron";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "veré";
						else print "veremos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "verás";
						else print "veréis";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "verá";
						else print "verán";
				}
				" nada inusual.";
		}

	Mild:
		!! Respuesta si se usa como primera palabra algún insulto suave.
		"Bastante.";

!! TODO
	Miscellany:
		!! Esta es una falsa acción, que se usa simplemente para agrupar aquí
		!! todos los mensajes de error del parser, los mensajes ante algunos
		!! metacommandos, o algnouns mensajes de librería no relacionados con
		!! acción alguna. La asignación de números a mensajes es bastante
		!! caprichosa.
		switch (n) {
			1:
				!! El jugador ha especificado objetos multiples, pero el parser
				!! tiene una lista que no admite más de 16, de modo que los
				!! restantes objetos no serán procesados.
				"(Sólo se consideran los dieciséis primeros objetos).";
			2:
				!! El jugador ha usado objetos múltiples, pero por alguna razón
				!! la lista del parser está vacía.
				"No se pudo determinar a qué objetos te has referido.";
			3:
				!! Mensaje de fin del relato. Has muerto.
				! TextoLlamativo(" Has muerto ");
				switch (_grammatical_inflection) {
					1:	print " He muerto ";
					2:	print " Has muerto ";
					3:	print " Ha muerto ";
					4:	print " Había muerto ";
					5:	print " Habías muerto ";
					6:	print " Había muerto ";
					7:	print " Habré muerto ";
					8:	print " Habrás muerto ";
					9:	print " Habrá muerto ";
				}
!! TODO - probar
			4:
				!! Mensaje de fin del relato. Victoria.
				! TextoLlamativo(" Has ganado ");
				switch (_grammatical_inflection) {
					1:	print " He ganado ";
					2:	print " Has ganado ";
					3:	print " Ha ganado ";
					4:	print " Había ganado ";
					5:	print " Habías ganado ";
					6:	print " Había ganado ";
					7:	print " Habré ganado ";
					8:	print " Habrás ganado ";
					9:	print " Habrá ganado ";
				}
!! TODO - mensaje del parser
			5:
				!! Mensaje a mostrar tras el fin del juego, para pedir al
				!! jugador si quiere reniciar, recuperar, anular, puntuación,
				!! curiosidades o terminar.
				print "^¿Quieres REINICIAR, RECUPERAR un juego guardado";
				#IFDEF DEATH_MENTION_UNDO;
					print ", ANULAR tu último movimiento";
				#ENDIF;
				! #IFNDEF NO_PUNTUACION;
					if (TASKS_PROVIDED==0)
						print ", ver la PUNTUACIÓN de este juego";
				! #ENDIF; ! NO_PUNTUACION
				if (deadflag==2 && AMUSING_PROVIDED==0)
					print ", ver algunas CURIOSIDADES";
				" o TERMINAR?";
			6:
				!! Error si el intérprete no tiene "undo"
				!! -- "[Tu intérprete no puede ~deshacer~ acciones,
				!! ¡lo siento!]";
				"Tu intérprete no puede ~DESHACER~ acciones.";
			#Ifdef TARGET_ZCODE; ![6/11]
			!! Otro error si el intérprete no tiene "undo", pero no había
			!! sido detectado correctamente.
			7:
				"~DESHACER~ falló. (No todos los intérpretes lo implementan.)";
			#Ifnot; ! TARGET_GLULX
			7:
				"No puedes ~DESHACER~ más.";
			#Endif; ! TARGET_
			8:
				!! Si el jugador no responde correctamente a la pregunta del
				!! mensaje [Miscellany,5]
				"Por favor, introduce una de las respuestas anteriores.";
!! TODO - cambiar mensaje
			9:
				!! Mensaje cuando se detecta, al final del turno, que ya no hay
				!! una fuente de luz en la localidad actual.
				switch (_grammatical_inflection) {
					1:	"^¡Me he quedado a oscuras!";
					2:	"^¡Te has quedado a oscuras!";
					3:	"^¡Se ha quedado a oscuras!";
					4:	"^¡Me había quedado a oscuras!";
					5:	"^¡Te habías quedado a oscuras!";
					6:	"^¡Se había quedado a oscuras!";
					7:	"^¡Me habré quedado a oscuras!";
					8:	"^¡Te habrás quedado a oscuras!";
					9:	"^¡Se habrá quedado a oscuras!";
				}
			10:
				!! Mensaje cuando el jugador introduce una linea en blanco.
				"No has introducido ninguna instrucción.";
			11:
				!! Si el jugador intenta "undo" al principio del juego
				!! -- "[No puedes ~deshacer~ lo que no has hecho.]";
				"No se puede ~DESHACER~ algo que no has hecho.";
			12:
				!! Si el jugador pone "undo" dos veces.
				!! -- "[No puedes ~deshacer~ dos veces seguidas. ¡Lo siento!]";
				"No se puede ~DESHACER~ dos veces seguidas.";
			13:
				!! Éxito en el "undo".
				"Retrocediendo al turno anterior.";
			14:
				!! Si el jugador pone EEPA (verbo para corregir), pero el
				!! parser no recordaba ninguna palabra mal. Ejmplo de uso del
				!! comando EEPA:
				!!		> SACA MAZANA VERDE DE LA CESTA
				!!		No vqeo eso por aquí.
				!!		> EEPA MANZANA
				!!		Sacas la manzana verde de la cesta de mimbre.
				!! -- "Lo siento, eso no puede corregirse.";
				"Eso no puede corregirse.";
			15:
				!! Se usa EEPA sin especificar la palabra corregida.
				"Has utilizado ~EEPA~ sin especificar qué palabra deseabas
				corregir.";
			16:
				!! Si el jugador pone EEPA seguido de dos o más palabras.
				"~EEPA~ sólo puede corregir una palabra.";
			17:
				!! Descripción del objeto Oscuridad.
				switch (_grammatical_inflection) {
				1,2,3:	"Está muy oscuro como para poder ver algo.";
				4,5,6:	"Estaba muy oscuro como para poder ver algo.";
				7,8,9:	"Estará muy oscuro como para poder ver algo.";
				}
			18:
				!! Nombre corto del objeto jugador.
				switch (_grammatical_inflection) {
					1,4,7:	print " mi mism", (o) player;
					2,5,8:	print " ti mism", (o) player;
					3,6,9:	print " si mism", (o) player;
				}
			19:
				!! Descripción del objeto jugador.
				!! -- "Tan buen aspecto como siempre.";
				<<Inv>>;
			20:
				!! Cuando el jugador pone PNJ, REPITE para que el PNJ haga otra
				!! vez la última acción.
				"Para repetir un comando como ~PERSONAJE, SALTA~, escribe
				~REPITE~, en lugar de ~PERSONAJE, REPITE~.";
			21:
				!! Cuando el jugador pone REPITE como primer commando del juego.
				"No hay comando que repetir.";
			22:
				!! El jugador ha comenzado la frase con una coma.
				"No se puede empezar una frase con una coma.";
			23:
				!! Cuando el jugador pone, por ejemplo; PEPE, COGE HACHA, pero
				!! no hay un objeto que responda al name PEPE.
				"Parece que has tratado de hablar con alguien, pero no se pudo
				identificar con quién.";
			24:
				!! Si el jugador intenta hablar con un objeto que no es
				!! "animate" ni "talkable" ("talkable" debe ponerse a objetos
				!! inanimates con los que se podría hablar, como un micrófono).
				"No puedes hablar con ", (the) x1, ".";
			25:	!! Hay palabras no comprendidas entre el nombre de un PNJ y la
				!! coma, ej: PEPE ZAFDSRGG, SALTA.
				!! -- "Para hablar con alguien intenta ~alguien, hola~ o algo
				!! -- así.";
				"Para iniciar una conversación, intenta órdenes del tipo:
				PERSONAJE, HOLA.";
			26:
				!! La gramática especifica que una acción debe efectuarse sobre
				!! un objeto en poder del jugador (token 'held'), pero el
				!! jugador lo ha intentado sobre un objeto que no tiene, aunque
				!! está a su alcance. El parser intentará automáticamente coger
				!! ese objeto antes de efectuar la acción. En este mensaje se
				!! avisa al jugador de esta intención.
				switch (_grammatical_inflection) {
				1:	"(Primero trato de ", (coge)"r ", (the) x1, ".)";
				2:	"(Primero tratas de ", (coge)"r ", (the) x1, ".)";
				3:	"(Primero trata de ", (coge)"r ", (the) x1, ".)";
				4:	"(Primero traté de ", (coge)"r ", (the) x1, ".)";
				5:	"(Primero trataste de ", (coge)"r ", (the) x1, ".)";
				6:	"(Primero trató de ", (coge)"r ", (the) x1, ".)";
				7:	"(Primero trataré de ", (coge)"r ", (the) x1, ".)";
				8:	"(Primero tratarás de ", (coge)"r ", (the) x1, ".)";
				9:	"(Primero tratará de ", (coge)"r ", (the) x1, ".)";
				}

			!! ERRORES DE PARSING: Estos errores son generados por la librería,
			!! a menos que el programador proporcione su propia función
			!! ParserError para manejo de errores.

			! 27:	!! manejado por ParserError.
			! 28:	!! manejado por ParserError.
			! 29:	!! manejado por ParserError.
			! 30:	!! manejado por ParserError.
			! 31:	!! manejado por ParserError.
			! 32:	!! manejado por ParserError.
			! 33:	!! manejado por ParserError.
			! 34:	!! manejado por ParserError.
			! 35:	!! manejado por ParserError.
			! 36:	!! manejado por ParserError.
			! 37:	!! manejado por ParserError.
			! 38:	!! manejado por ParserError.
			! 39:	!! manejado por ParserError.
			! 40:	!! manejado por ParserError.
			! 41:	!! manejado por ParserError.
			! 42:	!! manejado por ParserError.
			! 43:	!! manejado por ParserError.

!! TODO - cambiar mensaje
			44:
				!! El jugador ha intentado objetos múltiples usando TODO
				!! pero el parser no ha encontrado ninguno. Por ejemplo, COGE
				!! TODO o DEJA TODO si no hay nada cerca o en el inventario.
				!! Modificado en [020621] para dar un mensaje más coherente
				!! si el jugador tiene algún objeto en su inventario.
				if (action_to_be == ##Drop) {
					print "¡Pero si no llevas nada";
					if (children (player)) " de eso!";
					else "!";
				}
				switch (_grammatical_inflection) {
				1,2,3:	print "No hay nada para ";
				4,5,6:	print "No había nada para ";
				7,8,9:	print "No habrá nada para ";
				}
				LanguageVerb(verb_word);
				".";
!! TODO - mensaje del parser
			45:
				!! El jugador ha nombrado un PNJ ambiguo (hay más de noun con
				!! el mismo name cerca). El parser le pide aclaración. Este
				!! mensaje es la primera parte de la pregunta, el resto lo pone
				!! el parser (que es la lista de PNJs entre los que duda).
				!! Debemos poner a 1 la variable PreguntaCualExactamente cuando
				!! se generan este tipo de preguntas aclaratorias.
				print "¿Quién concretamente, ";
				PreguntaCualExactamente=1;
				ImprimirListaDudosos("o");
				!print "?^";
!! TODO - mensaje del parser
			46:
				!! El jugador ha nombrado un objeto ambiguo (hay más de objeto
				!! con el mismo nombre cerca). El parser le pide aclaración.
				!! Este mensaje es la primera parte de la pregunta, el resto lo
				!! pone el parser (que es la lista de objetos entre los que
				!! duda). Debemos poner a 1 la variable PreguntaCualExactamente
				!! cuando se generan este tipo de preguntas aclaratorias.
				print "¿Cuál concretamente, ";
				PreguntaCualExactamente=1;
				ImprimirListaDudosos("o");
				!print "?^";
!! TODO - mensaje del parser
			47:
				!! El jugador ha respondido "TODOS" o "AMBOS" a una pregunta
				!! aclaratoria como la anterior, pero el verbo no admite
				!! objetos múltiples.
				print "Desafortunadamente sólo puedes referirte a un objeto
				en este caso. ¿Cuál exactamente?^";
				PreguntaCualExactamente=1;
!! TODO - Tienes que indicar a quien tiene que/quieres <comando>...
			48:
				!! El jugador ha escrito una frase u orden a PSI incompleta,
				!! como BESA (verbo aplicado sobre PSIs normalmente). El parser
				!! le pregunta para que complete la frase.
				PreguntaCualExactamente = 1;
				if (IniciarPregunta() ==0 ) print "A quién";
				if (actor ~= player) print " tiene que ";
				else print " quieres ";
				IdiomaImprimirComando();
				if (actor~=player) print " ", (the) actor;
				print "?";
				new_line;
!! TODO - Tienes que indicar qué tiene que/quieres <comando>...
			49:
				!! El jugador ha escrito una frase u orden incompleta, como
				!! COGE (verbo aplicado sobre objetos normalmente). El parser
				!! le pregunta para que complete la frase.
				PreguntaCualExactamente = 1;
				if (IniciarPregunta() ==0 ) print "Qué";
				if (actor ~= player) print " tiene que ";
				else print " quieres ";
				IdiomaImprimirComando();
				if (actor~=player) print " ", (the) actor;
				print "?";
				new_line;
			!#IFNDEF NO_PUNTUACION;
!! TODO - mensaje del parser
			50:
				!! El jugador acaba de realizar una acción que puntúa (la
				!! librería ha detectado que la variable score ha cambiado de
				!! valor). Se informa de ello al player. El parámetro x1
				!! contiene el incremento (o decremento) en la puntuación.
				print "Tu puntuación ha ";
				if (x1 > 0) print "aumentado";
				else {
					x1 = -x1;
					print "disminuido";
				}
				print " en ", (number) x1, " punto";
				if (x1 > 1) print "s";
			!#ENDIF; ! NO_PUNTUACION
			51:
				!! El jugador ha intentado una acción con objeto múltiple
				!! (como COGE TODO). Esta acción es convertida por el parser en
				!! una serie de actiones COGE OBJETO1, COGE OBJETO2, etc... Si
				!! en la ejecución de alguna de estas actiones encuentra que la
				!! localidad del player ha cambiado, debe abortar el proceso.
				!! Este mensaje informa de ello al jugador.
				!!	-- (Ya que ha ocurrido algo dramático, se ha recortado la
				!!		lista de objetos sobre los que actuabas)
				"(Se ha producido un evento inesperado que ha obligado a
				recortar la lista de objetos sobre los que actuabas).";
			52:
				!! En los menús, se espera a que el player escriba un número
				!! para mostrar una entrada del menú. Si pulsa un numero
				!! incorrecto, se saca este mensaje. El parámetro x1 contiene
				!! el número más alto válido.
				new_line;
				print "Escribe un número del 1 al ", x1, ", 0 para volver a
				mostrarlo, o pulsa Intro.";
				new_line;
				return true;
			53:
				!! Mensaje que muestra el sistema de menús cuando espera una
				!! tecla.
				new_line;
				"Por favor, pulsa ESPACIO.";
			54:
				return true; ! FIXME
!				print_ret (parser) "Comentario guardado.";
			55:
				"Comentario NO guardado.";
			56:
				print ".^";
			57:
				print "?^";
		}

!! TODO
	No:
		!! Cuando el jugador pone NO, a secas, se genera esta acción. Está
		!! pensada por si el relato suelta una frase del estilo de "¿Pero tú
		!! eres tonto?" y el jugador responde NO. De todas formas, hay un
		!! problema, y es que NO es normalmente la acción Ir al noroeste. Si
		!! queremos que NO sea provisionalmente la acción No, entonces se debe
		!! poner a 1 la variable PreguntaSiNo antes de escribir el texto
		!! "¿Pero tú eres tonto?". En ese caso, el parser interpretará "NO"
		!! como la acción No, pero únicamente durante el siguiente turno.
		"Sólo era una pregunta retórica.";

!! TODO
	NotifyOff:
		"Notificación de puntuación desactivada.";

!! TODO
!!TODO - Mensaje del parser (parser_style)
	Objects:
		!! Ante el verbo "OBJETOS" se genera esta acción, que muestra una
		!! lista de todos los objetos que el jugador ha manipulado a lo largo
		!! del juego, junto con una indicación de qué hizo con ellos.
		!!
		!!	1:	Texto introductorio a la lista.
		!!	2:	Si no ha manejado aún ninguno.
		!!	3:	Indicación de que lo lleva puesto.
		!!	4:	Indicación de que lo lleva en su inventario.
		!!	5:	Indicación de quién lo tiene ahora (si lo tiene un PNJ).
		!!	6:	Indicación de dónde está el objeto (si está en una localidad).
		!!	7:	Indicación de dónde está el objeto (si está en un "entrable").
		!!	8:	Indicación de dónde está el objeto (si está en un recipiente).
		!!	9:	Indicación de dónde está el objeto (si está en un soporte).
		!!	10:	Indicación de que se ha perdido (no está en ninguno de los
		!!		casos anteriores).
		switch (n) {
			1:	"Objetos que has manejado:^";
			2:	"Ninguno.";
!! TODO - usar x1
			3:	print "   (puesto)";
			4:	print "   (contigo)";
!! TODO - usar x1
			5:	print "   (dejado con alguien)";
			6:	print "   (ahora en ", (name) x1, ")";
			7:	print "   (ahora en ", (the) x1, ")";
			8:	print "   (ahora dentro ", (del_) x1, ")";
			9:	print "   (ahora en ", (the) x1, ")";
!! TODO - usar x1
			10:	print "   (perdido)";
		}

!! TODO
	Open:
		!!	1:	Error, el objeto no tiene el atributo "openable".
		!!	2:	Error, el objeto es abrible, pero tiene "locked".
		!!	3:	Error, el objeto es abrible, pero ya tiene el atributo "open".
		!!	4:	Éxito, el objeto se abre, y además era recipiente. Se muestra
		!!		entoces la lista de objetos que había en su interior (si habia
		!!		algo).
		!!	5:	Éxito, el objeto se abre (pero no tiene nada en su
		!!		interior, o no era recipiente).
		switch (n) {
			1:	switch (_grammatical_inflection) {
				1,2,3:	"No es algo que pueda abrirse.";
				4,5,6:	"No era algo que se pudiese abrir.";
				7,8,9:	"No será algo que pueda abrirse.";
				}
			2:	switch (_grammatical_inflection) {
				1,2,3:	"Está", (n) x1, " cerrad", (o) x1, " con llave.";
				4,5,6:	"Estaba", (n) x1, " cerrad", (o) x1, " con llave.";
				7,8,9:	"Estará", (n) x1, " cerrad", (o) x1, " con llave.";
				}
			3:	switch (_grammatical_inflection) {
				1,2,3:	"Ya estaba", (n) x1, " abiert", (o) x1, ".";
				4,5,6:	"Ya estaba", (n) x1, " abiert", (o) x1, ".";
				7,8,9:	"Ya estará", (n) x1, " abiert", (o) x1, ".";
				}
			4:	switch (_grammatical_inflection) {
					1: print "Abro "; 	2: print "Abres ";	3: print "Abre ";
					4: print "Abrí ";	5: print "Abriste "; 6: print "Abrió ";
					7: print "Abriré ";	8: print "Abrirás "; 9: print "Abrirá ";
				}
				print (the) x1, ", descubriendo ";
				if (WriteListFrom(child(x1),
					ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT) == 0) {
					switch (_grammatical_inflection) {
					1,2,3:	"que está", (n) x1, " vací", (o) x1, ".";
					4,5,6:	"que estaba", (n) x1, " vací", (o) x1, ".";
					7,8,9:	"que estará", (n) x1, " vací", (o) x1, ".";
					}
				}
				".";
			5:	switch (_grammatical_inflection) {
					1: print "Abro "; 	2: print "Abres ";	3: print "Abre ";
					4: print "Abrí ";	5: print "Abriste "; 6: print "Abrió ";
					7: print "Abriré ";	8: print "Abrirás "; 9: print "Abrirá ";
				}
				print_ret (the) x1, ".";
		}

!!	Order:	see Answer.
!!		switch (GRAMMATICAL_INFLEXION) {
!!		1,2,3:	print_ret (The) x1," tiene", (n) x1," mejores cosas que hacer.";
!!		4,5,6:	print_ret (The) x1," tenía", (n) x1," mejores cosas que hacer.";
!!		}

	Places:
		!! El verbo "LUGARES" muestra un listado de los lugares que el jugador
		!! ha visitado. Aquí debemos escribir el texto introductorio a esa
		!! lista.
		switch (n) {
			1:  print "Has visitado: ";
			2:  print ".^";
		}

	Pray:
		print "La fe tal vez ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT, SECOND_PERSON_PRESENT, THIRD_PERSON_PRESENT:
				print "pueda";
			FIRST_PERSON_PAST, SECOND_PERSON_PAST, THIRD_PERSON_PAST:
				print "pudiese";
			FIRST_PERSON_FUTURE, SECOND_PERSON_FUTURE, THIRD_PERSON_FUTURE:
				print "podrá";
		}
		" resultar útil en una ocasión diferente.";

	Prompt:
		!! El prompt aparece justo antes de pedir una nueva línea al jugador.
		!! Puede definirse para que sea una frase, o se genere una frase
		!! aleatoria en cada turno, por ejemplo.
		new_line;
		print "> ";

!! TODO
	Pronouns:
		!! Esta acción (generada por el verbo PRONOMBRES) muestra una lista
		!! de qué significa en ese momento para el parser cada pronombre:
		!! -lo, -la, -los, -las...
		!!
		!!	1:	Texto introductorio.
		!!	2:	La palabra "es".
		!!	3:	Texto a mostrar si el pronombre no está definido.
		!!	4:	Si el juego no define pronombres.
		!!	5:	[6/11].
		switch (n) {
			1:	print "En este momento, ";
			2:	print "es ";
			3:	print "no está definido";
			4:	print "el juego no conoce ningún pronombre.";
				new_line;
				return true;
			5:	print ".";
				new_line;
				return true;
		}

!! TODO
	Pull, Push, Turn:
		!! Las acciones Pull, Push y Turn generan todas ellas los
		!! mismos mensajes, pero pueden darse 4 casos:
		!!	1:	El objeto tiene el atributo 'static'.
		!!	2:	El objeto tiene el atributo 'scenery'.
		!!	3:	El objeto no es 'static' ni 'scenery'.
		!!	4:	El objeto es un ser animado.
		!! [Nota, si el objeto tiene ambos 'estatico' y 'escenario' se
		!! está también en el caso 1.]
		switch (n) {
			1:	switch (_grammatical_inflection) {
				1,2,3:	print "Está", (n) x1;
				4,5,6:	print "Estaba", (n) x1;
				7,8,9:	print "Estará", (n) x1;
				}
				" firmemente sujet", (o) x1, ".";
			2:	switch (_grammatical_inflection) {
				1:	"No soy capaz.";
				2:	"No eres capaz.";
				3:	"No es capaz.";
				4:	"No fui capaz.";
				5:	"No fuiste capaz.";
				6:	"No fue capaz.";
				7:	"No seré capaz.";
				8:	"No serás capaz.";
				9:	"No será capaz.";
				}
			3:	switch (_grammatical_inflection) {
				1,2,3:	"No ocurre nada, aparentemente.";
				4,5,6:	"No ocurrió nada, aparentemente.";
				7,8,9:	"No ocurrirá nada, aparentemente.";
				}
			4:	switch (_grammatical_inflection) {
				1,2,3:	"Eso sería, como poco, maleducado.";
				4,5,6:	"Eso hubiese sido, como poco, maleducado.";
				7,8,9:	"Eso sería, como poco, maleducado.";
				}
		}

!!	Push:	see Pull.

!! TODO
	PushDir:
		!! La acción PushDir se genera ante frases como EMPUJA EL COCHE HACIA
		!! EL NORTE. Hay 3 casos posibles:
		!!	1:	Si el juego no ha previsto la posibilidad de empujar ese
		!!		objeto hacia una dirección (o sea, no llama a la rutina
		!!		PermitirEmujarDir). Esta es la respuesta por defecto más
		!!		habitual.
		!!	2:	Si el jugador pone tras HACIA algo que no es una dirección.
		!!		(respuesta por defecto en este caso).
		!!	3:	Si intenta empujar hacia arriba o hacia abajo.
		switch (n) {
			1:	switch (_grammatical_inflection) {
				1:	"No creo que empujar ", (the) x1, " sirva de nada.";
				2:	"No crees que empujar ", (the) x1, " sirva de nada.";
				3:	"No cree que empujar ", (the) x1, " sirva de nada.";
				4:	"No creía que empujar ", (the) x1, " hubiese servido
					de nada.";
				5:	"No creías que empujar ", (the) x1, " hubiese servido
					de nada.";
				6:	"No creía que empujar ", (the) x1, " hubiese servido
					de nada.";
				7,8,9:	"Empujar ", (the) x1, " no servirá de nada.";
				}
			2:	switch (_grammatical_inflection) {
					1,2,3:	"Eso no es una dirección.";
					4,5,6:	"Eso no era una dirección.";
					7,8,9:	"Eso no será una dirección.";
				}
			3:	switch (_grammatical_inflection) {
					1:	print "No puedo";
					2:	print "No puedes";
					3:	print "No puede";
					4:	print "No podía";
					5:	print "No podías";
					6:	print "No podía";
					7:	print "No podré";
					8:	print "No podrás";
					9:	print "No podrá";
				}
				" empujar", (lo) x1, " en esa dirección.";
		}

!! TODO
	PutOn:
		!!	1:	Error, el objeto no está en poder del jugador. [Nota, conviene
		!!		mirar en este caso si el objeto es animado o no, para generar
		!!		un mensaje más adecuado].
		!!	2:	Error, el jugador intenta poner un objeto sobre sí mismo.
		!!	3:	Error, el jugador intenta poner el objeto sobre otro que no
		!!		tiene el atributo "supporter".
		!!	4:	Error, el jugador intenta poner un objeto sobre el propio
		!!		jugador.
		!!	5:	Aviso, el objeto es una prenda puesta. La librería va a
		!!		quitárselo automáticamente antes de reintentar la acción PutOn.
		!!	6:	Error, se intenta poner el objeto sobre otro en el que ya no
		!!		queda sitio (el número de objetos que caben en el soporte se
		!!		indica en su propiedad "capacity").
		!!	7:	Exito. Mensaje a mostrar para cada objeto puesto cuando se
		!!		ponen muchos (ej: PON TODO SOBRE LA MESA).
		!!	8:	Exito. Mensaje a mostrar cuando se pone un objeto sobre otro.
		switch (n) {
			1:	switch (_grammatical_inflection) {
				1:	if (x1 has animate)
						"Antes tendría que ", (coge)"rl", (o) x1, " y no sé
						si se dejará", (n) x1, ".";
					else
						"Necesito tener ", (the) x1, " para poder poner",
						(lo) x1, " donde sea.";
				2:	if (x1 has animate)
						"Antes tendrías que ", (coge)"rl", (o) x1, " y no sabes
						si se dejará", (n) x1, ".";
					else
						"Necesitas tener ", (the) x1, " para poder poner",
						(lo) x1, " donde sea.";
				3:	if (x1 has animate)
						"Antes tendría que ", (coge)"rl", (o) x1, " y no sabe
						si se dejará", (n) x1, ".";
					else
						"Necesita tener ", (the) x1, " para poder poner",
						(lo) x1, " donde sea.";
				4:	if (x1 has animate)
						"Antes tendría que haber", (lo) x1, " cogido, y no
						sabía si ", (the) x1, " se hubiese", (n) x1,
						" dejado.";
					else
						"Hubiese necesitado tener ", (the) x1, " para poder
						poner", (lo) x1, " donde fuese.";
				5:	if (x1 has animate)
						"Antes tendrías que haber", (lo) x1, " cogido, y no
						sabías si ", (the) x1, " se hubiese", (n) x1,
						" dejado.";
					else
						"Hubieses necesitado tener ", (the) x1, " para poder
						poner", (lo) x1, " donde fuese.";
				6:	if (x1 has animate)
						"Antes tendría que haber", (lo) x1, " cogido, y no
						sabía si ", (the) x1, " se hubiese", (n) x1,
						" dejado.";
					else
						"Hubiese necesitado tener ", (the) x1, " para poder
						poner", (lo) x1, " donde fuese.";
				7:	if (x1 has animate)
						"Antes tendré que haber", (lo) x1, " cogido, y no
						sabré si ", (the) x1, " se habría", (n) x1,
						" dejado.";
					else
						"Necesitaré tener ", (the) x1, " para poder
						poner", (lo) x1, " donde sea.";
				8:	if (x1 has animate)
						"Antes tendrás que haber", (lo) x1, " cogido, y no
						sabrás si ", (the) x1, " se habría", (n) x1,
						" dejado.";
					else
						"Necesitarás tener ", (the) x1, " para poder
						poner", (lo) x1, " donde sea.";
				9:	if (x1 has animate)
						"Antes tendrá que haber", (lo) x1, " cogido, y no
						sabrá si ", (the) x1, " se habría", (n) x1,
						" dejado.";
					else
						"Necesitará tener ", (the) x1, " para poder
						poner", (lo) x1, " donde sea.";
				}
			2:	switch (_grammatical_inflection) {
					1:	print "No puedo";
					2:	print "No puedes";
					3:	print "No puede";
					4:	print "No podía";
					5:	print "No podías";
					6:	print "No podía";
					7:	print "No podré";
					8:	print "No podrás";
					9:	print "No podrá";
				}
				" poner un objeto sobre sí mismo.";
			3:	switch (_grammatical_inflection) {
				1,2,3:	"Poner cosas sobre ", (the) x1," no servirá de nada.";
				4,5,6:	"Poner cosas sobre ", (the) x1, " no hubiese servido
						de nada.";
				7,8,9:	"Poner cosas sobre ", (the) x1," no servirá de nada.";
				}
!! TODO - cambiar mensaje
			4:	switch (_grammatical_inflection) {
					1:	"Me falta destreza.";
					2:	"Te falta destreza.";
					3:	"Le falta destreza.";
					4:	"Me faltaba destreza.";
					5:	"Te faltaba destreza.";
					6:	"Le faltaba destreza.";
					7:	"Me faltará destreza.";
					8:	"Te faltará destreza.";
					9:	"Le faltará destreza.";
				}
			5:	switch (_grammatical_inflection) {
				1:	"(Primero me ", (lo) x1, " quito.)^";
				2:	"(Primero te ", (lo) x1, " quitas.)^";
				3:	"(Primero se ", (lo) x1, " quita.)^";
				4:	"(Primero me ", (lo) x1, " quité.)^";
				5:	"(Primero te ", (lo) x1, " quitaste.)^";
				6:	"(Primero se ", (lo) x1, " quitó.)^";
				7:	"(Primero me ", (lo) x1, " quitaré.)^";
				8:	"(Primero te ", (lo) x1, " quitarás.)^";
				9:	"(Primero se ", (lo) x1, " quitará.)^";
				}
			6:	switch (_grammatical_inflection) {
					1,2,3:	print "No queda";
					4,5,6:	print "No quedaba";
					7,8,9:	print "No quedará";
				}
				" sitio en ", (the) x1, " para poner nada más.";
			7:	"Hecho.";
			8:	switch (_grammatical_inflection) {
					1:	print "Coloco ";
					2:	print "Colocas ";
					3:	print "Coloca ";
					4:	print "Coloqué ";
					5:	print "Colocaste ";
					6:	print "Colocó ";
					7:	print "Colocaré ";
					8:	print "Colocarás ";
					9:	print "Colocará ";
				}
				print_ret (the) x1, " sobre ", (the) second, ".";
		}

!! TODO
	Quit:
		!!	1:	Respuesta al comando FIN.
		!!	2:	Respuesta si el jugador escribe algo distinto de "si" o "no".
		switch (n) {
			1:
				print "Por favor, responde SI o NO: ";
			2:
				print "¿Realmente quieres abandonar el relato? ";
		}
		return true;

!! TODO
	Remove:
		!!	1:	El recipiente que contiene el objeto que el jugador quiere
		!!		sacar, está cerrado. (x1 apunta al objeto, no al recipiente,
		!!		el cuál puede obtenerse con parent(x1)).
		!!	2:	El objeto no está dentro del recipiente que el jugador ha dicho.
		!!	3:	Éxito.
		switch (n) {
			1:	print "Por desgracia ", (the) parent(x1);
				switch (_grammatical_inflection) {
					1,2,3:	print " está", (n) parent(x1);
					4,5,6:	print " estaba", (n) parent(x1);
					7,8,9:	print " estará", (n) parent(x1);
				}
				" cerrad", (o) parent(x1), ".";
			2:	switch (_grammatical_inflection) {
				1,2,3:	if (second has animate)
							"¡Pero si no ", (lo) x1, " tiene", (n) second,"!";
						"¡Pero si no está", (n) x1, " ahí ahora!";
				4,5,6:	if (second has animate)
							"¡Pero si no ", (lo) x1, " tenía", (n) second,"!";
						"¡Pero si no estaba", (n) x1, " ahí!";
				7,8,9:	if (second has animate)
							"¡Pero si no ", (lo) x1, " tendrá", (n) second, "!";
						"¡Pero si no estará", (n) x1, " ahí!";
				}
			3:	if (verb_word == 'quita') "Quitad", (o) x1, ".";
				"Sacad", (o) x1, ".";
		}

!! TODO
	Restart:
		!!	1:	Respuesta al comando REINICIAR.
		!!	2:	Si no se puede reiniciar.
		switch (n) {
			1:	print "¿Realmente quieres reiniciar el relato?";
			2:	"Error al reiniciar la partida.";
		}

!! TODO
	Restore:
		!!	1:	Si no se pudo cargar la partida con LOAD.
		!!	2:	Éxito (no llega a mostrarse, porque en caso de éxito el estado
		!!		del juego cambia al momento en que se salvó. El "Ok" que se ve
		!!		entonces es el del comando Salvar.
		switch (n) {
			1:	"Error. No se pudo recuperar la
				partida.";
			2:	print "Partida cargada.";
				new_line; <<Look>>;
		}

!! TODO
	Rub:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT, SECOND_PERSON_PRESENT, THIRD_PERSON_PRESENT:
				print "Ya está", (n) x1;
			FIRST_PERSON_PAST, SECOND_PERSON_PAST, THIRD_PERSON_PAST:
				print "Ya estaba", (n) x1;
			FIRST_PERSON_FUTURE, SECOND_PERSON_FUTURE, THIRD_PERSON_FUTURE:
				print "Ya estará", (n) x1;
		}
		" bastante limpi", (o) x1, ".";

!! TODO
	Save:
		!!	1:	Si no se pudo guardar el juego.
		!!	2:	Éxito.
		switch (n) {
			1:	"Error. No se pudo guardar la partida.";
			2:	"Partida guardada.";
		}

!! TODO
	Score:
		!! Puntuación del juego. Puede activarse porque el jugador lo pide
		!! (con el verbo "PUNTUACION") o porque el juego ha terminado. En
		!! este ultimo caso, la variable "deadflag" valdrá true.
		switch (n) {
			1:
				if (deadflag) print "En este juego, tu puntuación ha sido ";
				else print "Hasta el momento tu puntuación es ";
				print score, " de un total de ", MAX_SCORE,
				", en ", turns, " turno";
				if (turns>1) print "s";
				print ".";
				new_line;
				return;
			2:	"Este juego no tiene conteo de puntuación.";
		}

!! TODO
	ScriptOff:
		!!	1:	Error ya estaba desactivada la transcrcipción.
		!!	2:	Éxito.
		switch (n) {
			1:	"La transcripción ya estaba
				desactivada.";
			2:	new_line; "Fin de la transcripción.";
			3:	"Intento fallido de finalización de
				transcripción.";
		}

!! TODO
	ScriptOn:
		!!	1:	Error, ya estaba activada la transcrcipción.
		!!	2:	Éxito (parte inicial del mensaje, la librería añade el título
		!!		del juego obtenido de la constante Historia).
		switch (n) {
			1:	"La transcripción ya estaba activada.";
			2:	"Iniciando la transcripción de:";
			3:	"Intento fallido de comienzo de la
				transcripción.";
		}

!! TODO
	Search:
		!! La acción Search se genera ante la frase MIRA EN RECIPIENTE, MIRA EN
		!! SOPORTE, REGISTRA OBJETO.
		!!
		!!	1:	Error, estamos a oscuras.
		!!	2:	Éxito examinando soporte, pero no hay nada sobre él.
		!!	3:	Éxito examinando soporte, listar lo que hay.
		!!	4:	El objeto examinado no es soporte ni recipiente, mensaje
		!!		estándar indicando que no se encuentra nada.
		!!	5:	Error, El objeto examinado es recipiente, pero está cerrado.
		!!	6:	Éxito, el objeto examinado es recipiente abierto, pero no
		!!		tiene nada dentro.
		!!	7:	Éxito, el objeto examinado es recipiente abierto y tiene
		!!		cosas dentro. Se las lista.
		switch (n) {
			1:	switch (_grammatical_inflection) {
					1,2,3:	print "Está";
					4,5,6:	print "Estaba";
					7,8,9:	print "Estará";
				}
				" demasiado oscuro como para ver algo.";
			2:	switch (_grammatical_inflection) {
					1,2,3:	"No hay nada sobre ", (the) x1, ".";
					4,5,6:	"No había nada sobre ", (the) x1, ".";
					7,8,9:	"No habrá nada sobre ", (the) x1, ".";
				}
!! TODO - comprobar funcionamiento
			3:	print "Sobre ", (the) x1;
				WriteListFrom(child(x1),
					TERSE_BIT + ENGLISH_BIT + ISARE_BIT + CONCEAL_BIT);
				".";
			4:	switch (_grammatical_inflection) {
					1:	print "No encuentro";
					2:	print "No encuentras";
					3:	print "No encuentra";
					4:	print "No encontré";
					5:	print "No encontraste";
					6:	print "No encontró";
					7:	print "No encontraré";
					8:	print "No encontrarás";
					9:	print "No encontrará";
				}
				" nada interesante.";
			5:	switch (_grammatical_inflection) {
				1:	"No puedo ver lo que hay dentro ", (del_) x1, " porque ",
					(esta) x1, " cerrad", (o) x1, ".";
				2:	"No puedes ver lo que hay dentro ", (del_) x1, " porque ",
					(esta) x1, " cerrad", (o) x1, ".";
				3:	"No puede ver lo que hay dentro ", (del_) x1, " porque ",
					(esta) x1, " cerrad", (o) x1, ".";
				4:	"No podía ver lo que hay dentro ", (del_) x1, " porque
					estaba", (n) x1, " cerrad", (o) x1, ".";
				5:	"No podías ver lo que hay dentro ", (del_) x1, " porque
					estaba", (n) x1, " cerrad", (o) x1, ".";
				6:	"No podía ver lo que hay dentro ", (del_) x1, " porque
					estaba", (n) x1, " cerrad", (o) x1, ".";
				7:	"No podré ver lo que hay dentro ", (del_) x1, " porque
					estará", (n) x1, " cerrad", (o) x1, ".";
				8:	"No podrás ver lo que hay dentro ", (del_) x1, " porque
					estará", (n) x1, " cerrad", (o) x1, ".";
				9:	"No podrá ver lo que hay dentro ", (del_) x1, " porque
					estará", (n) x1, " cerrad", (o) x1, ".";
				}
			6:	switch (_grammatical_inflection) {
					1,2,3:	print (The) x1, " ", (esta) x1;
					4,5,6:	print (The) x1, " estaba", (n) x1;
					7,8,9:	print (The) x1, " estará", (n) x1;
				}
				" vací", (o) x1, ".";
			7:	print "En ", (the) x1;
				WriteListFrom(child(x1),
					TERSE_BIT + ENGLISH_BIT + ISARE_BIT + CONCEAL_BIT);
				".";
		}

!! TODO
	Set:
		!! Set sale ante la frase FIJA OBJETO o AJUSTA OBJETO
		switch (_grammatical_inflection) {
			1:	"No, no puedo.";
			2:	"No, no puedes.";
			3:	"No, no puede.";
			4:	"No, no podía.";
			5:	"No, no podías.";
			6:	"No, no podía.";
			7:	"No, no podré.";
			8:	"No, no podrás.";
			9:	"No, no podrá.";
		}

	SetTo:
		!! SetTo sale ante la frase AJUSTA DIAL A 23 o FIJA CONTROL EN
		!! ACTIVADO, o PON REGULADOR A 30
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT, SECOND_PERSON_PRESENT, THIRD_PERSON_PRESENT:
				print "Eso no puede";
			FIRST_PERSON_PAST, SECOND_PERSON_PAST, THIRD_PERSON_PAST:
				print "Aquello no podía";
			FIRST_PERSON_FUTURE, SECOND_PERSON_FUTURE, THIRD_PERSON_FUTURE:
				print "Aquello no podrá";
		}
		" regularse a ningún valor.";

!! TODO
	Show:
		!!	1:	Error, el jugador intenta mostrar un objeto que no tiene.
		!!	2:	Aviso, se ha enviado la acción Show al PNJ, pero este no ha
		!!		respondido. En este caso x1 apunta al PNJ y no al objeto que
		!!		le hemos mostrado.
		switch (n) {
			1:	switch (_grammatical_inflection) {
					1:	"No tengo ", (the) x1, ".";
					2:	"No tienes ", (the) x1, ".";
					3:	"No tiene ", (the) x1, ".";
					4:	"No tenía ", (the) x1, ".";
					5:	"No tenías ", (the) x1, ".";
					6:	"No tenía ", (the) x1, ".";
					7:	"No tendré ", (the) x1, ".";
					8:	"No tendrás ", (the) x1, ".";
					9:	"No tendrá ", (the) x1, ".";
				}
			2:	switch (_grammatical_inflection) {
				1,2,3:	print_ret (The) x1, " no muestra", (n) x1,
						" ningún interés.";
				4,5,6:	print_ret (The) x1, " no mostraba", (n) x1,
						" ningún interés.";
				7,8,9:	print_ret (The) x1, " no mostrará", (n) x1,
						" ningún interés.";
				}
		}

!! TODO
	Sing:
		switch (_grammatical_inflection) {
			1:	"Canto fatal.";
			2:	"Cantas fatal.";
			3:	"Canta fatal.";
			4:	"Cantaba fatal.";
			5:	"Cantabas fatal.";
			6:	"Cantaba fatal.";
			7:	"Cantaré fatal.";
			8:	"Cantarás fatal.";
			9:	"Cantará fatal.";
		}

!! TODO
	Sleep:
		print "No estoy especialmente somnolient", (o) player, "."; ! FIXME

!! TODO
	Smell:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsSingularNoun(player)) print "huelo";
				else print "olemos";
			SECOND_PERSON_PRESENT:
				if (IsSingularNoun(player)) print "hueles";
				else print "oléis";
			THIRD_PERSON_PRESENT:
				if (IsSingularNoun(player)) print "huele";
				else print "huelen";
			FIRST_PERSON_PAST:
				if (IsSingularNoun(player)) print "olía";
				else print "olíamos";
			SECOND_PERSON_PAST:
				if (IsSingularNoun(player)) print "olías";
				else print "olíais";
			THIRD_PERSON_PAST:
				if (IsSingularNoun(player)) print "olía";
				else print "olían";
			FIRST_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "oleré";
				else print "oleremos";
			SECOND_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "olerás";
				else print "oleréis";
			THIRD_PERSON_FUTURE:
				if (IsSingularNoun(player)) print "olerá";
				else print "olerán";
			}
			" nada extraño.";

	Sorry:
		!! Esta acción se genera si el usuario introduce "LO SIENTO",
		!! "PERDONA" o cosas similares.
		!! TODO - Cambiar por un mensaje más apropiado.
		"Oh, no es necesario que te disculpes.";

!! TODO
	Squeeze:
		!!	1:	Tratar de retorcer un ser animado.
		!!	2:	Cualquier otro objeto.
		switch (n) {
			!! -- "¡Las manos quietas!";
			1:	switch (_grammatical_inflection) {
					1:	"No creo que deba.";
					2:	"En realidad no crees que debas.";
					3:	"No cree que deba.";
					4:	"No se me hubiese ocurrido hacer algo así.";
					5:	"No se te hubiese ocurrido hacer algo así.";
					6:	"No se le hubiese ocurrido hacer algo así.";
					7:	"No se me ocurrirá hacer algo así.";
					8:	"No se te ocurrirá hacer algo así.";
					9:	"No se le ocurrirá hacer algo así.";
				}
			2:	switch (_grammatical_inflection) {
					1:	"No consigo nada haciendo eso.";
					2:	"No consigues nada haciendo eso.";
					3:	"No consigue nada haciendo eso.";
					4:	"No conseguí nada haciendo eso.";
					5:	"No conseguiste nada haciendo eso.";
					6:	"No consiguió nada haciendo eso.";
					7:	"No conseguiré nada haciendo eso.";
					8:	"No conseguirás nada haciendo eso.";
					9:	"No conseguirá nada haciendo eso.";
				}
		}

!! TODO - Recomendar AYUDA
	Strong:
		!! Respuesta si se usa como primera palabra algún taco.
		!! TODO - Cambiar por un mensaje más apropiado.
		print "Los verdaderos aventureros no ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT, SECOND_PERSON_PRESENT, THIRD_PERSON_PRESENT:
				print "usan";
			FIRST_PERSON_PAST, SECOND_PERSON_PAST, THIRD_PERSON_PAST:
				print "usaban";
			FIRST_PERSON_FUTURE, SECOND_PERSON_FUTURE, THIRD_PERSON_FUTURE:
				print "usarán";
		}
		" ese vocabulario.";

	Swim:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT, SECOND_PERSON_PRESENT, THIRD_PERSON_PRESENT:
				print "es";
			FIRST_PERSON_PAST, SECOND_PERSON_PAST, THIRD_PERSON_PAST:
				print "era";
			FIRST_PERSON_FUTURE, SECOND_PERSON_FUTURE, THIRD_PERSON_FUTURE:
				print "será";
		}
		" un sitio apropiado para ponerse a nadar.";

!! TODO
	Swing:
		switch (_grammatical_inflection) {
			1:	"No parece", (n) x1, " el lugar más adecuado en el que
				columpiarme.";
			2:	"No parece", (n) x1, " el lugar más adecuado en el que
				columpiarte.";
			3:	"No parece", (n) x1, " el lugar más adecuado en el que
				columparse.";
			4:	"No parecía", (n) x1, " el lugar más adecuado en el que
				columpiarme.";
			5:	"No parecía", (n) x1, " el lugar más adecuado en el que
				columpiarte.";
			6:	"No parecía", (n) x1, " el lugar más adecuado en el que
				columpiarse.";
			7:	"No parecerá", (n) x1, " el lugar más adecuado en el que
				columpiarme.";
			8:	"No parecerá", (n) x1, " el lugar más adecuado en el que
				columpiarte.";
			9:	"No parecerá", (n) x1, " el lugar más adecuado en el que
				columpiarse.";
		}

!! TODO
	SwitchOff:
		!!	1:	Error, el objeto no tiene el atributo "switchable".
		!!	2:	Error, el objeto ya tenia desactivado el atributo "on".
		!!	3:	Éxito, el objeto tiene ahora desactivado "on".
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						"No es algo que pueda apagarse.";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						"No era algo que se pudiese apagar.";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"No será algo que pueda apagarse.";
				}
			2:	print "Ya ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "estaba", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "estará", (n) x1;
				}
				" apagad", (o) x1, ".";
			3:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "Apago";
						else print "Apagamos";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "Apagas";
						else print "Apagáis";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "Apaga";
						else print "Apagan";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "Apagué";
						else print "Apagamos";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "Apagaste";
						else print "Apagasteis";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "Apagó";
						else print "Apagaron";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "Apagaré";
						else print "Apagaremos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "Apagarás";
						else print "Apagaréis";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "Apagará";
						else print "Apagarán";
				}
				" ", (the) x1, ".";
		}

!! TODO
	SwitchOn:
		!! Generada al intentar ENCIENDE OBJETO si el objeto tiene el
		!! atributo "conmutable". Observar que si no lo tiene, la acción
		!! que se genera será sin embargo Quemar.
		!!	1:	Error, el objeto no es conmutable (este error no aparecerá
		!!		si el jugador pone ENCIENDE OBJETO, ya que en este caso la
		!!		acción generada será Quemar objeto, pero puede aparecer si
		!!		pone CONECTA OBJETO).
		!!	2:	Error, el objeto ya tenía el atributo "on".
		!!	3:	Éxito, el objeto tiene ahora activado "on".
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						"No es algo que pueda encenderse.";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						"No era algo que se pudiese encender.";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"No será algo que pueda encenderse.";
				}
			2:	print "Ya ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "estaba", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "estará", (n) x1;
				}
				" encendid", (o) x1, ".";
			3:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "Enciendo";
						else print "Encendemos";
					SECOND_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "Enciendes";
						else print "Encendéis";
					THIRD_PERSON_PRESENT:
						if (IsSingularNoun(player)) print "Enciende";
						else print "Encienden";
					FIRST_PERSON_PAST:
						if (IsSingularNoun(player)) print "Encendí";
						else print "Encendimos";
					SECOND_PERSON_PAST:
						if (IsSingularNoun(player)) print "Encendiste";
						else print "Encendisteis";
					THIRD_PERSON_PAST:
						if (IsSingularNoun(player)) print "Encendió";
						else print "Encendieron";
					FIRST_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "Encenderé";
						else print "Encenderemos";
					SECOND_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "Encenderás";
						else print "Encenderéis";
					THIRD_PERSON_FUTURE:
						if (IsSingularNoun(player)) print "Encenderá";
						else print "Encenderán";
				}
				" ", (the) x1, ".";
		}

!! TODO
	Take:
		!! Hay 13 casos diferentes. Se trata de 1 mensaje de éxito y 11
		!! mensajes de error y un aviso:
		!!	1:	Éxito.
		!!	2:	Error, el objeto cogido es el propio jugador.
		!!	3:	Error, el objeto cogido es un objeto animado.
		!!	4:	Error, el jugador está subido o metido en el objeto que intenta
		!!		coger.
		!!	5:	Error, el jugador ya tenía ese objeto en su inventario.
		!!	6:	Error, el objeto está en poder de un ser animado [x1 apunta
		!!		al ser, no al objeto, el cual puede obtenerse en la variable
		!!		"noun"].
		!!	7:	Error, el objeto es un sub-objeto de otro (está dentro de un
		!!		objeto que tiene el atributo "transparent", pero no tiene el
		!!		atributo "container" ni "supporter").
		!!	8:	Error, el objeto está dentro de otro, pero este otro no tiene
		!!		el atributo "container" ni "supporter" ni "transparent"
		!!		(probablemente un error de programación).
		!!	9:	Error, el objeto está dentro de un recipiente cerrado.
		!!	10:	Error, el objeto tiene el atributo "scenery".
		!!	11:	Error, el objeto tiene el atributo "static".
		!!	12:	Error, el jugador lleva demasiados objetos.
		!!	13: Mensaje de aviso, la librería ha decidido mover objetos del
		!!		inventario al "objeto saco" para hacer sitio y que el jugador
		!!		pueda coger el objeto. [El objeto saco es uno que puede
		!!		declarar el programador. Si el jugador lo coge y lo lleva
		!!		consigo, la librería lo usará automáticamente como mochila
		!!		para descargar al jugador cuando sea necesario].
		switch (n) {
			1:	if (dialecto_sudamericano) print "Tomad"; else print "Cogid";
				print_ret (o) noun, ".";
			2:	switch (_grammatical_inflection) {
					1:	"Siempre me tengo a mí mism", (o) player, ".";
					2:	"Siempre te tienes a tí mism", (o) player, ".";
					3:	"Siempre se tiene a sí mism", (o) player, ".";
					4:	"Siempre me he tenido a mí mism", (o) player, ".";
					5:	"Siempre te has tenido a tí mism", (o) player, ".";
					6:	"Siempre se ha tenido a sí mism", (o) player, ".";
					7:	"Siempre me tendré a mí mism", (o) player, ".";
					8:	"Siempre te tendrás a tí mism", (o) player, ".";
					9:	"Siempre se tendrá a sí mism", (o) player, ".";
				}
			3:	switch (_grammatical_inflection) {
				1:	"No creo que ", (al_) x1, " le", (s) x1, " gustara.";
				2:	"No crees que ", (al_) x1, " le", (s) x1, " gustara.";
				3:	"No cree que ", (al_) x1, " le", (s) x1, " gustara.";
				4:	"No creía que ", (al_) x1, " le", (s) x1, " hubiese
					gustado.";
				5:	"No creías que ", (al_) x1, " le", (s) x1, " hubiese
					gustado.";
				6:	"No creía que ", (al_) x1, " le", (s) x1, " hubiese
					gustado.";
				7:	"No lo creeré buena idea.";
				8:	"No lo creerás buena idea.";
				9:	"No lo creerá buena idea.";

				}
			4:	switch (_grammatical_inflection) {
					1:	print "Tengo que ";
						if (x1 has supporter) print "bajarme ";
						else print "salir ";
					2:	print "Tienes que ";
						if (x1 has supporter) print "bajarte ";
						else print "salir ";
					3:	print "Tiene que ";
						if (x1 has supporter) print "bajarse ";
						else print "salir ";
					4:	print "Tenía que ";
						if (x1 has supporter) print "bajarme ";
						else print "salir ";
					5:	print "Tenías que ";
						if (x1 has supporter) print "bajarte ";
						else print "salir ";
					6:	print "Tenía que ";
						if (x1 has supporter) print "bajarse ";
						else print "salir ";
					7:	print "Tendré que ";
						if (x1 has supporter) print "bajarme ";
						else print "salir ";
					8:	print "Tendrás que ";
						if (x1 has supporter) print "bajarte ";
						else print "salir ";
					9:	print "Tendrá que ";
						if (x1 has supporter) print "bajarse ";
						else print "salir ";
				}
				print_ret (del_) x1, " antes.";
			5:	switch (_grammatical_inflection) {
					1:	"Ya tengo ", (the) x1, ".";
					2:	"Ya tienes ", (the) x1, ".";
					3:	"Ya tiene ", (the) x1, ".";
					4:	"Ya tenía ", (the) x1, ".";
					5:	"Ya tenías ", (the) x1, ".";
					6:	"Ya tenía ", (the) x1, ".";
					7:	"Ya tendré ", (the) x1, ".";
					8:	"Ya tendrás ", (the) x1, ".";
					9:	"Ya tendrá ", (the) x1, ".";
				}
			6:	switch (_grammatical_inflection) {
					1,2,3:	print "Parece", (n) noun;
					4,5,6:	print "Parecía", (n) noun;
					7,8,9:	print "Parecerá", (n) noun;
				}
				" pertenecer ", (al_) x1, ".";
			7:	switch (_grammatical_inflection) {
					1,2,3:	print "Parece", (n) noun;
					4,5,6:	print "Parecía", (n) noun;
					7,8,9:	print "Parecerá", (n) noun;
				}
				" formar parte ", (del_) x1, ".";
			8:	switch (_grammatical_inflection) {
					1,2,3:	"No ", (esta) x1, " disponible", (s) x1, ".";
					4,5,6:	"No estaba", (n) x1, " disponible", (s) x1, ".";
					7,8,9:	"No estará", (n) x1, " disponible", (s) x1, ".";
				}
			9:	switch (_grammatical_inflection) {
					1,2,3:	print_ret (The) x1, " no ", (esta) x1,
							" abiert", (o) x1, ".";
					4,5,6:	print_ret (The) x1, " no estaba", (n) x1,
							" abiert", (o) x1, ".";
					7,8,9:	print_ret (The) x1, " no estará", (n) x1,
							" abiert", (o) x1, ".";
				}
			10:	switch (_grammatical_inflection) {
					1:	"Difícilmente podría llevarme eso.";
					2:	"Difícilmente podrías llevarte eso.";
					3:	"Difícilmente podría llevarse eso.";
					4:	"Difícilmente hubiese podido llevarme eso.";
					5:	"Difícilmente hubieses podido llevarte eso.";
					6:	"Difícilmente hubiese podido llevarse eso.";
					7:	"Difícilmente podré llevarme eso.";
					8:	"Difícilmente podrás llevarte eso.";
					9:	"Difícilmente podrá llevarse eso.";
				}
			11:	switch (_grammatical_inflection) {
					1,2,3:	print_ret (The) x1, " ", (esta) x1,
							" fij", (o) x1, " en el sitio.";
					4,5,6:	print_ret (The) x1, " estaba", (n) x1,
							" fij", (o) x1, " en el sitio.";
					7,8,9:	print_ret (The) x1, " estará", (n) x1,
							" fij", (o) x1, " en el sitio.";
				}
			12:	switch (_grammatical_inflection) {
					1:	print "Ya tengo";
					2:	print "Ya tienes";
					3:	print "Ya tiene";
					4:	print "Ya tenía";
					5:	print "Ya tenías";
					6:	print "Ya tenía";
					7:	print "Ya tendré";
					8:	print "Ya tendrás";
					9:	print "Ya tendrá";
				}
				" las manos ocupadas con demasiadas cosas.";
			!! -- "(colocas ", (the) x1, " en ", (the) SACK_OBJECT,
			!! -- " para hacer sitio)"
			13:	switch (_grammatical_inflection) {
					1:	print "(Primero meto ";
					2:	print "(Primero metes ";
					3:	print "(Primero mete ";
					4:	print "(Primero metí ";
					5:	print "(Primero metiste ";
					6:	print "(Primero metió ";
					7:	print "(Primero meteré ";
					8:	print "(Primero meterás ";
					9:	print "(Primero meterá ";
				}
				print_ret (the) x1, " en ", (the) SACK_OBJECT, " para hacer
				sitio).";
		}

!! TODO
	Taste:
		switch (_grammatical_inflection) {
			1:	"No saboreo nada inesperado.";
			2:	"No saboreas nada inesperado.";
			3:	"No saborea nada inesperado.";
			4:	"No saboreé nada inesperado.";
			5:	"No saboreaste nada inesperado.";
			6:	"No soboreó nada inesperado.";
			7:	"No saborearé nada inesperado.";
			8:	"No saborearás nada inesperado.";
			9:	"No saboreará nada inesperado.";
		}

!! TODO
!!	Tell:	see Answer.
!!		!!	1:	El jugador habla consigo mismo.
!!		!!	2:	Hablar con cualquier otro ser animado.
!!		!! [Nota: Hablar con un objeto inanimado no está permitido por el
!!		!! parser, que da un error y no llega a generar la acción.]
!!		!! [Los errores de parser se tratan en la sección "Miscelanea" de
!!		!! esta rutina, al final.]
!!		switch (n) {
!!			1:	switch (_grammatical_inflection) {
!!				1:	"Hablo sol", (o) player, " durante un rato.";
!!				2:	"Hablas sol", (o) player, " durante un rato.";
!!				3:	"Habla sol", (o) player, " durante un rato.";
!!				4:	"Hablé sol", (o) player, " durante un rato.";
!!				5:	"Hablaste sol", (o) player, " durante un rato.";
!!				6:	"Habló sol", (o) player, " durante un rato.";
!!				}
!!			2:	switch (_grammatical_inflection) {
!!				1:	"No he provocado ninguna reacción.";
!!				2:	"No has provocado ninguna reacción.";
!!				3:	"No ha provocado ninguna reacción.";
!!				4:	"No provoqué ninguna reacción.";
!!				5:	"No provocaste ninguna reacción.";
!!				6:	"No provocó ninguna reacción.";
!!				}
!!		}

!! TODO
	Think:
		!! -- "Vaya. Qué buena idea.";
		switch (_grammatical_inflection) {
			1:	"Si, eso intento.";
			2:	"Si, eso intentas.";
			3:	"Si, eso intenta.";
			4:	"Si, eso intentaba.";
			5:	"Si, eso intentabas.";
			6:	"Si, eso intentaba.";
			7:	"Si, eso intentaré.";
			8:	"Si, eso intentarás.";
			9:	"Si, eso intentará.";
		}

!! TODO
	ThrowAt:
		!!  1:	Lanzar cosas a objetos inanimados.
		!!	2:	Lanzar cosas a objetos animados.
		switch (n) {
			1:	switch (_grammatical_inflection) {
					1,2,3:	"No serviría de nada.";
					4,5,6:	"No hubiese servido de nada.";
					7,8,9:	"No servirá de nada.";
				}
			2:	switch (_grammatical_inflection) {
					1:	"En el último momento me echo atrás.";
					2:	"En el último momento te echas atrás.";
					3:	"En el último momento se echa atrás.";
					4:	"En el último momento me eché atrás.";
					5:	"En el último momento te echaste atrás.";
					6:	"En el último momento se echó atrás.";
					7:	"En el último momento me echaré atrás.";
					8:	"En el último momento te echarás atrás.";
					9:	"En el último momento se echará atrás.";
				}
		}

!!	Tie: see JumpOver

!! TODO
	Touch:
		!!	1:	Si se intenta tocar a un ser animado.
		!!	2:	Tocar un objeto normal del juego.
		!!	3: Tocarse a si mismo.
		switch (n) {
			!! "¡Las manos quietas!";
			1:	switch (_grammatical_inflection) {
					1:	"No creo que deba.";
					2:	"En realidad no crees que debas.";
					3:	"No cree que deba.";
					4:	"No creía que debiese hacer algo así.";
					5:	"En realidad no creías que debieses hacer algo así.";
					6:	"No creía que debiese hacer algo así.";
					7:	"No creeré que deba hacerlo.";
					8:	"No creerás que debas hacerlo.";
					9:	"No creerá que deba hacerlo.";
				}
			2:	switch (_grammatical_inflection) {
					1:	"No noto nada extraño al tacto.";
					2:	"No notas nada extraño al tacto.";
					3:	"No nota nada extraño al tacto.";
					4:	"No noté nada extraño al tacto.";
					5:	"No notaste nada extraño al tacto.";
					6:	"No notó nada extraño al tacto.";
					7:	"No notaré nada extraño al tacto.";
					8:	"No notarás nada extraño al tacto.";
					9:	"No notará nada extraño al tacto.";
				}
			!! "Si crees que eso servirá de algo...";
			3:	switch (_grammatical_inflection) {
				1:	"No creo que eso sirva de nada.";
				2:	"En realidad no crees que eso sirva de nada.";
				3:	"No cree que eso sirva de nada.";
				4:	"No creía que algo así hubiese servido de nada.";
				5:	"En realidad no creías que algo así hubiese servido de
					nada.";
				6:	"No creía que algo así hubiese servido de nada.";
				7:	"No creeré que eso sirva de nada.";
				8:	"No creerás que eso sirva de nada.";
				9:	"No creerá que eso sirva de nada.";
				}
    }

!!	Turn:	see Pull

!! TODO
	Unlock:
		!! Unlock se genera ante ABRE <objeto> CON <objeto2>, o también
		!! ante QUITA CERROJO A <objeto> (en este segundo caso no se
		!! especifica la "llave" que abre la puerta).
		!!
		!!	1:	Error, el objeto que se intenta abrir, no tiene el atributo
		!!		cerrojo.
		!!	2:	Error, el objeto que se intenta abrir tiene atributo "cerrojo",
		!!		pero no tiene atributo "cerrojoechado".
		!!	3:	Error, el <objeto2> que se intenta usar como llave, no coincide
		!!		con la propiedad "con_llave" del <objeto> que intenta ser
		!!		abierto.
		!!	4:	Éxito. El <objeto> se abre (con <objeto2> si éste ha sido
		!!		especificado, el cual podemos encontrarlo en la variable "otro".
		switch (n) {
			1:	switch (_grammatical_inflection) {
					1,2,3:	print "No parece", (n) x1;
					4,5,6:	print "No parecía", (n) x1;
					7,8,9:	print "No parecerá", (n) x1;
				}
				" tener ningún tipo de cerrojo.";
			2:	switch (_grammatical_inflection) {
					1,2,3:	print (The) x1, " ya tenía", (n) x1;
					4,5,6:	print (The) x1, " ya tenía", (n) x1;
					7,8,9:	print (The) x1, " ya tendrá", (n) x1;
				}
				" abierto el cerrojo.";
			3:	if (second) switch (_grammatical_inflection) {
					1,2,3:	"No parece", (n) x1, " encajar en la cerradura.";
					4,5,6:	"No parecía", (n) x1, " encajar en la cerradura.";
					7,8,9:	"No parecerá", (n) x1, " encajar en la cerradura.";
				}
				else switch (_grammatical_inflection) {
					1:	"Necesito algún tipo de llave.";
					2:	"Necesitas algún tipo de llave.";
					3:	"Necesita algún tipo de llave.";
					4:	"Necesitaba algún tipo de llave.";
					5:	"Necesitabas algún tipo de llave.";
					6:	"Necesitaba algún tipo de llave.";
					7:	"Necesitaré algún tipo de llave.";
					8:	"Necesitarás algún tipo de llave.";
					9:	"Necesitará algún tipo de llave.";
				}
			4:	switch (_grammatical_inflection) {
				1:	if (~~second) "Quito el cerrojo ", (al_) x1, ".";
					"Quito el cerrojo ", (al_) x1, " con ", (the) second, ".";
				2:	if (~~second) "Quitas el cerrojo ", (al_) x1, ".";
					"Quitas el cerrojo ", (al_) x1, " con ", (the) second, ".";
				3:	if (~~second) "Quita el cerrojo ", (al_) second, ".";
					"Quita el cerrojo ", (al_) x1, " con ", (the) second, ".";
				4:	if (~~second) "Quité el cerrojo ", (al_) x1, ".";
					"Quité el cerrojo ", (al_) x1, " con ", (the) second, ".";
				5:	if (~~second) "Quitaste el cerrojo ", (al_) x1, ".";
					"Quitaste el cerrojo ",(al_) x1," con ", (the) second, ".";
				6:	if (~~second) "Quitó el cerrojo ", (al_) x1, ".";
					"Quitó el cerrojo ", (al_) x1, " con ", (the) second, ".";
				7:	if (~~second) "Quitaré el cerrojo ", (al_) x1, ".";
					"Quitaré el cerrojo ", (al_) x1, " con ", (the) second, ".";
				8:	if (~~second) "Quitarás el cerrojo ", (al_) x1, ".";
					"Quitarás el cerrojo ", (al_) x1, " con ", (the) second,".";
				9:	if (~~second) "Quitará el cerrojo ", (al_) x1, ".";
					"Quitará el cerrojo ", (al_) x1, " con ", (the) second, ".";
				}
		}

!! TODO - mostrar salidas
	VagueGo:
		!! El jugador ha dicho IR sin especificar a dónde
		"Tienes que especificar en qué dirección ir.";

!! TODO
	Verify:
		!!	1:	Éxito.
		!!	2:	Error en la verificación.
		switch (n) {
			1:	"Fichero de juego verificado e
				intacto.";
			2:	"El fichero de juego no parece intacto,
				puede estar corrompido (a menos que estés jugando con un
				intérprete muy primitivo que no sea capaz de realizar la
				comprobación).";
		}

	Wait:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT, SECOND_PERSON_PRESENT, THIRD_PERSON_PRESENT:
				print "Pasa";
			FIRST_PERSON_PAST, SECOND_PERSON_PAST, THIRD_PERSON_PAST:
				print "Pasaba";
			FIRST_PERSON_FUTURE, SECOND_PERSON_FUTURE, THIRD_PERSON_FUTURE:
				print "Pasará";
		}
		" el tiempo...";

!! TODO dar respuesta adecuada
	Wake:
		print "La cruda realidad es que ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT, SECOND_PERSON_PRESENT, THIRD_PERSON_PRESENT:
				print "esto no es";
			FIRST_PERSON_PAST, SECOND_PERSON_PAST, THIRD_PERSON_PAST:
				print "aquello no era";
			FIRST_PERSON_FUTURE, SECOND_PERSON_FUTURE, THIRD_PERSON_FUTURE:
				print "aquello no será";
		}
		" un sueño.";

	WakeOther:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT, SECOND_PERSON_PRESENT, THIRD_PERSON_PRESENT:
				"No parece necesario hacer eso.";
			FIRST_PERSON_PAST, SECOND_PERSON_PAST, THIRD_PERSON_PAST:
				"No parecía necesario hacer aquello.";
			FIRST_PERSON_FUTURE, SECOND_PERSON_FUTURE, THIRD_PERSON_FUTURE:
				"No parecerá necesario hacer aquello.";
		}

!! TODO
	Wave:
		!!	1:	Si se intenta agitar un objeto que no está en el inventario.
		!!	2:	Si se agita un objeto que sí está en el inventario.
		switch (n) {
			1:	switch (_grammatical_inflection) {
				1: "No l", (o) x1, " tengo.";
				2: "No l", (o) x1, " tienes.";
				3: "No l", (o) x1, " tiene.";
				4: "No l", (o) x1, " tenía.";
				5: "No l", (o) x1, " tenías.";
				6: "No l", (o) x1, " tenía.";
				7:	"No l", (o) x1, " tendré.";
				8:	"No l", (o) x1, " tendrás.";
				9:	"No l", (o) x1, " tendrá.";
				}
			2:	switch (_grammatical_inflection) {
					1:	print "Me siento";
					2:	print "Te sientes";
					3:	print "Se siente";
					4:	print "Me sentía";
					5:	print "Te sentías";
					6:	print "Se sentía";
					7:	print "Me sentiré";
					8:	print "Te sentirás";
					9:	print "Se sentirá";
				}
				" ridícul", (o) player, " agitando ", (the) x1, ".";
		}

!! TODO
	WaveHands:
		!! La acción WaveHands se genera ante las frases "gesticula", "agita la
		!! mano", "sacude la mano", "saluda con la mano", etc.
		switch (_grammatical_inflection) {
			1:	print "Me encuentro";
			2:	print "Te encuentras";
			3:	print "Se encuentra";
			4:	print "Me encontraba";
			5:	print "Te encontrabas";
			6:	print "Se encontraba";
		}
		" ridícul", (o) player, " gesticulando así.";

!! TODO
	Wear:
		!! 1: Error, el objeto no tiene el atributo "clothing".
		!! 2: Error, el jugador no tiene el objeto.
		!! 3: Error, el objeto ya tiene el atributo "worn".
		!! 4: Éxito.
		switch (n) {
			!! "¡No puedes ponerte eso!";
			1:	switch (_grammatical_inflection) {
					1:	"No puedo ponerme eso.";
					2:	"No puedes ponerte eso.";
					3:	"No puede ponerse eso.";
					4:	"No podía ponerme aquello.";
					5:	"No podías ponerte aquello.";
					6:	"No podía ponerse aquello.";
					7:	"No podré ponerme aquello.";
					8:	"No podrás ponerte aquello.";
					9:	"No podrá ponerse aquello.";
				}
			2:	switch (_grammatical_inflection) {
					1:	"No ", (lo) x1, " tengo.";
					2:	"No ", (lo) x1, " tienes.";
					3:	"No ", (lo) x1, " tiene.";
					4:	"No ", (lo) x1, " tenía.";
					5:	"No ", (lo) x1, " tenías.";
					6:	"No ", (lo) x1, " tenía.";
					7:	"No ", (lo) x1, " tendré.";
					8:	"No ", (lo) x1, " tendrás.";
					9:	"No ", (lo) x1, " tendrá.";
				}
			3:	switch (_grammatical_inflection) {
				1:	"Ya ", (lo) x1, " llevo puest", (o) x1, ".";
				2:	"Ya ", (lo) x1, " llevas puest", (o) x1, ".";
				3:	"Ya ", (lo) x1, " lleva puest", (o) x1, ".";
				4:	"Ya ", (lo) x1, " llevaba puest", (o) x1, ".";
				5:	"Ya ", (lo) x1, " llevabas puest", (o) x1, ".";
				6:	"Ya ", (lo) x1, " llevaba puest", (o) x1, ".";
				7:	"Ya ", (lo) x1, " llevaré puest", (o) x1, ".";
				8:	"Ya ", (lo) x1, " llevarás puest", (o) x1, ".";
				9:	"Ya ", (lo) x1, " llevará puest", (o) x1, ".";
				}
			4:	switch (_grammatical_inflection) {
					1:	"Me pongo ", (the) x1, ".";
					2:	"Te pones ", (the) x1, ".";
					3:	"Se pone ", (the) x1, ".";
					4:	"Me puse ", (the) x1, ".";
					5:	"Te pusiste ", (the) x1, ".";
					6:	"Se puso ", (the) x1, ".";
					7:	"Me pondré ", (the) x1, ".";
					8:	"Te pondrás ", (the) x1, ".";
					9:	"Se pondrá ", (the) x1, ".";
				}
		}

!! TODO
	Yes:
		"La orden 'si' no tiene sentido en esta situación.";

];

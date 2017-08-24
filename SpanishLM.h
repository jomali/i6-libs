

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
!!	# NOTAS
!!
!!	Implementa el conjunto de mensajes por defecto de la librería Inform-INFSP,
!!	incluyendo la posibilidad de modificar en tiempo de ejecución tanto el
!!	tiempo verbal (presente, pasado, futuro) y la persona (primera, segunda,
!!	tercera), como el género (masculino, femenino) el número (singular,
!!	plural) ---estos últimos, en función de la definición del objeto 'player'
!!	controlado por el usuario---. Los mensajes están basados en gran medida en
!!	los de 'Spanish.h'.
!!
!!
!!	# UTILIZACIÓN
!!
!!	A continuación se detallan los pasos que deben seguirse para instalar la
!!	extensión:
!!
!!	1)	Declarar la constante SIN_MENSAJES para omitir los mensajes por defecto
!!		de la librería Inform (antes de incluir librerías y extensiones):
!!
!!			Constant SIN_MENSAJES;
!!
!!	2)	Declarar el reemplazo de la rutina 'ChangePlayer' definida en
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
System_file;


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
!! Imprime la terminación correcta de los verbos de primera conjugación para la
!! inflexión gramatical del narrador y el objeto pasado como parámetro. Por
!! defecto utiliza el pretérito imperfecto para imprimir las inflexiones en
!! pasado; a menos que se invoque con el parámetro 'pastSimple' activado, en
!! cuyo caso se utiliza el pretérito perfecto simple.
!!
!!	@param {Object} obj
!!	@param {boolean} [pastSimple=false] - Si se invoca con él activado
!!		(==true) utiliza el pretérito perfecto simple para imprimir las
!!		flexiones del verbo en pasado. En caso contrario, se utiliza el
!!		pretérito imperfecto
!!------------------------------------------------------------------------------
[ lm_as obj pastSimple;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "amos";
			else print "o";
		SECOND_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "áis";
			else print "as";
		THIRD_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "an";
			else print "a";
		FIRST_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "amos";
				else print "é";
			} else {
				if (IsPluralNoun(obj)) print "ábamos";
				else print "aba";
			}
		SECOND_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "asteis";
				else print "aste";
			} else {
				if (IsPluralNoun(obj)) print "abais";
				else print "abas";
			}
		THIRD_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "aron";
				else print "ó";
			} else {
				if (IsPluralNoun(obj)) print "aban";
				else print "aba";
			}
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "aremos";
			else print "aré";
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "aréis";
			else print "arás";
		THIRD_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "arán";
			else print "ará";
	}
];


!!==============================================================================
!! Invoca a la rutina 'lm_as()' con el parámetro opcional 'pastSimple'
!! activado para imprimir las flexiones en pasado utilizando el pretérito
!! perfecto simple.
!!
!!	@param {Object} obj
!!------------------------------------------------------------------------------
[ lm_as_ obj; return lm_as(obj, true); ];


!!==============================================================================
!! Imprime la construcción correcta (en forma amalgamada o no) formada por la
!! preposición 'con' y el pronombre o segmento pronominal que se corresponda
!! con la flexión gramatical del narrador y el objeto pasado como parámetro.
!!
!!	@param {Object} obj
!!------------------------------------------------------------------------------
[ lm_contigo obj;
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
!! Similar a la rutina 'lm_as()', con el verbo 'ser'.
!!
!!	@param {Object} obj
!!	@param {boolean} [pastSimple=false] - Activado (==true) para utilizar el
!!		pretérito perfecto simple en las flexiones en pasado. En caso contrario
!!		se utiliza el pretérito imperfecto
!!------------------------------------------------------------------------------
[ lm_eres obj pastSimple;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "somos";
			else print "soy";
		SECOND_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "sois";
			else print "eres";
		THIRD_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "son";
			else print "es";
		FIRST_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "fuimos";
				else print "fui";
			} else {
				if (IsPluralNoun(obj)) print "éramos";
				else print "era";
			}
		SECOND_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "fuisteis";
				else print "fuiste";
			} else {
				if (IsPluralNoun(obj)) print "érais";
				else print "eras";
			}
		THIRD_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "fueron";
				else print "fue";
			} else {
				if (IsPluralNoun(obj)) print "eran";
				else print "era";
			}
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "seremos";
			else print "seré";
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "seréis";
			else print "serás";
		THIRD_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "serán";
			else print "será";
	}
];


!!==============================================================================
!! Invoca a la rutina 'lm_eres()' con el parámetro opcional 'pastSimple'
!! activado para imprimir las flexiones en pasado utilizando el pretérito
!! perfecto simple.
!!
!!	@param {Object} obj
!!------------------------------------------------------------------------------
[ lm_eres_ obj; return lm_eres(obj, true); ];


!!==============================================================================
!! Similar a la rutina 'lm_as()', con el verbo 'ser', usando mayúsculas para la
!! primera letra.
!!
!!	@param {Object} obj
!!	@param {boolean} [pastSimple=false] - Activado (==true) para utilizar el
!!		pretérito perfecto simple en las flexiones en pasado. En caso contrario
!!		se utiliza el pretérito imperfecto
!!------------------------------------------------------------------------------
[ lm_eeres obj pastSimple;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "Somos";
			else print "Soy";
		SECOND_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "Sois";
			else print "Eres";
		THIRD_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "Son";
			else print "Es";
		FIRST_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "Fuimos";
				else print "Fui";
			} else {
				if (IsPluralNoun(obj)) print "Éramos";
				else print "Era";
			}
		SECOND_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "Fuisteis";
				else print "Fuiste";
			} else {
				if (IsPluralNoun(obj)) print "Érais";
				else print "Eras";
			}
		THIRD_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "Fueron";
				else print "Fue";
			} else {
				if (IsPluralNoun(obj)) print "Eran";
				else print "Era";
			}
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "Seremos";
			else print "Seré";
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "Seréis";
			else print "Serás";
		THIRD_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "Serán";
			else print "Será";
	}
];


!!==============================================================================
!! Invoca a la rutina 'lm_eeres()' con el parámetro opcional 'pastSimple'
!! activado para imprimir las flexiones en pasado utilizando el pretérito
!! perfecto simple.
!!
!!	@param {Object} obj
!!------------------------------------------------------------------------------
[ lm_eeres_ obj; return lm_eeres(obj, true); ];


!!==============================================================================
!! Similar a la rutina 'lm_as()', con el verbo 'estar'.
!!
!!	@param {Object} obj
!!	@param {boolean} [pastSimple=false] - Activado (==true) para utilizar el
!!		pretérito perfecto simple en las flexiones en pasado. En caso contrario
!!		se utiliza el pretérito imperfecto
!!------------------------------------------------------------------------------
[ lm_estas obj pastSimple;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "amos";
			else print "oy";
		SECOND_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "áis";
			else print "ás";
		THIRD_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "án";
			else print "á";
		FIRST_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "uvimos";
				else print "uve";
			} else {
				if (IsPluralNoun(obj)) print "ábamos";
				else print "aba";
			}
		SECOND_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "uvisteis";
				else print "uviste";
			} else {
				if (IsPluralNoun(obj)) print "abais";
				else print "abas";
			}
		THIRD_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "uvieron";
				else print "uvo";
			} else {
				if (IsPluralNoun(obj)) print "aban";
				else print "aba";
			}
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "aremos";
			else print "aré";
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "aréis";
			else print "arás";
		THIRD_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "arán";
			else print "ará";
	}
];


!!==============================================================================
!! Invoca a la rutina 'lm_estas()' con el parámetro opcional 'pastSimple'
!! activado para imprimir las flexiones en pasado utilizando el pretérito
!! perfecto simple.
!!
!!	@param {Object} obj
!!------------------------------------------------------------------------------
[ lm_estas_ obj; return lm_estas(obj, true); ];


!!==============================================================================
!! Similar a la rutina 'lm_as()', con el verbo 'poder'.
!!
!!	@param {Object} obj
!!	@param {boolean} [pastSimple=false] - Activado (==true) para utilizar el
!!		pretérito perfecto simple en las flexiones en pasado. En caso contrario
!!		se utiliza el pretérito imperfecto
!!------------------------------------------------------------------------------
[ lm_puedes obj pastSimple;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "podemos";
			else print "puedo";
		SECOND_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "podéis";
			else print "puedes";
		THIRD_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "pueden";
			else print "puede";
		FIRST_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "pudimos";
				else print "pude";
			} else {
				if (IsPluralNoun(obj)) print "podíamos";
				else print "podía";
			}
		SECOND_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "pudisteis";
				else print "pudimos";
			} else {
				if (IsPluralNoun(obj)) print "podíais";
				else print "podías";
			}
		THIRD_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "pudieron";
				else print "pudo";
			} else {
				if (IsPluralNoun(obj)) print "podían";
				else print "podía";
			}
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "podremos";
			else print "podré";
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "podréis";
			else print "podrás";
		THIRD_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "podrán";
			else print "podrá";
	}
];


!!==============================================================================
!! Invoca a la rutina 'lm_puedes()' con el parámetro opcional 'pastSimple'
!! activado para imprimir las flexiones en pasado utilizando el pretérito
!! perfecto simple.
!!
!!	@param {Object} obj
!!------------------------------------------------------------------------------
[ lm_puedes_ obj; return lm_puedes(obj, true); ];


!!==============================================================================
!! Similar a la rutina 'lm_as()', con el verbo 'poder', usando mayúsculas para
!! la primera letra.
!!
!!	@param {Object} obj
!!	@param {boolean} [pastSimple=false] - Activado (==true) para utilizar el
!!		pretérito perfecto simple en las flexiones en pasado. En caso contrario
!!		se utiliza el pretérito imperfecto
!!------------------------------------------------------------------------------
[ lm_ppuedes obj pastSimple;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "Podemos";
			else print "Puedo";
		SECOND_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "Podéis";
			else print "Puedes";
		THIRD_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "Pueden";
			else print "Puede";
		FIRST_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "Pudimos";
				else print "Pude";
			} else {
				if (IsPluralNoun(obj)) print "Podíamos";
				else print "Podía";
			}
		SECOND_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "Pudisteis";
				else print "Pudimos";
			} else {
				if (IsPluralNoun(obj)) print "Podíais";
				else print "Podías";
			}
		THIRD_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "Pudieron";
				else print "Pudo";
			} else {
				if (IsPluralNoun(obj)) print "Podían";
				else print "Podía";
			}
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "Podremos";
			else print "Podré";
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "Podréis";
			else print "Podrás";
		THIRD_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "Podrán";
			else print "Podrá";
	}
];


!!==============================================================================
!! Invoca a la rutina 'lm_ppuedes()' con el parámetro opcional 'pastSimple'
!! activado para imprimir las flexiones en pasado utilizando el pretérito
!! perfecto simple.
!!
!!	@param {Object} obj
!!------------------------------------------------------------------------------
[ lm_ppuedes_ obj; return lm_ppuedes(obj, true); ];


!!==============================================================================
!! Imprime el pronombre personal átono que se corresponde con el objeto pasado
!! como parámetro.
!!
!!	@param {Object} obj
!!------------------------------------------------------------------------------
[ lm_te obj;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT,
		FIRST_PERSON_PAST,
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "nos";
			else print "me";
		SECOND_PERSON_PRESENT,
		SECOND_PERSON_PAST,
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(player)) print "os";
			else print "te";
		THIRD_PERSON_PRESENT,
		THIRD_PERSON_PAST,
		THIRD_PERSON_FUTURE:
			print "se";
	}
];


!!==============================================================================
!! Similar a la rutina 'lm_as()', con el verbo 'tener'.
!!
!!	@param {Object} obj
!!	@param {boolean} [pastSimple=false] - Activado (==true) para utilizar el
!!		pretérito perfecto simple en las flexiones en pasado. En caso contrario
!!		se utiliza el pretérito imperfecto
!!------------------------------------------------------------------------------
[ lm_tienes obj pastSimple;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "tenemos";
			else print "tengo";
		SECOND_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "tenéis";
			else print "tienes";
		THIRD_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "tienen";
			else print "tiene";
		FIRST_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "tuvimos";
				else print "tuve";
			} else {
				if (IsPluralNoun(obj)) print "teníamos";
				else print "tenía";
			}
		SECOND_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "tuvisteis";
				else print "tuviste";
			} else {
				if (IsPluralNoun(obj)) print "teníais";
				else print "tenías";
			}
		THIRD_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "tuvieron";
				else print "tuvo";
			} else {
				if (IsPluralNoun(obj)) print "tenían";
				else print "tenía";
			}
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "tendremos";
			else print "tendré";
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "tendréis";
			else print "tendrás";
		THIRD_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "tendrán";
			else print "tendrá";
	}
];

!!==============================================================================
!! Invoca a la rutina 'lm_tienes()' con el parámetro opcional 'pastSimple'
!! activado para imprimir las flexiones en pasado utilizando el pretérito
!! perfecto simple.
!!
!!	@param {Object} obj
!!------------------------------------------------------------------------------
[ lm_tienes_ obj; return lm_tienes(obj, true); ];


!!==============================================================================
!! Similar a la rutina 'lm_as()', con el verbo 'tener', usando mayúsculas para
!! la primera letra.
!!
!!	@param {Object} obj
!!	@param {boolean} [pastSimple=false] - Activado (==true) para utilizar el
!!		pretérito perfecto simple en las flexiones en pasado. En caso contrario
!!		se utiliza el pretérito imperfecto
!!------------------------------------------------------------------------------
[ lm_ttienes obj pastSimple;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "Tenemos";
			else print "Tengo";
		SECOND_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "Tenéis";
			else print "Tienes";
		THIRD_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "Tienen";
			else print "Tiene";
		FIRST_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "Tuvimos";
				else print "Tuve";
			} else {
				if (IsPluralNoun(obj)) print "Teníamos";
				else print "Tenía";
			}
		SECOND_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "Tuvisteis";
				else print "Tuviste";
			} else {
				if (IsPluralNoun(obj)) print "Teníais";
				else print "Tenías";
			}
		THIRD_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "Tuvieron";
				else print "Tuvo";
			} else {
				if (IsPluralNoun(obj)) print "Tenían";
				else print "Tenía";
			}
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "Tendremos";
			else print "Tendré";
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "Tendréis";
			else print "Tendrás";
		THIRD_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "Tendrán";
			else print "Tendrá";
	}
];


!!==============================================================================
!! Invoca a la rutina 'lm_ttienes()' con el parámetro opcional 'pastSimple'
!! activado para imprimir las flexiones en pasado utilizando el pretérito
!! perfecto simple.
!!
!!	@param {Object} obj
!!------------------------------------------------------------------------------
[ lm_ttienes_ obj; return lm_ttienes(obj, true); ];


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
[ IsFemaleNoun obj;
	return (GetGNAOfObject(obj, true) == 1 or 4 or 7 or 10);
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
[ IsPluralNoun obj;
	return (GetGNAOfObject(obj, true) == 3 or 4 or 5 or 9 or 10 or 11);
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
			if (IsPluralNoun(player)) {
				ARE__TX			= " vemos";
				ARE2__TX		= "vemos ";
				CANTGO__TX		= "No podemos ir por ahí.";
				IS__TX			= " vemos";
				IS2__TX			= "vemos ";
				PARTICULA_TE	= "nos";
				if (IsFemaleNoun(player)) {
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
				if (IsFemaleNoun(player)) {
					FORMER__TX		= "mi antigua ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "mí misma";
				} else {
					FORMER__TX		= "mi antiguo ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "mí mismo";
				}
			}
		SECOND_PERSON_PRESENT:
			.defaultInflection;
			_grammatical_inflection = SECOND_PERSON_PRESENT;
			if (IsPluralNoun(player)) {
				ARE__TX			= " veis";
				ARE2__TX		= "veis ";
				CANTGO__TX		= "No podéis ir por ahí.";
				IS__TX			= " veis";
				IS2__TX			= "veis ";
				PARTICULA_TE	= "os";
				if (IsFemaleNoun(player)) {
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
				if (IsFemaleNoun(player)) {
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
			if (IsPluralNoun(player)) {
				ARE__TX			= " ven";
				ARE2__TX		= "ven ";
				CANTGO__TX		= "No pueden ir por ahí.";
				IS__TX			= " ven";
				IS2__TX			= "ven ";
				PARTICULA_TE	= "se";
				if (IsFemaleNoun(player)) {
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
				if (IsFemaleNoun(player)) {
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
			if (IsPluralNoun(player)) {
				ARE__TX			= " veíamos";
				ARE2__TX		= "veíamos ";
				CANTGO__TX		= "No podíamos ir por ahí.";
				IS__TX			= " veíamos";
				IS2__TX			= "veíamos ";
				PARTICULA_TE	= "nos";
				if (IsFemaleNoun(player)) {
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
				if (IsFemaleNoun(player)) {
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
			if (IsPluralNoun(player)) {
				ARE__TX			= " veíais";
				ARE2__TX		= "veíais ";
				CANTGO__TX		= "No podíais ir por ahí.";
				IS__TX			= " veíais";
				IS2__TX			= "veíais ";
				PARTICULA_TE	= "os";
				if (IsFemaleNoun(player)) {
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
				if (IsFemaleNoun(player)) {
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
			if (IsPluralNoun(player)) {
				ARE__TX			= " veían";
				ARE2__TX		= "veían ";
				CANTGO__TX		= "No podían ir por ahí.";
				IS__TX			= " veían";
				IS2__TX			= "veían ";
				PARTICULA_TE	= "se";
				if (IsFemaleNoun(player)) {
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
				if (IsFemaleNoun(player)) {
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
			if (IsPluralNoun(player)) {
				ARE__TX			= " veremos";
				ARE2__TX		= "veremos ";
				CANTGO__TX		= "No podremos ir por ahí.";
				IS__TX			= " veremos";
				IS2__TX			= "veremos ";
				PARTICULA_TE	= "nos";
				if (IsFemaleNoun(player)) {
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
				if (IsFemaleNoun(player)) {
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
			if (IsPluralNoun(player)) {
				ARE__TX			= " veréis";
				ARE2__TX		= "veréis ";
				CANTGO__TX		= "No podréis ir por ahí.";
				IS__TX			= " veréis";
				IS2__TX			= "veréis ";
				PARTICULA_TE	= "os";
				if (IsFemaleNoun(player)) {
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
				if (IsFemaleNoun(player)) {
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
			if (IsPluralNoun(player)) {
				ARE__TX			= " verán";
				ARE2__TX		= "verán ";
				CANTGO__TX		= "No podrán ir por ahí.";
				IS__TX			= " verán";
				IS2__TX			= "verán ";
				PARTICULA_TE	= "se";
				if (IsFemaleNoun(player)) {
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
				if (IsFemaleNoun(player)) {
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
	* number						-> Grammar;
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
			"^ARE__TX: ", ARE__TX,
			"^ARE2__TX: ", ARE2__TX,
			"^CANTGO__TX: ", CANTGO__TX,
			"^IS__TX: ", IS__TX,
			"^IS2__TX: ", IS2__TX,
			"^PARTICULA_TE: ", PARTICULA_TE,
			"^FORMER__TX: ", FORMER__TX,
			"^YOU__TX: ", YOU__TX,
			"^YOURSELF__TX: ", YOURSELF__TX;
	}
	print "Cambio de flexión gramatical: ";
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:	print "(1) presente 1a persona";
		SECOND_PERSON_PRESENT:	print "(2) presente 2a persona";
		THIRD_PERSON_PRESENT:	print "(3) presente 3a persona";
		FIRST_PERSON_PAST:		print "(4) pasado 1a persona";
		SECOND_PERSON_PAST:		print "(5) pasado 2a persona";
		THIRD_PERSON_PAST:		print "(6) pasado 3a persona";
		FIRST_PERSON_FUTURE:	print "(7) futuro 1a persona";
		SECOND_PERSON_FUTURE:	print "(8) futuro 2a persona";
		THIRD_PERSON_FUTURE:	print "(9) futuro 3a persona";
	}
	".";
];
#Endif; ! DEBUG;


!!==============================================================================
[ LanguageLM n x1;

	Answer, Ask, AskFor:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				"No hay respuesta.";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				"No había respuesta.";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				"No habrá respuesta.";
		}

!!	Ask:	see Answer
!!	AskFor:	see Answer

	Attack:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "es";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "era";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "será";
		}
		" necesario emprenderla a golpes con ", (the) x1, ".";

	Blow:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "Nuestro";
				else print "Mi";
				print " soplido no produce";
			SECOND_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "Vuestro";
				else print "Tu";
				print " soplido no produce";
			THIRD_PERSON_PRESENT:
				print "Su soplido no produce";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "Nuestro";
				else print "Mi";
				print " soplido no produjo";
			SECOND_PERSON_PAST:
				if (IsPluralNoun(player)) print "Vuestro";
				else print "Tu";
				print " soplido no produjo";
			THIRD_PERSON_PAST:
				print "Su soplido no produjo";
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "Nuestro";
				else print "Mi";
				print " soplido no producirá";
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "Vuestro";
				else print "Tu";
				print " soplido no producirá";
			THIRD_PERSON_FUTURE:
				print "Su soplido no producirá";
		}
		" ningún efecto.";

	Burn:
		print "Con esa peligrosa acción no ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "íbamos";
				else print "iba";
				" a lograr nada.";
			SECOND_PERSON_PRESENT,
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "ibais";
				else print "ibas";
				" a lograr nada.";
			THIRD_PERSON_PRESENT,
			THIRD_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "iban";
				else print "iba";
				" a lograr nada.";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "hubiésemos";
				else print "hubiese";
				" logrado nada.";
			SECOND_PERSON_PAST:
				if (IsPluralNoun(player)) print "hubieseis";
				else print "hubieses";
				" logrado nada.";
			THIRD_PERSON_PAST:
				if (IsPluralNoun(player)) print "hubiesen";
				else print "hubiese";
				" logrado nada.";
		}

	Buy:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "hay";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "había";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "habrá";
		}
		" nada en venta.";

	Climb:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "No creemos que vayamos";
				else print "No creo que vaya";
				" a lograr nada haciendo eso.";
			SECOND_PERSON_PRESENT:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creéis que vayáis";
				else print "crees que vayas";
				" a lograr nada haciendo eso.";
			THIRD_PERSON_PRESENT:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creen que vayan";
				else print "cree que vaya";
				" a lograr nada haciendo eso.";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "No creemos que hubiésemos";
				else print "No creo que hubiese";
				" logrado nada haciendo aquello.";
			SECOND_PERSON_PAST:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creéis que hubieseis";
				else print "crees que hubieses";
				" logrado nada haciendo aquello.";
			THIRD_PERSON_PAST:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creen que hubiesen";
				else print "cree que hubiese";
				" logrado nada haciendo aquello.";
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "No lograremos";
				else print "No lograré";
				" nada haciendo eso.";
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "No lograréis";
				else print "No lograrás";
				" nada haciendo eso.";
			THIRD_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "No lograrán";
				else print "No logrará";
				" nada haciendo eso.";
		}

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
						"No será algo que pueda cerrarse.";
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
						if (IsPluralNoun(player)) print "Cerramos";
						else print "Cierro";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Cerráis";
						else print "Cierras";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Cierran";
						else print "Cierra";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Cerramos";
						else print "Cerré";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Cerrasteis";
						else print "Cerraste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Cerraron";
						else print "Cerró";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Cerraremos";
						else print "Cerraré";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Cerraréis";
						else print "Cerrarás";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Cerrarán";
						else print "Cerrará";
				}
				" ", (the) x1, ".";
		}

	CommandsOff:
		switch (n) { ![6/11]
			1:	"[Grabación de órdenes finalizada.]";
			#Ifdef TARGET_GLULX;
			2:	"[Grabación de órdenes ya finalizada.]";
			#Endif; ! TARGET_
		}

	CommandsOn:
		switch (n) { ![6/11]
			1:	"[Grabación de órdenes activada.]";
			#Ifdef TARGET_GLULX;
			2:	"[Órdenes relanzadas.]";
			3:	"[Grabación de órdenes ya activada.]";
			4:	"[Fallo en la grabación de órdenes.]";
			#Endif; ! TARGET_
		}

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

	Consult:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "descubrimos";
				else print "descubro";
			SECOND_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "descubrís";
				else print "descubres";
			THIRD_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "descubren";
				else print "descubre";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "descubrimos";
				else print "descubrí";
				" nada interesante en ", (the) x1, " sobre aquel tema.";
			SECOND_PERSON_PAST:
				if (IsPluralNoun(player)) print "descubristeis";
				else print "descubriste";
				" nada interesante en ", (the) x1, " sobre aquel tema.";
			THIRD_PERSON_PAST:
				if (IsPluralNoun(player)) print "descubrieron";
				else print "descubrió";
				" nada interesante en ", (the) x1, " sobre aquel tema.";
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "descubriremos";
				else print "descubriré";
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "descubriréis";
				else print "descubrirás";
			THIRD_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "descubrirán";
				else print "descubrirá";
		}
		" nada interesante en ", (the) x1, " sobre ese tema.";

	Cut:
		print "Cortándo", (lo) x1, " no ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "lograremos";
				else print "lograré";
			SECOND_PERSON_PRESENT,
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "lograréis";
				else print "lograrás";
			THIRD_PERSON_PRESENT,
			THIRD_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "lograrán";
				else print "logrará";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "hubiésemos logrado";
				else print "hubiese logrado";
			SECOND_PERSON_PAST:
				if (IsPluralNoun(player)) print "hubieseis logrado";
				else print "hubiese logrado";
			THIRD_PERSON_PAST:
				if (IsPluralNoun(player)) print "hubiesen logrado";
				else print "hubiese logrado";
		}
		" gran cosa.";

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

	Disrobe:
		!!	1:	Error. El protagonista no lleva el objeto puesto.
		!!	2:	Mensaje cuando el protagonista se quita el objeto.
		switch (n) {
			1:	"No ", (lo) x1, " llev", (lm_as) player, " puest", (o) x1, ".";
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Nos quitamos";
						else print "Me quito";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Os quitáis";
						else print "Te quitas";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Se quitan";
						else print "Se quita";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Nos quitamos";
						else print "Me quité";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Os quitasteis";
						else print "Te quitaste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Se quitaron";
						else print "Se quitó";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Nos quitaremos";
						else print "Me quitaré";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Os quitaréis";
						else print "Te quitarás";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Se quitarán";
						else print "Se quitará";
				}
				" ", (the) x1, ".";
		}

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
				"Eso no parecerá potable.";
		}

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
						if (IsPluralNoun(player)) print "deberíamos";
						else print "debería";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "deberíais";
						else print "deberías";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "deberían";
						else print "debería";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "hubiésemos debido";
						else print "hubiese debido";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "hubieseis debido";
						else print "hubieses debido";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "hubiesen debido";
						else print "hubiese debido";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "deberemos";
						else print "deberé";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "deberéis";
						else print "deberás";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "deberán";
						else print "deberá";
				}
				" tener", (lo) x1, ".";
			2:	"No ", (lo) x1, " ", (lm_tienes) player, " ",
				(lm_contigo) player, ".";
			3:	print "(Primero ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "nos quitamos";
						else print "me quito";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "os quitáis";
						else print "te quitas";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "se quitan";
						else print "se quita";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "nos quitamos";
						else print "me quité";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "os quitasteis";
						else print "te quitaste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "se quitaron";
						else print "se quitó";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "nos quitaremos";
						else print "me quitaré";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "os quitaréis";
						else print "te quitarás";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "se quitarán";
						else print "se quitará";
				}
				" ", (the) x1, ".)";
			4:	"Dejad", (o) x1, ".";
		}

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
						"Eso no parecerá comestible.";
				}
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Nos comemos";
						else print "Me como";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Os coméis";
						else print "Te comes";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Se comen";
						else print "Se come";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Nos comimos";
						else print "Me comí";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Os comisteis";
						else print "Te comiste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Se comieron";
						else print "Se comió";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Nos comeremos";
						else print "Me comeré";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Os comeréis";
						else print "Te comerás";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Se comerán";
						else print "Se comerá";
				}
				" ", (the) x1, ".";
		}

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
			4:	"No ", (lm_puedes) player, " vaciar un objeto sobre sí mismo.";
		}

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
		!! contiene el verbo usado por el usuario (convertido en forma
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
		!!		al usuario en el objeto desde el cual pueda acceder al que el
		!!		usuario le ha indicado.
		switch (n) {
			1:	print "Ya ", (lm_estas) player, " ";
				if (x1 has supporter) print "sobre ";
				else print "en ";
				"", (the) x1, ".";
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player))
							print "No es algo donde podamos";
						else print "No es algo donde pueda";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player))
							print "No es algo donde podáis";
						else print "No es algo donde puedas";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player))
							print "No es algo donde puedan";
						else print "No es algo donde pueda";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player))
							print "No era algo donde pudiésemos";
						else print "No era algo donde pudiese";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player))
							print "No era algo donde pudieseis";
						else print "No era algo donde pudieses";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player))
							print "No era algo donde pudiesen";
						else print "No era algo donde pudiese";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player))
							print "No será algo donde podremos";
						else print "No será algo donde podré";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player))
							print "No será algo donde podréis";
						else print "No será algo donde podrás";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player))
							print "No será algo donde podrán";
						else print "No será algo donde podrá";
				}
				LanguageVerb(verb_word); ".";
			3:	print "No ", (lm_puedes) player, " ";
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
						if (IsPluralNoun(player)) print "vamos a poder";
						else print "voy a poder";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "vais a poder";
						else print "vas a poder";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "van a poder";
						else print "va a poder";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "íbamos a poder";
						else print "iba a poder";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "ibais a poder";
						else print "ibas a poder";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "iban a poder";
						else print "iba a poder";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "podremos";
						else print "podré";
						" hacerlo sin soltarlo antes.";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "podréis";
						else print "podrás";
						" hacerlo sin soltarlo antes.";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "podrán";
						else print "podrá";
						" hacerlo sin soltarlo antes.";
				}
				LanguageVerb(verb_word);
				print " ahí mientras no ", (lo) x1, " ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "soltemos";
						else print "suelte";
					SECOND_PERSON_PRESENT,
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "soltéis";
						else print "sueltes";
					THIRD_PERSON_PRESENT,
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "suelten";
						else print "suelte";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "soltásemos";
						else print "soltase";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "soltaseis";
						else print "soltases";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "soltasen";
						else print "soltase";
				}
				".";
			5:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Subimos";
							else print "Subo";
							print " ", (al_) x1;
						} else {
							if (IsPluralNoun(player)) print "Entramos";
							else print "Entro";
							print " en ", (the) x1;
						}
						".";
					SECOND_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Subís";
							else print "Subes";
							print " ", (al_) x1;
						} else {
							if (IsPluralNoun(player)) print "Entráis";
							else print "Entras";
							print " en ", (the) x1;
						}
						".";
					THIRD_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Suben";
							else print "Sube";
							print " ", (al_) x1;
						} else {
							if (IsPluralNoun(player)) print "Entran";
							else print "Entra";
							print " en ", (the) x1;
						}
						".";
					FIRST_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Subimos";
							else print "Subí";
							print " ", (al_) x1;
						} else {
							if (IsPluralNoun(player)) print "Entramos";
							else print "Entré";
							print " en ", (the) x1;
						}
						".";
					SECOND_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Subisteis";
							else print "Subiste";
							print " ", (al_) x1;
						} else {
							if (IsPluralNoun(player)) print "Entrasteis";
							else print "Entraste";
							print " en ", (the) x1;
						}
						".";
					THIRD_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Subieron";
							else print "Subió";
							print " ", (al_) x1;
						} else {
							if (IsPluralNoun(player)) print "Entraron";
							else print "Entró";
							print " en ", (the) x1;
						}
						".";
					FIRST_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Subiremos";
							else print "Subiré";
							print " ", (al_) x1;
						} else {
							if (IsPluralNoun(player)) print "Entraremos";
							else print "Entraré";
							print " en ", (the) x1;
						}
						".";
					SECOND_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Subiréis";
							else print "Subirás";
							print " ", (al_) x1;
						} else {
							if (IsPluralNoun(player)) print "Entraréis";
							else print "Entrarás";
							print " en ", (the) x1;
						}
						".";
					THIRD_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Subirán";
							else print "Subirá";
							print " ", (al_) x1;
						} else {
							if (IsPluralNoun(player)) print "Entrarán";
							else print "Entrará";
							print " en ", (the) x1;
						}
						".";
				}
			6:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Nos bajamos";
							else print "(Me bajo";
						} else {
							if (IsPluralNoun(player)) print "(Salimos";
							else print "(Salgo";
						}
					SECOND_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Os bajáis";
							else print "(Te bajas";
						} else {
							if (IsPluralNoun(player)) print "(Salís";
							else print "(Sales";
						}
					THIRD_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Se bajan";
							else print "(Se baja";
						} else {
							if (IsPluralNoun(player)) print "(Salen";
							else print "(Sale";
						}
					FIRST_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Nos bajamos";
							else print "(Me bajé";
						} else {
							if (IsPluralNoun(player)) print "(Salimos";
							else print "(Salí";
						}
					SECOND_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Os bajásteis";
							else print "(Te bajaste";
						} else {
							if (IsPluralNoun(player)) print "(Salisteis";
							else print "(Saliste";
						}
					THIRD_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Se bajaron";
							else print "(Se bajó";
						} else {
							if (IsPluralNoun(player)) print "(Salieron";
							else print "(Salió";
						}
					FIRST_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Nos bajaremos";
							else print "(Me bajaré";
						} else {
							if (IsPluralNoun(player)) print "(Saldremos";
							else print "(Saldré";
						}
					SECOND_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Os bajaréis";
							else print "(Te bajarás";
						} else {
							if (IsPluralNoun(player)) print "(Saldréis";
							else print "(Saldrás";
						}
					THIRD_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Se bajarán";
							else print "(Se bajará";
						} else {
							if (IsPluralNoun(player)) print "(Saldrán";
							else print "(Saldrá";
						}
				}
				" ", (del_) x1, ").";
			7:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Nos subimos";
							else print "(Me subo";
							" ", (al_) x1, ").^";
						} else if (x1 has container) {
							if (IsPluralNoun(player)) print "(Nos metemos";
							else print "(Me meto";
						} else {
							if (IsPluralNoun(player)) print "(Entramos";
							else print "(Entro";
						}
					SECOND_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Os subís";
							else print "(Te subes";
							" ", (al_) x1, ").^";
						} else if (x1 has container) {
							if (IsPluralNoun(player)) print "(Os metéis";
							else print "(Te metes";
						} else {
							if (IsPluralNoun(player)) print "(Entráis";
							else print "(Entras";
						}
					THIRD_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Se suben";
							else print "(Se sube";
							" ", (al_) x1, ").^";
						} else if (x1 has container) {
							if (IsPluralNoun(player)) print "(Se meten";
							else print "(Se mete";
						} else {
							if (IsPluralNoun(player)) print "(Entran";
							else print "(Entra";
						}
					FIRST_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Nos subimos";
							else print "(Me subí";
							" ", (al_) x1, ").^";
						} else if (x1 has container) {
							if (IsPluralNoun(player)) print "(Nos metimos";
							else print "(Me metí";
						} else {
							if (IsPluralNoun(player)) print "(Entramos";
							else print "(Entré";
						}
					SECOND_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Os subisteis";
							else print "(Te subiste";
							" ", (al_) x1, ").^";
						} else if (x1 has container) {
							if (IsPluralNoun(player)) print "(Os metisteis";
							else print "(Te metiste";
						} else {
							if (IsPluralNoun(player)) print "(Entrasteis";
							else print "(Entraste";
						}
					THIRD_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Se subieron";
							else print "(Se subió";
							" ", (al_) x1, ").^";
						} else if (x1 has container) {
							if (IsPluralNoun(player)) print "(Se metieron";
							else print "(Se metió";
						} else {
							if (IsPluralNoun(player)) print "(Entraron";
							else print "(Entró";
						}
					FIRST_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Nos subiremos";
							else print "(Me subiré";
							" ", (al_) x1, ").^";
						} else if (x1 has container) {
							if (IsPluralNoun(player)) print "(Nos meteremos";
							else print "(Me meteré";
						} else {
							if (IsPluralNoun(player)) print "(Entraremos";
							else print "(Entraré";
						}
					SECOND_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Os subiréis";
							else print "(Te subirás";
							" ", (al_) x1, ").^";
						} else if (x1 has container) {
							if (IsPluralNoun(player)) print "(Os meteréis";
							else print "(Te meterás";
						} else {
							if (IsPluralNoun(player)) print "(Entraréis";
							else print "(Entrarás";
						}
					THIRD_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Se subirán";
							else print "(Se subirá";
							" ", (al_) x1, ").^";
						} else if (x1 has container) {
							if (IsPluralNoun(player)) print "(Se meterán";
							else print "(Se meterá";
						} else {
							if (IsPluralNoun(player)) print "(Entrarán";
							else print "(Entrará";
						}
				}
				" en ", (the) x1, ").^";
		}

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
				" demasiado oscuro. No ", (lm_puedes) player, " ver nada.";
			2:	"No observ", (lm_as_) player, "  nada especial en ",
				(the) x1, ".";
			3:	switch (_grammatical_inflection) {
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
				if (x1 has on) " encendid", (o) x1, ".";
				else " apagad", (o) x1,".";
		}

	Exit:
		!!	1:	Error, el usuario no está subido/sentado/metido en ningún
		!!		objeto. [Nota, si la localidad tiene la propiedad "afuera",
		!!		entonces la acción Salir lo sacará de la localidad. En caso
		!!		contrario es cuando se genera este error.]
		!!	2:	Error, el usuario está dentro de un recipiente cerrado.
		!!	3:	Éxito, el usuario sale/baja del objeto
		!!	4:	Error, más específico. [6/11]
		switch (n) {
			1:	print "No ", (lm_estas) player, " en ningún sitio del que ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "debamos";
						else print "deba";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "debáis";
						else print "debas";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "deban";
						else print "deba";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "debiésemos";
						else print "debiese";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "debieseis";
						else print "debieses";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "debiesen";
						else print "debiese";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "tener que";
				}
				print " ";
				LanguageVerb(verb_word);
				".";
			2:	print "No ", (lm_puedes) player, " salir ", (del_) x1,
				" porque ";
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
							if (IsPluralNoun(player)) print "Bajamos";
							else print "Bajo";
						} else {
							if (IsPluralNoun(player)) print "Salimos";
							else print "Salgo";
						}
					SECOND_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Bajáis";
							else print "Bajas";
						} else {
							if (IsPluralNoun(player)) print "Salís";
							else print "Sales";
						}
					THIRD_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Bajan";
							else print "Baja";
						} else {
							if (IsPluralNoun(player)) print "Salen";
							else print "Sale";
						}
					FIRST_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Bajamos";
							else print "Bajé";
						} else {
							if (IsPluralNoun(player)) print "Salimos";
							else print "Salí";
						}
					SECOND_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Bajasteis";
							else print "Bajaste";
						} else {
							if (IsPluralNoun(player)) print "Salisteis";
							else print "Saliste";
						}
					THIRD_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Bajaron";
							else print "Bajó";
						} else {
							if (IsPluralNoun(player)) print "Salieron";
							else print "Salió";
						}
					FIRST_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Bajaremos";
							else print "Bajaré";
						} else {
							if (IsPluralNoun(player)) print "Saldremos";
							else print "Saldré";
						}
					SECOND_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Bajaréis";
							else print "Bajarás";
						} else {
							if (IsPluralNoun(player)) print "Saldréis";
							else print "Saldrás";
						}
					THIRD_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Bajarán";
							else print "Bajará";
						} else {
							if (IsPluralNoun(player)) print "Saldrán";
							else print "Saldrá";
						}
				}
				" ", (del_) x1, ".";
			4:	print "No ", (lm_puedes) player, ". No ", (lm_estas) player," ";
				if (x1 has supporter) print "encima";
				else print "dentro";
				" ", (del_) x1, ".";
		}

	Fill:
		 "No ", (lm_puedes) player, " llenar", (lo) x1, ".";

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

	GetOff:
		!! Esta acción se genera ante la frase SAL DEL ARMARIO o similares.
		!! Ante SAL a secas la acción es Salir. Si el usuario no está en el
		!! objeto indicado, se genera el siguiente mensaje de error. Si está,
		!! la librería generará una acción Salir, por lo que el mensaje de
		!! éxito será el de Salir.
		"No ", (lm_puedes) player, ". No ", (lm_estas) player, " en ",
		(the) x1, ".";

	Give:
		!!	1:	Error, el usuario intenta dar un objeto que no tiene.
		!!	2:	Error, el usuario se da el objeto a sí mismo.
		!!	3:	Aviso, se ha enviado la acción Dar al PNJ, pero este no ha
		!!		respondido. En este caso x1 apunta al PNJ y no al objeto
		!!		que le hemos dado.
		!!
		!! [Observar que por defecto el objeto sigue en poder del
		!! usuario. Si queremos que el PNJ lo acepte, hay que programarlo
		!! como parte de su rutina Vida.]
		switch (n) {
			1:	"No ", (lm_tienes) player, " ", (the) x1, ".";
			2:	"Manose", (lm_as_) player, " ", (the) x1, " durante unos
				momentos, sin conseguir nada.";
			3:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						"", (The) x1, " no parece", (n) x1,
						" interesad", (o) x1, ".";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						"", (The) x1, " no parecía", (n) x1,
						" interesad", (o) x1, ".";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"", (The) x1, " no parecerá", (n) x1,
						" interesad", (o) x1, ".";
				}
		}

	Go:
		!!	1:	Error, el usuario está dentro/subido en un objeto del que
		!!		tiene que salir antes.
		!!	2:	Error, la localidad no tiene salida en esa dirección (y tampoco
		!!		tiene la propiedad "cant_go", ya que en este caso se habría
		!!		impreso el valor de esa propiedad.
		!!	3:	Error, el usuario ha intentado ir hacia arriba, pero allí hay
		!!		una puerta cerrada.
		!!	4:	Error, el usuario ha intentado ir hacia abajo, pero allí hay
		!!		una puerta cerrada.
		!!	5:	Error, en la dirección que ha dicho el usuario hay una
		!!		puerta cerrada.
		!!	6:	Error, en la dirección que ha dicho el usuario hay una puerta,
		!!		pero ésta no tiene una propiedad "door_to" (probablemente un
		!!		error de programación del juego).
		switch (n) {
			1:	print (lm_ttienes) player, " que ";
				if (x1 has supporter) print "bajar", (lm_te) player;
				else print "salir";
				" ", (del_) x1, " antes.";
			2:	"No ", (lm_puedes) player, " ir por ahí.";
			3:	"", (lm_eeres) player, " incapaz de trepar por ", (the) x1, ".";
			4:	"", (lm_eeres) player, " incapaz de bajar por ", (the) x1, ".";
			5:	"No ", (lm_puedes) player, " pasar a través ", (del_) x1, ".";
			6:	print "No ", (lm_puedes) player, " ir porque ", (the) x1," no ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "lleva", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "llevaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "llevará", (n) x1;
				}
				" a ningún sitio.";
		}

	Insert:
		!!	1:	Error, el objeto no está en poder del usuario. [Nota, conviene
		!!		mirar en este caso si el objeto es animado o no, para generar
		!!		un mensaje más adecuado].
		!!	2:	Error, el usuario intenta meter el objeto en otro que no tiene
		!!		el atributo "container".
		!!	3:	Error, el usuario intenta meter el objeto en un recipiente
		!!		cerrado.
		!!	4:	Error, el objeto es una prenda que el usuario lleva puesta.
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
					FIRST_PERSON_PRESENT:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendríamos que ", (coge)"r", (lo) x1,
								" y no sabemos si se dejará", (n) x1, ".";
							"Antes tendría que ", (coge)"r", (lo) x1,
							" y no sé si se dejará", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitamos";
							else print "Necesito";
							" tener ", (the) x1, " para poder meter", (lo) x1,
							" donde sea.";
						}
					SECOND_PERSON_PRESENT:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendríais que ", (coge)"r", (lo) x1,
								" y no sabéis si se dejará", (n) x1, ".";
							"Antes tendrías que ", (coge)"r", (lo) x1,
							" y no sabes si se dejará", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitáis";
							else print "Necesitas";
							" tener ", (the) x1, " para poder meter", (lo) x1,
							" donde sea.";
						}
					THIRD_PERSON_PRESENT:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendrían que ", (coge)"r", (lo) x1,
								" y no saben si se dejará", (n) x1, ".";
							"Antes tendría que ", (coge)"r", (lo) x1,
							" y no sabe si se dejará", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitan";
							else print "Necesita";
							" tener ", (the) x1, " para poder meter", (lo) x1,
							" donde sea.";
						}
					FIRST_PERSON_PAST:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes teníamos que ", (coge)"r", (lo) x1,
								" y no sabíamos si se hubiese", (n) x1,
								" dejado.";
							"Antes tenía que ", (coge)"r", (lo) x1,
							" y no sabía si se hubiese", (n) x1, " dejado.";
						} else {
							if (IsPluralNoun(player)) print "Necesitábamos";
							else print "Necesitaba";
							" tener ", (the) x1, " para poder meter", (lo) x1,
							" donde fuese.";
						}
					SECOND_PERSON_PAST:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes teníais que ", (coge)"r", (lo) x1,
								" y no sabíais si se hubiese", (n) x1,
								" dejado.";
							"Antes tenías que ", (coge)"r", (lo) x1,
							" y no sabías si se hubiese", (n) x1, " dejado.";
						} else {
							if (IsPluralNoun(player)) print "Necesitabais";
							else print "Necesitabas";
							" tener ", (the) x1, " para poder meter", (lo) x1,
							" donde fuese.";
						}
					THIRD_PERSON_PAST:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tenían que ", (coge)"r", (lo) x1,
								" y no sabían si se hubiese", (n) x1,
								" dejado.";
							"Antes tenía que ", (coge)"r", (lo) x1,
							" y no sabía si se hubiese", (n) x1, " dejado.";
						} else {
							if (IsPluralNoun(player)) print "Necesitaban";
							else print "Necesitaba";
							" tener ", (the) x1, " para poder meter", (lo) x1,
							" donde fuese.";
						}
					FIRST_PERSON_FUTURE:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendremos que ", (coge)"r", (lo) x1,
								" y no sabremos si se dejará", (n) x1, ".";
							"Antes tendré que ", (coge)"r", (lo) x1,
							" y no sab?e si se dejará", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitaremos";
							else print "Necesitaré";
							" tener ", (the) x1, " para poder meter", (lo) x1,
							" donde sea.";
						}
					SECOND_PERSON_FUTURE:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendréis que ", (coge)"r", (lo) x1,
								" y no sabréis si se dejará", (n) x1, ".";
							"Antes tendrás que ", (coge)"r", (lo) x1,
							" y no sabrás si se dejará", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitaréis";
							else print "Necesitarás";
							" tener ", (the) x1, " para poder meter", (lo) x1,
							" donde sea.";
						}
					THIRD_PERSON_FUTURE:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendrán que ", (coge)"r", (lo) x1,
								" y no sabrán si se dejará", (n) x1, ".";
							"Antes tendrá que ", (coge)"r", (lo) x1,
							" y no sabrá si se dejará", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitarán";
							else print "Necesitará";
							" tener ", (the) x1, " para poder meter", (lo) x1,
							" donde sea.";
						}
				}
			2:	print "No se ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "pueden";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "podían";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "podrán";
				}
				" meter cosas dentro ", (del_) x1, ".";
			3:	switch (_grammatical_inflection) {
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
			4:	"", (lm_ttienes) player, " que quitár", (lm_te) player, "",
				(lo) x1, " antes.";
			5:	"No ",(lm_puedes) player," poner un objeto dentro de sí mismo.";
			6:	"(Primero ", (lm_te) player, "", (lo) x1, " quit",
				(lm_as_) player, ").^";
			7:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "queda";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "quedaba";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "quedará";
				}
				" sitio en ", (the) x1, ".";
			8:	"Hecho.";
			9:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Metimos";
						else print "Meto";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Meteis";
						else print "Metes";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Meten";
						else print "Metes";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Metimos";
						else print "Metí";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Metisteis";
						else print "Metiste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Metieron";
						else print "Metió";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Meteremos";
						else print "Meteré";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Meteréis";
						else print "Meterás";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Meterán";
						else print "Meterá";
				}
				" ", (the) x1, " dentro ", (del_) second, ".";
		}

	Inv:
		!!	1:	Mensaje si el inventario está vacío
		!!	2:	Encabezado del inventario, antes de la lista de objetos
		!!		generada por la librería
		!!	3 y 4: [6/11]
		switch (n) {
			1:	print "No llev", (lm_as) player, " nada.";
			2:	print "LLev", (lm_as) player;
			3:	print ":^";
			4:	print ".^";
		}

	Jump:
		"Salt", (lm_as_) player, " en el sitio, sin ningún resultado.";

	JumpOver, Tie:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "lograremos";
				else print "lograré";
			SECOND_PERSON_PRESENT,
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "lograréis";
				else print "lograrás";
			THIRD_PERSON_PRESENT,
			THIRD_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "lograrán";
				else print "logrará";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "hubiésemos logrado";
				else print "hubiese logrado";
			SECOND_PERSON_PAST:
				if (IsPluralNoun(player)) print "hubieseis logrado";
				else print "hubieses logrado";
			THIRD_PERSON_PAST:
				if (IsPluralNoun(player)) print "hubiesen logrado";
				else print "hubiese logrado";
		}
		" nada así.";

	Kiss:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsPluralNoun(player)) "En realidad no deberíamos.";
				"No creo que deba.";
			SECOND_PERSON_PRESENT:
				if (IsPluralNoun(player)) "En realidad no deberíais.";
				"En realidad no crees que debas.";
			THIRD_PERSON_PRESENT:
				if (IsPluralNoun(player)) "En realidad no deberían.";
				"No cree que deba.";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "No se nos ocurrió";
				else print "No se me ocurrió";
				" hacer algo así en aquel momento.";
			SECOND_PERSON_PAST:
				if (IsPluralNoun(player)) print "No se os ocurrió";
				else print "No se te ocurrió";
				" hacer algo así en aquel momento.";
			THIRD_PERSON_PAST:
				if (IsPluralNoun(player)) print "No se les ocurrió";
				else print "No se le ocurrió";
				" hacer algo así en aquel momento.";
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "No se nos ocurrirá";
				else print "No se me ocurrirá";
				" hacer algo así en ese momento.";
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "No se os ocurrirá";
				else print "No se te ocurrirá";
				" hacer algo así en ese momento.";
			THIRD_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "No se le ocurrirá";
				else print "No se le ocurrirá";
				" hacer algo así en ese momento.";
		}

	Listen:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "No escuchamos";
				else print "No escucho";
			SECOND_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "No escucháis";
				else print "No escuchas";
			THIRD_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "No escuchas";
				else print "No escucha";
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

	ListMiscellany:
		!! Los siguientes mensajes se muestran como aclaraciones cuando se está
		!! listando el inventario del usuario, o los objetos que hay en una
		!! localidad. Junto a cada mensaje se comenta qué condiciones deben
		!! darse en ese objeto para que se muestre ese mensaje aclaratorio.
		switch (n) {
			1:	print " (alumbrando)";
			!! El objeto tiene "luz" y la localidad no
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print " (que está", (n) x1, " cerrad", (o) x1, ")";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print " (que estaba", (n) x1, " cerrad", (o) x1, ")";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print " (que estará", (n) x1, " cerrad", (o) x1, ")";
				}
			!! El objeto tiene "recipiente" pero no "abierto"
			3:	print " (cerrad", (o) x1, " y alumbrando)";
			!! Casos 2 y 1 juntos
			4:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print " (que está", (n) x1, " vací", (o) x1, ")";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print " (que estaba", (n) x1, " vací", (o) x1, ")";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print " (que estará", (n) x1, " vací", (o) x1, ")";
				}
			!! El objeto es un recipiente abierto (o transparente) y no
			!!! tiene nada en su interior
			5:	print " (vací", (o) x1, " y alumbrando)";
			!! Casos 1 y 4 juntos
			6:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print " (que está", (n) x1, " cerrad", (o) x1,
						" y vací", (o) x1, ")";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print " (que estaba", (n) x1, " cerrad", (o) x1,
						" y vací", (o) x1, ")";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print " (que estará", (n) x1, " cerrad", (o) x1,
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

			8:	print " (alumbrando y que llev", (lm_as) player,
				" puest", (o) x1;
			!! El objeto tiene "luz" y "puesto"
			9:	print " (alumbrando";
			!! El objeto tiene "luz" pero no "puesto"
			10:	print " (que llev", (lm_as) player, " puest", (o) x1;
			!! El objeto tiene "puesto" pero no "luz"
			11:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print " (que está", (n) x1, " ";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print " (que estaba", (n) x1, " ";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print " (que estará", (n) x1, " ";
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
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print " (que está", (n) x1, " vací", (o) x1, ")";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print " (que estaba", (n) x1, " vací", (o) x1, ")";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print " (que estará", (n) x1, " vací", (o) x1, ")";
				}
			!! Como el caso anterior, pero mensaje más "largo" (que se activa
			!! si EscribirListaDesde es llamada sin el modo BREVE_BIT)
			18:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print " que contiene", (n) x1, " ";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print " que contenía", (n) x1, " ";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print " que contendrá", (n) x1, " ";
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
			1:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "parece", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "parecía", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "parecerá", (n) x1;
				}
				" tener ningún tipo de cerrojo.";
			2:	if (x1 provides with_key) {
					switch (_grammatical_inflection) {
						FIRST_PERSON_PRESENT,
						SECOND_PERSON_PRESENT,
						THIRD_PERSON_PRESENT:
							print (The) x1, " ya estaba", (n) x1;
						FIRST_PERSON_PAST,
						SECOND_PERSON_PAST,
						THIRD_PERSON_PAST:
							print (The) x1, " ya estaba", (n) x1;
						FIRST_PERSON_FUTURE,
						SECOND_PERSON_FUTURE,
						THIRD_PERSON_FUTURE:
							print (The) x1, " ya estará", (n) x1;
					}
					" cerrad", (o) x1, " con llave.";
				}
				else {
					switch (_grammatical_inflection) {
						FIRST_PERSON_PRESENT,
						SECOND_PERSON_PRESENT,
						THIRD_PERSON_PRESENT:
							print (The) x1, " ya tiene", (n) x1;
						FIRST_PERSON_PAST,
						SECOND_PERSON_PAST,
						THIRD_PERSON_PAST:
							print (The) x1, " ya tenía", (n) x1;
						FIRST_PERSON_FUTURE,
						SECOND_PERSON_FUTURE,
						THIRD_PERSON_FUTURE:
							print (The) x1, " ya tendrá", (n) x1;
					}
					" echado el cerrojo.";
				}
			3:	"Primero ", (lm_tienes) player, " que cerrar ", (the) x1, ".";
			4:	if (second) switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						"No parece", (n) x1, " encajar en la cerradura.";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						"No parecía", (n) x1, " encajar en la cerradura.";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"No parecerá", (n) x1, " encajar en la cerradura.";
				}
				"Necesit", (lm_as) player, " algún tipo de llave.";
			5:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (second) {
							if (IsPluralNoun(player)) print "Cerramos";
							else print "Cierro";
							" ", (the) x1, " con ", (the) second, ".";
						} else {
							if (IsPluralNoun(player)) print "Echamos";
							else print "Echo";
						}
					SECOND_PERSON_PRESENT:
						if (second) {
							if (IsPluralNoun(player)) print "Cerrais";
							else print "Cierras";
							" ", (the) x1, " con ", (the) second, ".";
						} else {
							if (IsPluralNoun(player)) print "Echáis";
							else print "Echas";
						}
					THIRD_PERSON_PRESENT:
						if (second) {
							if (IsPluralNoun(player)) print "Cierran";
							else print "Cierra";
							" ", (the) x1, " con ", (the) second, ".";
						} else {
							if (IsPluralNoun(player)) print "Echan";
							else print "Echa";
						}
					FIRST_PERSON_PAST:
						if (second) {
							if (IsPluralNoun(player)) print "Cerramos";
							else print "Cerré";
							" ", (the) x1, " con ", (the) second, ".";
						} else {
							if (IsPluralNoun(player)) print "Echamos";
							else print "Eché";
						}
					SECOND_PERSON_PAST:
						if (second) {
							if (IsPluralNoun(player)) print "Cerrasteis";
							else print "Cerraste";
							" ", (the) x1, " con ", (the) second, ".";
						} else {
							if (IsPluralNoun(player)) print "Echasteis";
							else print "Echaste";
						}
					THIRD_PERSON_PAST:
						if (second) {
							if (IsPluralNoun(player)) print "Cerraron";
							else print "Cerró";
							" ", (the) x1, " con ", (the) second, ".";
						} else {
							if (IsPluralNoun(player)) print "Echaron";
							else print "Echó";
						}
					FIRST_PERSON_FUTURE:
						if (second) {
							if (IsPluralNoun(player)) print "Cerraremos";
							else print "Cerraré";
							" ", (the) x1, " con ", (the) second, ".";
						} else {
							if (IsPluralNoun(player)) print "Echaremos";
							else print "Echaré";
						}
					SECOND_PERSON_FUTURE:
						if (second) {
							if (IsPluralNoun(player)) print "Cerraréis";
							else print "Cerrarás";
							" ", (the) x1, " con ", (the) second, ".";
						} else {
							if (IsPluralNoun(player)) print "Echaréis";
							else print "Echarás";
						}
					THIRD_PERSON_FUTURE:
						if (second) {
							if (IsPluralNoun(player)) print "Cerrarán";
							else print "Cerrará";
							" ", (the) x1, " con ", (the) second, ".";
						} else {
							if (IsPluralNoun(player)) print "Echarán";
							else print "Echará";
						}
				}
				" el cerrojo ", (al_) x1, ".";
		}

	Look:
		!! La acción Look se genera cuando el usuario pone MIRAR, pero también
		!! de forma automática al entrar en una localidad nueva, o cuando el
		!! usuario sale/se baja de un objeto en el que estaba.
		!!
		!! Algunos de los mensajes que se definen aquí aparecen en el "título"
		!! de la localidad (lo que aparece en negrita antes de la descripción
		!! de la localidad).
		!!
		!!	1:	Aclaración a añadir tras el título si el usuario está subido
		!!		en un objeto.
		!!	2:	Aclaración a añadir tras el título si el usuario está dentro
		!!		de un objeto.
		!!	3:	Aclaración a añadir tras el título si el usuario ha sido
		!!		transformado en otro personaje mediante una llamada a
		!!		ChangePlayer(nuevo, 1); (sin el 1, la librería no intentará
		!!		mostrar este mensaje).
		!!	4:	Una vez que la librería ha mostrado la descripción de la
		!!		localidad, si el usuario estaba encima de un supporter, la
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
					print (the) x1, " ", (lm_puedes) player, " ver ";
				} else print (lm_ppuedes) player, " ver ";
				if (n==5) print "también ";
				WriteListFrom(child(x1),
					ENGLISH_BIT + WORKFLAG_BIT + RECURSE_BIT
					+ PARTINV_BIT + TERSE_BIT + CONCEAL_BIT);
				".";
			7:	"No observ", (lm_as_) player, " nada digno de mención al mirar
				hacia ", (the) x1, ".";
			8:	if (x1 has supporter) print " (sobre "; else print " (en ";
				print (the) x1, ")";
		}

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
						if (IsPluralNoun(player)) print "vemos";
						else print "veo";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "veis";
						else print "ves";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "ven";
						else print "ve";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "vimos";
						else print "vi";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "visteis";
						else print "viste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "vieron";
						else print "vio";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "veremos";
						else print "veré";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "veréis";
						else print "verás";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "verán";
						else print "verá";
				}
				" nada inusual.";
		}

	Mild:
		!! Respuesta si se usa como primera palabra algún insulto suave.
		"Bastante.";

	Miscellany:
		!! Esta es una falsa acción, que se usa simplemente para agrupar aquí
		!! todos los mensajes de error del parser, los mensajes ante algunos
		!! metacommandos, o algnouns mensajes de librería no relacionados con
		!! acción alguna. La asignación de números a mensajes es bastante
		!! caprichosa.
		switch (n) {
			1:
				!! El usuario ha especificado objetos multiples, pero el parser
				!! tiene una lista que no admite más de 16, de modo que los
				!! restantes objetos no serán procesados.
				"(Sólo se consideran los dieciséis primeros objetos).";
			2:
				!! El usuario ha usado objetos múltiples, pero por alguna razón
				!! la lista del parser está vacía.
				"[No se pudo determinar a qué objetos te has referido].";
			3:
				!! Mensaje de fin del relato. Has muerto.
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print " Hemos muerto ";
						else print " He muerto ";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print " Habéis muerto ";
						else print " Has muerto ";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print " Han muerto ";
						else print " Ha muerto ";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print " Habíamos muerto ";
						else print " Había muerto ";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print " Habíais muerto ";
						else print " Habías muerto ";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print " Habían muerto ";
						else print " Había muerto ";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print " Habremos muerto ";
						else print " Habré muerto ";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print " Habréis muerto ";
						else print " Habrás muerto ";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print " Habrán muerto ";
						else print " Habrá muerto ";
				}
			4:
				!! Mensaje de fin del relato. Victoria.
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print " Hemos ganado ";
						else print " He ganado ";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print " Habéis ganado ";
						else print " Has ganado ";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print " Han ganado ";
						else print " Ha ganado ";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print " Habíamos ganado ";
						else print " Había ganado ";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print " Habíais ganado ";
						else print " Habías ganado ";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print " Habían ganado ";
						else print " Había ganado ";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print " Habremos ganado ";
						else print " Habré ganado ";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print " Habréis ganado ";
						else print " Habrás ganado ";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print " Habrán ganado ";
						else print " Habrá ganado ";
				}
			5:
				!! Mensaje a mostrar tras el fin del juego, para pedir al
				!! usuario si quiere reniciar, recuperar, anular, puntuación,
				!! curiosidades o terminar.
				print "^¿Quieres REINICIAR, RECUPERAR un juego guardado";
				#IFDEF DEATH_MENTION_UNDO;
					print ", ANULAR tu último movimiento";
				#ENDIF;
				#IFNDEF NO_PUNTUACION;
					if (TASKS_PROVIDED==0)
						print ", ver la PUNTUACIÓN de este juego";
				#ENDIF; ! NO_PUNTUACION
				if (deadflag==2 && AMUSING_PROVIDED==0)
					print ", ver algunas CURIOSIDADES";
				" o TERMINAR?";
			6:
				!! Error si el intérprete no tiene "undo"
				"[Tu intérprete no puede ~DESHACER~ acciones].";
			#Ifdef TARGET_ZCODE; ![6/11]
				!! Otro error si el intérprete no tiene "undo", pero no había
				!! sido detectado correctamente.
			7:
				"[~DESHACER~ falló. (Puede que tu intérprete no permita
				realizar la acción)].";
			#Ifnot; ! TARGET_GLULX
			7:
				"[No puedes ~DESHACER~ más].";
			#Endif; ! TARGET_
			8:
				!! Si el usuario no responde correctamente a la pregunta del
				!! mensaje [Miscellany,5]
				"[Por favor, introduce una de las respuestas anteriores].";
			9:
				!! Mensaje cuando se detecta, al final del turno, que ya no hay
				!! una fuente de luz en la localidad actual.
				print "^¡";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Nos hemos";
						else print "Me he";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Os habéis";
						else print "Te has";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Se han";
						else print "Se ha";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Nos habíamos";
						else print "Me había";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Os habíais";
						else print "Te habías";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Se habían";
						else print "Se había";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Nos habremos";
						else print "Me habré";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Os habréis";
						else print "Te habrás";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Se habrán";
						else print "Se habrá";
				}
				" quedado a oscuras!";
			10:
				!! Mensaje cuando el usuario introduce una linea en blanco.
				"[No has introducido ninguna instrucción].";
			11:
				!! Si el usuario intenta "undo" al principio del juego
				"[No se puede ~DESHACER~ algo que no has hecho].";
			12:
				!! Si el usuario pone "undo" dos veces.
				"[No se puede ~DESHACER~ dos veces seguidas].";
			13:
				!! Éxito en el "undo".
				"[Retrocediendo al turno anterior].";
			14:
				!! Si el usuario pone EEPA (verbo para corregir), pero el
				!! parser no recordaba ninguna palabra mal. Ejmplo de uso del
				!! comando EEPA:
				!!		> SACA MAZANA VERDE DE LA CESTA
				!!		No vqeo eso por aquí.
				!!		> EEPA MANZANA
				!!		Sacas la manzana verde de la cesta de mimbre.
				"[Eso no puede corregirse].";
			15:
				!! Se usa EEPA sin especificar la palabra corregida.
				"[Has utilizado ~EEPA~ sin especificar qué palabra deseabas
				corregir].";
			16:
				!! Si el usuario pone EEPA seguido de dos o más palabras.
				"[~EEPA~ sólo puede corregir una palabra].";
			17:
				!! Descripción del objeto Oscuridad.
				switch (_grammatical_inflection) {
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
				" demasiado oscuro como para poder ver algo.";
			18:
				!! Nombre corto del objeto usuario.
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					FIRST_PERSON_PAST,
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "nosotr", (o) player;
						else print "mí";
					SECOND_PERSON_PRESENT,
					SECOND_PERSON_PAST,
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "vosotr", (o) player;
						else print "tí";
					THIRD_PERSON_PRESENT,
					THIRD_PERSON_PAST,
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "ell", (o) player;
						else print "sí";
				}
				print " mism", (o) player;
			19:
				!! Descripción del objeto usuario.
				"Tan buen aspecto como siempre.";
			20:
				!! Cuando el usuario pone PNJ, REPITE para que el PNJ haga otra
				!! vez la última acción.
				"[Para repetir un comando como ~PERSONAJE, SALTA~, escribe
				~REPITE~, en lugar de ~PERSONAJE, REPITE~].";
			21:
				!! Cuando el usuario pone REPITE como primer commando del juego.
				"[No hay comando que repetir].";
			22:
				!! El usuario ha comenzado la frase con una coma.
				"[No se puede empezar una frase con una coma].";
			23:
				!! Cuando el usuario pone, por ejemplo; PEPE, COGE HACHA, pero
				!! no hay un objeto que responda al name PEPE.
				"[Parece que has tratado de hablar con alguien, pero no se pudo
				identificar con quién].";
			24:
				!! Si el usuario intenta hablar con un objeto que no es
				!! "animate" ni "talkable" ("talkable" debe ponerse a objetos
				!! inanimates con los que se podría hablar, como un micrófono).
				"[No es posible hablar con ", (the) x1, "].";
			25:	!! Hay palabras no comprendidas entre el nombre de un PNJ y la
				!! coma, ej: PEPE ZAFDSRGG, SALTA.
				"[Para iniciar una conversación, intenta órdenes del tipo:
				PERSONAJE, HOLA].";
			26:
				!! La gramática especifica que una acción debe efectuarse sobre
				!! un objeto en poder del usuario (token 'held'), pero el
				!! usuario lo ha intentado sobre un objeto que no tiene, aunque
				!! está a su alcance. El parser intentará automáticamente coger
				!! ese objeto antes de efectuar la acción. En este mensaje se
				!! avisa al usuario de esta intención.
				"(Primero trat", (lm_as_) player, " de ", (coge) "r ",
				(the) x1, ".)";

			!! ERRORES DE PARSING: Estos errores son generados por la librería,
			!! a menos que el programador proporcione su propia función
			!! ParserError para manejo de errores.

			27:
				!! ERROR DE PARSING. El parser se ha atascado. Es el tipo de
				!! error más genérico. Si el parser puede, se generará un error
				!! más concreto.
				"[No se pudo entender esa instrucción.]";

			28:
				!! ERROR DE PARSING. A la instrucción le sobraban palabras,
				!! aunque el parser ha entendido gran parte de su significado.
				print "[Intenta de nuevo porque sólo se pudo entender: ~";
				PrintCommand();
				print "~.]^";
				return true;

			29:
				!! ERROR DE PARSING. El parser esperaba un token de tipo
				!! número.
				"[No se pudo comprender ese número.]";

			30:
				!! ERROR DE PARSING. El parser no ha comprendido el nombre del
				!! objeto al que se refiere el jugador, o ese objeto no está
				!! aquí.
				"[Te has referido a algo con lo que no se puede interactuar en
				este momento.]";

			31:
				!! ERROR DE PARSING. Este error parece que no se genera nunca.
				!! Un posible bug de libreria, o restos de versiones arcaicas.
				"[Parece que falta información en esa instrucción.]";

			32:
				!! ERROR DE PARSING. El objeto que el usuario intenta usar no
				!! está en su poder. El parser ha intentado "cogerlo de forma
				!! automatica", pero ha fallado.
				"No ", (lm_tienes) player, " eso.";

			33:
				!! ERROR DE PARSING. El usuario ha intentado usar objetos
				!! múltiples (o "TODO") con un verbo que en su gramática no lo
				!! admite.
				"[No se pueden especificar objetos múltiples con ~",
				(address) verb_word, "~.]";

			34:
				!! ERROR DE PARSING. El usuario ha intentado objetos multiples
				!! para "noun" y para "second", como en METE TODO EN TODO.
				"[Sólo se pueden especificar objetos múltiples una vez en cada
				línea].";

			35:
				!! ERROR DE PARSING. El usuario ha usado un pronombre, como
				!! COMELO, pero el parser no tiene asignado un valor a ese
				!! pronombre.
				"[No está claro a qué te refieres con ~",
				(address) pronoun_word ,"~].";

			36:
				!! ERROR DE PARSING. El usuario ha puesto una lista de objetos
				!! y ha usado la palabra EXCEPTO para exceptuar algo que no
				!! estaba incluido en la lista, por ejemplo: COGE TODAS LAS
				!! MONEDAS EXCEPTO EL SACO.
				"[Has exceptuado algo que no estaba incluido].";

			37:
				!! ERROR DE PARSING. La gramática de un verbo obliga a que el
				!! objeto sobre el que se actúe sea animate (tiene un token de
				!! tipo "creature"), pero el usuario lo ha intentado sobre un
				!! objeto que no es animate.
				"[Sólo se puede hacer eso con seres animados].";

			38:
				!! ERROR DE PARSING. La primera palabra usada por el usuario es
				!! desconocida (o la primera palabra tras la coma, si se trata
				!! de una orden a un PNJ).
				print "[La acción ~";
				for (j = 0: j < WordLength(1): j++)
					print (char) WordAddress(1) -> j;
				"~ no está definida].";

			39:
				!! ERROR DE PARSING. El usuario intenta actiones sobre las
				!! palabras que están en la propiedad "irrelevante" de la
				!! localidad.
				"[No es necesario referirse a eso para terminar la historia].";

			40:
				!! ERROR DE PARSING. El usuario ha usado un pronombre, como
				!! EXAMINALO, pero el pronombre se refiere a un objeto que ya
				!! no está visible.
				"[Ahora mismo no se puede encontrar lo que representa el
				pronombre ~", (address) pronoun_word, "~ (", (the) pronoun_obj,
				").]";

			41:
				!! ERROR DE PARSING. Este error no se produce nunca.
				!! Probablemente sigue aqui por razones de compatibilidad, o
				!! por despiste de Graham. ¿Tal vez ha sido sustituido en
				!! versiones mas recients por el mensaje número 28?
				"[No se pudo entender la última parte de la instrucción].";

			42:
				!! ERROR DE PARSING. El usuario ha solicitado un numero de
				!! objetos en una lista de objetos múltiples, pero el parser no
				!! es capaz de encontrar tantos. Por ejemplo: COGE SEIS MONEDAS.
				if (x1==0) "[No hay suficientes].";
		        else if (x1 == 1) {
			    	print "[Aquí sólo hay un";
			    	if (multiple_object-->1) print (o) multiple_object-->1;
			    	else print "o";
			    	" disponible].";
			    }
				"[Sólo hay ", (number) x1, " disponibles para esa acción].";

			43:
				!! ERROR DE PARSING. El usuario ha puesto TODO como objeto
				!! múltiple, pero el parser no ha encontrado ningún objeto. En
				!! realidad este error parece no producirse nunca y el que
				!! acaba generándose siempre es el siguiente (#44, ASKSCOPE_PE).
				"[No se puede encontrar nada con lo que hacer eso].";

			44:
				! TODO - mensaje del parser
				!! El usuario ha intentado objetos múltiples usando TODO
				!! pero el parser no ha encontrado ninguno. Por ejemplo, COGE
				!! TODO o DEJA TODO si no hay nada cerca o en el inventario.
				!! Modificado en [020621] para dar un mensaje más coherente
				!! si el usuario tiene algún objeto en su inventario.
				if (action_to_be == ##Drop) {
					print "¡Pero si no llev", (lm_as) player, " nada";
					if (children (player)) " de eso!";
					else "!";
				}
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					FIRST_PERSON_PAST,
					FIRST_PERSON_FUTURE:
						print "No hay nada que ";
					SECOND_PERSON_PRESENT,
					SECOND_PERSON_PAST,
					SECOND_PERSON_FUTURE:
						print "No había nada que ";
					THIRD_PERSON_PRESENT,
					THIRD_PERSON_PAST,
					THIRD_PERSON_FUTURE:
						print "No habrá nada que ";
				}
				LanguageVerb(verb_word);
				".";
			45:
				! TODO - mensaje del parser
				!! El usuario ha nombrado un PNJ ambiguo (hay más de noun con
				!! el mismo name cerca). El parser le pide aclaración. Este
				!! mensaje es la primera parte de la pregunta, el resto lo pone
				!! el parser (que es la lista de PNJs entre los que duda).
				!! Debemos poner a 1 la variable PreguntaCualExactamente cuando
				!! se generan este tipo de preguntas aclaratorias.
				print "¿Quién concretamente, ";
				PreguntaCualExactamente=1;
				ImprimirListaDudosos("o");
				!print "?^";
			46:
				! TODO - mensaje del parser
				!! El usuario ha nombrado un objeto ambiguo (hay más de objeto
				!! con el mismo nombre cerca). El parser le pide aclaración.
				!! Este mensaje es la primera parte de la pregunta, el resto lo
				!! pone el parser (que es la lista de objetos entre los que
				!! duda). Debemos poner a 1 la variable PreguntaCualExactamente
				!! cuando se generan este tipo de preguntas aclaratorias.
				print "¿Cuál concretamente, ";
				PreguntaCualExactamente=1;
				ImprimirListaDudosos("o");
				!print "?^";
			47:
				!! El usuario ha respondido "TODOS" o "AMBOS" a una pregunta
				!! aclaratoria como la anterior, pero el verbo no admite
				!! objetos múltiples.
				print "[Desafortunadamente sólo puedes referirte a un objeto
				en este caso. ¿Cuál exactamente?]^";
				PreguntaCualExactamente=1;
			48:
				! TODO - Editar mensaje: "Tienes que indicar a quién..."
				!! El usuario ha escrito una frase u orden a PSI incompleta,
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
			49:
				! TODO - Editar mensaje: "Tienes que indicar a quién..."
				!! El usuario ha escrito una frase u orden incompleta, como
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
			50:
				! TODO - mensaje del parser
				!! El usuario acaba de realizar una acción que puntúa (la
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
				!! El usuario ha intentado una acción con objeto múltiple
				!! (como COGE TODO). Esta acción es convertida por el parser en
				!! una serie de actiones COGE OBJETO1, COGE OBJETO2, etc... Si
				!! en la ejecución de alguna de estas actiones encuentra que la
				!! localidad del player ha cambiado, debe abortar el proceso.
				!! Este mensaje informa de ello al usuario.
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
				print "[Escribe un número del 1 al ", x1, ", 0 para volver a
				mostrarlo, o pulsa Intro].";
				new_line;
				return true;
			53:
				!! Mensaje que muestra el sistema de menús cuando espera una
				!! tecla.
				new_line;
				"[Por favor, pulsa ESPACIO].";
			54:
				! TODO - Guardar comentarios sin imprimir mensajes
				"[Comentario guardado].";
			55:
				"[Comentario NO guardado].";
			56:
				print ".^";
			57:
				print "?^";
		}

	No:
		!! Cuando el usuario pone NO, a secas, se genera esta acción. Está
		!! pensada por si el relato suelta una frase del estilo de "¿Pero tú
		!! eres tonto?" y el usuario responde NO. De todas formas, hay un
		!! problema, y es que NO es normalmente la acción Ir al noroeste. Si
		!! queremos que NO sea provisionalmente la acción No, entonces se debe
		!! poner a 1 la variable PreguntaSiNo antes de escribir el texto
		!! "¿Pero tú eres tonto?". En ese caso, el parser interpretará "NO"
		!! como la acción No, pero únicamente durante el siguiente turno.
		"[Sólo se trataba de una pregunta retórica].";

	NotifyOff:
		"[Notificación de puntuación desactivada].";

	Objects:
		! TODO - mensaje del parser
		!! Ante el verbo "OBJETOS" se genera esta acción, que muestra una
		!! lista de todos los objetos que el usuario ha manipulado a lo largo
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
			3:	print "   (puest", (o) x1, ")";
			4:	print "   (", (lm_contigo) player, ")";
			5:	print "   (dejad", (o) x1, " con alguien)";
			6:	print "   (";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "ahora";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "entonces";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "en ese momento";
				}
				print " en ", (name) x1, ")";
			7:	print "   (";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "ahora";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "entonces";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "en ese momento";
				}
				print " en ", (the) x1, ")";
			8:	print "   (";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "ahora";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "entonces";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "en ese momento";
				}
				print " dentro ", (del_) x1, ")";
			9:	print "   (";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "ahora";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "entonces";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "en ese momento";
				}
				print " en ", (the) x1, ")";
			10:	print "   (perdid", (o) x1, ")";
		}

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
			1:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						"es algo que pueda abrirse";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						"era algo que se pudiese abrir.";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"será algo que pueda abrirse.";
				}
			2:	switch (_grammatical_inflection) {
				FIRST_PERSON_PRESENT,
				SECOND_PERSON_PRESENT,
				THIRD_PERSON_PRESENT:
					print "Está", (n) x1;
				FIRST_PERSON_PAST,
				SECOND_PERSON_PAST,
				THIRD_PERSON_PAST:
					print "Estaba", (n) x1;
				FIRST_PERSON_FUTURE,
				SECOND_PERSON_FUTURE,
				THIRD_PERSON_FUTURE:
					print "Estará", (n) x1;
				}
				" cerrad", (o) x1, " con llave.";
			3:	print "Ya ";
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
				" abiert", (o) x1, ".";
			4:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Abrimos";
						else print "Abro";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Abréis";
						else print "Abres";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Abren";
						else print "Abre";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Abrimos";
						else print "Abrí";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Abristeis";
						else print "Abriste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Abrieron";
						else print "Abrió";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Abriremos";
						else print "Abriré";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Abriréis";
						else print "Abrirás";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Abrirán";
						else print "Abrirá";
				}
				print " ", (the) x1, ", descubriendo ";
				if (WriteListFrom(child(x1),
					ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT) == 0) {
					switch (_grammatical_inflection) {
						FIRST_PERSON_PRESENT,
						SECOND_PERSON_PRESENT,
						THIRD_PERSON_PRESENT:
							"que está", (n) x1, " vací", (o) x1, ".";
						FIRST_PERSON_PAST,
						SECOND_PERSON_PAST,
						THIRD_PERSON_PAST:
							"que estaba", (n) x1, " vací", (o) x1, ".";
						FIRST_PERSON_FUTURE,
						SECOND_PERSON_FUTURE,
						THIRD_PERSON_FUTURE:
							"que estará", (n) x1, " vací", (o) x1, ".";
					}
				} else ".";
			5:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Abrimos";
						else print "Abro";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Abréis";
						else print "Abres";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Abren";
						else print "Abre";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Abrimos";
						else print "Abrí";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Abristeis";
						else print "Abriste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Abrieron";
						else print "Abrió";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Abriremos";
						else print "Abriré";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Abriréis";
						else print "Abrirás";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Abrirán";
						else print "Abrirá";
				}
				"", (the) x1, ".";
		}

	Order:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print (The) x1, " tiene", (n) x1;
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print (The) x1, " tenía", (n) x1;
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print (The) x1, " tendrá", (n) x1;
		}
		" mejores cosas que hacer.";

	Places:
		!! El verbo "LUGARES" muestra un listado de los lugares que el usuario
		!! ha visitado. Aquí debemos escribir el texto introductorio a esa
		!! lista.
		switch (n) {
			1:  print "[Has visitado: ";
			2:  print ".]^";
		}

	Pray:
		print "La fe tal vez ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "pueda";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "pudiese";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "podrá";
		}
		" resultar útil en una ocasión diferente.";

	Prompt:
		!! El prompt aparece justo antes de pedir una nueva línea al usuario.
		!! Puede definirse para que sea una frase, o se genere una frase
		!! aleatoria en cada turno, por ejemplo.
		new_line;
		print "> ";

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
			1:	print "[En este momento, ";
			2:	print "es ";
			3:	print "no está definido";
			4:	print "el juego no conoce ningún pronombre].";
				new_line;
				return true;
			5:	print "].";
				new_line;
				return true;
		}

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
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "Está", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "Estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "Estará", (n) x1;
				}
				" firmemente sujet", (o) x1, ".";
			2:	"No ", (lm_eres_) player, " capaz.";
			3:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "ocurre";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "ocurrió";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "ocurrirá";
				}
				" nada, aparentemente.";
			4:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "Eso sería";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "Aquello hubiese sido";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "Eso sería";
				}
				", como poco, maleducado.";
		}

!!	Push:	see Pull.

	PushDir:
		!! La acción PushDir se genera ante frases como EMPUJA EL COCHE HACIA
		!! EL NORTE. Hay 3 casos posibles:
		!!	1:	Si el juego no ha previsto la posibilidad de empujar ese
		!!		objeto hacia una dirección (o sea, no llama a la rutina
		!!		PermitirEmujarDir). Esta es la respuesta por defecto más
		!!		habitual.
		!!	2:	Si el usuario pone tras HACIA algo que no es una dirección.
		!!		(respuesta por defecto en este caso).
		!!	3:	Si intenta empujar hacia arriba o hacia abajo.
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						print "No ";
						if (IsPluralNoun(player)) "creemos";
						else print "creo";
						" que empujar", (lo) x1, " sirva de nada.";
					SECOND_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) "creéis";
						else print "crees";
						" que empujar", (lo) x1, " sirva de nada.";
					THIRD_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "creen";
						else print "cree";
						" que empujar", (lo) x1, " sirva de nada.";
					FIRST_PERSON_PAST:
						print "No ";
						if (IsPluralNoun(player)) print "creíamos";
						else print "creía";
						" que empujar", (lo) x1, " hubiese servido de nada.";
					SECOND_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "creíais";
						else print "creías";
						" que empujar", (lo) x1, " hubiese servido de nada.";
					THIRD_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "creían";
						else print "creía";
						" que empujar", (lo) x1, " hubiese servido de nada.";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"Empujar ", (the) x1, " no servirá de nada.";
				}
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						"Eso no es una dirección.";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						"Aquello no era una dirección.";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"Eso no será una dirección.";
				}
			3:	"No ", (lm_puedes) player, " empujar", (lo) x1, " en esa
				dirección.";
		}

	PutOn:
		!!	1:	Error, el objeto no está en poder del usuario. [Nota, conviene
		!!		mirar en este caso si el objeto es animado o no, para generar
		!!		un mensaje más adecuado].
		!!	2:	Error, el usuario intenta poner un objeto sobre sí mismo.
		!!	3:	Error, el usuario intenta poner el objeto sobre otro que no
		!!		tiene el atributo "supporter".
		!!	4:	Error, el usuario intenta poner un objeto sobre el propio
		!!		usuario.
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
					FIRST_PERSON_PRESENT:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendríamos que ", (coge)"r", (lo) x1,
								" y no sabemos si se dejará", (n) x1, ".";
							"Antes tendría que ", (coge)"r", (lo) x1,
							" y no sé si se dejará", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitamos";
							else print "Necesito";
							" tener ", (the) x1, " para poder poner", (lo) x1,
							" donde sea.";
						}
					SECOND_PERSON_PRESENT:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendríais que ", (coge)"r", (lo) x1,
								" y no sabéis si se dejará", (n) x1, ".";
							"Antes tendrías que ", (coge)"r", (lo) x1,
							" y no sabes si se dejará", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitáis";
							else print "Necesitas";
							" tener ", (the) x1, " para poder poner", (lo) x1,
							" donde sea.";
						}
					THIRD_PERSON_PRESENT:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendrían que ", (coge)"r", (lo) x1,
								" y no saben si se dejará", (n) x1, ".";
							"Antes tendría que ", (coge)"r", (lo) x1,
							" y no sabe si se dejará", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitan";
							else print "Necesita";
							" tener ", (the) x1, " para poder poner", (lo) x1,
							" donde sea.";
						}
					FIRST_PERSON_PAST:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes teníamos que ", (coge)"r", (lo) x1,
								" y no sabíamos si se hubiese", (n) x1,
								" dejado.";
							"Antes tenía que ", (coge)"r", (lo) x1,
							" y no sabía si se hubiese", (n) x1, " dejado.";
						} else {
							if (IsPluralNoun(player)) print "Necesitábamos";
							else print "Necesitaba";
							" tener ", (the) x1, " para poder poner", (lo) x1,
							" donde fuese.";
						}
					SECOND_PERSON_PAST:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes teníais que ", (coge)"r", (lo) x1,
								" y no sabíais si se hubiese", (n) x1,
								" dejado.";
							"Antes tenías que ", (coge)"r", (lo) x1,
							" y no sabías si se hubiese", (n) x1, " dejado.";
						} else {
							if (IsPluralNoun(player)) print "Necesitabais";
							else print "Necesitabas";
							" tener ", (the) x1, " para poder poner", (lo) x1,
							" donde fuese.";
						}
					THIRD_PERSON_PAST:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tenían que ", (coge)"r", (lo) x1,
								" y no sabían si se hubiese", (n) x1,
								" dejado.";
							"Antes tenía que ", (coge)"r", (lo) x1,
							" y no sabía si se hubiese", (n) x1, " dejado.";
						} else {
							if (IsPluralNoun(player)) print "Necesitaban";
							else print "Necesitaba";
							" tener ", (the) x1, " para poder poner", (lo) x1,
							" donde fuese.";
						}
					FIRST_PERSON_FUTURE:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendremos que ", (coge)"r", (lo) x1,
								" y no sabremos si se dejará", (n) x1, ".";
							"Antes tendré que ", (coge)"r", (lo) x1,
							" y no sab?e si se dejará", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitaremos";
							else print "Necesitaré";
							" tener ", (the) x1, " para poder poner", (lo) x1,
							" donde sea.";
						}
					SECOND_PERSON_FUTURE:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendréis que ", (coge)"r", (lo) x1,
								" y no sabréis si se dejará", (n) x1, ".";
							"Antes tendrás que ", (coge)"r", (lo) x1,
							" y no sabrás si se dejará", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitaréis";
							else print "Necesitarás";
							" tener ", (the) x1, " para poder poner", (lo) x1,
							" donde sea.";
						}
					THIRD_PERSON_FUTURE:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendrán que ", (coge)"r", (lo) x1,
								" y no sabrán si se dejará", (n) x1, ".";
							"Antes tendrá que ", (coge)"r", (lo) x1,
							" y no sabrá si se dejará", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitarán";
							else print "Necesitará";
							" tener ", (the) x1, " para poder poner", (lo) x1,
							" donde sea.";
						}
				}
			2:	"No ", (lm_puedes_) player, " poner un objeto sobre sí mismo.";
			3:	print "Poner cosas sobre ", (the) x1, " no ";
				switch (_grammatical_inflection) {
						FIRST_PERSON_PRESENT,
						SECOND_PERSON_PRESENT,
						THIRD_PERSON_PRESENT:
							print "servirá";
						FIRST_PERSON_PAST,
						SECOND_PERSON_PAST,
						THIRD_PERSON_PAST:
							print "hubiese servido";
						FIRST_PERSON_FUTURE,
						SECOND_PERSON_FUTURE,
						THIRD_PERSON_FUTURE:
							print "servirá";
				}
				" de nada.";
			4:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) "Nos falta";
						else print "Me falta";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) "Os falta";
						else print "Te falta";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Les falta";
						else print "Le falta";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Nos faltaba";
						else print "Me faltaba";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Os faltaba";
						else print "Te faltaba";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Les faltaba";
						else print "Le faltaba";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Nos faltará";
						else print "Me faltará";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Os faltará";
						else print "Te faltará";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Les faltará";
						else print "Le faltará";
				}
				" destreza.";
			5:	"(Primero ", (lm_te) player, " ", (lo) x1, "quit",
				(lm_as_) player, ").^";
			6:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "queda";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "quedaba";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "quedará";
				}
				" sitio en ", (the) x1, " para poner nada más.";
			7:	"Hecho.";
			8:	if ((_grammatical_inflection == FIRST_PERSON_PAST)
			 		&& (~~IsPluralNoun(player))) print "Coloqué";
				else print "Coloc", (lm_as_) player;
				" ", (the) x1, " sobre ", (the) second, ".";
		}

	Quit:
		!!	1:	Respuesta al comando FIN.
		!!	2:	Respuesta si el usuario escribe algo distinto de "si" o "no".
		switch (n) {
			1:
				print "[Por favor, responde SI o NO]: ";
			2:
				print "[¿Realmente quieres abandonar el relato?] ";
		}
		return true;

	Remove:
		!!	1:	El recipiente que contiene el objeto que el usuario quiere
		!!		sacar, está cerrado. (x1 apunta al objeto, no al recipiente,
		!!		el cuál puede obtenerse con parent(x1)).
		!!	2:	El objeto no está dentro del recipiente que el usuario ha dicho.
		!!	3:	Éxito.
		switch (n) {
			1:	print "Por desgracia ", (the) parent(x1);
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print " está", (n) parent(x1);
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print " estaba", (n) parent(x1);
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print " estará", (n) parent(x1);
				}
				" cerrad", (o) parent(x1), ".";
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						if (second has animate)
							"¡Pero si no ", (lo) x1, " tiene", (n) second,"!";
						"¡Pero si no está", (n) x1, " ahí ahora!";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						if (second has animate)
							"¡Pero si no ", (lo) x1, " tenía", (n) second,"!";
						"¡Pero si no estaba", (n) x1, " ahí en aquel momento!";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						if (second has animate)
							"¡Pero si no ", (lo) x1, " tendrá", (n) second, "!";
						"¡Pero si no estará", (n) x1, " ahí en ese momento!";
				}
			3:	if (verb_word == 'quita') "Quitad", (o) x1, ".";
				"Sacad", (o) x1, ".";
		}

	Restart:
		!!	1:	Respuesta al comando REINICIAR.
		!!	2:	Si no se puede reiniciar.
		switch (n) {
			1:	print "[¿Realmente quieres reiniciar el relato?]";
			2:	"[Error al reiniciar la partida].";
		}

	Restore:
		!!	1:	Si no se pudo cargar la partida con LOAD.
		!!	2:	Éxito (no llega a mostrarse, porque en caso de éxito el estado
		!!		del juego cambia al momento en que se salvó. El "Ok" que se ve
		!!		entonces es el del comando Salvar.
		switch (n) {
			1:	"[Error. No se pudo recuperar la partida].";
			2:	print "[Partida cargada].";
				new_line;
				<<Look>>;
		}

	Rub:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "Ya está", (n) x1;
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "Ya estaba", (n) x1;
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "Ya estará", (n) x1;
		}
		" bastante limpi", (o) x1, ".";

	Save:
		!!	1:	Si no se pudo guardar el juego.
		!!	2:	Éxito.
		switch (n) {
			1:	"[Error. No se pudo guardar la partida].";
			2:	"[Partida guardada].";
		}

	Score:
		!! Puntuación del juego. Puede activarse porque el usuario lo pide
		!! (con el verbo "PUNTUACION") o porque el juego ha terminado. En
		!! este ultimo caso, la variable "deadflag" valdrá true.
		switch (n) {
			1:
				if (deadflag) print "[En este juego, tu puntuación ha sido ";
				else print "[Hasta el momento tu puntuación es ";
				print score, " de un total de ", MAX_SCORE,
				", en ", turns, " turno";
				if (turns>1) print "s";
				print "].";
				new_line;
				return;
			2:	"[Este juego no tiene conteo de puntuación].";
		}

	ScriptOff:
		!!	1:	Error ya estaba desactivada la transcrcipción.
		!!	2:	Éxito.
		switch (n) {
			1:	"[La transcripción ya estaba desactivada].";
			2:	new_line; "[Fin de la transcripción].";
			3:	"[Intento fallido de finalización de transcripción].";
		}

	ScriptOn:
		!!	1:	Error, ya estaba activada la transcrcipción.
		!!	2:	Éxito (parte inicial del mensaje, la librería añade el título
		!!		del juego obtenido de la constante Historia).
		switch (n) {
			1:	"[La transcripción ya estaba activada].";
			2:	"[Iniciando la transcripción de]:";
			3:	"[Intento fallido de comienzo de la transcripción].";
		}

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
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "hay";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "había";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "habrá";
				}
				" nada sobre ", (the) x1, ".";
			3:

			3:	print "Sobre ", (the) x1;
				WriteListFrom(child(x1),
					ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT + ISARE_BIT);
				".";
			4:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "encontramos";
						else print "encuentro";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "encontráis";
						else print "encuentras";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "encuentran";
						else print "encuentra";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "encontramos";
						else print "encontré";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "encontrasteis";
						else print "encontraste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "encontraron";
						else print "encontró";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "encontraremos";
						else print "encontraré";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "encontraréis";
						else print "encontrarás";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "encontrarán";
						else print "encontrará";
				}
				" nada interesante.";
			5:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "podemos";
						else print "puedo";
						" ver lo que hay dentro ", (del_) x1, " porque
						está", (n) x1, " cerrad", (o) x1, ".";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "podéis";
						else print "puedes";
						" ver lo que hay dentro ", (del_) x1, " porque
						está", (n) x1, " cerrad", (o) x1, ".";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "pueden";
						else print "puede";
						" ver lo que hay dentro ", (del_) x1, " porque
						está", (n) x1, " cerrad", (o) x1, ".";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "podíamos";
						else print "podía";
						" ver lo que había dentro ", (del_) x1, " porque
						estaba", (n) x1, " cerrad", (o) x1, ".";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "podíais";
						else print "podías";
						" ver lo que había dentro ", (del_) x1, " porque
						estaba", (n) x1, " cerrad", (o) x1, ".";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "podían";
						else print "podía";
						" ver lo que había dentro ", (del_) x1, " porque
						estaba", (n) x1, " cerrad", (o) x1, ".";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "podremos";
						else print "podré";
						" ver lo que haya dentro ", (del_) x1, " porque
						estará", (n) x1, " cerrad", (o) x1, ".";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "podréis";
						else print "podrás";
						" ver lo que haya dentro ", (del_) x1, " porque
						estará", (n) x1, " cerrad", (o) x1, ".";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "podrán";
						else print "podrá";
						" ver lo que haya dentro ", (del_) x1, " porque
						estará", (n) x1, " cerrad", (o) x1, ".";
				}
			6:	switch (_grammatical_inflection) {
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
				" vací", (o) x1, ".";
			7:	print "En ", (the) x1;
				WriteListFrom(child(x1),
					TERSE_BIT + ENGLISH_BIT + ISARE_BIT + CONCEAL_BIT);
				".";
		}

	Set:
		!! Set sale ante la frase FIJA OBJETO o AJUSTA OBJETO
		"No, no ", (lm_puedes) player, ".";

	SetTo:
		!! SetTo sale ante la frase AJUSTA DIAL A 23 o FIJA CONTROL EN
		!! ACTIVADO, o PON REGULADOR A 30
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "Eso no puede";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "Aquello no podía";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "Eso no podrá";
		}
		" regularse a ningún valor.";

	Show:
		!!	1:	Error, el usuario intenta mostrar un objeto que no tiene.
		!!	2:	Aviso, se ha enviado la acción Show al PNJ, pero este no ha
		!!		respondido. En este caso x1 apunta al PNJ y no al objeto que
		!!		le hemos mostrado.
		switch (n) {
			1:	"No ", (lm_tienes) player, " ", (the) x1, ".";
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print (The) x1, " no muestra", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print (The) x1, " no mostraba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print (The) x1, " no mostrará", (n) x1;
				}
				" ningún interés.";
		}

	Sing:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "Cantamos";
				else print "Canto";
				" bastante mal.";
			SECOND_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "Cantáis";
				else print "Cantas";
				" bastante mal.";
			THIRD_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "Cantan";
				else print "Canta";
				" bastante mal.";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "Cantábamos";
				else print "Cantaba";
				" fatal.";
			SECOND_PERSON_PAST:
				if (IsPluralNoun(player)) print "Cantábais";
				else print "Cantabas";
				" fatal.";
			THIRD_PERSON_PAST:
				if (IsPluralNoun(player)) print "Cantaban";
				else print "Cantaban";
				" fatal.";
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "Nunca llegaremos";
				else print "Nunca llegaré";
				" a cantar especialmente bien.";
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "Nunca llegaréis";
				else print "Nunca llegarás";
				" a cantar especialmente bien.";
			THIRD_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "Nunca llegarán";
				else print "Nunca llegará";
				" a cantar especialmente bien.";
			}

	Sleep:
		"No ", (lm_estas) player, " especialmente somnolient", (o) player, ".";

	Smell:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "olemos";
				else print "huelo";
			SECOND_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "oléis";
				else print "hueles";
			THIRD_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "huelen";
				else print "huele";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "olíamos";
				else print "olía";
			SECOND_PERSON_PAST:
				if (IsPluralNoun(player)) print "olíais";
				else print "olías";
			THIRD_PERSON_PAST:
				if (IsPluralNoun(player)) print "olían";
				else print "olía";
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "oleremos";
				else print "oleré";
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "oleréis";
				else print "olerás";
			THIRD_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "olerán";
				else print "olerá";
			}
			" nada extraño.";

	Sorry:
		!! Esta acción se genera si el usuario introduce "LO SIENTO",
		!! "PERDONA" o cosas similares.
		"[Oh, no es necesario que te disculpes].";

	Squeeze:
		!!	1:	Tratar de retorcer un ser animado.
		!!	2:	Cualquier otro objeto.
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						print "No ";
						if (IsPluralNoun(player)) "creemos que debamos.";
						else "creo que deba";
					SECOND_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) "creéis que debáis.";
						else "crees que debas.";
					THIRD_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) "creen que deban.";
						else "cree que deba.";
					FIRST_PERSON_PAST:
						print "No ";
						if (IsPluralNoun(player))
							print "se nos hubiese ocurrido";
						else print "se me hubiese ocurrido";
					SECOND_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player))
							print "se os hubiese ocurrido";
						else print "se te hubiese ocurrido";
					THIRD_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player))
							print "se les hubiese ocurrido";
						else print "se le hubiese ocurrido";
					FIRST_PERSON_FUTURE:
						print "No ";
						if (IsPluralNoun(player)) print "se nos ocurrirá";
						else print "se me ocurrirá";
					SECOND_PERSON_FUTURE:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "se os ocurrirá";
						else print "se te ocurrirá";
					THIRD_PERSON_FUTURE:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "se les ocurrirá";
						else print "se le ocurrirá";
				}
				" hacer algo así.";
			2:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "conseguimos";
						else print "consigo";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "conseguís";
						else print "consigues";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "consiguen";
						else print "consigue";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "conseguimos";
						else print "conseguí";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "conseguisteis";
						else print "conseguiste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "consiguieron";
						else print "consiguió";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "conseguiremos";
						else print "conseguiré";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "conseguiréis";
						else print "conseguirás";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "conseguirán";
						else print "conseguirá";
				}
				" nada haciendo eso.";
		}

	Strong:
		!! Respuesta si se usa como primera palabra algún taco.
		!! TODO - Cambiar por un mensaje más apropiado (¿recomendar AYUDA?)
		print "[Los verdaderos aventureros no ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "usan";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "usaban";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "usarán";
		}
		" ese vocabulario].";

	Swim:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "es";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "era";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "será";
		}
		" un sitio apropiado para ponerse a nadar.";

	Swing:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "parece", (n) x1;
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "parecía", (n) x1;
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "parecerá", (n) x1;
		}
		" el lugar más adecuado en el que columpiar", (lm_te) player, ".";

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
			3:	if (_grammatical_inflection == FIRST_PERSON_PAST
					&& ~~IsPluralNoun(player)) "Apagué ", (the) x1, ".";
				"Apag", (lm_as_) player, " ", (the) x1, ".";
		}

	SwitchOn:
		!! Generada al intentar ENCIENDE OBJETO si el objeto tiene el
		!! atributo "conmutable". Observar que si no lo tiene, la acción
		!! que se genera será sin embargo Quemar.
		!!	1:	Error, el objeto no es conmutable (este error no aparecerá
		!!		si el usuario pone ENCIENDE OBJETO, ya que en este caso la
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
						if (IsPluralNoun(player)) print "Encendemos";
						else print "Enciendo";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Encendéis";
						else print "Enciendes";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Encienden";
						else print "Enciendes";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Encendimos";
						else print "Encendí";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Encendisteis";
						else print "Encendiste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Encendieron";
						else print "Encendió";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Encenderemos";
						else print "Encenderé";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Encenderéis";
						else print "Encenderás";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Encenderán";
						else print "Encenderá";
				}
				" ", (the) x1, ".";
		}

	Take:
		!! Hay 13 casos diferentes. Se trata de 1 mensaje de éxito y 11
		!! mensajes de error y un aviso:
		!!	1:	Éxito.
		!!	2:	Error, el objeto cogido es el propio usuario.
		!!	3:	Error, el objeto cogido es un objeto animado.
		!!	4:	Error, el usuario está subido o metido en el objeto que intenta
		!!		coger.
		!!	5:	Error, el usuario ya tenía ese objeto en su inventario.
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
		!!	12:	Error, el usuario lleva demasiados objetos.
		!!	13: Mensaje de aviso, la librería ha decidido mover objetos del
		!!		inventario al "objeto saco" para hacer sitio y que el usuario
		!!		pueda coger el objeto. [El objeto saco es uno que puede
		!!		declarar el programador. Si el usuario lo coge y lo lleva
		!!		consigo, la librería lo usará automáticamente como mochila
		!!		para descargar al usuario cuando sea necesario].
		switch (n) {
			1:	if (dialecto_sudamericano) print "Tomad";
				else print "Cogid";
				"", (o) noun, ".";
			2:	"Siempre ", (lm_te) player, " ", (lm_tienes) player, " a ",
				(string) YOURSELF__TX, ".";
			3:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "No creemos";
						else print "No creo";
						" que ", (al_) x1, " le", (s) x1, " gustara.";
					SECOND_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "creéis";
						else print "crees";
						" que ", (al_) x1, " le", (s) x1, " gustara.";
					THIRD_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "creen";
						else print "cree";
						" que ", (al_) x1, " le", (s) x1, " gustara.";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "No creíamos";
						else print "No creía";
						" que ", (al_) x1, " le", (s) x1, " hubiese gustado.";
					SECOND_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "creíais";
						else print "creías";
						" que ", (al_) x1, " le", (s) x1, " hubiese gustado.";
					THIRD_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "creían";
						else print "creía";
						" que ", (al_) x1, " le", (s) x1, " hubiese gustado.";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "No lo creeremos";
						else print "No lo creeré";
						" buena idea.";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "No lo creeréis";
						else print "No lo creerás";
						" buena idea.";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "No lo creerán";
						else print "No lo creerá";
						" buena idea.";
				}
			4:	print (lm_ttienes) player, " que ";
				if (x1 has supporter) print "bajar", (lm_te) player;
				else print "salir";
				"", (del_) x1, " antes.";
			5:	"Ya ", (lm_tienes) player, " ", (the) x1, ".";
			6:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "Parece", (n) noun;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "Parecía", (n) noun;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "Parecerá", (n) noun;
				}
				" pertenecer ", (al_) x1, ".";
			7:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "Parece", (n) noun;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "Parecía", (n) noun;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "Parecerá", (n) noun;
				}
				" formar parte ", (del_) x1, ".";
			8:	print "No ";
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
					" disponible", (s) x1, ".";
			9:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print (The) x1, " no está", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print (The) x1, " no estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print (The) x1, " no estará", (n) x1;
				}
				" abiert", (o) x1, ".";
			10:	print "Difícilmente ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) "podríamos llevarnos eso.";
						"podría llevarme eso.";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) "podríais llevaros eso.";
						"podrías llevarte eso.";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) "podrían llevarse eso.";
						"podría llevarse eso.";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player))
							"hubiésemos podido llevarnos aquello.";
						"hubiese podido llevarme aquello.";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player))
							"hubiéseis podido llevaros aquello.";
						"hubieses podido llevarte aquello.";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player))
							"hubiesen podido llevarse aquello.";
						"hubiese podido llevarse aquello.";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) "podremos llevarnos eso.";
						"podré llevarme eso.";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) "podréis llevaros eso.";
						"podrás llevarte eso.";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) "podrán llevarse eso.";
						"podrá llevarse eso.";
				}
			11:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print (The) x1, " está", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print (The) x1, "estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print (The) x1, "estará", (n) x1;
				}
				" fij", (o) x1, " en el sitio.";
			12:	"Ya ", (lm_tienes) player, " las manos ocupadas con demasiadas
				cosas.";
			13:	print "(Primero ";
				if (_grammatical_inflection == FIRST_PERSON_PAST
					&& ~~IsPluralNoun(player)) print "coloqué";
				else print "coloc", (lm_as_) player;
				" ", (the) x1, " en ", (the) SACK_OBJECT, " para hacer sitio).";
		}

	Taste:
		"No sabore", (lm_as_) player, " nada inesperado.";

	Tell:
		!!	1:	El usuario habla consigo mismo.
		!!	2:	Hablar con cualquier otro ser animado.
		!! [Nota: Hablar con un objeto inanimado no está permitido por el
		!! parser, que da un error y no llega a generar la acción.]
		!! [Los errores de parser se tratan en la sección "Miscelánea" de
		!! esta rutina, al final.]
		switch (n) {
			1:	"Habl", (lm_as_) player, " sol", (o) player," durante un rato.";
			2:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "hemos provocado";
						else print "he provocado";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "habéis provocado";
						else print "has provocado";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "han provocado";
						else print "ha provocado";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "provocamos";
						else print "provoqué";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "provocasteis";
						else print "provocaste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "provocaron";
						else print "provocó";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "provocaremos";
						else print "provocaré";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "provocaréis";
						else print "provocarás";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "provocarán";
						else print "provocará";
				}
				" ninguna reacción.";
		}

	Think:
		"Si, eso intent", (lm_as) player, ".";

	ThrowAt:
		!!  1:	Lanzar cosas a objetos inanimados.
		!!	2:	Lanzar cosas a objetos animados.
		switch (n) {
			1:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "serviría";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "hubiese servido";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "servirá";
				}
				" de nada.";
			2:	"En el último momento ", (lm_te) player, " ech",
				(lm_as_) player, " atrás.";
		}

!!	Tie: see JumpOver

	Touch:
		!!	1:	Si se intenta tocar a un ser animado.
		!!	2:	Tocar un objeto normal del juego.
		!!	3:	Tocarse a si mismo.
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "No creemos";
						else print "No creo";
						" que ", (al_) x1, " le", (s) x1, " gustara.";
					SECOND_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "creéis";
						else print "crees";
						" que ", (al_) x1, " le", (s) x1, " gustara.";
					THIRD_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "creen";
						else print "cree";
						" que ", (al_) x1, " le", (s) x1, " gustara.";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "No creíamos";
						else print "No creía";
						" que ", (al_) x1, " le", (s) x1, " hubiese gustado.";
					SECOND_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "creíais";
						else print "creías";
						" que ", (al_) x1, " le", (s) x1, " hubiese gustado.";
					THIRD_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "creían";
						else print "creía";
						" que ", (al_) x1, " le", (s) x1, " hubiese gustado.";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "No lo creeremos";
						else print "No lo creeré";
						" buena idea.";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "No lo creeréis";
						else print "No lo creerás";
						" buena idea.";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "No lo creerán";
						else print "No lo creerá";
						" buena idea.";
				}
			2:	"No not", (lm_as_) player, " nada extraño al tacto.";
			3:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "No creemos";
						else print "No creo";
						" que eso sirva de nada.";
					SECOND_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "creéis";
						else print "crees";
						" que eso sirva de nada.";
					THIRD_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "creen";
						else print "cree";
						" que eso sirva de nada.";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "No creíamos";
						else print "No creía";
						" que algo así hubiese servido de nada.";
					SECOND_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "creíais";
						else print "creías";
						" que algo así hubiese servido de nada.";
					THIRD_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "creían";
						else print "creía";
						" que algo así hubiese servido de nada.";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"No será un buen momento para andar tocándo",
						(lm_te) player, ".";
				}
    	}

!!	Turn:	see Pull

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
			1:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "parece", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "parecía", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "parecerá", (n) x1;
				}
				" tener ningún tipo de cerrojo.";
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print (The) x1, " ya tenía", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print (The) x1, " ya tenía", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print (The) x1, " ya tendrá", (n) x1;
				}
				" abierto el cerrojo.";
			3:	if (second) {
					print "No ";
					switch (_grammatical_inflection) {
						FIRST_PERSON_PRESENT,
						SECOND_PERSON_PRESENT,
						THIRD_PERSON_PRESENT:
							print "parece", (n) x1;
						FIRST_PERSON_PAST,
						SECOND_PERSON_PAST,
						THIRD_PERSON_PAST:
							print "parecía", (n) x1;
						FIRST_PERSON_FUTURE,
						SECOND_PERSON_FUTURE,
						THIRD_PERSON_FUTURE:
							print "parecerá", (n) x1;
					}
					" encajar en la cerradura.";
				} else "Necesit", (lm_as) player, " algún tipo de llave.";
			4:	print "Quit", (lm_as_) player, " el cerrojo ", (al_) x1;
				if (second) " con ", (the) second, ".";
				".";
		}

	VagueGo:
		!! El usuario ha dicho IR sin especificar a dónde
		"[Tienes que especificar en qué dirección ir].";

	Verify:
		!!	1:	Éxito.
		!!	2:	Error en la verificación.
		switch (n) {
			1:	"[Fichero de juego verificado e intacto].";
			2:	"[El fichero de juego no parece intacto,
				puede estar corrompido (a menos que estés jugando con un
				intérprete muy primitivo que no sea capaz de realizar la
				comprobación)].";
		}

	Wait:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "Pasa";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "Pasaba";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "Pasará";
		}
		" el tiempo...";

	Wake:
		print "La cruda realidad es que ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "esto no es";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "aquello no era";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "eso no será";
		}
		" un sueño.";

	WakeOther:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				"No parece necesario hacer eso.";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				"No parecía necesario hacer aquello.";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				"No parecerá necesario hacer eso.";
		}

	Wave:
		!!	1:	Si se intenta agitar un objeto que no está en el inventario.
		!!	2:	Si se agita un objeto que sí está en el inventario.
		switch (n) {
			1:	"No l", (o) x1, " ", (lm_tienes) player, ".";
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Nos sentimos";
						else print "Me siento";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Os sentís";
						else print "Te sientes";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Se sienten";
						else print "Se siente";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Nos sentíamos";
						else print "Me sentía";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Os sentíais";
						else print "Te sentías";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Se sentían";
						else print "Se sentía";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Nos sentiremos";
						else print "Me sentiré";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Os sentiréis";
						else print "Te sentirás";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Se sentirán";
						else print "Se sentirá";
				}
				" ridícul", (o) player, " agitando ", (the) x1, ".";
		}

	WaveHands:
		!! La acción WaveHands se genera ante las frases "gesticula", "agita la
		!! mano", "sacude la mano", "saluda con la mano", etc.
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "Nos encontramos";
				else print "Me encuentro";
			SECOND_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "Os encontráis";
				else print "Te encuentras";
			THIRD_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "Se encuentran";
				else print "Se encuentra";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "Nos encontrábamos";
				else print "Me encontraba";
			SECOND_PERSON_PAST:
				if (IsPluralNoun(player)) print "Os encontrábais";
				else print "Te encontrabas";
			THIRD_PERSON_PAST:
				if (IsPluralNoun(player)) print "Se encontraban";
				else print "Se encontraba";
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "Nos encontraremos";
				else print "Me encontraré";
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "Os encontraréis";
				else print "Te encontrarás";
			THIRD_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "Se encontrarán";
				else print "Se encontrará";
		}
		" ridícul", (o) player, " gesticulando así.";

	Wear:
		!! 1: Error, el objeto no tiene el atributo "clothing".
		!! 2: Error, el usuario no tiene el objeto.
		!! 3: Error, el objeto ya tiene el atributo "worn".
		!! 4: Éxito.
		switch (n) {
			1:	print "No ", (lm_puedes) player, " poner", (lm_te) player, " ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "eso";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "aquello";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "eso";
				}
				".";
			2:	"No ", (lo) x1, " ", (lm_tienes) player, ".";
			3:	"Ya ", (lo) x1, " llev", (lm_as) player, " puest", (o) x1, ".";
			4:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Nos ponemos";
						else print "Me pongo";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Os ponéis";
						else print "Te pones";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Se ponen";
						else print "Se pone";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Nos pusimos";
						else print "Me puse";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Os pusisteis";
						else print "Te pusiste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Se pusieron";
						else print "Se puso";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Nos pondremos";
						else print "Me pondré";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Os pondréis";
						else print "Te pondrás";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Se pondrán";
						else print "Se pondrá";
				}
				" ", (the) x1, ".";
		}

	Yes:
		"[La instrucción ~SÍ~ no tiene sentido en esta situación.]";

];

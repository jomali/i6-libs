

!!==============================================================================
!!
!!	GRAMÁTICA ESPAÑOLA EXTENDIDA
!!
!!==============================================================================
!!
!!	File:			SpanishEG.inf
!!	Author(s):		Emily Short <emshort@mindspring.com>
!!					J. Francisco Martín <jfm.lisaso@gmail.com>
!!					Mapache
!!	Language:		ES (Español)
!!	System:			Inform-INFSP 6
!!	Platform:		Máquina-Z / GLULX
!!	Version:		5.3
!!	Released:		2018/07/02
!!
!!------------------------------------------------------------------------------
!!
!!	NOTAS
!!
!!	Basada en "ExpertGrammar.h", de Emily Short <emshort@mindspring.com>
!!	y en su traducción al castellano "GramaticaExperta.h", de Mapache.
!!
!!
!!	DERECHOS
!!
!!	Esta librería puede tratarse como de dominio público. Puede incluirse
!!	con o sin citar al autor original. Puede ser modificada a discreción
!!	por el usuario. Se puede distribuir libremente. Pueden extraerse
!!	fragmentos de la librería.
!!
!!
!!	INSTALACIÓN
!!
!!	Incluye "SpanishEG.h" después de SpanishG en tu archivo de juego.
!!
!!	Se puede definir la variable '_grammatical_inflection' en el archivo de
!!	juego, que puede tomar los valores: 1 (PRESENTE 1ª PERSONA), 2 (PRESENTE 2ª
!!	PERSONA), 3 (PRESENTE 3ª PERSONA), 4 (PASADO 1ª PERSONA), 5 (PASADO 2ª
!!	PERSONA) o 6 (PASADO 3ª PERSONA) para modificar la conjugación gramatical
!!	de los mensajes de la librería. Si no se define ninguna
!!	'_grammatical_inflection', la librería interpreta que se usa el valor 2 y
!!	los mensajes de "SpanishEG.h" se imprimen en presente y segunda persona.
!!
!!
!!	NUEVAS ACCIONES
!!
!!	<>	Dance
!!	<>	GoDown
!!	<>	GoUp
!!	<>	KnockOn
!!	<>	Masturbate
!!	<>	Read
!!	<>	Shout
!!	<>	Sit
!!	<>	SleepWith
!!	<>	StandUp
!!	<>	Untie
!!	<>	Use
!!	<>	Write
!!	<>	Xyzzy
!!
!!------------------------------------------------------------------------------

!!------------------------------------------------------------------------------
!! Valores de la extensión por defecto
!!------------------------------------------------------------------------------

Default	FIRST_PERSON_PRESENT 1;
Default	SECOND_PERSON_PRESENT 2;
Default THIRD_PERSON_PRESENT 3;
Default FIRST_PERSON_PAST 4;
Default SECOND_PERSON_PAST 5;
Default THIRD_PERSON_PAST 6;
Default FIRST_PERSON_FUTURE 7;
Default SECOND_PERSON_FUTURE 8;
Default THIRD_PERSON_FUTURE 9;
Default	_grammatical_inflection 2;

!!------------------------------------------------------------------------------
!! Nuevos sinónimos
!!------------------------------------------------------------------------------

Verb	'machaca'						= 'ataca';
Verb	'silba' 'tararea' 'tatarea'		= 'canta';
Verb	'roba' 'agarra'					= 'coge';
Verb	'talla' 'esculpe'				= 'corta';
Verb	'emplaza' 'deposita' 'abandona'	= 'deja';
Verb	'berrea' 'aulla'				= 'grita';
Verb	'marcha'						= 'ir';
Verb	'incinera' 'tuesta'				= 'quema';
VerboIrregular "tostar" with imperativo 'tuesta';
Verb	'acaricia'						= 'toca';

!!------------------------------------------------------------------------------
!! Extensiones a las acciones de la librería por defecto
!!------------------------------------------------------------------------------

Extend	'sopla'
	* 'sobre' / 'dentro' / 'a' noun	-> Blow
	* 'a' 'traves' 'de' noun		-> Blow
;

Extend	'prende' last
	* 'fuego' noun					-> Burn
	* noun 'fuego'					-> Burn
	* 'fuego' 'a//' noun			-> Burn
	* 'a//' noun 'fuego'			-> Burn
	* 'fuego' noun 'con' held		-> Burn
	* noun 'fuego' 'con' held		-> Burn
	* 'fuego' 'a//' noun 'con' held	-> Burn
	* 'a//' noun 'fuego' 'con' held	-> Burn
;

Verb	'muerde'
	* noun							-> Eat
	* edible						-> Eat
!	* animate						-> Attack
!	* 'a' animate					-> Attack
;
VerboIrregular "morder" with imperativo 'muerde';

Extend	'salta'
	* 'en' noun						-> JumpOver
;

Extend	'mira'
	* 'alrededor'					-> Look
	* 'a' 'mi'/'tu' 'alrededor'		-> Look
	* 'a' 'nuestro' 'alrededor'		-> Look
	* 'a' 'vuestro' 'alrededor'		-> Look
	* 'a' 'su' 'alrededor'			-> Look
;

Extend	'busca'
	* 'bajo' noun					-> LookUnder
	* 'debajo' 'de' noun			-> LookUnder
	* 'entre' noun					-> Search
;

Extend	'mira'
	* 'entre' noun					-> Search
;

Extend	'duerme'
	* '-te'/'-me'					-> Sleep
	* noun							-> Sleep
	* '-te'/'-me' noun				-> Sleep
	* 'en' noun						-> Sleep
	* '-te'/'-me' 'en' noun			-> Sleep
;

Verb	meta 'creditos' 'credits' 'autor' 'author' 'informacion' 'info'
	*								-> Version
;

!!------------------------------------------------------------------------------
!! ##Dance
!!------------------------------------------------------------------------------

Verb	'baila'
	*								-> Dance
;

[ DanceSub gna;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 6:
					"Nunca he sido un gran bailarín.";
				1, 7:
					"Nunca he sido una gran bailarina.";
				3, 9:
					"Nunca hemos sido unos grandes bailarines.";
				4, 10:
					"Nunca hemos sido unas grandes bailarinas.";
			}
		SECOND_PERSON_PRESENT:
			switch (gna) {
				0, 6:
					"Nunca has sido un gran bailarín.";
				1, 7:
					"Nunca has sido una gran bailarina.";
				3, 9:
					"Nunca habéis sido unos grandes bailarines.";
				4, 10:
					"Nunca habéis sido unas grandes bailarinas.";
			}
		THIRD_PERSON_PRESENT:
			switch (gna) {
				0, 6:
					"Nunca ha sido un gran bailarín.";
				1, 7:
					"Nunca ha sido una gran bailarina.";
				3, 9:
					"Nunca han sido unos grandes bailarines.";
				4, 10:
					"Nunca han sido unas grandes bailarinas.";
			}
		FIRST_PERSON_PAST:
			switch (gna) {
				0, 6:
					"Nunca fui un gran bailarín.";
				1, 7:
					"Nunca fui una gran bailarina.";
				3, 9:
					"Nunca fuimos unos grandes bailarines.";
				4, 10:
					"Nunca fuimos unas grandes bailarinas.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 6:
					"Nunca fuiste un gran bailarín.";
				1, 7:
					"Nunca fuiste una gran bailarina.";
				3, 9:
					"Nunca fuisteis unos grandes bailarines.";
				4, 10:
					"Nunca fuisteis unas grandes bailarinas.";
			}
		THIRD_PERSON_PAST:
			switch (gna) {
				0, 6:
					"Nunca fue un gran bailarín.";
				1, 7:
					"Nunca fue una gran bailarina.";
				3, 9:
					"Nunca fueron unos grandes bailarines.";
				4, 10:
					"Nunca fueron unas grandes bailarinas.";
			}
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 6:
					"No llegaré a ser un gran bailarín.";
				1, 7:
					"No llegaré a ser una gran bailarina.";
				3, 9:
					"No llegaremos a ser unos grandes bailarines.";
				4, 10:
					"No llegaremos a ser unas grandes bailarinas.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 6:
					"No llegarás a ser un gran bailarín.";
				1, 7:
					"No llegarás a ser una gran bailarina.";
				3, 9:
					"No llegaréis a ser unos grandes bailarines.";
				4, 10:
					"No llegaréis a ser unas grandes bailarinas.";
			}
		THIRD_PERSON_FUTURE:
			switch (gna) {
				0, 6:
					"No llegará a ser un gran bailarín.";
				1, 7:
					"No llegará a ser una gran bailarina.";
				3, 9:
					"No llegarán a ser unos grandes bailarines.";
				4, 10:
					"No llegarán a ser unas grandes bailarinas.";
			}
	}
];

!!------------------------------------------------------------------------------
!! ##GoDown, ##GoUp
!!------------------------------------------------------------------------------

Verb	'desciende'
	*								-> GoDown
	* noun							-> Enter
	* 'por' noun					-> Enter
; VerboIrregular "descender" with imperativo 'desciende';

Verb	'asciende'
	*								-> GoUp
	* noun							-> Enter
	* 'por' noun					-> Enter
; VerboIrregular "ascender" with imperativo 'asciende';

[ GoDownSub;
	<<Go d_obj>>;
];

[ GoUpSub;
	<<Go u_obj>>;
];

!!------------------------------------------------------------------------------
!! ##KnockOn
!!------------------------------------------------------------------------------

Extend only 'golpea' first
	* door							-> KnockOn
	* 'a//' door					-> KnockOn
;

Verb	'llama'
	* door							-> KnockOn
	* 'a//' door					-> KnockOn
	* animate						-> Tell
	* 'a//' animate					-> Tell
;

[ KnockOnSub;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT,
		SECOND_PERSON_PRESENT,
		THIRD_PERSON_PRESENT:
			if (noun has door) "No contesta nadie.";
			"No ocurre nada.";
		FIRST_PERSON_PAST,
		SECOND_PERSON_PAST,
		THIRD_PERSON_PAST:
			if (noun has door) "No contestó nadie.";
			"No ocurrió nada.";
		FIRST_PERSON_FUTURE,
		SECOND_PERSON_FUTURE,
		THIRD_PERSON_FUTURE:
			if (noun has door) "No contestará nadie.";
			"No ocurrirá nada.";
	}
];

!!------------------------------------------------------------------------------
!! ##Masturbate
!!------------------------------------------------------------------------------

Verb	'masturba'
	* '-me'/'-te'					-> Masturbate
;

[ MasturbateSub gna;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Ahora no tengo ganas.";
				3, 4, 9, 10:
					"Ahora no tenemos ganas.";
			}
		SECOND_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Ahora no tienes ganas en realidad.";
				3, 4, 9, 10:
					"Ahora no tenéis ganas en realidad.";
			}
		THIRD_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Ahora no tiene ganas.";
				3, 4, 9, 10:
					"Ahora no tienen ganas.";
			}
		FIRST_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No tenía ganas.";
				3, 4, 9, 10:
					"No teníamos ganas.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No tenías ganas.";
				3, 4, 9, 10:
					"No teníais ganas.";
			}
		THIRD_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No tenía ganas.";
				3, 4, 9, 10:
					"No tenían ganas.";
			}
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"No tendré ganas.";
				3, 4, 9, 10:
					"No tendremos ganas.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"No tendrás ganas.";
				3, 4, 9, 10:
					"No tendréis ganas.";
			}
		THIRD_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"No tendrá ganas.";
				3, 4, 9, 10:
					"No tendrán ganas.";
			}
	}
];

!!------------------------------------------------------------------------------
!! ##Read
!!------------------------------------------------------------------------------

Extend	'lee' first
	* noun							-> Read
;

[ ReadSub;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT,
		SECOND_PERSON_PRESENT,
		THIRD_PERSON_PRESENT:
			"No hay nada que leer en ", (the) noun, ".";
		FIRST_PERSON_PAST,
		SECOND_PERSON_PAST,
		THIRD_PERSON_PAST:
			"No había nada que leer en ", (the) noun, ".";
		FIRST_PERSON_FUTURE,
		SECOND_PERSON_FUTURE,
		THIRD_PERSON_FUTURE:
			"No habrá nada que leer en ", (the) noun, ".";
	}
];

!!------------------------------------------------------------------------------
!! ##Shout
!!------------------------------------------------------------------------------

Verb	'chilla'
	*								-> Shout
;

Extend	'grita' last
	*								-> Shout
;

[ ShoutSub gna;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Grito con fuerza.";
				3, 4, 9, 10:
					"Gritamos con fuerza.";
			}
		SECOND_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Gritas con fuerza.";
				3, 4, 9, 10:
					"Gritais con fuerza.";
			}
		THIRD_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Grita con fuerza.";
				3, 4, 9, 10:
					"Gritan con fuerza.";
			}
		FIRST_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"Grité con fuerza.";
				3, 4, 9, 10:
					"Gritamos con fuerza.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"Gritaste con fuerza.";
				3, 4, 9, 10:
					"Gritasteis con fuerza.";
			}
		THIRD_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"Gritó con fuerza.";
				3, 4, 9, 10:
					"Gritaron con fuerza.";
			}
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Gritaré con fuerza.";
				3, 4, 9, 10:
					"Gritaremos con fuerza.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Gritarás con fuerza.";
				3, 4, 9, 10:
					"Gritaréis con fuerza.";
			}
		THIRD_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Gritará con fuerza.";
				3, 4, 9, 10:
					"Gritarán con fuerza.";
			}
	}
];

!!------------------------------------------------------------------------------
!! ##Sit
!!------------------------------------------------------------------------------

Extend    'sienta' replace
    * 								-> Sit
	* '-te' / '-me'					-> Sit
	* noun							-> Sit
	* '-te' / '-me' noun			-> Sit
	* 'en' noun						-> Sit
	* '-te' / '-me'	'en' noun		-> Sit
; VerboIrregular "sentar" with imperativo 'sientate';

[ SitSub gna;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 6:
					"Ya estoy bastante cómodo de pie.";
				1, 7:
					"Ya estoy bastante cómoda de pie.";
				3, 9:
					"Ya estamos bastante cómodos de pie.";
				4, 10:
					"Ya estamos bastante cómodas de pie.";
			}
		SECOND_PERSON_PRESENT:
			switch (gna) {
				0, 6:
					"Ya estás bastante cómodo de pie.";
				1, 7:
					"Ya estás bastante cómoda de pie.";
				3, 9:
					"Ya estáis bastante cómodos de pie.";
				4, 10:
					"Ya estáis bastante cómodas de pie.";
			}
		THIRD_PERSON_PRESENT:
			switch (gna) {
				0, 6:
					"Ya está bastante cómodo de pie.";
				1, 7:
					"Ya está bastante cómoda de pie.";
				3, 9:
					"Ya están bastante cómodos de pie.";
				4, 10:
					"Ya están bastante cómodas de pie.";
			}
		FIRST_PERSON_PAST:
			switch (gna) {
				0, 6:
					"Ya estaba bastante cómodo de pie.";
				1, 7:
					"Ya estaba bastante cómoda de pie.";
				3, 9:
					"Ya estábamos bastante cómodos de pie.";
				4, 10:
					"Ya estábamos bastante cómodas de pie.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 6:
					"Ya estabas bastante cómodo de pie.";
				1, 7:
					"Ya estabas bastante cómoda de pie.";
				3, 9:
					"Ya estabais bastante cómodos de pie.";
				4, 10:
					"Ya estabais bastante cómodas de pie.";
			}
		THIRD_PERSON_PAST:
			switch (gna) {
				0, 6:
					"Ya estaba bastante cómodo de pie.";
				1, 7:
					"Ya estaba bastante cómoda de pie.";
				3, 9:
					"Ya estaban bastante cómodos de pie.";
				4, 10:
					"Ya estaban bastante cómodas de pie.";
			}
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 6:
					"Ya estaré bastante cómodo de pie.";
				1, 7:
					"Ya estaré bastante cómoda de pie.";
				3, 9:
					"Ya estaremos bastante cómodos de pie.";
				4, 10:
					"Ya estaremos bastante cómodas de pie.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 6:
					"Ya estarás bastante cómodo de pie.";
				1, 7:
					"Ya estarás bastante cómoda de pie.";
				3, 9:
					"Ya estaréis bastante cómodos de pie.";
				4, 10:
					"Ya estaréis bastante cómodas de pie.";
			}
		THIRD_PERSON_FUTURE:
			switch (gna) {
				0, 6:
					"Ya estará bastante cómodo de pie.";
				1, 7:
					"Ya estará bastante cómoda de pie.";
				3, 9:
					"Ya estarán bastante cómodos de pie.";
				4, 10:
					"Ya estarán bastante cómodas de pie.";
			}
	}
];

!!------------------------------------------------------------------------------
!! ##SleepWith
!!------------------------------------------------------------------------------

Verb	'folla' 'copula'
	* animate						-> SleepWith
	* '-te' / '-me' animate			-> SleepWith
	* 'a//' / 'con' animate			-> SleepWith
	* '-te' / '-me' 'a' animate		-> SleepWith
;

Extend	only 'jode' first
	* animate						-> SleepWith
	* 'a//' / 'con' animate			-> SleepWith
;

Verb	'ten'
	* 'sexo' 'con' animate			-> SleepWith
	* 'coito' 'con' animate			-> SleepWith
; VerboIrregular "tener" with imperativo 'ten';

Verb	'haz'
	* 'el' 'amor' 'con' animate		-> SleepWith
; VerboIrregular "hacer el amor" with imperativo 'haz';


[ SleepWithSub gna;
	if (noun == player) <<Masturbate>>;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Ni se me pasa por la cabeza algo así ahora.";
				3, 4, 9, 10:
					"Ni se nos pasa por la cabeza algo así ahora.";
			}
		SECOND_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"En realidad no se te pasaría por la cabeza algo así
					ahora.";
				3, 4, 9, 10:
					"En realidad no se os pasaría por la cabeza algo así
					ahora.";
			}
		THIRD_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"En realidad no se le pasaría por la cabeza algo así
					ahora.";
				3, 4, 9, 10:
					"En realidad no se les pasaría por la cabeza algo así
					ahora.";
			}
		FIRST_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No se me hubiese pasado por la cabeza algo así en aquel
					momento.";
				3, 4, 9, 10:
					"No se nos hubiese pasado por la cabeza algo así en aquel
					momento.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No se te hubiese pasado por la cabeza algo así en aquel
					momento.";
				3, 4, 9, 10:
					"No se os hubiese pasado por la cabeza algo así en aquel
					momento.";
			}
		THIRD_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No se le hubiese pasado por la cabeza algo así en aquel
					momento.";
				3, 4, 9, 10:
					"No se les hubiese pasado por la cabeza algo así en aquel
					momento.";
			}
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Ni se me pasará por la cabeza algo así en ese momento.";
				3, 4, 9, 10:
					"Ni se nos pasará por la cabeza algo así en ese momento.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Ni se te pasará por la cabeza algo así en ese momento.";
				3, 4, 9, 10:
					"Ni se os pasará por la cabeza algo así en ese momento.";
			}
		THIRD_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Ni se le pasará por la cabeza algo así en ese momento.";
				3, 4, 9, 10:
					"Ni se les pasará por la cabeza algo así en ese momento.";
			}
	}
];

!!------------------------------------------------------------------------------
!! ##StandUp
!!------------------------------------------------------------------------------

Extend	only 'levantate' 'levantarse' 'levantarte' first
	*								-> StandUp
	* 'de' noun						-> StandUp
;

Verb    'levanta' 'incorpora'
    * 								-> StandUp
	* '-te'/'-me'					-> StandUp
    * 'de' noun 					-> StandUp
	* '-te'/'-me' 'de//' noun		-> StandUp
;

[ StandUpSub gna;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"No estoy en ningún sitio del que deba levantarme.";
				3, 4, 9, 10:
					"No estamos en ningún sitio del que debamos levantarnos.";
			}
		SECOND_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"No estás en ningún sitio del que debas levantarte.";
				3, 4, 9, 10:
					"No estáis en ningún sitio del que debais levantaros.";
			}
		THIRD_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"No está en ningún sitio del que deba levantarse.";
				3, 4, 9, 10:
					"No están en ningún sitio del que deban levantarse.";
			}
		FIRST_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No estaba en ningún sitio del que debiese levantarme.";
				3, 4, 9, 10:
					"No estábamos en ningún sitio del que debiésemos
					levantarnos.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No estabas en ningún sitio del que debieses levantarte.";
				3, 4, 9, 10:
					"No estabais en ningún sitio del que debieseis levantaros.";
			}
		THIRD_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No estaba en ningún sitio del que debiese levantarse.";
				3, 4, 9, 10:
					"No estaban en ningún sitio del que debiesen levantarse.";
			}
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"No estaré en ningún sitio del que debiese
					levantarme.";
				3, 4, 9, 10:
					"No estaremos en ningún sitio del que debiésemos
					levantarnos.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"No estarás en ningún sitio del que debieses
					levantarte.";
				3, 4, 9, 10:
					"No estaréis en ningún sitio del que debiésesis
					levantaros.";
			}
		THIRD_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"No estará en ningún sitio del que debiese
					levantarse.";
				3, 4, 9, 10:
					"No estarán en ningún sitio del que debiesen
					levantarse.";
			}
	}
];

!!------------------------------------------------------------------------------
!! ##Untie
!!------------------------------------------------------------------------------

Verb	'desata' 'libera' 'desune' 'desenchufa'
	* noun							-> Untie
	* 'a//' creature				-> Untie
	* 'a//' creature 'de' noun		-> Untie
	* noun 'de' noun				-> Untie
;

Extend	only 'desconecta' last
	* noun 'de' noun				-> Untie
;

[ UntieSub gna;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 6:
					"No estoy seguro de cómo hacerlo.";
				1, 7:
					"No estoy segura de cómo hacerlo.";
				3, 9:
					"No estamos seguros de cómo hacerlo.";
				4, 10:
					"No estamos seguras de cómo hacerlo.";
			}
		SECOND_PERSON_PRESENT:
			switch (gna) {
				0, 6:
					"No estás seguro de cómo hacerlo.";
				1, 7:
					"No estás segura de cómo hacerlo.";
				3, 9:
					"No estáis seguros de cómo hacerlo.";
				4, 10:
					"No estáis seguras de cómo hacerlo.";
			}
		THIRD_PERSON_PRESENT:
			switch (gna) {
				0, 6:
					"No parece estar seguro de cómo hacerlo.";
				1, 7:
					"No parece estar segura de cómo hacerlo.";
				3, 9:
					"No parecen estar seguros de cómo hacerlo.";
				4, 10:
					"No parecen estar seguras de cómo hacerlo.";
			}
		FIRST_PERSON_PAST:
			switch (gna) {
				0, 6:
					"No estaba seguro de cómo hacer eso.";
				1, 7:
					"No estaba segura de cómo hacer eso.";
				3, 9:
					"No estábamos seguros de cómo hacer eso.";
				4, 10:
					"No estábamos seguras de cómo hacer eso.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 6:
					"No estabas seguro de cómo hacer eso.";
				1, 7:
					"No estabas segura de cómo hacer eso.";
				3, 9:
					"No estabais seguros de cómo hacer eso.";
				4, 10:
					"No estabais seguras de cómo hacer eso.";
			}
		THIRD_PERSON_PAST:
			switch (gna) {
				0, 6:
					"No estaba seguro de cómo hacer eso.";
				1, 7:
					"No estaba segura de cómo hacer eso.";
				3, 9:
					"No estaban seguros de cómo hacer eso.";
				4, 10:
					"No estaban seguras de cómo hacer eso.";
			}
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 6:
					"No estaré seguro de cómo hacer eso.";
				1, 7:
					"No estaré segura de cómo hacer eso.";
				3, 9:
					"No estaremos seguros de cómo hacer eso.";
				4, 10:
					"No estaremos seguras de cómo hacer eso.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 6:
					"No estarás seguro de cómo hacer eso.";
				1, 7:
					"No estarás segura de cómo hacer eso.";
				3, 9:
					"No estaréis seguros de cómo hacer eso.";
				4, 10:
					"No estaréis seguras de cómo hacer eso.";
			}
		THIRD_PERSON_FUTURE:
			switch (gna) {
				0, 6:
					"No estará seguro de cómo hacer eso.";
				1, 7:
					"No estará segura de cómo hacer eso.";
				3, 9:
					"No estarán seguros de cómo hacer eso.";
				4, 10:
					"No estarán seguras de cómo hacer eso.";
			}
	}
];

!!------------------------------------------------------------------------------
!! ##Use
!!------------------------------------------------------------------------------

Verb	'emplea' 'usa' 'utiliza'
	* noun							-> Use
	* noun 'con'/'en' noun			-> Use
;

Verb	'actua' 'interactua'
	* noun							-> Use
	* 'con' noun					-> Use
	* noun 'con'/'en' noun			-> Use
	* 'con' noun 'en' noun			-> Use
	* 'en' noun 'con' noun			-> Use reverse
;

[ UseSub gna;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Pienso en algún uso para ", (the) noun ,", pero no
					termino de decidirme por una acción concreta.";
				3, 4, 9, 10:
					"Pensamos en algún uso para ", (the) noun ,", pero no
					terminamos de decidirnos por una acción concreta.";
			}
		SECOND_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Piensas en algún uso para ", (the) noun ,", pero no
					terminas de decidirte por una acción concreta.";
				3, 4, 9, 10:
					"Pensáis en algún uso para ", (the) noun ,", pero no
					termináis de decidiros por una acción concreta.";
			}
		THIRD_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Piensa en algún uso para ", (the) noun ,", pero no
					termina de decidirse por una acción concreta.";
				3, 4, 9, 10:
					"Piensan en algún uso para ", (the) noun ,", pero no
					terminan de decidirse por una acción concreta.";
			}
		FIRST_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"Pensé en algún uso para ", (the) noun ,", pero no
					terminé de decidirme por una acción concreta.";
				3, 4, 9, 10:
					"Pensamos en algún uso para ", (the) noun ,", pero no
					terminamos de decidirnos por una acción concreta.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"Pensaste en algún uso para ", (the) noun ,", pero no
					terminaste de decidirte por una acción concreta.";
				3, 4, 9, 10:
					"Pensasteis en algún uso para ", (the) noun ,", pero no
					terminasteis de decidiros por una acción concreta.";
			}
		THIRD_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"Pensó en algún uso para ", (the) noun ,", pero no
					terminó de decidirse por una acción concreta.";
				3, 4, 9, 10:
					"Pensaron en algún uso para ", (the) noun ,", pero no
					terminaron de decidirse por una acción concreta.";
			}
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Pensaré en algún uso para ", (the) noun ,", pero no
					terminaré de decidirme por una acción concreta.";
				3, 4, 9, 10:
					"Pensaremos en algún uso para ", (the) noun ,", pero no
					terminaremos de decidirnos por una acción concreta.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Pensarás en algún uso para ", (the) noun ,", pero no
					terminarás de decidirte por una acción concreta.";
				3, 4, 9, 10:
					"Pensaréis en algún uso para ", (the) noun ,", pero no
					terminaréis de decidiros por una acción concreta.";
			}
		THIRD_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Pensará en algún uso para ", (the) noun ,", pero no
					terminará de decidirse por una acción concreta.";
				3, 4, 9, 10:
					"Pensarán en algún uso para ", (the) noun ,", pero no
					terminarán de decidirse por una acción concreta.";
			}
	}
];

!!------------------------------------------------------------------------------
!! ##Write
!!------------------------------------------------------------------------------

Verb	'escribe'
	* noun							-> Write
	* 'en'/'el' noun				-> Write
	* noun 'con' noun				-> Write
	* 'en'/'el' noun 'con' noun		-> Write
; VerboIrregular "escribir" with imperativo 'escribe';

[ WriteSub gna;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Ahora no tengo nada que escribir.";
				3, 4, 9, 10:
					"Ahora no tenemos nada que escribir.";
			}
		SECOND_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Ahora no tienes nada que escribir.";
				3, 4, 9, 10:
					"Ahora no teneis nada que escribir.";
			}
		THIRD_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Ahora no tiene nada que escribir.";
				3, 4, 9, 10:
					"Ahora no tienen nada que escribir.";
			}
		FIRST_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No tenía nada que escribir en aquel momento.";
				3, 4, 9, 10:
					"No teníamos nada que escribir en aquel momento.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No tenías nada que escribir en aquel momento.";
				3, 4, 9, 10:
					"No teníais nada que escribir en aquel momento.";
			}
		THIRD_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No tenía nada que escribir en aquel momento.";
				3, 4, 9, 10:
					"No tenían nada que escribir en aquel momento.";
			}
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"No tendré nada que escribir en ese momento.";
				3, 4, 9, 10:
					"No tendremos nada que escribir en ese momento.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"No tendrás nada que escribir en ese momento.";
				3, 4, 9, 10:
					"No tendréis nada que escribir en ese momento.";
			}
		THIRD_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"No tendrá nada que escribir en ese momento.";
				3, 4, 9, 10:
					"No tendrán nada que escribir en ese momento.";
			}
	}
];

!!------------------------------------------------------------------------------
!! ##Xyzzy
!!------------------------------------------------------------------------------

Verb	'xyzzy' 'plugh' 'plover' 'abracadabra'
	*								-> Xyzzy
; VerboIrregular "xyzzy" with imperativo 'xyzzy';

[ XyzzySub gna;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Un rumor silencioso responde a mis palabras.";
				3, 4, 9, 10:
					"Un rumor silencioso responde a nuestras palabras.";
			}
		SECOND_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Un rumor silencioso responde a tus palabras.";
				3, 4, 9, 10:
					"Un rumor silencioso responde a vuestras palabras.";
			}
		THIRD_PERSON_PRESENT:
			"Un rumor silencioso responde a sus palabras.";
		FIRST_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"Un rumor silencioso respondió a mis palabras.";
				3, 4, 9, 10:
					"Un rumor silencioso respondió a nuestras palabras.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"Un rumor silencioso respondió a tus palabras.";
				3, 4, 9, 10:
					"Un rumor silencioso respondió a vuestras palabras.";
			}
		THIRD_PERSON_PAST:
			"Un rumor silencioso respondió a sus palabras.";
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Un rumor silencioso responderá a mis palabras.";
				3, 4, 9, 10:
					"Un rumor silencioso responderá a nuestras palabras.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Un rumor silencioso responderá a tus palabras.";
				3, 4, 9, 10:
					"Un rumor silencioso responderá a vuestras palabras.";
			}
		THIRD_PERSON_FUTURE:
			"Un rumor silencioso responderá a sus palabras.";
	}
];

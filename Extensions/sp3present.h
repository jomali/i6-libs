

!!==============================================================================
!!
!!	MENSAJES DE LA LIBRERÍA EN ESPAÑOL
!!	Narrador en tercera persona, tiempo presente
!!
!!==============================================================================
!!
!!	Archivo:		sp3present.inf
!!	Autor(es):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!	Idioma:			ES (Español)
!!	Sistema:		Inform-INFSP 6
!!	Plataforma:		Máquina-Z/Glulx
!!	Versión:		1.0
!!	Fecha:			2018/09/21
!!
!!------------------------------------------------------------------------------
!!
!!	HISTORIAL DE VERSIONES
!!
!!	1.0: 2018/09/21	Versión inicial
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

[ ThirdPersonPresent_ES n x1;

	Answer, Ask, AskFor:
		"No hay respuesta.";

	Attack:
		if (x1 == player) {
			print "No ";
			if (IsPluralNoun(player)) print "se autolesionarían";
			else print "se autolesionaría";
			" a propósito.";
		}
		print "No serviría de nada tratar de ";
		LanguageVerb(verb_word);
		" ", (the) x1, ".";

	Blow:
		if (IsPluralNoun(player)) print "Su";
		else print "Su";
		" soplido no produce ningún efecto.";

	Burn:
		print "Esa es una idea peligrosa con la que no ";
		if (IsPluralNoun(player)) print "lograrían";
		else print "lograría";
		" nada en cualquier caso.";

	Buy:
		if (x1 == 0) "No hay nada en venta.";
		else {
			print "No ";
			if (IsPluralNoun(player)) print "pueden";
			else print "puede";
			" comprar ", (the) x1, ".";
		}

	Climb:
		print "No es algo a lo que ";
		if (IsPluralNoun(player)) print "puedan";
		else print "pueda";
		print " ";
		LanguageVerb(verb_word);
		".";

	Close:
		switch (n) {
			1:
				"No es algo que se pueda cerrar.";
			2:
				"Ya está", (n) x1, " cerrad", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Cierran";
				else print "Cierra";
				" ", (the) x1, ".";
		}

	Consult:
		print "No ";
		if (IsPluralNoun(player)) print "descubren";
		else print "descubre";
		" nada interesante en ", (the) x1, " sobre ese tema.";

	Cut:
		print "Cortándo", (lo) x1, " no ";
		if (IsPluralNoun(player)) print "lograrían";
		else print "lograría";
		" gran cosa.";

	Dig:
		print "No serviría de nada que ";
		if (IsPluralNoun(player)) print "se pongan";
		else print "se ponga";
		print " a ";
		LanguageVerb(verb_word);
		" allí.";

	Disrobe:
		switch (n) {
			1:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "llevan";
				else print "lleva";
				" puest", (o) x1, ".";
			2:
				if (IsPluralNoun(player)) print "Se quitan";
				else print "Se quita";
				" ", (the) x1, ".";
		}

	Drink:
		"Eso no parece potable.";

	Drop:
		switch (n) {
			1:
				print "Para poder dejar ", (the) x1, " ";
				if (IsPluralNoun(player)) print "deberían";
				else print "debería";
				" tener", (lo) x1, ".";
			2:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "tienen";
				else print "tiene";
				" ", (contigo) player, ".";
			3:
				print "(Primero ";
				if (IsPluralNoun(player)) print "se quitan";
				else print "se quita";
				" ", (the) x1, ".)";
			4:
				"Dejad", (o) x1, ".";
		}

	Eat:
		switch (n) {
			1:
				"Eso no parece comestible.";
			2:
				if (IsPluralNoun(player)) print "Se comen";
				else print "Se come";
				" ", (the) x1, ".";
		}

	EmptyT:
		switch (n) {
			1:
 				"", (The) x1, " no puede", (n) x1, " tener cosas dentro.";
			2:
				print "No ";
 				if (IsPluralNoun(player)) print "pueden";
				else print "puede";
				" hacerlo porque ", (the) x1, " está", (n) x1,
				" cerrad", (o) x1, ".";
			3:
				"", (The) x1, " ya está", (n) x1, " vací", (o) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "pueden";
				else print "puede";
				" vaciar un objeto sobre sí mismo.";
		}

	Enter:
		switch (n) {
			1:
				print "Ya ";
				if (IsPluralNoun(player)) print "están";
				else print "está";
				print " ";
				if (x1 has supporter) print "sobre";
				else print "en";
				" ", (the) x1, ".";
			2:
				print "No ";
				if (IsPluralNoun(x1)) print "son";
				else print "es";
				print " algo donde ";
				if (IsPluralNoun(player)) print "puedan";
				else print "pueda";
				print " ";
				LanguageVerb(verb_word);
				".";
			3:
				print "No ";
				if (IsPluralNoun(player)) print "pueden";
				else print "puede";
				print " ";
				LanguageVerb(verb_word);
				print " en ", (the) x1, " porque está", (n) x1,
				" cerrad", (o) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "van a poder";
				else print "va a poder";
				print " ";
				LanguageVerb(verb_word);
				print " ahí mientras no ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "suelten";
				else print "suelte";
				" primero.";
			5:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "Suben";
					else print "Sube";
					print " ", (al) x1;
				} else {
					if (IsPluralNoun(player)) print "Entran";
					else print "Entra";
					print " en ", (the) x1;
				}
				".";
			6:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "(Se bajan";
					else print "(Se baja";
				} else {
					if (IsPluralNoun(player)) print "(Salen";
					else print "(Sale";
				}
				" ", (del) x1, ").";
			7:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "(Se suben";
					else print "(Se sube";
					" ", (al) x1, ").^";
				} else if (x1 has container) {
					if (IsPluralNoun(player)) print "(Se meten";
					else print "(Se mete";
					" en ", (the) x1, ").^";
				} else {
					if (IsPluralNoun(player)) print "(Entran";
					else print "(Entra";
					" en ", (the) x1, ").^";
				}
		}

	Examine:
		switch (n) {
			1:
				print "Está demasiado oscuro. No ";
				if (IsPluralNoun(player)) print "pueden";
				else print "puede";
				" ver nada.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "observan";
				else print "observa";
				"  nada especial en ", (the) x1, ".";
			3:
				print (The) x1, " está", (n) x1;
				if (x1 has on) print " encendid", (o) x1;
				else print " apagad", (o) x1;
				".";
		}

	Exit:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "están";
				else print "está";
 				print " en ningún sitio del que ";
				if (IsPluralNoun(player)) print "deban";
				else print "deba";
				print " ";
				LanguageVerb(verb_word);
				".";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "pueden";
				else print "puede";
				" salir ", (del) x1, " porque está", (n) x1,
				" cerrad", (o) x1, ".";
			3:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "Bajan";
					else print "Baja";
				} else {
					if (IsPluralNoun(player)) print "Salen";
					else print "Sale";
				}
				" ", (del) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "pueden";
				else print "puede";
				print ". No ";
				if (IsPluralNoun(player)) print "están";
				else print "está";
				print " ";
				if (x1 has supporter) print "encima";
				else print "dentro";
				" ", (del) x1, ".";
		}

	Fill:
		print "No ";
		if (IsPluralNoun(player)) print "pueden";
		else print "puede";
		" llenar", (lo) x1, ".";

	GetOff:
		print "No ";
		if (IsPluralNoun(player)) print "pueden";
		else print "puede";
		print ". No ";
		if (IsPluralNoun(player)) print "están";
		else print "está";
		" en ", (the) x1, ".";

	Give:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "tienen";
				else print "tiene";
				" ", (the) x1, ".";
			2:
				if (IsPluralNoun(player)) print "Manosean";
				else print "Manosea";
				" ", (the) x1, " durante unos momentos, sin conseguir nada.";
			3:
				"", (The) x1, " no parece", (n) x1, " interesad", (o) x1, ".";
		}

	Go:
		switch (n) {
			1:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Tienen";
				else print "Tiene";
				print " que ";
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "bajarse";
					else print "bajarse";
				}
				else print "salir";
				" ", (del) x1, " antes.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "pueden";
				else print "puede";
				" ir por ahí.";
			3:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Son incapaces";
				else print "Es incapaz";
				" de trepar por ", (the) x1, ".";
			4:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Son incapaces";
				else print "Es incapaz";
				" de bajar por ", (the) x1, ".";
			5:
				PronounNotice(x1);
				print "No ";
				if (IsPluralNoun(player)) print "pueden";
				else print "puede";
				" pasar a través ", (del) x1, ".";
			6:
				PronounNotice(x1);
				print "No ";
				if (IsPluralNoun(player)) print "pueden";
				else print "puede";
				" ir porque ", (the) x1, " no lleva", (n) x1,
				" a ningún sitio.";
		}

	Insert:
		switch (n) {
			1:
				if (x1 has animate) {
					if (IsPluralNoun(player))
						"Antes tienen que ", (coge)"r", (lo) x1,
						" y no saben si se dejaría", (n) x1, ".";
					else
						"Antes tiene que ", (coge)"r", (lo) x1,
						" y no sabe si se dejaría", (n) x1, ".";
				} else {
					if (IsPluralNoun(player)) print "Necesitan";
					else print "Necesita";
					" tener ", (the) x1, " para poder meter", (lo) x1,
					" donde sea.";
				}
			2:
				"No se pueden meter cosas dentro ", (del) x1, ".";
			3:
				"", (The) x1, " está", (n) x1, " cerrad", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Tienen que quitárse";
				else print "Tiene que quitárse";
				"", (lo) x1, " antes.";
			5:
				print "No ";
				if (IsPluralNoun(player)) print "pueden";
				else print "puede";
				" poner un objeto dentro de sí mismo.";
			6:
				print "(Primero ";
				if (IsPluralNoun(player)) print "se ", (lo) x1, " quitan";
				else print "se ", (lo) x1, " quita";
				").^";
			7:
				"No queda sitio en ", (the) x1, ".";
			8:
				"Hecho.";
			9:
				if (IsPluralNoun(player)) print "Meten";
				else print "Mete";
				" ", (the) x1, " dentro ", (del) second, ".";
		}

	Inv:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "llevan";
				else print "lleva";
				" nada.";
			2:
				if (IsPluralNoun(player)) print "Llevan";
				else print "Lleva";
			3:
				print ":^";
			4:
				print ".^";
		}

	Jump:
		if (IsPluralNoun(player)) print "Saltan";
		else print "Salta";
		" en el sitio, sin ningún resultado.";

	JumpOver, Tie:
		print "No ";
		if (IsPluralNoun(player)) print "conseguirían";
		else print "conseguiría";
		" nada así.";

	Kiss:
		print "No ";
		if (IsPluralNoun(player)) print "se les ocurriría";
		else print "se le ocurriría";
		" hacer algo así en este momento.";

	Listen:
		print "No ";
		if (IsPluralNoun(player)) print "escuchan";
		else print "escucha";
		" nada fuera de lo común.";

	ListMiscellany:
		switch (n) {
			2:
				print " (que está", (n) x1, " cerrad", (o) x1, ")";
			4:
				print " (que está", (n) x1, " vací", (o) x1, ")";
			6:
				print " (que está", (n) x1, " cerrad", (o) x1,
				" y vací", (o) x1, ")";
			8:
				print " (alumbrando y que ";
				if (IsPluralNoun(player)) print "llevan";
				else print "lleva";
				print " puest", (o) x1;
			10:
				print " (que ";
				if (IsPluralNoun(player)) print "llevan";
				else print "lleva";
				print " puest", (o) x1;
			11:
				print " (que está", (n) x1, " ";
			17:
				print " (que está", (n) x1, " vací", (o) x1, ")";
			18:
				print " que contiene", (n) x1, " ";
			default:
				ThirdPersonPast_ES(n, x1);
		}

	Lock:
		switch (n) {
			1:
				"No parece", (n) x1, " tener ningún tipo de cerrojo.";
			2:
				if (x1 provides with_key) {
					"", (The) x1, " ya está", (n) x1, " cerrad", (o) x1,
					" con llave.";
				}
				else {
					"", (The) x1, " ya tiene", (n) x1, " echado el cerrojo.";
				}
			3:
				print "Primero ";
				if (IsPluralNoun(player)) print "tienen";
				else print "tiene";
 				" que cerrar ", (the) x1, ".";
			4:
				if (second) {
					"No parece", (n) x1, " encajar en la cerradura.";
				} else {
					if (IsPluralNoun(player)) print "Necesitan";
					else print "Necesita";
					" algún tipo de llave.";
				}
			5:
				if (second) {
					if (IsPluralNoun(player)) print "Cierran";
					else print "Cierra";
					" ", (the) x1, " con ", (the) second, ".";
				} else {
					if (IsPluralNoun(player)) print "Echan";
					else print "Echa";
					" el cerrojo ", (al) x1, ".";
				}
		}

	Look:
		switch (n) {
			5, 6:
				if (real_location provides inhibit_object_list)
					if (real_location.inhibit_object_list)
						return true;
				new_line;
				if (x1 ~= location) {
					if (x1 has supporter) print "Sobre ";
					else print "En ";
					print (the) x1, " ";
					if (IsPluralNoun(player)) print "pueden";
					else print "puede";
					print " ver ";
				} else {
					if (IsPluralNoun(player)) print "Pueden";
					else print "Puede";
					print " ver ";
				}
				if (n==5) print "también ";
				WriteListFrom(child(x1),
					ENGLISH_BIT + WORKFLAG_BIT + RECURSE_BIT
					+ PARTINV_BIT + TERSE_BIT + CONCEAL_BIT);
				".";
			7:
				print "No ";
				if (IsPluralNoun(player)) print "observan";
				else print "observa";
				" nada digno de mención al mirar hacia ", (the) x1, ".";
			default:
				ThirdPersonPast_ES(n, x1);
		}

	LookUnder:
		switch (n) {
			1:
				"Está demasiado oscuro como para poder ver algo.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "ven";
				else print "ve";
				" nada destacable.";
		}

	Miscellany:
		switch (n) {
			9:
				print "^¡";
				if (IsPluralNoun(player)) print "Se han";
				else print "Se ha";
				" quedado a oscuras!";
			17:
				"Está demasiado oscuro como para poder ver algo.";
			18:
				if (IsPluralNoun(player)) print "ell", (o) player;
				else {
					if (IsFemaleNoun(player)) print "ella";
					else print "él";
				}
				print " mism", (o) player;
			19:
				"Tan buen aspecto como siempre.";
			26:
				print "(Primero ";
				if (IsPluralNoun(player)) print "tratan";
				else print "trata";
				" de ", (coge) "r ", (the) x1, ".)";
			32:
				print "No ";
				if (IsPluralNoun(player)) print "tienen";
				else print "tiene";
				" eso.";
			44:
				if (action_to_be == ##Drop) {
					print "[No ";
					if (IsPluralNoun(player)) print "tienen";
					else print "tiene";
					print " nada que ";
					LanguageVerb(verb_word);
					"].";
				} else {
					print "[No hay nada que ";
					LanguageVerb(verb_word);
					"].";
				}
			default:
				ThirdPersonPast_ES(n, x1);
		}

	Objects:
		switch (n) {
			1:
				print "[Objectos que has manejado:]^";
			2:
				"Ninguno.";
			3:
				print "   (puest", (o) x1, ")";
			4:
				print "   (", (contigo) player, ")";
			5:
				print "   (dejad", (o) x1, " con alguien)";
			6:
				print "   (ahora en ", (name) x1, ")";
			7:
				print "   (ahora en ", (the) x1, ")";
			8:
				print "   (ahora dentro ", (del) x1, ")";
			9:
				print "   (ahora en ", (the) x1, ")";
			10:
				print "   (perdid", (o) x1, ")";
		}

	Open:
		switch (n) {
			1:
				"No es algo que se pueda abrir.";
			2:
				"Está", (n) x1, " cerrad", (o) x1, " con llave.";
			3:
				"Ya está", (n) x1, " abiert", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Abren";
				else print "Abre";
				print " ", (the) x1, ", descubriendo ";
				if (WriteListFrom(child(x1),
					ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT) == 0) {
					print "que está", (n) x1, " vací", (o) x1;
				}
				".";
			5:
				if (IsPluralNoun(player)) print "Abren";
				else print "Abre";
				" ", (the) x1, ".";
		}

	Order:
		"", (The) x1, " tiene", (n) x1, " mejores cosas que hacer.";

	Pray:
		"La fe tal vez pueda resultar útil en una ocasión diferente.";

	Pull, Push, Turn:
		switch (n) {
			1:
				"Está", (n) x1, " firmemente sujet", (o) x1, ".";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "son capaces";
				else print "es capaz";
				".";
			3:
				"No ocurre nada, aparentemente.";
			4:
				"Eso sería, como poco, maleducado.";
		}

	PushDir:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creen";
				else print "cree";
				" que empujar", (lo) x1, " sirva de nada.";
			2:
				"Eso no es una dirección.";
			3:
				print "No ";
				if (IsPluralNoun(player)) print "pueden";
				else print "puede";
				" empujar", (lo) x1, " en esa dirección.";
		}

	PutOn:
		switch (n) {
			1:
				if (x1 has animate) {
					if (IsPluralNoun(player))
						"Antes tienen que ", (coge)"r", (lo) x1,
						" y no saben si se dejaría", (n) x1, ".";
					else
						"Antes tiene que ", (coge)"r", (lo) x1,
						" y no sabe si se dejaría", (n) x1, ".";
				} else {
					if (IsPluralNoun(player)) print "Necesitan";
					else print "Necesita";
					" tener ", (the) x1, " para poder poner", (lo) x1,
					" donde fuese.";
				}
			2:
				print "No ";
				if (IsPluralNoun(player)) print "pueden";
				else print "puede";
				" poner un objeto sobre sí mismo.";
			3:
				"Poner cosas sobre ", (the) x1, " no serviría de nada.";
			4:
				if (IsPluralNoun(player)) print "Les falta";
				else print "Le falta";
				" destreza.";
			5:
				print "(Primero ";
				if (IsPluralNoun(player)) print "se ", (lo) x1, " quitan";
				else print "se ", (lo) x1, " quita";
				").^";
			6:
				"No queda sitio en ", (the) x1, " para poner nada más.";
			7:
				"Hecho.";
			8:
				if (IsPluralNoun(player)) print "Colocan";
				else print "Coloca";
				" ", (the) x1, " sobre ", (the) second, ".";
		}

	Remove:
		switch (n) {
			1:
				"Por desgracia ", (the) parent(x1), " está", (n) parent(x1),
				" cerrad", (o) parent(x1), ".";
			2:
				if (second has animate)
					"¡Pero si no ", (lo) x1, " tiene", (n) second,"!";
				else
					"¡Pero si no está", (n) x1, " ahí en este momento!";
			3:
				if (verb_word == 'quita') "Quitad", (o) x1, ".";
				"Sacad", (o) x1, ".";
		}

	Rub:
		"Ya está", (n) x1, " bastante limpi", (o) x1, ".";

	Search:
		switch (n) {
			1:
				"Está demasiado oscuro como para poder ver algo.";
			2:
				"No hay nada sobre ", (the) x1, ".";
			3:
				print "Sobre ", (the) x1;
				WriteListFrom(child(x1),
					ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT + ISARE_BIT);
				".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "encuentran";
				else print "encuentra";
				" nada interesante.";
			5:
				print "No ";
				if (IsPluralNoun(player)) print "pueden";
				else print "puede";
				" ver lo que hay dentro ", (del) x1, " porque
				está", (n) x1, " cerrad", (o) x1, ".";
			6:
				"", (The) x1, " está", (n) x1, " vací", (o) x1, ".";
			7:
				print "En ", (the) x1;
				WriteListFrom(child(x1),
					TERSE_BIT + ENGLISH_BIT + ISARE_BIT + CONCEAL_BIT);
				".";
		}

	Set:
		print "No, no ";
		if (IsPluralNoun(player)) print "pueden";
		else print "puede";
 		".";

	SetTo:
		"Eso no puede regularse a ningún valor.";

	Show:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "tienen";
				else print "tiene";
				" ", (the) x1, ".";
			2:
				"", (The) x1, " no muestra", (n) x1, " ningún interés.";
		}

	Sing:
		if (IsPluralNoun(player)) print "Cantan";
		else print "Canta";
		" fatal.";

	Sleep:
		print "No ";
		if (IsPluralNoun(player)) print "están";
		else print "está";
		" especialmente somnolient", (o) player, ".";

	Smell:
		print "No ";
		if (IsPluralNoun(player)) print "huelen";
		else print "huele";
		" nada extraño.";

	Squeeze:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "se les ocurriría";
				else print "se le ocurriría";
				" hacer algo así.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "consiguen";
				else print "consigue";
				" nada haciendo eso.";
		}

	Swim:
		"No es el momento ni el lugar para ponerse a nadar.";

	Swing:
		print "No parece", (n) x1, " el lugar más adecuado en el que ";
		if (IsPluralNoun(player)) print "columpiarse";
		else print "columpiarse";
		".";

	SwitchOff:
		switch (n) {
			1:
				"No es algo que se pueda apagar.";
			2:
				"Ya está", (n) x1, "apagad", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Apagan";
				else print "Apaga";
				" ", (the) x1, ".";
		}

	SwitchOn:
		switch (n) {
			1:
				"No es algo que se pueda encender.";
			2:
				"Ya está", (n) x1, " encendid", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Encienden";
				else print "Enciende";
				" ", (the) x1, ".";
		}

	Take:
		switch (n) {
			1:
				if (dialecto_sudamericano) print "Tomad";
				else print "Cogid";
				"", (o) noun, ".";
			2:
				print "Siempre ";
				if (IsPluralNoun(player)) print "se tienen";
				else print "se tiene";
 				" a ", (string) YOURSELF__TX, ".";
			3:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creen";
				else print "cree";
				" que ", (al) x1, " le", (s) x1, " fuese a gustar.";
			4:
				if (IsPluralNoun(player)) print "Tienen";
				else print "Tiene";
				print " que ";
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "bajarse";
					else print "bajarse";
				}
				else print "salir";
				"", (del) x1, " antes.";
			5:
				print "Ya ";
				if (IsPluralNoun(player)) print "tienen";
				else print "tiene";
				" ", (the) x1, ".";
			6:
				"Parece", (n) noun, " pertenecer ", (al) x1, ".";
			7:
				"Parece", (n) noun, " formar parte ", (del) x1, ".";
			8:
				"No está", (n) x1, " disponible", (s) x1, ".";
			9:
				"", (The) x1, " no está", (n) x1, " abiert", (o) x1, ".";
			10:
				print "Difícilmente ";
				if (IsPluralNoun(player)) print "podrían llevarse";
				else print "podría llevarse";
				" aquello.";
			11:
				"", (The) x1, " está", (n) x1, " fij", (o) x1,
				" en el sitio.";
			12:
				print "Ya ";
				if (IsPluralNoun(player)) print "tienen";
				else print "tiene";
				" las manos ocupadas con demasiadas cosas.";
			13:
				print "(Primero ";
				if (IsPluralNoun(player)) print "colocan";
				else print "coloca";
				" ", (the) x1, " en ", (the) SACK_OBJECT,
				" para hacer sitio).";
		}

	Taste:
		print "No ";
		if (IsPluralNoun(player)) print "saborean";
		else print "saborea";
		" nada inesperado.";

	Tell:
		switch (n) {
			1:
				if (IsPluralNoun(player)) print "Hablan";
				else print "Habla";
				" sol", (o) player, " durante un rato.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "provocan";
				else print "provoca";
				" ninguna reacción.";
		}

	Think:
		print "Si, eso ";
		if (IsPluralNoun(player)) print "intentan";
		else print "intenta";
		".";

	ThrowAt:
		switch (n) {
			1:
				"No serviría de nada.";
			2:
				print "En el último momento ";
				if (IsPluralNoun(player)) print "se echan";
				else print "se echa";
				" atrás.";
		}

	Touch:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creen";
				else print "cree";
				" que ", (al) x1, " le", (s) x1, " pueda gustar.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "notan";
				else print "nota";
				" nada extraño al tacto.";
			3:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creen";
				else print "cree";
				" que algo así pueda servir de nada.";
    	}

	Unlock:
		switch (n) {
			1:
				"No parece", (n) x1, " tener ningún tipo de cerrojo.";
			2:
				"", (The) x1, " ya tiene", (n) x1, " abierto el cerrojo.";
			3:
				if (second) {
					"No parece", (n) x1, " encajar en la cerradura.";
				} else {
					if (IsPluralNoun(player)) print "Necesitan";
					else print "Necesita";
					" algún tipo de llave.";
				}
			4:
				if (IsPluralNoun(player)) print "Quitan";
				else print "Quita";
				print " el cerrojo ", (al) x1;
				if (second) print " con ", (the) second;
				".";
		}

	Wait:
		"Pasa el tiempo...";

	Wake:
		"La cruda realidad es que eso no es un sueño.";

	WakeOther:
		"No parece necesario hacer eso.";

	Wave:
		switch (n) {
			1:
				print "No l", (o) x1, " ";
				if (IsPluralNoun(player)) print "tienen";
				else print "tiene";
				" ", (contigo) player, ".";
			2:
				if (IsPluralNoun(player)) print "Se sienten";
				else print "Se siente";
				" ridícul", (o) player, " agitando ", (the) x1, ".";
		}

	WaveHands:
		if (IsPluralNoun(player)) print "Se encuentran";
		else print "Se encuentra";
		" ridícul", (o) player, " gesticulando así.";

	Wear:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "pueden ponerse";
				else print "puede ponerse";
				" aquello.";
			2:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "tienen";
				else print "tiene";
 				".";
			3:
				print "Ya ", (lo) x1;
				if (IsPluralNoun(player)) print "llevan";
				else print "lleva";
				" puest", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Se ponen";
				else print "Se pone";
				" ", (the) x1, ".";
		}

	default:
		ThirdPersonPast_ES(n, x1);

];

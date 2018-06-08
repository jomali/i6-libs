

!!==============================================================================
!!
!!	MENSAJES DE LA LIBRERÍA EN ESPAÑOL
!!	Narrador en segunda persona, tiempo presente
!!
!!==============================================================================
!!
!!	Archivo:		sp2present.inf
!!	Autor(es):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!	Idioma:			ES (Español)
!!	Sistema:		Inform-INFSP 6
!!	Plataforma:		Máquina-Z/Glulx
!!	Versión:		0.0
!!	Fecha:			2018/06/08
!!
!!------------------------------------------------------------------------------
!!
!!	HISTORIAL DE VERSIONES
!!
!!	0.0: 2018/06/08	Versión en desarrollo.
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

[ SecondPersonPresent_ES n x1;

	Answer, Ask, AskFor:
		"No hay respuesta.";

	Attack:
		if (x1 == player) {
			print "No ";
			if (IsPluralNoun(player)) print "os autolesionaríais";
			else print "te autolesionarías";
			" a propósito.";
		}
		print "No serviría de nada tratar de ";
		LanguageVerb(verb_word);
		" ", (the) x1, ".";

	Blow:
		if (IsPluralNoun(player)) print "Vuestro";
		else print "Tu";
		" soplido no produce ningún efecto.";

	Burn:
		print "Esa es una idea peligrosa con la que no ";
		if (IsPluralNoun(player)) print "lograríais";
		else print "lograrías";
		" nada en cualquier caso.";

	Buy:
		if (x1 == 0) "No hay nada en venta.";
		else {
			print "No ";
			if (IsPluralNoun(player)) print "podéis";
			else print "puedes";
			" comprar ", (the) x1, ".";
		}

	Climb:
		print "No es algo a lo que ";
		if (IsPluralNoun(player)) print "podáis";
		else print "puedas";
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
				if (IsPluralNoun(player)) print "Cerráis";
				else print "Cierras";
				" ", (the) x1, ".";
		}

	Consult:
		print "No ";
		if (IsPluralNoun(player)) print "descubrís";
		else print "descubres";
		" nada interesante en ", (the) x1, " sobre ese tema.";

	Cut:
		print "Cortándo", (lo) x1, " no ";
		if (IsPluralNoun(player)) print "lograríais";
		else print "lograrías";
		" gran cosa.";

	Dig:
		print "No serviría de nada que ";
		if (IsPluralNoun(player)) print "os pongáis";
		else print "te pongas";
		print " a ";
		LanguageVerb(verb_word);
		" allí.";

	Disrobe:
		switch (n) {
			1:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "lleváis";
				else print "llevas";
				" puest", (o) x1, ".";
			2:
				if (IsPluralNoun(player)) print "Os quitáis";
				else print "Te quitas";
				" ", (the) x1, ".";
		}

	Drink:
		"Eso no parece potable.";

	Drop:
		switch (n) {
			1:
				print "Para poder dejar ", (the) x1, " ";
				if (IsPluralNoun(player)) print "deberíais";
				else print "deberías";
				" tener", (lo) x1, ".";
			2:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "tenéis";
				else print "tienes";
				"", (contigo) player, ".";
			3:
				print "(Primero ";
				if (IsPluralNoun(player)) print "os quitáis";
				else print "te quitas";
				" ", (the) x1, ".)";
			4:
				"Dejad", (o) x1, ".";
		}

	Eat:
		switch (n) {
			1:
				"Eso no parece comestible.";
			2:
				if (IsPluralNoun(player)) print "Os coméis";
				else print "Te comes";
				" ", (the) x1, ".";
		}

	EmptyT:
		switch (n) {
			1:
 				"", (The) x1, " no puede", (n) x1, " tener cosas dentro.";
			2:
				print "No ";
 				if (IsPluralNoun(player)) print "podéis";
				else print "puedes";
				" hacerlo porque ", (the) x1, " está", (n) x1,
				" cerrad", (o) x1, ".";
			3:
				"", (The) x1, " ya está", (n) x1, " vací", (o) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podéis";
				else print "puedes";
				" vaciar un objeto sobre sí mismo.";
		}

	Enter:
		switch (n) {
			1:
				print "Ya ";
				if (IsPluralNoun(player)) print "estáis";
				else print "estás";
				print " ";
				if (x1 has supporter) print "sobre";
				else print "en";
				" ", (the) x1, ".";
			2:
				print "No ";
				if (IsPluralNoun(x1)) print "son";
				else print "es";
				print " algo donde ";
				if (IsPluralNoun(player)) print "podáis";
				else print "puedas";
				print " ";
				LanguageVerb(verb_word);
				".";
			3:
				print "No ";
				if (IsPluralNoun(player)) print "podéis";
				else print "puedes";
				print " ";
				LanguageVerb(verb_word);
				print " en ", (the) x1, " porque está", (n) x1,
				" cerrad", (o) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "váis a poder";
				else print "vas a poder";
				print " ";
				LanguageVerb(verb_word);
				print " ahí mientras no ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "soltéis";
				else print "sueltes";
				" primero.";
			5:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "Subís";
					else print "Subes";
					print " ", (al) x1;
				} else {
					if (IsPluralNoun(player)) print "Entráis";
					else print "Entras";
					print " en ", (the) x1;
				}
				".";
			6:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "(Os bajáis";
					else print "(Te bajas";
				} else {
					if (IsPluralNoun(player)) print "(Salís";
					else print "(Sales";
				}
				" ", (del) x1, ").";
			7:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "(Os subís";
					else print "(Te subes";
					" ", (al) x1, ").^";
				} else if (x1 has container) {
					if (IsPluralNoun(player)) print "(Os metéis";
					else print "(Te metes";
					" en ", (the) x1, ").^";
				} else {
					if (IsPluralNoun(player)) print "(Entráis";
					else print "(Entras";
					" en ", (the) x1, ").^";
				}
		}

	Examine:
		switch (n) {
			1:
				print "Está demasiado oscuro. No ";
				if (IsPluralNoun(player)) print "podéis";
				else print "puedes";
				" ver nada.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "observáis";
				else print "observas";
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
				if (IsPluralNoun(player)) print "estáis";
				else print "estás";
 				print " en ningún sitio del que ";
				if (IsPluralNoun(player)) print "debáis";
				else print "debas";
				print " ";
				LanguageVerb(verb_word);
				".";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podéis";
				else print "puedes";
				" salir ", (del) x1, " porque está", (n) x1,
				" cerrad", (o) x1, ".";
			3:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "Bajáis";
					else print "Bajas";
				} else {
					if (IsPluralNoun(player)) print "Salís";
					else print "Sales";
				}
				" ", (del) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podéis";
				else print "puedes";
				print ". No ";
				if (IsPluralNoun(player)) print "estáis";
				else print "estás";
				print " ";
				if (x1 has supporter) print "encima";
				else print "dentro";
				" ", (del) x1, ".";
		}

	Fill:
		print "No ";
		if (IsPluralNoun(player)) print "podéis";
		else print "puedes";
		" llenar", (lo) x1, ".";

	GetOff:
		print "No ";
		if (IsPluralNoun(player)) print "podéis";
		else print "puedes";
		print ". No ";
		if (IsPluralNoun(player)) print "estáis";
		else print "estás";
		" en ", (the) x1, ".";

	Give:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "tenéis";
				else print "tienes";
				" ", (the) x1, ".";
			2:
				if (IsPluralNoun(player)) print "Manoseáis";
				else print "Manoseas";
				" ", (the) x1, " durante unos momentos, sin conseguir nada.";
			3:
				"", (The) x1, " no parece", (n) x1, " interesad", (o) x1, ".";
		}

	Go:
		switch (n) {
			1:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Tenéis";
				else print "Tienes";
				print " que ";
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "bajaros";
					else print "bajarte";
				}
				else print "salir";
				" ", (del) x1, " antes.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podéis";
				else print "puedes";
				" ir por ahí.";
			3:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Sois incapaces";
				else print "Eres incapaz";
				" de trepar por ", (the) x1, ".";
			4:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Sois incapaces";
				else print "Eres incapaz";
				" de bajar por ", (the) x1, ".";
			5:
				PronounNotice(x1);
				print "No ";
				if (IsPluralNoun(player)) print "podéis";
				else print "puedes";
				" pasar a través ", (del) x1, ".";
			6:
				PronounNotice(x1);
				print "No ";
				if (IsPluralNoun(player)) print "podéis";
				else print "puedes";
				" ir porque ", (the) x1, " no lleva", (n) x1,
				" a ningún sitio.";
		}

	Insert:
		switch (n) {
			1:
				if (x1 has animate) {
					if (IsPluralNoun(player))
						"Antes tenéis que ", (coge)"r", (lo) x1,
						" y no sabéis si se dejaría", (n) x1, ".";
					else
						"Antes tienes que ", (coge)"r", (lo) x1,
						" y no sabes si se dejaría", (n) x1, ".";
				} else {
					if (IsPluralNoun(player)) print "Necesitáis";
					else print "Necesitas";
					" tener ", (the) x1, " para poder meter", (lo) x1,
					" donde sea.";
				}
			2:
				"No se pueden meter cosas dentro ", (del) x1, ".";
			3:
				"", (The) x1, " está", (n) x1, " cerrad", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Tenéis que quitáros";
				else print "Tienes que quitárte";
				"", (lo) x1, " antes.";
			5:
				print "No ";
				if (IsPluralNoun(player)) print "podéis";
				else print "puedes";
				" poner un objeto dentro de sí mismo.";
			6:
				print "(Primero ";
				if (IsPluralNoun(player)) print "os ", (lo) x1, " quitáis";
				else print "te ", (lo) x1, "quitas";
				").^";
			7:
				"No queda sitio en ", (the) x1, ".";
			8:
				"Hecho.";
			9:
				if (IsPluralNoun(player)) print "Metéis";
				else print "Metes";
				" ", (the) x1, " dentro ", (del) second, ".";
		}

	Inv:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "lleváis";
				else print "llevas";
				" nada.";
			2:
				if (IsPluralNoun(player)) print "Lleváis";
				else print "Llevas";
			3:
				print ":^";
			4:
				print ".^";
		}

	Jump:
		if (IsPluralNoun(player)) print "Saltáis";
		else print "Saltas";
		" en el sitio, sin ningún resultado.";

	JumpOver, Tie:
		print "No ";
		if (IsPluralNoun(player)) print "conseguiríais";
		else print "conseguirías";
		" nada así.";

	Kiss:
		print "No ";
		if (IsPluralNoun(player)) print "se os ocurriría";
		else print "se te ocurriría";
		" hacer algo así en este momento.";

	Listen:
		print "No ";
		if (IsPluralNoun(player)) print "escucháis";
		else print "escuchas";
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
				if (IsPluralNoun(player)) print "lleváis";
				else print "llevas";
				print " puest", (o) x1;
			10:
				print " (que ";
				if (IsPluralNoun(player)) print "lleváis";
				else print "llevas";
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
				if (IsPluralNoun(player)) print "tenéis";
				else print "tienes";
 				" que cerrar ", (the) x1, ".";
			4:
				if (second) {
					"No parece", (n) x1, " encajar en la cerradura.";
				} else {
					if (IsPluralNoun(player)) print "Necesitáis";
					else print "Necesitas";
					" algún tipo de llave.";
				}
			5:
				if (second) {
					if (IsPluralNoun(player)) print "Cerráis";
					else print "Cierras";
					" ", (the) x1, " con ", (the) second, ".";
				} else {
					if (IsPluralNoun(player)) print "Echáis";
					else print "Echas";
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
					if (IsPluralNoun(player)) print "podéis";
					else print "puedes";
					print " ver ";
				} else {
					if (IsPluralNoun(player)) print "Podéis";
					else print "Puedes";
					print " ver ";
				}
				if (n==5) print "también ";
				WriteListFrom(child(x1),
					ENGLISH_BIT + WORKFLAG_BIT + RECURSE_BIT
					+ PARTINV_BIT + TERSE_BIT + CONCEAL_BIT);
				".";
			7:
				print "No ";
				if (IsPluralNoun(player)) print "observáis";
				else print "observas";
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
				if (IsPluralNoun(player)) print "véis";
				else print "ves";
				" nada destacable.";
		}

	Miscellany:
		switch (n) {
			3:
				if (IsPluralNoun(player)) print " Habéis muerto ";
				else print " Has muerto ";
			4:
				if (IsPluralNoun(player)) print " Habéis ganado ";
				else print " Has ganado ";
			9:
				print "^¡";
				if (IsPluralNoun(player)) print "Os habéis";
				else print "Te has";
				" quedado a oscuras!";
			17:
				"Está demasiado oscuro como para poder ver algo.";
			18:
				if (IsPluralNoun(player)) print "vosotr", (o) player;
				else print "tú";
				print " mism", (o) player;
			19:
				"Tan buen aspecto como siempre.";
			26:
				print "(Primero ";
				if (IsPluralNoun(player)) print "tratáis";
				else print "tratas";
				" de ", (coge) "r ", (the) x1, ".)";
			32:
				print "No ";
				if (IsPluralNoun(player)) print "tenéis";
				else print "tienes";
				" eso.";
			44:
				if (action_to_be == ##Drop) {
					print "[No ";
					if (IsPluralNoun(player)) print "tenéis";
					else print "tienes";
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
				print "Objectos que ";
				if (IsPluralNoun(player)) print "habéis";
				else print "has";
				" manejado:^";
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
				if (IsPluralNoun(player)) print "Abrís";
				else print "Abres";
				print " ", (the) x1, ", descubriendo ";
				if (WriteListFrom(child(x1),
					ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT) == 0) {
					print "que está", (n) x1, " vací", (o) x1;
				}
				".";
			5:
				if (IsPluralNoun(player)) print "Abrís";
				else print "Abres";
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
				if (IsPluralNoun(player)) print "sois capaces";
				else print "eres capaz";
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
				if (IsPluralNoun(player)) print "creéis";
				else print "crees";
				" que empujar", (lo) x1, " sirva de nada.";
			2:
				"Eso no es una dirección.";
			3:
				print "No ";
				if (IsPluralNoun(player)) print "podéis";
				else print "puedes";
				" empujar", (lo) x1, " en esa dirección.";
		}

	PutOn:
		switch (n) {
			1:
				if (x1 has animate) {
					if (IsPluralNoun(player))
						"Antes tenéis que ", (coge)"r", (lo) x1,
						" y no sabéis si se dejaría", (n) x1, ".";
					else
						"Antes tienes que ", (coge)"r", (lo) x1,
						" y no sabes si se dejaría", (n) x1, ".";
				} else {
					if (IsPluralNoun(player)) print "Necesitáis";
					else print "Necesitas";
					" tener ", (the) x1, " para poder poner", (lo) x1,
					" donde fuese.";
				}
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podéis";
				else print "puedes";
				" poner un objeto sobre sí mismo.";
			3:
				"Poner cosas sobre ", (the) x1, " no serviría de nada.";
			4:
				if (IsPluralNoun(player)) print "Os falta";
				else print "Te falta";
				" destreza.";
			5:
				print "(Primero ";
				if (IsPluralNoun(player)) print "os ", (lo) x1, "quitáis";
				else print "te ", (lo) x1, "quitas";
				").^";
			6:
				"No queda sitio en ", (the) x1, " para poner nada más.";
			7:
				"Hecho.";
			8:
				if (IsPluralNoun(player)) print "Colocáis";
				else print "Colocas";
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
				if (IsPluralNoun(player)) print "encontráis";
				else print "encuentras";
				" nada interesante.";
			5:
				print "No ";
				if (IsPluralNoun(player)) print "podéis";
				else print "puedes";
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
		if (IsPluralNoun(player)) print "podéis";
		else print "puedes";
 		".";

	SetTo:
		"Eso no puede regularse a ningún valor.";

	Show:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "tenéis";
				else print "tienes";
				" ", (the) x1, ".";
			2:
				"", (The) x1, " no muestra", (n) x1, " ningún interés.";
		}

	Sing:
		if (IsPluralNoun(player)) print "Cantáis";
		else print "Cantas";
		" fatal.";

	Sleep:
		print "No ";
		if (IsPluralNoun(player)) print "estáis";
		else print "estás";
		" especialmente somnolient", (o) player, ".";

	Smell:
		print "No ";
		if (IsPluralNoun(player)) print "oléis";
		else print "hueles";
		" nada extraño.";

	Squeeze:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "se os ocurriría";
				else print "se te ocurriría";
				" hacer algo así.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "conseguís";
				else print "consigues";
				" nada haciendo eso.";
		}

	Swim:
		"No es el momento ni el lugar para ponerse a nadar.";

	Swing:
		print "No parece", (n) x1, " el lugar más adecuado en el que ";
		if (IsPluralNoun(player)) print "columpiaros";
		else print "columpiarte";
		".";

	SwitchOff:
		switch (n) {
			1:
				"No es algo que se pueda apagar.";
			2:
				"Ya está", (n) x1, "apagad", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Apagáis";
				else print "Apagas";
				" ", (the) x1, ".";
		}

	SwitchOn:
		switch (n) {
			1:
				"No es algo que se pueda encender.";
			2:
				"Ya está", (n) x1, " encendid", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Encendéis";
				else print "Enciendes";
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
				if (IsPluralNoun(player)) print "os tenéis";
				else print "te tienes";
 				" a ", (string) YOURSELF__TX, ".";
			3:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creéis";
				else print "crees";
				" que ", (al) x1, " le", (s) x1, " fuese a gustar.";
			4:
				if (IsPluralNoun(player)) print "Tenéis";
				else print "Tienes";
				print " que ";
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "bajaros";
					else print "bajarte";
				}
				else print "salir";
				"", (del) x1, " antes.";
			5:
				print "Ya ";
				if (IsPluralNoun(player)) print "tenéis";
				else print "tienes";
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
				if (IsPluralNoun(player)) print "podríais";
				else print "podrías";
				" llevarse aquello.";
			11:
				"", (The) x1, "está", (n) x1, " fij", (o) x1,
				" en el sitio.";
			12:
				print "Ya ";
				if (IsPluralNoun(player)) print "tenéis";
				else print "tienes";
				" las manos ocupadas con demasiadas cosas.";
			13:
				print "(Primero ";
				if (IsPluralNoun(player)) print "colocáis";
				else print "colocas";
				" ", (the) x1, " en ", (the) SACK_OBJECT,
				" para hacer sitio).";
		}

	Taste:
		print "No ";
		if (IsPluralNoun(player)) print "saboreáis";
		else print "saboreas";
		" nada inesperado.";

	Tell:
		switch (n) {
			1:
				if (IsPluralNoun(player)) print "Habláis";
				else print "Hablas";
				" sol", (o) player, " durante un rato.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "provocáis";
				else print "provocas";
				" ninguna reacción.";
		}

	Think:
		print "Si, eso ";
		if (IsPluralNoun(player)) print "intentáis";
		else print "intentas";
		".";

	ThrowAt:
		switch (n) {
			1:
				"No serviría de nada.";
			2:
				print "En el último momento ";
				if (IsPluralNoun(player)) print "os echáis";
				else print "te echas";
				" atrás.";
		}

	Touch:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creéis";
				else print "crees";
				" que ", (al) x1, " le", (s) x1, " pueda gustar.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "notáis";
				else print "notas";
				" nada extraño al tacto.";
			3:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creéis";
				else print "crees";
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
					if (IsPluralNoun(player)) print "Necesitáis";
					else print "Necesitas";
					" algún tipo de llave.";
				}
			4:
				if (IsPluralNoun(player)) print "Quitáis";
				else print "Quitas";
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
				if (IsPluralNoun(player)) print "tenéis";
				else print "tienes";
				"", (contigo) player, ".";
			2:
				if (IsPluralNoun(player)) print "Os sentís";
				else print "Te sientes";
				" ridícul", (o) player, " agitando ", (the) x1, ".";
		}

	WaveHands:
		if (IsPluralNoun(player)) print "Os encontráis";
		else print "Te encuentras";
		" ridícul", (o) player, " gesticulando así.";

	Wear:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "podéis poneros";
				else print "puedes ponerte";
				" aquello.";
			2:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "tenéis";
				else print "tienes";
 				".";
			3:
				print "Ya ", (lo) x1;
				if (IsPluralNoun(player)) print "lleváis";
				else print "llevas";
				" puest", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Os ponéis";
				else print "Te pones";
				" ", (the) x1, ".";
		}

	default:
		ThirdPersonPast_ES(n, x1);

];

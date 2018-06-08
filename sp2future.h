

!!==============================================================================
!!
!!	MENSAJES DE LA LIBRERÍA EN ESPAÑOL
!!	Narrador en segunda persona, tiempo futuro
!!
!!==============================================================================
!!
!!	Archivo:		sp2future.inf
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

[ SecondPersonFuture_ES n x1;

	Answer, Ask, AskFor:
		"No habrá respuesta.";

	Attack:
		if (x1 == player) {
			print "No ";
			if (IsPluralNoun(player)) print "os iréis a autolesionar";
			else print "te irás a autolesionar";
			" a propósito.";
		}
		print "No irá a servir de nada tratar de ";
		LanguageVerb(verb_word);
		" ", (the) x1, ".";

	Blow:
		if (IsPluralNoun(player)) print "Vuestro";
		else print "Tu";
		" soplido no producirá ningún efecto.";

	Burn:
		print "Esa será una idea peligrosa con la que no ";
		if (IsPluralNoun(player)) print "iráis a lograr";
		else print "irás a lograr";
		" nada en cualquier caso.";

	Buy:
		if (x1 == 0) "No habrá nada en venta.";
		else {
			print "No ";
			if (IsPluralNoun(player)) print "podréis";
			else print "podrás";
			" comprar ", (the) x1, ".";
		}

	Climb:
		print "No será algo a lo que ";
		if (IsPluralNoun(player)) print "podáis";
		else print "puedas";
		print " ";
		LanguageVerb(verb_word);
		".";

	Close:
		switch (n) {
			1:
				"No será algo que se pueda cerrar.";
			2:
				"Ya estará", (n) x1, " cerrad", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Cerraréis";
				else print "Cerrarás";
				" ", (the) x1, ".";
		}

	Consult:
		print "No ";
		if (IsPluralNoun(player)) print "descubriréis";
		else print "descubrirás";
		" nada interesante en ", (the) x1, " sobre ese tema.";

	Cut:
		print "Cortándo", (lo) x1, " no ";
		if (IsPluralNoun(player)) print "iréis a lograr";
		else print "irás a lograr";
		" gran cosa.";

	Dig:
		print "No irá a servir de nada que ";
		if (IsPluralNoun(player)) print "os pongáis";
		else print "te pongas";
		print " a ";
		LanguageVerb(verb_word);
		" allí.";

	Disrobe:
		switch (n) {
			1:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "llevaréis";
				else print "llevarás";
				" puest", (o) x1, ".";
			2:
				if (IsPluralNoun(player)) print "Os quitaréis";
				else print "Te quitarás";
				" ", (the) x1, ".";
		}

	Drink:
		"Eso no parecerá potable.";

	Drop:
		switch (n) {
			1:
				print "Para poder dejar ", (the) x1, " ";
				if (IsPluralNoun(player)) print "deberéis";
				else print "deberás";
				" tener", (lo) x1, ".";
			2:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "tendréis";
				else print "tendrás";
				"", (contigo) player, ".";
			3:
				print "(Primero ";
				if (IsPluralNoun(player)) print "os quitaréis";
				else print "te quitarás";
				" ", (the) x1, ".)";
			4:
				"Dejad", (o) x1, ".";
		}

	Eat:
		switch (n) {
			1:
				"Eso no parecerá comestible.";
			2:
				if (IsPluralNoun(player)) print "Os comeréis";
				else print "Te comerás";
				" ", (the) x1, ".";
		}

	EmptyT:
		switch (n) {
			1:
 				"", (The) x1, " no podrá", (n) x1, " tener cosas dentro.";
			2:
				print "No ";
 				if (IsPluralNoun(player)) print "podréis";
				else print "podrás";
				" hacerlo porque ", (the) x1, " estará", (n) x1,
				" cerrad", (o) x1, ".";
			3:
				"", (The) x1, " ya estará", (n) x1, " vací", (o) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podréis";
				else print "podrás";
				" vaciar un objeto sobre sí mismo.";
		}

	Enter:
		switch (n) {
			1:
				print "Ya ";
				if (IsPluralNoun(player)) print "estaréis";
				else print "estarás";
				print " ";
				if (x1 has supporter) print "sobre";
				else print "en";
				" ", (the) x1, ".";
			2:
				print "No ";
				if (IsPluralNoun(x1)) print "serán";
				else print "será";
				print " algo donde ";
				if (IsPluralNoun(player)) print "podáis";
				else print "puedas";
				print " ";
				LanguageVerb(verb_word);
				".";
			3:
				print "No ";
				if (IsPluralNoun(player)) print "podréis";
				else print "podrás";
				print " ";
				LanguageVerb(verb_word);
				print " en ", (the) x1, " porque estará", (n) x1,
				" cerrad", (o) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podréis";
				else print "podrás";
				print " ";
				LanguageVerb(verb_word);
				print " ahí mientras no ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "soltéis";
				else print "sueltes";
				" primero.";
			5:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "Subiréis";
					else print "Subirás";
					print " ", (al) x1;
				} else {
					if (IsPluralNoun(player)) print "Entraréis";
					else print "Entrarás";
					print " en ", (the) x1;
				}
				".";
			6:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "(Os bajaréis";
					else print "(Te bajarás";
				} else {
					if (IsPluralNoun(player)) print "(Saldréis";
					else print "(Saldrás";
				}
				" ", (del) x1, ").";
			7:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "(Os subiréis";
					else print "(Te subirás";
					" ", (al) x1, ").^";
				} else if (x1 has container) {
					if (IsPluralNoun(player)) print "(Os meteréis";
					else print "(Te meterás";
					" en ", (the) x1, ").^";
				} else {
					if (IsPluralNoun(player)) print "(Entreréis";
					else print "(Entrarás";
					" en ", (the) x1, ").^";
				}
		}

	Examine:
		switch (n) {
			1:
				print "Estará demasiado oscuro. No ";
				if (IsPluralNoun(player)) print "podréis";
				else print "podrás";
				" ver nada.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "observaréis";
				else print "observarás";
				"  nada especial en ", (the) x1, ".";
			3:
				print (The) x1, " estará", (n) x1;
				if (x1 has on) print " encendid", (o) x1;
				else print " apagad", (o) x1;
				".";
		}

	Exit:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "estaréis";
				else print "estarás";
 				print " en ningún sitio del que ";
				if (IsPluralNoun(player)) print "debáis";
				else print "debas";
				print " ";
				LanguageVerb(verb_word);
				".";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podréis";
				else print "podrás";
				" salir ", (del) x1, " porque estará", (n) x1,
				" cerrad", (o) x1, ".";
			3:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "Bajaréis";
					else print "Bajarás";
				} else {
					if (IsPluralNoun(player)) print "Saldréis";
					else print "Saldrás";
				}
				" ", (del) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podréis";
				else print "podrás";
				print ". No ";
				if (IsPluralNoun(player)) print "estaréis";
				else print "estarás";
				print " ";
				if (x1 has supporter) print "encima";
				else print "dentro";
				" ", (del) x1, ".";
		}

	Fill:
		print "No ";
		if (IsPluralNoun(player)) print "podréis";
		else print "podrás";
		" llenar", (lo) x1, ".";

	GetOff:
		print "No ";
		if (IsPluralNoun(player)) print "podréis";
		else print "podrás";
		print ". No ";
		if (IsPluralNoun(player)) print "estaréis";
		else print "estarás";
		" en ", (the) x1, ".";

	Give:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "tendréis";
				else print "tendrás";
				" ", (the) x1, ".";
			2:
				if (IsPluralNoun(player)) print "Manosearéis";
				else print "Manosearás";
				" ", (the) x1, " durante unos momentos, sin conseguir nada.";
			3:
				"", (The) x1, " no parecerá", (n) x1, " interesad", (o) x1, ".";
		}

	Go:
		switch (n) {
			1:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Tendréis";
				else print "Tendrás";
				print " que ";
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "bajaros";
					else print "bajarte";
				}
				else print "salir";
				" ", (del) x1, " antes.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podréis";
				else print "podrás";
				" ir por ahí.";
			3:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Seréis incapaces";
				else print "Serás incapaz";
				" de trepar por ", (the) x1, ".";
			4:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Seréis incapaces";
				else print "Serás incapaz";
				" de bajar por ", (the) x1, ".";
			5:
				PronounNotice(x1);
				print "No ";
				if (IsPluralNoun(player)) print "podréis";
				else print "podrás";
				" pasar a través ", (del) x1, ".";
			6:
				PronounNotice(x1);
				print "No ";
				if (IsPluralNoun(player)) print "podréis";
				else print "podrás";
				" ir porque ", (the) x1, " no llevará", (n) x1,
				" a ningún sitio.";
		}

	Insert:
		switch (n) {
			1:
				if (x1 has animate) {
					if (IsPluralNoun(player))
						"Antes tendréis que ", (coge)"r", (lo) x1,
						" y no sabréis si se irá", (n) x1, " a dejar.";
					else
						"Antes tendrás que ", (coge)"r", (lo) x1,
						" y no sabrás si se irá", (n) x1, " a dejar.";
				} else {
					if (IsPluralNoun(player)) print "Necesitaréis";
					else print "Necesitarás";
					" tener ", (the) x1, " para poder meter", (lo) x1,
					" donde sea.";
				}
			2:
				"No se podrán meter cosas dentro ", (del) x1, ".";
			3:
				"", (The) x1, " estará", (n) x1, " cerrad", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Tendréis que quitáros";
				else print "Tendrás que quitárte";
				"", (lo) x1, " antes.";
			5:
				print "No ";
				if (IsPluralNoun(player)) print "podréis";
				else print "podrás";
				" poner un objeto dentro de sí mismo.";
			6:
				print "(Primero ";
				if (IsPluralNoun(player)) print "os ", (lo) x1, " quitaréis";
				else print "te ", (lo) x1, "quitarás";
				").^";
			7:
				"No quedará sitio en ", (the) x1, ".";
			8:
				"Hecho.";
			9:
				if (IsPluralNoun(player)) print "Meteréis";
				else print "Meterás";
				" ", (the) x1, " dentro ", (del) second, ".";
		}

	Inv:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "llevaréis";
				else print "llevarás";
				" nada.";
			2:
				if (IsPluralNoun(player)) print "Llevaréis";
				else print "Llevarás";
			3:
				print ":^";
			4:
				print ".^";
		}

	Jump:
		if (IsPluralNoun(player)) print "Saltaréis";
		else print "Saltarás";
		" en el sitio, sin ningún resultado.";

	JumpOver, Tie:
		print "No ";
		if (IsPluralNoun(player)) print "iréis a conseguir";
		else print "irás a conseguir";
		" nada así.";

	Kiss:
		print "No ";
		if (IsPluralNoun(player)) print "se os ocurrirá";
		else print "se te ocurrirá";
		" hacer algo así en ese momento.";

	Listen:
		print "No ";
		if (IsPluralNoun(player)) print "escucharéis";
		else print "escucharás";
		" nada fuera de lo común.";

	ListMiscellany:
		switch (n) {
			2:
				print " (que estará", (n) x1, " cerrad", (o) x1, ")";
			4:
				print " (que estará", (n) x1, " vací", (o) x1, ")";
			6:
				print " (que estará", (n) x1, " cerrad", (o) x1,
				" y vací", (o) x1, ")";
			8:
				print " (alumbrando y que ";
				if (IsPluralNoun(player)) print "llevaréis";
				else print "llevarás";
				print " puest", (o) x1;
			10:
				print " (que ";
				if (IsPluralNoun(player)) print "llevaréis";
				else print "llevarás";
				print " puest", (o) x1;
			11:
				print " (que estará", (n) x1, " ";
			17:
				print " (que estará", (n) x1, " vací", (o) x1, ")";
			18:
				print " que contendrá", (n) x1, " ";
			default:
				ThirdPersonPast_ES(n, x1);
		}

	Lock:
		switch (n) {
			1:
				"No parecerá", (n) x1, " tener ningún tipo de cerrojo.";
			2:
				if (x1 provides with_key) {
					"", (The) x1, " ya estará", (n) x1, " cerrad", (o) x1,
					" con llave.";
				}
				else {
					"", (The) x1, " ya tendrá", (n) x1, " echado el cerrojo.";
				}
			3:
				print "Primero ";
				if (IsPluralNoun(player)) print "tendréis";
				else print "tendrás";
 				" que cerrar ", (the) x1, ".";
			4:
				if (second) {
					"No parecerá", (n) x1, " encajar en la cerradura.";
				} else {
					if (IsPluralNoun(player)) print "Necesitaréis";
					else print "Necesitarás";
					" algún tipo de llave.";
				}
			5:
				if (second) {
					if (IsPluralNoun(player)) print "Cerraréis";
					else print "Cerrarás";
					" ", (the) x1, " con ", (the) second, ".";
				} else {
					if (IsPluralNoun(player)) print "Echaréis";
					else print "Echarás";
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
					if (IsPluralNoun(player)) print "podréis";
					else print "podrás";
					print " ver ";
				} else {
					if (IsPluralNoun(player)) print "Podréis";
					else print "Podrás";
					print " ver ";
				}
				if (n==5) print "también ";
				WriteListFrom(child(x1),
					ENGLISH_BIT + WORKFLAG_BIT + RECURSE_BIT
					+ PARTINV_BIT + TERSE_BIT + CONCEAL_BIT);
				".";
			7:
				print "No ";
				if (IsPluralNoun(player)) print "observaréis";
				else print "observarás";
				" nada digno de mención al mirar hacia ", (the) x1, ".";
			default:
				ThirdPersonPast_ES(n, x1);
		}

	LookUnder:
		switch (n) {
			1:
				"Estará demasiado oscuro como para poder ver algo.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "veréis";
				else print "verás";
				" nada destacable.";
		}

	Miscellany:
		switch (n) {
			3:
				if (IsPluralNoun(player)) print " Habréis muerto ";
				else print " Habrás muerto ";
			4:
				if (IsPluralNoun(player)) print " Habréis ganado ";
				else print " Habrás ganado ";
			9:
				print "^¡";
				if (IsPluralNoun(player)) print "Os habréis";
				else print "Te habrás";
				" quedado a oscuras!";
			17:
				"Estrá demasiado oscuro como para poder ver algo.";
			18:
				if (IsPluralNoun(player)) print "vosotr", (o) player;
				else print "tú";
				print " mism", (o) player;
			19:
				"Tan buen aspecto como siempre.";
			26:
				print "(Primero ";
				if (IsPluralNoun(player)) print "trataréis";
				else print "tratarás";
				" de ", (coge) "r ", (the) x1, ".)";
			32:
				print "No ";
				if (IsPluralNoun(player)) print "tendréis";
				else print "tendrás";
				" eso.";
			44:
				if (action_to_be == ##Drop) {
					print "[No ";
					if (IsPluralNoun(player)) print "tendréis";
					else print "tendrás";
					print " nada que ";
					LanguageVerb(verb_word);
					"].";
				} else {
					print "[No habrá nada que ";
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
				if (IsPluralNoun(player)) print "habréis";
				else print "habrás";
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
				print "   (en ese momento en ", (name) x1, ")";
			7:
				print "   (en ese momento en ", (the) x1, ")";
			8:
				print "   (en ese momento dentro ", (del) x1, ")";
			9:
				print "   (en ese momento en ", (the) x1, ")";
			10:
				print "   (perdid", (o) x1, ")";
		}

	Open:
		switch (n) {
			1:
				"No será algo que se pueda abrir.";
			2:
				"Estará", (n) x1, " cerrad", (o) x1, " con llave.";
			3:
				"Ya estará", (n) x1, " abiert", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Abriréis";
				else print "Abrirás";
				print " ", (the) x1, ", descubriendo ";
				if (WriteListFrom(child(x1),
					ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT) == 0) {
					print "que estará", (n) x1, " vací", (o) x1;
				}
				".";
			5:
				if (IsPluralNoun(player)) print "Abriréis";
				else print "Abrirás";
				" ", (the) x1, ".";
		}

	Order:
		"", (The) x1, " tendrá", (n) x1, " mejores cosas que hacer.";

	Pray:
		"La fe tal vez podrá resultar útil en una ocasión diferente.";

	Pull, Push, Turn:
		switch (n) {
			1:
				"Estará", (n) x1, " firmemente sujet", (o) x1, ".";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "seréis capaces";
				else print "serás capaz";
				".";
			3:
				"No ocurrirá nada, aparentemente.";
			4:
				"Eso será, como poco, maleducado.";
		}

	PushDir:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creeréis";
				else print "creerás";
				" que empujar", (lo) x1, " sirva de nada.";
			2:
				"Eso no será una dirección.";
			3:
				print "No ";
				if (IsPluralNoun(player)) print "podréis";
				else print "podrás";
				" empujar", (lo) x1, " en esa dirección.";
		}

	PutOn:
		switch (n) {
			1:
				if (x1 has animate) {
					if (IsPluralNoun(player))
						"Antes tendrán que ", (coge)"r", (lo) x1,
						" y no sabrán si se irá", (n) x1, " a dejar.";
					else
						"Antes tendrás que ", (coge)"r", (lo) x1,
						" y no sabrás si se irá", (n) x1, " a dejar.";
				} else {
					if (IsPluralNoun(player)) print "Necesitaréis";
					else print "Necesitarás";
					" tener ", (the) x1, " para poder poner", (lo) x1,
					" donde fuese.";
				}
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podréis";
				else print "podrás";
				" poner un objeto sobre sí mismo.";
			3:
				"Poner cosas sobre ", (the) x1, " no irá a servir de nada.";
			4:
				if (IsPluralNoun(player)) print "Os faltará";
				else print "Te faltará";
				" destreza.";
			5:
				print "(Primero ";
				if (IsPluralNoun(player)) print "os ", (lo) x1, "quitaréis";
				else print "te ", (lo) x1, "quitarás";
				").^";
			6:
				"No quedará sitio en ", (the) x1, " para poner nada más.";
			7:
				"Hecho.";
			8:
				if (IsPluralNoun(player)) print "Colocaréis";
				else print "Colocarás";
				" ", (the) x1, " sobre ", (the) second, ".";
		}

	Remove:
		switch (n) {
			1:
				"Por desgracia ", (the) parent(x1), " estará", (n) parent(x1),
				" cerrad", (o) parent(x1), ".";
			2:
				if (second has animate)
					"¡Pero si no ", (lo) x1, " tendrá", (n) second,"!";
				else
					"¡Pero si no estará", (n) x1, " ahí en ese momento!";
			3:
				if (verb_word == 'quita') "Quitad", (o) x1, ".";
				"Sacad", (o) x1, ".";
		}

	Rub:
		"Ya estará", (n) x1, " bastante limpi", (o) x1, ".";

	Search:
		switch (n) {
			1:
				"Estará demasiado oscuro como para poder ver algo.";
			2:
				"No habrá nada sobre ", (the) x1, ".";
			3:
				print "Sobre ", (the) x1;
				WriteListFrom(child(x1),
					ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT + ISARE_BIT);
				".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "encontraréis";
				else print "encontrarás";
				" nada interesante.";
			5:
				print "No ";
				if (IsPluralNoun(player)) print "podréis";
				else print "podrás";
				" ver lo que hay dentro ", (del) x1, " porque
				estará", (n) x1, " cerrad", (o) x1, ".";
			6:
				"", (The) x1, " estará", (n) x1, " vací", (o) x1, ".";
			7:
				print "En ", (the) x1;
				WriteListFrom(child(x1),
					TERSE_BIT + ENGLISH_BIT + ISARE_BIT + CONCEAL_BIT);
				".";
		}

	Set:
		print "No, no ";
		if (IsPluralNoun(player)) print "podréis";
		else print "podrás";
 		".";

	SetTo:
		"Eso no podrá regularse a ningún valor.";

	Show:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "tendréis";
				else print "tendrás";
				" ", (the) x1, ".";
			2:
				"", (The) x1, " no mostrará", (n) x1, " ningún interés.";
		}

	Sing:
		if (IsPluralNoun(player)) print "Cantaréis";
		else print "Cantarás";
		" fatal.";

	Sleep:
		print "No ";
		if (IsPluralNoun(player)) print "estaréis";
		else print "estarás";
		" especialmente somnolient", (o) player, ".";

	Smell:
		print "No ";
		if (IsPluralNoun(player)) print "oleréis";
		else print "olerás";
		" nada extraño.";

	Squeeze:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "se os ocurrirá";
				else print "se te ocurrirá";
				" hacer algo así.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "conseguiréis";
				else print "conseguirás";
				" nada haciendo eso.";
		}

	Swim:
		"No será el momento ni el lugar para ponerse a nadar.";

	Swing:
		print "No parecerá", (n) x1, " el lugar más adecuado en el que ";
		if (IsPluralNoun(player)) print "columpiaros";
		else print "columpiarte";
		".";

	SwitchOff:
		switch (n) {
			1:
				"No será algo que se pueda apagar.";
			2:
				"Ya estará", (n) x1, "apagad", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Apagaréis";
				else print "Apagarás";
				" ", (the) x1, ".";
		}

	SwitchOn:
		switch (n) {
			1:
				"No será algo que se pueda encender.";
			2:
				"Ya estará", (n) x1, " encendid", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Encenderéis";
				else print "Encenderás";
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
				if (IsPluralNoun(player)) print "os tendréis";
				else print "te tendrás";
 				" a ", (string) YOURSELF__TX, ".";
			3:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creeréis";
				else print "creerás";
				" que ", (al) x1, " le", (s) x1, " gustase.";
			4:
				if (IsPluralNoun(player)) print "Tendréis";
				else print "Tendrás";
				print " que ";
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "bajarse";
					else print "bajarse";
				}
				else print "salir";
				"", (del) x1, " antes.";
			5:
				print "Ya ";
				if (IsPluralNoun(player)) print "tendréis";
				else print "tendrás";
				" ", (the) x1, ".";
			6:
				"Parecerá", (n) noun, " pertenecer ", (al) x1, ".";
			7:
				"Parecerá", (n) noun, " formar parte ", (del) x1, ".";
			8:
				"No estará", (n) x1, " disponible", (s) x1, ".";
			9:
				"", (The) x1, " no estará", (n) x1, " abiert", (o) x1, ".";
			10:
				print "Difícilmente ";
				if (IsPluralNoun(player)) print "podréis";
				else print "podrás";
				" llevarse aquello.";
			11:
				"", (The) x1, "estará", (n) x1, " fij", (o) x1,
				" en el sitio.";
			12:
				print "Ya ";
				if (IsPluralNoun(player)) print "tendréis";
				else print "tendrás";
				" las manos ocupadas con demasiadas cosas.";
			13:
				print "(Primero ";
				if (IsPluralNoun(player)) print "colocaréis";
				else print "colocarás";
				" ", (the) x1, " en ", (the) SACK_OBJECT,
				" para hacer sitio).";
		}

	Taste:
		print "No ";
		if (IsPluralNoun(player)) print "saborearéis";
		else print "saborearás";
		" nada inesperado.";

	Tell:
		switch (n) {
			1:
				if (IsPluralNoun(player)) print "Hablaréis";
				else print "Hablarás";
				" sol", (o) player, " durante un rato.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "provocaréis";
				else print "provocarás";
				" ninguna reacción.";
		}

	Think:
		print "Si, eso ";
		if (IsPluralNoun(player)) print "intentaréis";
		else print "intentarás";
		".";

	ThrowAt:
		switch (n) {
			1:
				"No irá a servir de nada.";
			2:
				print "En el último momento ";
				if (IsPluralNoun(player)) print "os echaréis";
				else print "te echarás";
				" atrás.";
		}

	Touch:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creeréis";
				else print "creerás";
				" que ", (al) x1, " le", (s) x1, " gustase.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "notaréis";
				else print "notarás";
				" nada extraño al tacto.";
			3:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creeréis";
				else print "creerás";
				" que algo así pueda servir de nada.";
    	}

	Unlock:
		switch (n) {
			1:
				"No parecerá", (n) x1, " tener ningún tipo de cerrojo.";
			2:
				"", (The) x1, " ya tendrá", (n) x1, " abierto el cerrojo.";
			3:
				if (second) {
					"No parecerá", (n) x1, " encajar en la cerradura.";
				} else {
					if (IsPluralNoun(player)) print "Necesitaréis";
					else print "Necesitarás";
					" algún tipo de llave.";
				}
			4:
				if (IsPluralNoun(player)) print "Quitaréis";
				else print "Quitarás";
				print " el cerrojo ", (al) x1;
				if (second) print " con ", (the) second;
				".";
		}

	Wait:
		"Pasará el tiempo...";

	Wake:
		"La cruda realidad será que eso no será un sueño.";

	WakeOther:
		"No parecerá necesario hacer eso.";

	Wave:
		switch (n) {
			1:
				print "No l", (o) x1, " ";
				if (IsPluralNoun(player)) print "tendréis";
				else print "tendrás";
				"", (contigo) player, ".";
			2:
				if (IsPluralNoun(player)) print "Os sentiréis";
				else print "Te sentirás";
				" ridícul", (o) player, " agitando ", (the) x1, ".";
		}

	WaveHands:
		if (IsPluralNoun(player)) print "Os encontraréis";
		else print "Te encontrarás";
		" ridícul", (o) player, " gesticulando así.";

	Wear:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "podréis poneros";
				else print "podrás ponerte";
				" aquello.";
			2:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "tendréis";
				else print "tendrás";
 				".";
			3:
				print "Ya ", (lo) x1;
				if (IsPluralNoun(player)) print "llevaréis";
				else print "llevarás";
				" puest", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Os pondréis";
				else print "Te pondrás";
				" ", (the) x1, ".";
		}

	default:
		ThirdPersonPast_ES(n, x1);

];

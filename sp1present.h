

!!==============================================================================
!!
!!	MENSAJES DE LA LIBRERÍA EN ESPAÑOL
!!	Narrador en primera persona, tiempo presente
!!
!!==============================================================================
!!
!!	Archivo:		sp1present.inf
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

[ FirstPersonPresent_ES n x1;

	Answer, Ask, AskFor:
		"No hay respuesta.";

	Attack:
		if (x1 == player) {
			print "No ";
			if (IsPluralNoun(player)) print "nos autolesionaríamos";
			else print "me autolesionaría";
			" a propósito.";
		}
		print "No serviría de nada tratar de ";
		LanguageVerb(verb_word);
		" ", (the) x1, ".";

	Blow:
		if (IsPluralNoun(player)) print "Nuestro";
		else print "Mi";
		" soplido no produce ningún efecto.";

	Burn:
		print "Esa es una idea peligrosa con la que no ";
		if (IsPluralNoun(player)) print "lograríamos";
		else print "lograría";
		" nada en cualquier caso.";

	Buy:
		if (x1 == 0) "No hay nada en venta.";
		else {
			print "No ";
			if (IsPluralNoun(player)) print "podemos";
			else print "puedo";
			" comprar ", (the) x1, ".";
		}

	Climb:
		print "No es algo a lo que ";
		if (IsPluralNoun(player)) print "podamos";
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
				if (IsPluralNoun(player)) print "Cerramos";
				else print "Cierro";
				" ", (the) x1, ".";
		}

	Consult:
		print "No ";
		if (IsPluralNoun(player)) print "descubrimos";
		else print "descubro";
		" nada interesante en ", (the) x1, " sobre ese tema.";

	Cut:
		print "Cortándo", (lo) x1, " no ";
		if (IsPluralNoun(player)) print "lograríamos";
		else print "lograría";
		" gran cosa.";

	Dig:
		print "No serviría de nada que ";
		if (IsPluralNoun(player)) print "nos pongamos";
		else print "me ponga";
		print " a ";
		LanguageVerb(verb_word);
		" allí.";

	Disrobe:
		switch (n) {
			1:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "llevamos";
				else print "llevo";
				" puest", (o) x1, ".";
			2:
				if (IsPluralNoun(player)) print "Nos quitamos";
				else print "Me quito";
				" ", (the) x1, ".";
		}

	Drink:
		"Eso no parece potable.";

	Drop:
		switch (n) {
			1:
				print "Para poder dejar ", (the) x1, " ";
				if (IsPluralNoun(player)) print "deberíamos";
				else print "debería";
				" tener", (lo) x1, ".";
			2:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "tenemos";
				else print "tengo";
				" ", (contigo) player, ".";
			3:
				print "(Primero ";
				if (IsPluralNoun(player)) print "nos quitamos";
				else print "me quito";
				" ", (the) x1, ".)";
			4:
				"Dejad", (o) x1, ".";
		}

	Eat:
		switch (n) {
			1:
				"Eso no parece comestible.";
			2:
				if (IsPluralNoun(player)) print "Nos comemos";
				else print "Me como";
				" ", (the) x1, ".";
		}

	EmptyT:
		switch (n) {
			1:
 				"", (The) x1, " no puede", (n) x1, " tener cosas dentro.";
			2:
				print "No ";
 				if (IsPluralNoun(player)) print "podemos";
				else print "puedo";
				" hacerlo porque ", (the) x1, " está", (n) x1,
				" cerrad", (o) x1, ".";
			3:
				"", (The) x1, " ya está", (n) x1, " vací", (o) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podemos";
				else print "puedo";
				" vaciar un objeto sobre sí mismo.";
		}

	Enter:
		switch (n) {
			1:
				print "Ya ";
				if (IsPluralNoun(player)) print "estamos";
				else print "estoy";
				print " ";
				if (x1 has supporter) print "sobre";
				else print "en";
				" ", (the) x1, ".";
			2:
				print "No ";
				if (IsPluralNoun(x1)) print "son";
				else print "es";
				print " algo donde ";
				if (IsPluralNoun(player)) print "podamos";
				else print "pueda";
				print " ";
				LanguageVerb(verb_word);
				".";
			3:
				print "No ";
				if (IsPluralNoun(player)) print "podemos";
				else print "puedo";
				print " ";
				LanguageVerb(verb_word);
				print " en ", (the) x1, " porque está", (n) x1,
				" cerrad", (o) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "vamos a poder";
				else print "voy a poder";
				print " ";
				LanguageVerb(verb_word);
				print " ahí mientras no ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "soltemos";
				else print "suelte";
				" primero.";
			5:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "Subimos";
					else print "Subo";
					print " ", (al) x1;
				} else {
					if (IsPluralNoun(player)) print "Entramos";
					else print "Entro";
					print " en ", (the) x1;
				}
				".";
			6:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "(Nos bajamos";
					else print "(Me bajo";
				} else {
					if (IsPluralNoun(player)) print "(Salimos";
					else print "(Salgo";
				}
				" ", (del) x1, ").";
			7:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "(Nos subimos";
					else print "(Me subo";
					" ", (al) x1, ").^";
				} else if (x1 has container) {
					if (IsPluralNoun(player)) print "(Nos metemos";
					else print "(Me meto";
					" en ", (the) x1, ").^";
				} else {
					if (IsPluralNoun(player)) print "(Entramos";
					else print "(Entro";
					" en ", (the) x1, ").^";
				}
		}

	Examine:
		switch (n) {
			1:
				print "Está demasiado oscuro. No ";
				if (IsPluralNoun(player)) print "podemos";
				else print "puedo";
				" ver nada.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "observamos";
				else print "observo";
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
				if (IsPluralNoun(player)) print "estamos";
				else print "estoy";
 				print " en ningún sitio del que ";
				if (IsPluralNoun(player)) print "debamos";
				else print "deba";
				print " ";
				LanguageVerb(verb_word);
				".";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podemos";
				else print "puedo";
				" salir ", (del) x1, " porque está", (n) x1,
				" cerrad", (o) x1, ".";
			3:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "Bajamos";
					else print "Bajo";
				} else {
					if (IsPluralNoun(player)) print "Salimos";
					else print "Salgo";
				}
				" ", (del) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podemos";
				else print "puedo";
				print ". No ";
				if (IsPluralNoun(player)) print "estamos";
				else print "estoy";
				print " ";
				if (x1 has supporter) print "encima";
				else print "dentro";
				" ", (del) x1, ".";
		}

	Fill:
		print "No ";
		if (IsPluralNoun(player)) print "podemos";
		else print "puedo";
		" llenar", (lo) x1, ".";

	GetOff:
		print "No ";
		if (IsPluralNoun(player)) print "podemos";
		else print "puedo";
		print ". No ";
		if (IsPluralNoun(player)) print "estamos";
		else print "estoy";
		" en ", (the) x1, ".";

	Give:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "tenemos";
				else print "tengo";
				" ", (the) x1, ".";
			2:
				if (IsPluralNoun(player)) print "Manoseamos";
				else print "Manoseo";
				" ", (the) x1, " durante unos momentos, sin conseguir nada.";
			3:
				"", (The) x1, " no parece", (n) x1, " interesad", (o) x1, ".";
		}

	Go:
		switch (n) {
			1:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Tenemos";
				else print "Tengo";
				print " que ";
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "bajarnos";
					else print "bajarme";
				}
				else print "salir";
				" ", (del) x1, " antes.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podemos";
				else print "puedo";
				" ir por ahí.";
			3:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Somos incapaces";
				else print "Soy incapaz";
				" de trepar por ", (the) x1, ".";
			4:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Somos incapaces";
				else print "Soy incapaz";
				" de bajar por ", (the) x1, ".";
			5:
				PronounNotice(x1);
				print "No ";
				if (IsPluralNoun(player)) print "podemos";
				else print "puedo";
				" pasar a través ", (del) x1, ".";
			6:
				PronounNotice(x1);
				print "No ";
				if (IsPluralNoun(player)) print "podemos";
				else print "puedo";
				" ir porque ", (the) x1, " no lleva", (n) x1,
				" a ningún sitio.";
		}

	Insert:
		switch (n) {
			1:
				if (x1 has animate) {
					if (IsPluralNoun(player))
						"Antes tenemos que ", (coge)"r", (lo) x1,
						" y no sabemos si se dejaría", (n) x1, ".";
					else
						"Antes tengo que ", (coge)"r", (lo) x1,
						" y no se si se dejaría", (n) x1, ".";
				} else {
					if (IsPluralNoun(player)) print "Necesitamos";
					else print "Necesito";
					" tener ", (the) x1, " para poder meter", (lo) x1,
					" donde sea.";
				}
			2:
				"No se pueden meter cosas dentro ", (del) x1, ".";
			3:
				"", (The) x1, " está", (n) x1, " cerrad", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Tenemos que quitárnos";
				else print "Tengo que quitárme";
				"", (lo) x1, " antes.";
			5:
				print "No ";
				if (IsPluralNoun(player)) print "podemos";
				else print "puedo";
				" poner un objeto dentro de sí mismo.";
			6:
				print "(Primero ";
				if (IsPluralNoun(player)) print "nos ", (lo) x1, " quitamos";
				else print "me ", (lo) x1, " quito";
				").^";
			7:
				"No queda sitio en ", (the) x1, ".";
			8:
				"Hecho.";
			9:
				if (IsPluralNoun(player)) print "Metemos";
				else print "Meto";
				" ", (the) x1, " dentro ", (del) second, ".";
		}

	Inv:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "llevamos";
				else print "llevo";
				" nada.";
			2:
				if (IsPluralNoun(player)) print "Llevamos";
				else print "Llevo";
			3:
				print ":^";
			4:
				print ".^";
		}

	Jump:
		if (IsPluralNoun(player)) print "Saltamos";
		else print "Salto";
		" en el sitio, sin ningún resultado.";

	JumpOver, Tie:
		print "No ";
		if (IsPluralNoun(player)) print "conseguiríamos";
		else print "conseguiría";
		" nada así.";

	Kiss:
		print "No ";
		if (IsPluralNoun(player)) print "se nos ocurriría";
		else print "se me ocurriría";
		" hacer algo así en este momento.";

	Listen:
		print "No ";
		if (IsPluralNoun(player)) print "escuchamos";
		else print "escucho";
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
				if (IsPluralNoun(player)) print "llevamos";
				else print "llevo";
				print " puest", (o) x1;
			10:
				print " (que ";
				if (IsPluralNoun(player)) print "llevamos";
				else print "llevo";
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
				if (IsPluralNoun(player)) print "tenemos";
				else print "tengo";
 				" que cerrar ", (the) x1, ".";
			4:
				if (second) {
					"No parece", (n) x1, " encajar en la cerradura.";
				} else {
					if (IsPluralNoun(player)) print "Necesitamos";
					else print "Necesito";
					" algún tipo de llave.";
				}
			5:
				if (second) {
					if (IsPluralNoun(player)) print "Cerramos";
					else print "Cierro";
					" ", (the) x1, " con ", (the) second, ".";
				} else {
					if (IsPluralNoun(player)) print "Echamos";
					else print "Echo";
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
					if (IsPluralNoun(player)) print "podemos";
					else print "puedo";
					print " ver ";
				} else {
					if (IsPluralNoun(player)) print "Podemos";
					else print "Puedo";
					print " ver ";
				}
				if (n==5) print "también ";
				WriteListFrom(child(x1),
					ENGLISH_BIT + WORKFLAG_BIT + RECURSE_BIT
					+ PARTINV_BIT + TERSE_BIT + CONCEAL_BIT);
				".";
			7:
				print "No ";
				if (IsPluralNoun(player)) print "observamos";
				else print "observo";
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
				if (IsPluralNoun(player)) print "vemos";
				else print "veo";
				" nada destacable.";
		}

	Miscellany:
		switch (n) {
			9:
				print "^¡";
				if (IsPluralNoun(player)) print "Nos hemos";
				else print "Me he";
				" quedado a oscuras!";
			17:
				"Está demasiado oscuro como para poder ver algo.";
			18:
				if (IsPluralNoun(player)) print "nosotr", (o) player;
				else print "yo";
				print " mism", (o) player;
			19:
				"Tan buen aspecto como siempre.";
			26:
				print "(Primero ";
				if (IsPluralNoun(player)) print "tratamos";
				else print "trato";
				" de ", (coge) "r ", (the) x1, ".)";
			32:
				print "No ";
				if (IsPluralNoun(player)) print "tenemos";
				else print "tengo";
				" eso.";
			44:
				if (action_to_be == ##Drop) {
					print "[No ";
					if (IsPluralNoun(player)) print "tenemos";
					else print "tengo";
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
				if (IsPluralNoun(player)) print "Abrimos";
				else print "Abro";
				print " ", (the) x1, ", descubriendo ";
				if (WriteListFrom(child(x1),
					ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT) == 0) {
					print "que está", (n) x1, " vací", (o) x1;
				}
				".";
			5:
				if (IsPluralNoun(player)) print "Abrimos";
				else print "Abro";
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
				if (IsPluralNoun(player)) print "somos capaces";
				else print "soy capaz";
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
				if (IsPluralNoun(player)) print "creemos";
				else print "creo";
				" que empujar", (lo) x1, " sirva de nada.";
			2:
				"Eso no es una dirección.";
			3:
				print "No ";
				if (IsPluralNoun(player)) print "podemos";
				else print "puedo";
				" empujar", (lo) x1, " en esa dirección.";
		}

	PutOn:
		switch (n) {
			1:
				if (x1 has animate) {
					if (IsPluralNoun(player))
						"Antes tenemos que ", (coge)"r", (lo) x1,
						" y no sabemos si se dejaría", (n) x1, ".";
					else
						"Antes tengo que ", (coge)"r", (lo) x1,
						" y no se si se dejaría", (n) x1, ".";
				} else {
					if (IsPluralNoun(player)) print "Necesitamos";
					else print "Necesito";
					" tener ", (the) x1, " para poder poner", (lo) x1,
					" donde fuese.";
				}
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podemos";
				else print "puedo";
				" poner un objeto sobre sí mismo.";
			3:
				"Poner cosas sobre ", (the) x1, " no serviría de nada.";
			4:
				if (IsPluralNoun(player)) print "Nos falta";
				else print "Me falta";
				" destreza.";
			5:
				print "(Primero ";
				if (IsPluralNoun(player)) print "nos ", (lo) x1, " quitamos";
				else print "me ", (lo) x1, " quito";
				").^";
			6:
				"No queda sitio en ", (the) x1, " para poner nada más.";
			7:
				"Hecho.";
			8:
				if (IsPluralNoun(player)) print "Colocamos";
				else print "Coloco";
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
				if (IsPluralNoun(player)) print "encontramos";
				else print "encuentro";
				" nada interesante.";
			5:
				print "No ";
				if (IsPluralNoun(player)) print "podemos";
				else print "puedo";
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
		if (IsPluralNoun(player)) print "podemos";
		else print "puedo";
 		".";

	SetTo:
		"Eso no puede regularse a ningún valor.";

	Show:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "tenemos";
				else print "tengo";
				" ", (the) x1, ".";
			2:
				"", (The) x1, " no muestra", (n) x1, " ningún interés.";
		}

	Sing:
		if (IsPluralNoun(player)) print "Cantamos";
		else print "Canto";
		" fatal.";

	Sleep:
		print "No ";
		if (IsPluralNoun(player)) print "estamos";
		else print "estoy";
		" especialmente somnolient", (o) player, ".";

	Smell:
		print "No ";
		if (IsPluralNoun(player)) print "olemos";
		else print "huelo";
		" nada extraño.";

	Squeeze:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "se nos ocurriría";
				else print "se me ocurriría";
				" hacer algo así.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "conseguimos";
				else print "consigo";
				" nada haciendo eso.";
		}

	Swim:
		"No es el momento ni el lugar para ponerse a nadar.";

	Swing:
		print "No parece", (n) x1, " el lugar más adecuado en el que ";
		if (IsPluralNoun(player)) print "columpiarnos";
		else print "columpiarme";
		".";

	SwitchOff:
		switch (n) {
			1:
				"No es algo que se pueda apagar.";
			2:
				"Ya está", (n) x1, "apagad", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Apagamos";
				else print "Apago";
				" ", (the) x1, ".";
		}

	SwitchOn:
		switch (n) {
			1:
				"No es algo que se pueda encender.";
			2:
				"Ya está", (n) x1, " encendid", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Encendemos";
				else print "Enciendo";
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
				if (IsPluralNoun(player)) print "nos tenemos";
				else print "me tengo";
 				" a ", (string) YOURSELF__TX, ".";
			3:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creemos";
				else print "creo";
				" que ", (al) x1, " le", (s) x1, " fuese a gustar.";
			4:
				if (IsPluralNoun(player)) print "Tenemos";
				else print "Tengo";
				print " que ";
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "bajarnos";
					else print "bajarme";
				}
				else print "salir";
				"", (del) x1, " antes.";
			5:
				print "Ya ";
				if (IsPluralNoun(player)) print "tenemos";
				else print "tengo";
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
				if (IsPluralNoun(player)) print "podríamos llevarnos";
				else print "podría llevarme";
				" aquello.";
			11:
				"", (The) x1, "está", (n) x1, " fij", (o) x1,
				" en el sitio.";
			12:
				print "Ya ";
				if (IsPluralNoun(player)) print "tenemos";
				else print "tengo";
				" las manos ocupadas con demasiadas cosas.";
			13:
				print "(Primero ";
				if (IsPluralNoun(player)) print "colocamos";
				else print "coloco";
				" ", (the) x1, " en ", (the) SACK_OBJECT,
				" para hacer sitio).";
		}

	Taste:
		print "No ";
		if (IsPluralNoun(player)) print "saboreamos";
		else print "saboreo";
		" nada inesperado.";

	Tell:
		switch (n) {
			1:
				if (IsPluralNoun(player)) print "Hablamos";
				else print "Hablo";
				" sol", (o) player, " durante un rato.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "provocamos";
				else print "provoco";
				" ninguna reacción.";
		}

	Think:
		print "Si, eso ";
		if (IsPluralNoun(player)) print "intentamos";
		else print "intento";
		".";

	ThrowAt:
		switch (n) {
			1:
				"No serviría de nada.";
			2:
				print "En el último momento ";
				if (IsPluralNoun(player)) print "nos echamos";
				else print "me echo";
				" atrás.";
		}

	Touch:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creemos";
				else print "creo";
				" que ", (al) x1, " le", (s) x1, " pueda gustar.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "notamos";
				else print "noto";
				" nada extraño al tacto.";
			3:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creemos";
				else print "creo";
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
					if (IsPluralNoun(player)) print "Necesitamos";
					else print "Necesito";
					" algún tipo de llave.";
				}
			4:
				if (IsPluralNoun(player)) print "Quitamos";
				else print "Quito";
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
				if (IsPluralNoun(player)) print "tenemos";
				else print "tengo";
				" ", (contigo) player, ".";
			2:
				if (IsPluralNoun(player)) print "Nos sentimos";
				else print "Me siento";
				" ridícul", (o) player, " agitando ", (the) x1, ".";
		}

	WaveHands:
		if (IsPluralNoun(player)) print "Nos encontramos";
		else print "Me encuentro";
		" ridícul", (o) player, " gesticulando así.";

	Wear:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "podemos ponernos";
				else print "puedo ponerme";
				" aquello.";
			2:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "tenemos";
				else print "tengo";
 				".";
			3:
				print "Ya ", (lo) x1;
				if (IsPluralNoun(player)) print "llevamos";
				else print "llevo";
				" puest", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Nos ponemos";
				else print "Me pongo";
				" ", (the) x1, ".";
		}

	default:
		ThirdPersonPast_ES(n, x1);

];



!!==============================================================================
!!
!!	MENSAJES DE LA LIBRERÍA EN ESPAÑOL
!!	Narrador en primera persona, tiempo pasado
!!
!!==============================================================================
!!
!!	Archivo:		sp1pasado.inf
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

[ FirstPersonPast_ES n x1;

	Answer, Ask, AskFor:
		"No había respuesta.";

	Attack:
		if (x1 == player) {
			print "No ";
			if (IsPluralNoun(player)) print "nos hubiésemos autolesionado";
			else print "me hubiese autolesionado";
			" a propósito.";
		}
		print "No hubiese servido de nada tratar de ";
		LanguageVerb(verb_word);
		" ", (the) x1, ".";

	Blow:
		if (IsPluralNoun(player)) print "Nuestro";
		else print "Mi";
		" soplido no produjo ningún efecto.";

	Burn:
		print "Aquella era una idea peligrosa con la que no ";
		if (IsPluralNoun(player)) print "hubiésemos logrado";
		else print "hubiese logrado";
		" nada en cualquier caso.";

	Buy:
		if (x1 == 0) "No había nada en venta.";
		else {
			print "No ";
			if (IsPluralNoun(player)) print "podíamos";
			else print "podía";
			" comprar ", (the) x1, ".";
		}

	Climb:
		print "No era algo a lo que ";
		if (IsPluralNoun(player)) print "pudiésemos";
		else print "pudiese";
		print " ";
		LanguageVerb(verb_word);
		".";

	Close:
		switch (n) {
			1:
				"No era algo que se pudiese cerrar.";
			2:
				"Ya estaba", (n) x1, " cerrad", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Cerramos";
				else print "Cerré";
				" ", (the) x1, ".";
		}

	Consult:
		print "No ";
		if (IsPluralNoun(player)) print "descubrimos";
		else print "descubrí";
		" nada interesante en ", (the) x1, " sobre aquel tema.";

	Cut:
		print "Cortándo", (lo) x1, " no ";
		if (IsPluralNoun(player)) print "hubiésemos logrado";
		else print "hubiese logrado";
		" gran cosa.";

	Dig:
		print "No hubiese servido de nada que ";
		if (IsPluralNoun(player)) print "nos pusiésemos";
		else print "me pusiese";
		print " a ";
		LanguageVerb(verb_word);
		" allí.";

	Disrobe:
		switch (n) {
			1:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "llevábamos";
				else print "llevaba";
				" puest", (o) x1, ".";
			2:
				if (IsPluralNoun(player)) print "Nos quitamos";
				else print "Me quité";
				" ", (the) x1, ".";
		}

	Drink:
		"Aquello no parecía potable.";

	Drop:
		switch (n) {
			1:
				print "Para poder dejar ", (the) x1, " ";
				if (IsPluralNoun(player)) print "hubiésemos debido";
				else print "hubiese debido";
				" tener", (lo) x1, ".";
			2:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "teníamos";
				else print "tenía";
				" ", (contigo) player, ".";
			3:
				print "(Primero ";
				if (IsPluralNoun(player)) print "nos quitamos";
				else print "me quité";
				" ", (the) x1, ".)";
			4:
				"Dejad", (o) x1, ".";
		}

	Eat:
		switch (n) {
			1:
				"Aquello no parecía comestible.";
			2:
				if (IsPluralNoun(player)) print "Nos comimos";
				else print "Me comí";
				" ", (the) x1, ".";
		}

	EmptyT:
		switch (n) {
			1:
 				"", (The) x1, " no podía", (n) x1, " tener cosas dentro.";
			2:
				print "No ";
 				if (IsPluralNoun(player)) print "podíamos";
				else print "podía";
				" hacerlo porque ", (the) x1, " estaba", (n) x1,
				" cerrad", (o) x1, ".";
			3:
				"", (The) x1, " ya estaba", (n) x1, " vací", (o) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podíamos";
				else print "podía";
				" vaciar un objeto sobre sí mismo.";
		}

	Enter:
		switch (n) {
			1:
				print "Ya ";
				if (IsPluralNoun(player)) print "estábamos";
				else print "estaba";
				print " ";
				if (x1 has supporter) print "sobre";
				else print "en";
				" ", (the) x1, ".";
			2:
				print "No ";
				if (IsPluralNoun(x1)) print "eran";
				else print "era";
				print " algo donde ";
				if (IsPluralNoun(player)) print "pudiésemos";
				else print "pudiese";
				print " ";
				LanguageVerb(verb_word);
				".";
			3:
				print "No ";
				if (IsPluralNoun(player)) print "podíamos";
				else print "podía";
				print " ";
				LanguageVerb(verb_word);
				print " en ", (the) x1, " porque estaba", (n) x1,
				" cerrad", (o) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "íbamos a poder";
				else print "iba a poder";
				print " ";
				LanguageVerb(verb_word);
				print " ahí mientras no ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "soltásemos";
				else print "soltase";
				" primero.";
			5:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "Subimos";
					else print "Subí";
					print " ", (al) x1;
				} else {
					if (IsPluralNoun(player)) print "Entramos";
					else print "Entré";
					print " en ", (the) x1;
				}
				".";
			6:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "(Nos bajamos";
					else print "(Me bajé";
				} else {
					if (IsPluralNoun(player)) print "(Salimos";
					else print "(Salí";
				}
				" ", (del) x1, ").";
			7:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "(Nos subimos";
					else print "(Me subí";
					" ", (al) x1, ").^";
				} else if (x1 has container) {
					if (IsPluralNoun(player)) print "(Nos metimos";
					else print "(Me metí";
					" en ", (the) x1, ").^";
				} else {
					if (IsPluralNoun(player)) print "(Entramos";
					else print "(Entré";
					" en ", (the) x1, ").^";
				}
		}

	Examine:
		switch (n) {
			1:
				print "Estaba demasiado oscuro. No ";
				if (IsPluralNoun(player)) print "podíamos";
				else print "podía";
				" ver nada.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "observamos";
				else print "observé";
				"  nada especial en ", (the) x1, ".";
			3:
				print (The) x1, " estaba", (n) x1;
				if (x1 has on) print " encendid", (o) x1;
				else print " apagad", (o) x1;
				".";
		}

	Exit:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "estábamos";
				else print "estaba";
 				print " en ningún sitio del que ";
				if (IsPluralNoun(player)) print "debiésemos";
				else print "debiese";
				print " ";
				LanguageVerb(verb_word);
				".";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podíamos";
				else print "podía";
				" salir ", (del) x1, " porque estaba", (n) x1,
				" cerrad", (o) x1, ".";
			3:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "Bajamos";
					else print "Bajé";
				} else {
					if (IsPluralNoun(player)) print "Salimos";
					else print "Salí";
				}
				" ", (del) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podíamos";
				else print "podía";
				print ". No ";
				if (IsPluralNoun(player)) print "estábamos";
				else print "estaba";
				print " ";
				if (x1 has supporter) print "encima";
				else print "dentro";
				" ", (del) x1, ".";
		}

	Fill:
		print "No ";
		if (IsPluralNoun(player)) print "podíamos";
		else print "podía";
		" llenar", (lo) x1, ".";

	GetOff:
		print "No ";
		if (IsPluralNoun(player)) print "podíamos";
		else print "podía";
		print ". No ";
		if (IsPluralNoun(player)) print "estábamos";
		else print "estaba";
		" en ", (the) x1, ".";

	Give:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "teníamos";
				else print "tenía";
				" ", (the) x1, ".";
			2:
				if (IsPluralNoun(player)) print "Manoseamos";
				else print "Manoseé";
				" ", (the) x1, " durante unos momentos, sin conseguir nada.";
			3:
				"", (The) x1, " no parecía", (n) x1, " interesad", (o) x1, ".";
		}

	Go:
		switch (n) {
			1:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Teníamos";
				else print "Tenía";
				print " que ";
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "bajarnos";
					else print "bajarme";
				}
				else print "salir";
				" ", (del) x1, " antes.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podíamos";
				else print "podía";
				" ir por ahí.";
			3:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Éramos incapaces";
				else print "Era incapaz";
				" de trepar por ", (the) x1, ".";
			4:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Éramos incapaces";
				else print "Era incapaz";
				" de bajar por ", (the) x1, ".";
			5:
				PronounNotice(x1);
				print "No ";
				if (IsPluralNoun(player)) print "podíamos";
				else print "podía";
				" pasar a través ", (del) x1, ".";
			6:
				PronounNotice(x1);
				print "No ";
				if (IsPluralNoun(player)) print "podíamos";
				else print "podía";
				" ir porque ", (the) x1, " no llevaba", (n) x1,
				" a ningún sitio.";
		}

	Insert:
		switch (n) {
			1:
				if (x1 has animate) {
					if (IsPluralNoun(player))
						"Antes teníamos que ", (coge)"r", (lo) x1,
						" y no sabíamos si se hubiese", (n) x1, " dejado.";
					else
						"Antes tenía que ", (coge)"r", (lo) x1,
						" y no sabía si se hubiese", (n) x1, " dejado.";
				} else {
					if (IsPluralNoun(player)) print "Necesitábamos";
					else print "Necesitaba";
					" tener ", (the) x1, " para poder meter", (lo) x1,
					" donde fuese.";
				}
			2:
				"No se podían meter cosas dentro ", (del) x1, ".";
			3:
				"", (The) x1, " estaba", (n) x1, " cerrad", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Teníamos que quitárnos";
				else print "Tenía que quitárme";
				"", (lo) x1, " antes.";
			5:
				print "No ";
				if (IsPluralNoun(player)) print "podíamos";
				else print "podía";
				" poner un objeto dentro de sí mismo.";
			6:
				print "(Primero ";
				if (IsPluralNoun(player)) print "nos ", (lo) x1, " quitamos";
				else print "me ", (lo) x1, " quité";
				").^";
			7:
				"No quedaba sitio en ", (the) x1, ".";
			8:
				"Hecho.";
			9:
				if (IsPluralNoun(player)) print "Metimos";
				else print "Metí";
				" ", (the) x1, " dentro ", (del) second, ".";
		}

	Inv:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "llevábamos";
				else print "llevaba";
				" nada.";
			2:
				if (IsPluralNoun(player)) print "Llevábamos";
				else print "Llevaba";
			3:
				print ":^";
			4:
				print ".^";
		}

	Jump:
		if (IsPluralNoun(player)) print "Saltamos";
		else print "Salté";
		" en el sitio, sin ningún resultado.";

	JumpOver, Tie:
		print "No ";
		if (IsPluralNoun(player)) print "hubiésemos conseguido";
		else print "hubiese conseguido";
		" nada así.";

	Kiss:
		print "No ";
		if (IsPluralNoun(player)) print "se nos hubiese ocurrido";
		else print "se me hubiese ocurrido";
		" hacer algo así en aquel momento.";

	Listen:
		print "No ";
		if (IsPluralNoun(player)) print "escuchamos";
		else print "escuché";
		" nada fuera de lo común.";

	ListMiscellany:
		switch (n) {
			2:
				print " (que estaba", (n) x1, " cerrad", (o) x1, ")";
			4:
				print " (que estaba", (n) x1, " vací", (o) x1, ")";
			6:
				print " (que estaba", (n) x1, " cerrad", (o) x1,
				" y vací", (o) x1, ")";
			8:
				print " (alumbrando y que ";
				if (IsPluralNoun(player)) print "llevábamos";
				else print "llevaba";
				print " puest", (o) x1;
			10:
				print " (que ";
				if (IsPluralNoun(player)) print "llevábamos";
				else print "llevaba";
				print " puest", (o) x1;
			11:
				print " (que estaba", (n) x1, " ";
			17:
				print " (que estaba", (n) x1, " vací", (o) x1, ")";
			18:
				print " que contenía", (n) x1, " ";
			default:
				ThirdPersonPast_ES(n, x1);
		}

	Lock:
		switch (n) {
			1:
				"No parecía", (n) x1, " tener ningún tipo de cerrojo.";
			2:
				if (x1 provides with_key) {
					"", (The) x1, " ya estaba", (n) x1, " cerrad", (o) x1,
					" con llave.";
				}
				else {
					"", (The) x1, " ya tenía", (n) x1, " echado el cerrojo.";
				}
			3:
				print "Primero ";
				if (IsPluralNoun(player)) print "teníamos";
				else print "tenía";
 				" que cerrar ", (the) x1, ".";
			4:
				if (second) {
					"No parecía", (n) x1, " encajar en la cerradura.";
				} else {
					if (IsPluralNoun(player)) print "Necesitábamos";
					else print "Necesitaba";
					" algún tipo de llave.";
				}
			5:
				if (second) {
					if (IsPluralNoun(player)) print "Cerramos";
					else print "Cerré";
					" ", (the) x1, " con ", (the) second, ".";
				} else {
					if (IsPluralNoun(player)) print "Echamos";
					else print "Eché";
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
					if (IsPluralNoun(player)) print "podíamos";
					else print "podía";
					print " ver ";
				} else {
					if (IsPluralNoun(player)) print "Podíamos";
					else print "Podía";
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
				else print "observé";
				" nada digno de mención al mirar hacia ", (the) x1, ".";
			default:
				ThirdPersonPast_ES(n, x1);
		}

	LookUnder:
		switch (n) {
			1:
				"Estaba demasiado oscuro como para poder ver algo.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "vimos";
				else print "vi";
				" nada destacable.";
		}

	Miscellany:
		switch (n) {
			9:
				print "^¡";
				if (IsPluralNoun(player)) print "Nos habíamos";
				else print "Me había";
				" quedado a oscuras!";
			17:
				"Estaba demasiado oscuro como para poder ver algo.";
			18:
				if (IsPluralNoun(player)) print "nosotr", (o) player;
				else print "yo";
				print " mism", (o) player;
			19:
				"Tan buen aspecto como siempre.";
			26:
				print "(Primero ";
				if (IsPluralNoun(player)) print "tratamos";
				else print "traté";
				" de ", (coge) "r ", (the) x1, ".)";
			32:
				print "No ";
				if (IsPluralNoun(player)) print "teníamos";
				else print "tenía";
				" eso.";
			44:
				if (action_to_be == ##Drop) {
					print "[No ";
					if (IsPluralNoun(player)) print "teníamos";
					else print "tenía";
					print " nada que ";
					LanguageVerb(verb_word);
					"].";
				} else {
					print "[No había nada que ";
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
				print "   (entonces en ", (name) x1, ")";
			7:
				print "   (entonces en ", (the) x1, ")";
			8:
				print "   (entonces dentro ", (del) x1, ")";
			9:
				print "   (entonces en ", (the) x1, ")";
			10:
				print "   (perdid", (o) x1, ")";
		}

	Open:
		switch (n) {
			1:
				"No era algo que se pudiese abrir.";
			2:
				"Estaba", (n) x1, " cerrad", (o) x1, " con llave.";
			3:
				"Ya estaba", (n) x1, " abiert", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Abrimos";
				else print "Abrí";
				print " ", (the) x1, ", descubriendo ";
				if (WriteListFrom(child(x1),
					ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT) == 0) {
					print "que estaba", (n) x1, " vací", (o) x1;
				}
				".";
			5:
				if (IsPluralNoun(player)) print "Abrimos";
				else print "Abrí";
				" ", (the) x1, ".";
		}

	Order:
		"", (The) x1, " tenía", (n) x1, " mejores cosas que hacer.";

	Pray:
		"La fe tal vez pudiese resultar útil en una ocasión diferente.";

	Pull, Push, Turn:
		switch (n) {
			1:
				"Estaba", (n) x1, " firmemente sujet", (o) x1, ".";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "fuimos capaces";
				else print "fui capaz";
				".";
			3:
				"No ocurrió nada, aparentemente.";
			4:
				"Aquello hubiese sido, como poco, maleducado.";
		}

	PushDir:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creíamos";
				else print "creía";
				" que empujar", (lo) x1, " hubiese servido de nada.";
			2:
				"Aquello no era una dirección.";
			3:
				print "No ";
				if (IsPluralNoun(player)) print "podíamos";
				else print "podía";
				" empujar", (lo) x1, " en esa dirección.";
		}

	PutOn:
		switch (n) {
			1:
				if (x1 has animate) {
					if (IsPluralNoun(player))
						"Antes teníamos que ", (coge)"r", (lo) x1,
						" y no sabíamos si se hubiese", (n) x1,
						" dejado.";
					else
						"Antes tenía que ", (coge)"r", (lo) x1,
						" y no sabía si se hubiese", (n) x1, " dejado.";
				} else {
					if (IsPluralNoun(player)) print "Necesitábamos";
					else print "Necesitaba";
					" tener ", (the) x1, " para poder poner", (lo) x1,
					" donde fuese.";
				}
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podíamos";
				else print "podía";
				" poner un objeto sobre sí mismo.";
			3:
				"Poner cosas sobre ", (the) x1, " no hubiese servido de nada.";
			4:
				if (IsPluralNoun(player)) print "Nos faltaba";
				else print "Me faltaba";
				" destreza.";
			5:
				print "(Primero ";
				if (IsPluralNoun(player)) print "nos ", (lo) x1, " quitamos";
				else print "me ", (lo) x1, " quité";
				").^";
			6:
				"No quedaba sitio en ", (the) x1, " para poner nada más.";
			7:
				"Hecho.";
			8:
				if (IsPluralNoun(player)) print "Colocamos";
				else print "Coloqué";
				" ", (the) x1, " sobre ", (the) second, ".";
		}

	Remove:
		switch (n) {
			1:
				"Por desgracia ", (the) parent(x1), " estaba", (n) parent(x1),
				" cerrad", (o) parent(x1), ".";
			2:
				if (second has animate)
					"¡Pero si no ", (lo) x1, " tenía", (n) second, "!";
				else
					"¡Pero si no estaba", (n) x1, " ahí en aquel momento!";
			3:
				if (verb_word == 'quita') "Quitad", (o) x1, ".";
				"Sacad", (o) x1, ".";
		}

	Rub:
		"Ya estaba", (n) x1, " bastante limpi", (o) x1, ".";

	Search:
		switch (n) {
			1:
				"Estaba demasiado oscuro como para poder ver algo.";
			2:
				"No había nada sobre ", (the) x1, ".";
			3:
				print "Sobre ", (the) x1;
				WriteListFrom(child(x1),
					ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT + ISARE_BIT);
				".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "encontramos";
				else print "encontré";
				" nada interesante.";
			5:
				print "No ";
				if (IsPluralNoun(player)) print "podíamos";
				else print "podía";
				" ver lo que había dentro ", (del) x1, " porque
				estaba", (n) x1, " cerrad", (o) x1, ".";
			6:
				"", (The) x1, " estaba", (n) x1, " vací", (o) x1, ".";
			7:
				print "En ", (the) x1;
				WriteListFrom(child(x1),
					TERSE_BIT + ENGLISH_BIT + ISARE_BIT + CONCEAL_BIT);
				".";
		}

	Set:
		print "No, no ";
		if (IsPluralNoun(player)) print "podíamos";
		else print "podía";
 		".";

	SetTo:
		"Aquello no podía regularse a ningún valor.";

	Show:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "teníamos";
				else print "tenía";
				" ", (the) x1, ".";
			2:
				"", (The) x1, " no mostraba", (n) x1, " ningún interés.";
		}

	Sing:
		if (IsPluralNoun(player)) print "Cantábamos";
		else print "Cantaba";
		" fatal.";

	Sleep:
		print "No ";
		if (IsPluralNoun(player)) print "estábamos";
		else print "estaba";
		" especialmente somnolient", (o) player, ".";

	Smell:
		print "No ";
		if (IsPluralNoun(player)) print "olimos";
		else print "olí";
		" nada extraño.";

	Squeeze:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "se nos hubiese ocurrido";
				else print "se me hubiese ocurrido";
				" hacer algo así.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "conseguimos";
				else print "conseguí";
				" nada haciendo eso.";
		}

	Swim:
		"No era el momento ni el lugar para ponerse a nadar.";

	Swing:
		print "No parecía", (n) x1, " el lugar más adecuado en el que ";
		if (IsPluralNoun(player)) print "columpiarnos";
		else print "columpiarme";
		".";

	SwitchOff:
		switch (n) {
			1:
				"No era algo que se pudiese apagar.";
			2:
				"Ya estaba", (n) x1, "apagad", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Apagamos";
				else print "Apagué";
				" ", (the) x1, ".";
		}

	SwitchOn:
		switch (n) {
			1:
				"No era algo que se pudiese encender.";
			2:
				"Ya estaba", (n) x1, " encendid", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Encendimos";
				else print "Encendí";
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
				if (IsPluralNoun(player)) print "nos teníamos";
				else print "me tenía";
 				" a ", (string) YOURSELF__TX, ".";
			3:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creíamos";
				else print "creía";
				" que ", (al) x1, " le", (s) x1, " hubiese gustado.";
			4:
				if (IsPluralNoun(player)) print "Teníamos";
				else print "Tenía";
				print " que ";
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "bajarnos";
					else print "bajarme";
				}
				else print "salir";
				"", (del) x1, " antes.";
			5:
				print "Ya ";
				if (IsPluralNoun(player)) print "teníamos";
				else print "tenía";
				" ", (the) x1, ".";
			6:
				"Parecía", (n) noun, " pertenecer ", (al) x1, ".";
			7:
				"Parecía", (n) noun, " formar parte ", (del) x1, ".";
			8:
				"No estaba", (n) x1, " disponible", (s) x1, ".";
			9:
				"", (The) x1, " no estaba", (n) x1, " abiert", (o) x1, ".";
			10:
				print "Difícilmente ";
				if (IsPluralNoun(player)) print "hubiésemos podido llevarnos";
				else print "hubiese podido llevarme";
				" aquello.";
			11:
				"", (The) x1, "estaba", (n) x1, " fij", (o) x1,
				" en el sitio.";
			12:
				print "Ya ";
				if (IsPluralNoun(player)) print "teníamos";
				else print "tenía";
				" las manos ocupadas con demasiadas cosas.";
			13:
				print "(Primero ";
				if (IsPluralNoun(player)) print "colocamos";
				else print "coloqué";
				" ", (the) x1, " en ", (the) SACK_OBJECT,
				" para hacer sitio).";
		}

	Taste:
		print "No ";
		if (IsPluralNoun(player)) print "saboreamos";
		else print "saboreé";
		" nada inesperado.";

	Tell:
		switch (n) {
			1:
				if (IsPluralNoun(player)) print "Hablamos";
				else print "Hablé";
				" sol", (o) player, " durante un rato.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "provocamos";
				else print "provoqué";
				" ninguna reacción.";
		}

	Think:
		print "Si, eso ";
		if (IsPluralNoun(player)) print "intentábamos";
		else print "intentaba";
		".";

	ThrowAt:
		switch (n) {
			1:
				"No hubiese servido de nada.";
			2:
				print "En el último momento ";
				if (IsPluralNoun(player)) print "nos echamos";
				else print "me eché";
				" atrás.";
		}

	Touch:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creíamos";
				else print "creía";
				" que ", (al) x1, " le", (s) x1, " hubiese gustado.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "notamos";
				else print "noté";
				" nada extraño al tacto.";
			3:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creíamos";
				else print "creía";
				" que algo así hubiese servido de nada.";
    	}

	Unlock:
		switch (n) {
			1:
				"No parecía", (n) x1, " tener ningún tipo de cerrojo.";
			2:
				"", (The) x1, " ya tenía", (n) x1, " abierto el cerrojo.";
			3:
				if (second) {
					"No parecía", (n) x1, " encajar en la cerradura.";
				} else {
					if (IsPluralNoun(player)) print "Necesitábamos";
					else print "Necesitaba";
					" algún tipo de llave.";
				}
			4:
				if (IsPluralNoun(player)) print "Quitamos";
				else print "Quité";
				print " el cerrojo ", (al) x1;
				if (second) print " con ", (the) second;
				".";
		}

	Wait:
		"Pasaba el tiempo...";

	Wake:
		"La cruda realidad es que aquello no era un sueño.";

	WakeOther:
		"No parecía necesario hacer aquello.";

	Wave:
		switch (n) {
			1:
				print "No l", (o) x1, " ";
				if (IsPluralNoun(player)) print "teníamos";
				else print "tenía";
				" ", (contigo) player, ".";
			2:
				if (IsPluralNoun(player)) print "Nos sentíamos";
				else print "Me sentía";
				" ridícul", (o) player, " agitando ", (the) x1, ".";
		}

	WaveHands:
		if (IsPluralNoun(player)) print "Nos encontrábamos";
		else print "Me encontraba";
		" ridícul", (o) player, " gesticulando así.";

	Wear:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "podíamos ponernos";
				else print "podía ponerme";
				" aquello.";
			2:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "teníamos";
				else print "tenía";
 				".";
			3:
				print "Ya ", (lo) x1;
				if (IsPluralNoun(player)) print "llevábamos";
				else print "llevaba";
				" puest", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Nos pusimos";
				else print "Me puse";
				" ", (the) x1, ".";
		}

	default:
		ThirdPersonPast_ES(n, x1);

];

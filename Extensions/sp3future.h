

!!==============================================================================
!!
!!	MENSAJES DE LA LIBRERÍA EN ESPAÑOL
!!	Narrador en tercera persona, tiempo futuro
!!
!!==============================================================================
!!
!!	Archivo:		sp3future.inf
!!	Autor(es):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!	Idioma:			ES (Español)
!!	Sistema:		Inform-INFSP 6
!!	Plataforma:		Máquina-Z/Glulx
!!	Versión:		1.1
!!	Fecha:			2011/02/21
!!
!!------------------------------------------------------------------------------
!!
!!	HISTORIAL DE VERSIONES
!!
!!	1.1: 2019/02/21 Modificación de mensajes de la acción ##Look para
!!					reemplazar 'inhibit_object_list' por la nueva propiedad
!!					'list_visible_objects'.
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

[ ThirdPersonFuture_ES n x1;

	Answer, Ask, AskFor:
		"No habrá respuesta.";

	Attack:
		if (x1 == player) {
			print "No ";
			if (IsPluralNoun(player)) print "se irán a autolesionar";
			else print "se irá a autolesionar";
			" a propósito.";
		}
		print "No irá a servir de nada tratar de ";
		LanguageVerb(verb_word);
		" ", (the) x1, ".";

	Blow:
		if (IsPluralNoun(player)) print "Su";
		else print "Su";
		" soplido no producirá ningún efecto.";

	Burn:
		print "Esa será una idea peligrosa con la que no ";
		if (IsPluralNoun(player)) print "irán a lograr";
		else print "irá a lograr";
		" nada en cualquier caso.";

	Buy:
		if (x1 == 0) "No habrá nada en venta.";
		else {
			print "No ";
			if (IsPluralNoun(player)) print "podrán";
			else print "podrá";
			" comprar ", (the) x1, ".";
		}

	Climb:
		print "No será algo a lo que ";
		if (IsPluralNoun(player)) print "puedan";
		else print "pueda";
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
				if (IsPluralNoun(player)) print "Cerrarán";
				else print "Cerrará";
				" ", (the) x1, ".";
		}

	Consult:
		print "No ";
		if (IsPluralNoun(player)) print "descubrirán";
		else print "descubrirá";
		" nada interesante en ", (the) x1, " sobre ese tema.";

	Cut:
		print "Cortándo", (lo) x1, " no ";
		if (IsPluralNoun(player)) print "irán a lograr";
		else print "irá a lograr";
		" gran cosa.";

	Dig:
		print "No irá a servir de nada que ";
		if (IsPluralNoun(player)) print "se pongan";
		else print "se ponga";
		print " a ";
		LanguageVerb(verb_word);
		" allí.";

	Disrobe:
		switch (n) {
			1:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "llevarán";
				else print "llevará";
				" puest", (o) x1, ".";
			2:
				if (IsPluralNoun(player)) print "Se quitarán";
				else print "Se quitará";
				" ", (the) x1, ".";
		}

	Drink:
		"Eso no parecerá potable.";

	Drop:
		switch (n) {
			1:
				print "Para poder dejar ", (the) x1, " ";
				if (IsPluralNoun(player)) print "deberán";
				else print "deberá";
				" tener", (lo) x1, ".";
			2:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "tendrán";
				else print "tendrá";
				" ", (contigo) player, ".";
			3:
				print "(Primero ";
				if (IsPluralNoun(player)) print "se quitarán";
				else print "se quitará";
				" ", (the) x1, ".)";
			4:
				"Dejad", (o) x1, ".";
		}

	Eat:
		switch (n) {
			1:
				"Eso no parecerá comestible.";
			2:
				if (IsPluralNoun(player)) print "Se comerán";
				else print "Se comerá";
				" ", (the) x1, ".";
		}

	EmptyT:
		switch (n) {
			1:
 				"", (The) x1, " no podrá", (n) x1, " tener cosas dentro.";
			2:
				print "No ";
 				if (IsPluralNoun(player)) print "podrán";
				else print "podrá";
				" hacerlo porque ", (the) x1, " estará", (n) x1,
				" cerrad", (o) x1, ".";
			3:
				"", (The) x1, " ya estará", (n) x1, " vací", (o) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podrán";
				else print "podrá";
				" vaciar un objeto sobre sí mismo.";
		}

	Enter:
		switch (n) {
			1:
				print "Ya ";
				if (IsPluralNoun(player)) print "estarán";
				else print "estará";
				print " ";
				if (x1 has supporter) print "sobre";
				else print "en";
				" ", (the) x1, ".";
			2:
				print "No ";
				if (IsPluralNoun(x1)) print "serán";
				else print "será";
				print " algo donde ";
				if (IsPluralNoun(player)) print "puedan";
				else print "pueda";
				print " ";
				LanguageVerb(verb_word);
				".";
			3:
				print "No ";
				if (IsPluralNoun(player)) print "podrán";
				else print "podrá";
				print " ";
				LanguageVerb(verb_word);
				print " en ", (the) x1, " porque estará", (n) x1,
				" cerrad", (o) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podrán";
				else print "podrá";
				print " ";
				LanguageVerb(verb_word);
				print " ahí mientras no ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "suelten";
				else print "suelte";
				" primero.";
			5:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "Subirán";
					else print "Subirá";
					print " ", (al) x1;
				} else {
					if (IsPluralNoun(player)) print "Entrarán";
					else print "Entrará";
					print " en ", (the) x1;
				}
				".";
			6:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "(Se bajarán";
					else print "(Se bajará";
				} else {
					if (IsPluralNoun(player)) print "(Saldrán";
					else print "(Saldrá";
				}
				" ", (del) x1, ").";
			7:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "(Se subirán";
					else print "(Se subirá";
					" ", (al) x1, ").^";
				} else if (x1 has container) {
					if (IsPluralNoun(player)) print "(Se meterán";
					else print "(Se meterá";
					" en ", (the) x1, ").^";
				} else {
					if (IsPluralNoun(player)) print "(Entrarán";
					else print "(Entrará";
					" en ", (the) x1, ").^";
				}
		}

	Examine:
		switch (n) {
			1:
				print "Estará demasiado oscuro. No ";
				if (IsPluralNoun(player)) print "podrán";
				else print "podrá";
				" ver nada.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "observarán";
				else print "observará";
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
				if (IsPluralNoun(player)) print "estarán";
				else print "estará";
 				print " en ningún sitio del que ";
				if (IsPluralNoun(player)) print "deban";
				else print "deba";
				print " ";
				LanguageVerb(verb_word);
				".";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podrán";
				else print "podrá";
				" salir ", (del) x1, " porque estará", (n) x1,
				" cerrad", (o) x1, ".";
			3:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "Bajarán";
					else print "Bajará";
				} else {
					if (IsPluralNoun(player)) print "Saldrán";
					else print "Saldrá";
				}
				" ", (del) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podrán";
				else print "podrá";
				print ". No ";
				if (IsPluralNoun(player)) print "estarán";
				else print "estará";
				print " ";
				if (x1 has supporter) print "encima";
				else print "dentro";
				" ", (del) x1, ".";
		}

	Fill:
		print "No ";
		if (IsPluralNoun(player)) print "podrán";
		else print "podrá";
		" llenar", (lo) x1, ".";

	GetOff:
		print "No ";
		if (IsPluralNoun(player)) print "podrán";
		else print "podrá";
		print ". No ";
		if (IsPluralNoun(player)) print "estarán";
		else print "estará";
		" en ", (the) x1, ".";

	Give:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "tendrán";
				else print "tendrá";
				" ", (the) x1, ".";
			2:
				if (IsPluralNoun(player)) print "Manosearán";
				else print "Manoseará";
				" ", (the) x1, " durante unos momentos, sin conseguir nada.";
			3:
				"", (The) x1, " no parecerá", (n) x1, " interesad", (o) x1, ".";
		}

	Go:
		switch (n) {
			1:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Tendrán";
				else print "Tendrá";
				print " que ";
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "bajarse";
					else print "bajarse";
				}
				else print "salir";
				" ", (del) x1, " antes.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podrán";
				else print "podrá";
				" ir por ahí.";
			3:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Serán incapaces";
				else print "Será incapaz";
				" de trepar por ", (the) x1, ".";
			4:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Serán incapaces";
				else print "Será incapaz";
				" de bajar por ", (the) x1, ".";
			5:
				PronounNotice(x1);
				print "No ";
				if (IsPluralNoun(player)) print "podrán";
				else print "podrá";
				" pasar a través ", (del) x1, ".";
			6:
				PronounNotice(x1);
				print "No ";
				if (IsPluralNoun(player)) print "podrán";
				else print "podrá";
				" ir porque ", (the) x1, " no llevará", (n) x1,
				" a ningún sitio.";
		}

	Insert:
		switch (n) {
			1:
				if (x1 has animate) {
					if (IsPluralNoun(player))
						"Antes tendrán que ", (coge)"r", (lo) x1,
						" y no sabrán si se irá", (n) x1, " a dejar.";
					else
						"Antes tendrá que ", (coge)"r", (lo) x1,
						" y no sabrá si se irá", (n) x1, " a dejar.";
				} else {
					if (IsPluralNoun(player)) print "Necesitarán";
					else print "Necesitará";
					" tener ", (the) x1, " para poder meter", (lo) x1,
					" donde sea.";
				}
			2:
				"No se podrán meter cosas dentro ", (del) x1, ".";
			3:
				"", (The) x1, " estará", (n) x1, " cerrad", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Tendrán que quitárse";
				else print "Tendrá que quitárse";
				"", (lo) x1, " antes.";
			5:
				print "No ";
				if (IsPluralNoun(player)) print "podrán";
				else print "podrá";
				" poner un objeto dentro de sí mismo.";
			6:
				print "(Primero ";
				if (IsPluralNoun(player)) print "se ", (lo) x1, " quitarán";
				else print "se ", (lo) x1, " quitará";
				").^";
			7:
				"No quedará sitio en ", (the) x1, ".";
			8:
				"Hecho.";
			9:
				if (IsPluralNoun(player)) print "Meterán";
				else print "Meterá";
				" ", (the) x1, " dentro ", (del) second, ".";
		}

	Inv:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "llevarán";
				else print "llevará";
				" nada.";
			2:
				if (IsPluralNoun(player)) print "Llevarán";
				else print "Llevará";
			3:
				print ":^";
			4:
				print ".^";
		}

	Jump:
		if (IsPluralNoun(player)) print "Saltarán";
		else print "Saltará";
		" en el sitio, sin ningún resultado.";

	JumpOver, Tie:
		print "No ";
		if (IsPluralNoun(player)) print "irán a conseguir";
		else print "irá a conseguir";
		" nada así.";

	Kiss:
		print "No ";
		if (IsPluralNoun(player)) print "se les ocurrirá";
		else print "se le ocurrirá";
		" hacer algo así en ese momento.";

	Listen:
		print "No ";
		if (IsPluralNoun(player)) print "escucharán";
		else print "escuchará";
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
				if (IsPluralNoun(player)) print "llevarán";
				else print "llevará";
				print " puest", (o) x1;
			10:
				print " (que ";
				if (IsPluralNoun(player)) print "llevarán";
				else print "llevará";
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
				if (IsPluralNoun(player)) print "tendrán";
				else print "tendrá";
 				" que cerrar ", (the) x1, ".";
			4:
				if (second) {
					"No parecerá", (n) x1, " encajar en la cerradura.";
				} else {
					if (IsPluralNoun(player)) print "Necesitarán";
					else print "Necesitará";
					" algún tipo de llave.";
				}
			5:
				if (second) {
					if (IsPluralNoun(player)) print "Cerrarán";
					else print "Cerrará";
					" ", (the) x1, " con ", (the) second, ".";
				} else {
					if (IsPluralNoun(player)) print "Echarán";
					else print "Echará";
					" el cerrojo ", (al) x1, ".";
				}
		}

	Look:
		switch (n) {
			5, 6:
				if (location provides list_visible_objects) {
					if (metaclass(location.list_visible_objects) == String) {
						new_line;
						print (string) location.list_visible_objects;
						new_line;
						return true;
					}
					if (metaclass(location.list_visible_objects) == Routine) {
						if (location.list_visible_objects(n==5)) {
							return true;
						}
					}
				}
				new_line;
				if (x1 ~= location) {
					if (x1 has supporter) print "Sobre ";
					else print "En ";
					print (the) x1, " ";
					if (IsPluralNoun(player)) print "podrán";
					else print "podrá";
					print " ver ";
				} else {
					if (IsPluralNoun(player)) print "Podrán";
					else print "Podrá";
					print " ver ";
				}
				if (n==5) print "también ";
				WriteListFrom(child(x1),
					ENGLISH_BIT + WORKFLAG_BIT + RECURSE_BIT
					+ PARTINV_BIT + TERSE_BIT + CONCEAL_BIT);
				".";
			7:
				print "No ";
				if (IsPluralNoun(player)) print "observarán";
				else print "observará";
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
				if (IsPluralNoun(player)) print "verán";
				else print "verá";
				" nada destacable.";
		}

	Miscellany:
		switch (n) {
			9:
				print "^¡";
				if (IsPluralNoun(player)) print "Se habrán";
				else print "Se habrá";
				" quedado a oscuras!";
			17:
				"Estrá demasiado oscuro como para poder ver algo.";
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
				if (IsPluralNoun(player)) print "tratarán";
				else print "tratará";
				" de ", (coge) "r ", (the) x1, ".)";
			32:
				print "No ";
				if (IsPluralNoun(player)) print "tendrán";
				else print "tendrá";
				" eso.";
			44:
				if (action_to_be == ##Drop) {
					print "[No ";
					if (IsPluralNoun(player)) print "tendrán";
					else print "tendrá";
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
				if (IsPluralNoun(player)) print "Abrirán";
				else print "Abrirá";
				print " ", (the) x1, ", descubriendo ";
				if (WriteListFrom(child(x1),
					ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT) == 0) {
					print "que estará", (n) x1, " vací", (o) x1;
				}
				".";
			5:
				if (IsPluralNoun(player)) print "Abrirán";
				else print "Abrirá";
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
				if (IsPluralNoun(player)) print "serán capaces";
				else print "será capaz";
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
				if (IsPluralNoun(player)) print "creerán";
				else print "creerá";
				" que empujar", (lo) x1, " sirva de nada.";
			2:
				"Eso no será una dirección.";
			3:
				print "No ";
				if (IsPluralNoun(player)) print "podrán";
				else print "podrá";
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
						"Antes tendrá que ", (coge)"r", (lo) x1,
						" y no sabrá si se irá", (n) x1, " a dejar.";
				} else {
					if (IsPluralNoun(player)) print "Necesitarán";
					else print "Necesitará";
					" tener ", (the) x1, " para poder poner", (lo) x1,
					" donde fuese.";
				}
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podrán";
				else print "podrá";
				" poner un objeto sobre sí mismo.";
			3:
				"Poner cosas sobre ", (the) x1, " no irá a servir de nada.";
			4:
				if (IsPluralNoun(player)) print "Les faltará";
				else print "Le faltará";
				" destreza.";
			5:
				print "(Primero ";
				if (IsPluralNoun(player)) print "se ", (lo) x1, " quitarán";
				else print "se ", (lo) x1, " quitará";
				").^";
			6:
				"No quedará sitio en ", (the) x1, " para poner nada más.";
			7:
				"Hecho.";
			8:
				if (IsPluralNoun(player)) print "Colocarán";
				else print "Colocará";
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
				if (IsPluralNoun(player)) print "encontrarán";
				else print "encontrará";
				" nada interesante.";
			5:
				print "No ";
				if (IsPluralNoun(player)) print "podrán";
				else print "podrá";
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
		if (IsPluralNoun(player)) print "podrán";
		else print "podrá";
 		".";

	SetTo:
		"Eso no podrá regularse a ningún valor.";

	Show:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "tendrán";
				else print "tendrá";
				" ", (the) x1, ".";
			2:
				"", (The) x1, " no mostrará", (n) x1, " ningún interés.";
		}

	Sing:
		if (IsPluralNoun(player)) print "Cantarán";
		else print "Cantará";
		" fatal.";

	Sleep:
		print "No ";
		if (IsPluralNoun(player)) print "estarán";
		else print "estará";
		" especialmente somnolient", (o) player, ".";

	Smell:
		print "No ";
		if (IsPluralNoun(player)) print "olerán";
		else print "olerá";
		" nada extraño.";

	Squeeze:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "se les ocurrirá";
				else print "se le ocurrirá";
				" hacer algo así.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "conseguirán";
				else print "conseguirá";
				" nada haciendo eso.";
		}

	Swim:
		"No será el momento ni el lugar para ponerse a nadar.";

	Swing:
		print "No parecerá", (n) x1, " el lugar más adecuado en el que ";
		if (IsPluralNoun(player)) print "columpiarse";
		else print "columpiarse";
		".";

	SwitchOff:
		switch (n) {
			1:
				"No será algo que se pueda apagar.";
			2:
				"Ya estará", (n) x1, "apagad", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Apagarán";
				else print "Apagará";
				" ", (the) x1, ".";
		}

	SwitchOn:
		switch (n) {
			1:
				"No será algo que se pueda encender.";
			2:
				"Ya estará", (n) x1, " encendid", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Encenderán";
				else print "Encenderá";
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
				if (IsPluralNoun(player)) print "se tendrán";
				else print "se tendrá";
 				" a ", (string) YOURSELF__TX, ".";
			3:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creerán";
				else print "creerá";
				" que ", (al) x1, " le", (s) x1, " gustase.";
			4:
				if (IsPluralNoun(player)) print "Tendrán";
				else print "Tendrá";
				print " que ";
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "bajarse";
					else print "bajarse";
				}
				else print "salir";
				"", (del) x1, " antes.";
			5:
				print "Ya ";
				if (IsPluralNoun(player)) print "tendrán";
				else print "tendrá";
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
				if (IsPluralNoun(player)) print "podrán llevarse";
				else print "podrá llevarse";
				" aquello.";
			11:
				"", (The) x1, "estará", (n) x1, " fij", (o) x1,
				" en el sitio.";
			12:
				print "Ya ";
				if (IsPluralNoun(player)) print "tendrán";
				else print "tendrá";
				" las manos ocupadas con demasiadas cosas.";
			13:
				print "(Primero ";
				if (IsPluralNoun(player)) print "colocarán";
				else print "colocará";
				" ", (the) x1, " en ", (the) SACK_OBJECT,
				" para hacer sitio).";
		}

	Taste:
		print "No ";
		if (IsPluralNoun(player)) print "saborearán";
		else print "saboreará";
		" nada inesperado.";

	Tell:
		switch (n) {
			1:
				if (IsPluralNoun(player)) print "Hablarán";
				else print "Hablará";
				" sol", (o) player, " durante un rato.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "povocarán";
				else print "provocará";
				" ninguna reacción.";
		}

	Think:
		print "Si, eso ";
		if (IsPluralNoun(player)) print "intentarán";
		else print "intentará";
		".";

	ThrowAt:
		switch (n) {
			1:
				"No irá a servir de nada.";
			2:
				print "En el último momento ";
				if (IsPluralNoun(player)) print "se echarán";
				else print "se echará";
				" atrás.";
		}

	Touch:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creerán";
				else print "creerá";
				" que ", (al) x1, " le", (s) x1, " gustase.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "notarán";
				else print "notará";
				" nada extraño al tacto.";
			3:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creerán";
				else print "creerá";
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
					if (IsPluralNoun(player)) print "Necesitarán";
					else print "Necesitará";
					" algún tipo de llave.";
				}
			4:
				if (IsPluralNoun(player)) print "Quitarán";
				else print "Quitará";
				print " el cerrojo ", (al) x1;
				if (second) print " con ", (the) second;
				".";
		}

	Wait:
		"Pasará el tiempo…";

	Wake:
		"La cruda realidad es que eso no será un sueño.";

	WakeOther:
		"No parecerá necesario hacer eso.";

	Wave:
		switch (n) {
			1:
				print "No l", (o) x1, " ";
				if (IsPluralNoun(player)) print "tendrán";
				else print "tendrá";
				" ", (contigo) player, ".";
			2:
				if (IsPluralNoun(player)) print "Se sentirán";
				else print "Se sentirá";
				" ridícul", (o) player, " agitando ", (the) x1, ".";
		}

	WaveHands:
		if (IsPluralNoun(player)) print "Se encontrarán";
		else print "Se encontrará";
		" ridícul", (o) player, " gesticulando así.";

	Wear:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "podrán ponerse";
				else print "podrá ponerse";
				" aquello.";
			2:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "tendrán";
				else print "tendrá";
 				".";
			3:
				print "Ya ", (lo) x1;
				if (IsPluralNoun(player)) print "llevarán";
				else print "llevará";
				" puest", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Se pondrán";
				else print "Se pondrá";
				" ", (the) x1, ".";
		}

	default:
		ThirdPersonPast_ES(n, x1);

];

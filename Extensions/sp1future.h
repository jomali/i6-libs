

!!==============================================================================
!!
!!	MENSAJES DE LA LIBRERÍA EN ESPAÑOL
!!	Narrador en primera persona, tiempo futuro
!!
!!==============================================================================
!!
!!	Archivo:		sp1future.inf
!!	Autor(es):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!	Idioma:			ES (Español)
!!	Sistema:		Inform-INFSP 6
!!	Plataforma:		Máquina-Z/Glulx
!!	Versión:		1.20
!!	Fecha:			2019/09/16
!!
!!------------------------------------------------------------------------------
!!
!!	HISTORIAL DE VERSIONES
!!
!!	1.20: 2019/09/16 Corrección de erratas: acción ##Wear
!!	1.1: 2019/02/21 Modificación de mensajes de la acción ##Look para
!!					reemplazar 'inhibit_object_list' por la nueva propiedad
!!					'list_visible_objects'.
!!	1.0: 2018/09/21	Versión inicial.
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

[ FirstPersonFuture_ES n x1;

	Answer, Ask, AskFor:
		"No habrá respuesta.";

	Attack:
		if (x1 == player) {
			print "No ";
			if (IsPluralNoun(player)) print "nos iremos a autolesionar";
			else print "me iré a autolesionar";
			" a propósito.";
		}
		print "No irá a servir de nada tratar de ";
		LanguageVerb(verb_word);
		" ", (the) x1, ".";

	Blow:
		if (IsPluralNoun(player)) print "Nuestro";
		else print "Mi";
		" soplido no producirá ningún efecto.";

	Burn:
		print "Esa será una idea peligrosa con la que no ";
		if (IsPluralNoun(player)) print "iríamos a lograr";
		else print "iría a lograr";
		" nada en cualquier caso.";

	Buy:
		if (x1 == 0) "No habrá nada en venta.";
		else {
			print "No ";
			if (IsPluralNoun(player)) print "podremos";
			else print "podré";
			" comprar ", (the) x1, ".";
		}

	Climb:
		print "No será algo a lo que ";
		if (IsPluralNoun(player)) print "podamos";
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
				if (IsPluralNoun(player)) print "Cerraremos";
				else print "Cerraré";
				" ", (the) x1, ".";
		}

	Consult:
		print "No ";
		if (IsPluralNoun(player)) print "descubriremos";
		else print "descubriré";
		" nada interesante en ", (the) x1, " sobre ese tema.";

	Cut:
		print "Cortándo", (lo) x1, " no ";
		if (IsPluralNoun(player)) print "iremos a lograr";
		else print "iré a lograr";
		" gran cosa.";

	Dig:
		print "No irá a servir de nada que ";
		if (IsPluralNoun(player)) print "nos pongamos";
		else print "me ponga";
		print " a ";
		LanguageVerb(verb_word);
		" allí.";

	Disrobe:
		switch (n) {
			1:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "llevaremos";
				else print "llevaré";
				" puest", (o) x1, ".";
			2:
				if (IsPluralNoun(player)) print "Nos quitaremos";
				else print "Me quitaré";
				" ", (the) x1, ".";
		}

	Drink:
		"Eso no parecerá potable.";

	Drop:
		switch (n) {
			1:
				print "Para poder dejar ", (the) x1, " ";
				if (IsPluralNoun(player)) print "deberemos";
				else print "deberé";
				" tener", (lo) x1, ".";
			2:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "tendremos";
				else print "tendré";
				" ", (contigo) player, ".";
			3:
				print "(Primero ";
				if (IsPluralNoun(player)) print "nos quitaremos";
				else print "me quitaré";
				" ", (the) x1, ".)";
			4:
				"Dejad", (o) x1, ".";
		}

	Eat:
		switch (n) {
			1:
				"Eso no parecerá comestible.";
			2:
				if (IsPluralNoun(player)) print "Nos comeremos";
				else print "Me comeré";
				" ", (the) x1, ".";
		}

	EmptyT:
		switch (n) {
			1:
 				"", (The) x1, " no podrá", (n) x1, " tener cosas dentro.";
			2:
				print "No ";
 				if (IsPluralNoun(player)) print "podremos";
				else print "podré";
				" hacerlo porque ", (the) x1, " estará", (n) x1,
				" cerrad", (o) x1, ".";
			3:
				"", (The) x1, " ya estará", (n) x1, " vací", (o) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podré";
				" vaciar un objeto sobre sí mismo.";
		}

	Enter:
		switch (n) {
			1:
				print "Ya ";
				if (IsPluralNoun(player)) print "estaremos";
				else print "estaré";
				print " ";
				if (x1 has supporter) print "sobre";
				else print "en";
				" ", (the) x1, ".";
			2:
				print "No ";
				if (IsPluralNoun(x1)) print "serán";
				else print "será";
				print " algo donde ";
				if (IsPluralNoun(player)) print "podamos";
				else print "pueda";
				print " ";
				LanguageVerb(verb_word);
				".";
			3:
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podré";
				print " ";
				LanguageVerb(verb_word);
				print " en ", (the) x1, " porque estará", (n) x1,
				" cerrad", (o) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podré";
				print " ";
				LanguageVerb(verb_word);
				print " ahí mientras no ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "soltemos";
				else print "suelte";
				" primero.";
			5:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "Subiremos";
					else print "Subiré";
					print " ", (al) x1;
				} else {
					if (IsPluralNoun(player)) print "Entraremos";
					else print "Entraré";
					print " en ", (the) x1;
				}
				".";
			6:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "(Nos bajaremos";
					else print "(Me bajaré";
				} else {
					if (IsPluralNoun(player)) print "(Saldremos";
					else print "(Saldré";
				}
				" ", (del) x1, ").";
			7:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "(Nos subiremos";
					else print "(Me subiré";
					" ", (al) x1, ").^";
				} else if (x1 has container) {
					if (IsPluralNoun(player)) print "(Nos meteremos";
					else print "(Me meteré";
					" en ", (the) x1, ").^";
				} else {
					if (IsPluralNoun(player)) print "(Entraremos";
					else print "(Entraré";
					" en ", (the) x1, ").^";
				}
		}

	Examine:
		switch (n) {
			1:
				print "Estará demasiado oscuro. No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podré";
				" ver nada.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "observaremos";
				else print "observaré";
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
				if (IsPluralNoun(player)) print "estaremos";
				else print "estaré";
 				print " en ningún sitio del que ";
				if (IsPluralNoun(player)) print "debiésemos";
				else print "debiese";
				print " ";
				LanguageVerb(verb_word);
				".";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podré";
				" salir ", (del) x1, " porque estará", (n) x1,
				" cerrad", (o) x1, ".";
			3:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "Bajaremos";
					else print "Bajaré";
				} else {
					if (IsPluralNoun(player)) print "Saldremos";
					else print "Saldré";
				}
				" ", (del) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podré";
				print ". No ";
				if (IsPluralNoun(player)) print "estaremos";
				else print "estaré";
				print " ";
				if (x1 has supporter) print "encima";
				else print "dentro";
				" ", (del) x1, ".";
		}

	Fill:
		print "No ";
		if (IsPluralNoun(player)) print "podremos";
		else print "podré";
		" llenar", (lo) x1, ".";

	GetOff:
		print "No ";
		if (IsPluralNoun(player)) print "podremos";
		else print "podré";
		print ". No ";
		if (IsPluralNoun(player)) print "estaremos";
		else print "estaré";
		" en ", (the) x1, ".";

	Give:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "tendremos";
				else print "tendré";
				" ", (the) x1, ".";
			2:
				if (IsPluralNoun(player)) print "Manosearemos";
				else print "Manosearé";
				" ", (the) x1, " durante unos momentos, sin conseguir nada.";
			3:
				"", (The) x1, " no parecerá", (n) x1, " interesad", (o) x1, ".";
		}

	Go:
		switch (n) {
			1:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Tendremos";
				else print "Tendré";
				print " que ";
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "bajaros";
					else print "bajarte";
				}
				else print "salir";
				" ", (del) x1, " antes.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podré";
				" ir por ahí.";
			3:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Seremos incapaces";
				else print "Seré incapaz";
				" de trepar por ", (the) x1, ".";
			4:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Seremos incapaces";
				else print "Seré incapaz";
				" de bajar por ", (the) x1, ".";
			5:
				PronounNotice(x1);
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podré";
				" pasar a través ", (del) x1, ".";
			6:
				PronounNotice(x1);
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podré";
				" ir porque ", (the) x1, " no llevará", (n) x1,
				" a ningún sitio.";
		}

	Insert:
		switch (n) {
			1:
				if (x1 has animate) {
					if (IsPluralNoun(player))
						"Antes tendremos que ", (coge)"r", (lo) x1,
						" y no sabremos si se irá", (n) x1, " a dejar.";
					else
						"Antes tendré que ", (coge)"r", (lo) x1,
						" y no sabré si se irá", (n) x1, " a dejar.";
				} else {
					if (IsPluralNoun(player)) print "Necesitaremos";
					else print "Necesitaré";
					" tener ", (the) x1, " para poder meter", (lo) x1,
					" donde sea.";
				}
			2:
				"No se podrán meter cosas dentro ", (del) x1, ".";
			3:
				"", (The) x1, " estará", (n) x1, " cerrad", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Tendremos que quitárnos";
				else print "Tendré que quitárme";
				"", (lo) x1, " antes.";
			5:
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podré";
				" poner un objeto dentro de sí mismo.";
			6:
				print "(Primero ";
				if (IsPluralNoun(player)) print "nos ", (lo) x1, " quitaremos";
				else print "me ", (lo) x1, " quitaré";
				").^";
			7:
				"No quedará sitio en ", (the) x1, ".";
			8:
				"Hecho.";
			9:
				if (IsPluralNoun(player)) print "Meteremos";
				else print "Meteré";
				" ", (the) x1, " dentro ", (del) second, ".";
		}

	Inv:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "llevaremos";
				else print "llevaré";
				" nada.";
			2:
				if (IsPluralNoun(player)) print "Llevaremos";
				else print "Llevaré";
			3:
				print ":^";
			4:
				print ".^";
		}

	Jump:
		if (IsPluralNoun(player)) print "Saltaremos";
		else print "Saltaré";
		" en el sitio, sin ningún resultado.";

	JumpOver, Tie:
		print "No ";
		if (IsPluralNoun(player)) print "iremos a conseguir";
		else print "iré a conseguir";
		" nada así.";

	Kiss:
		print "No ";
		if (IsPluralNoun(player)) print "se nos ocurrirá";
		else print "se me ocurrirá";
		" hacer algo así en ese momento.";

	Listen:
		print "No ";
		if (IsPluralNoun(player)) print "escucharemos";
		else print "escucharé";
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
				if (IsPluralNoun(player)) print "llevaremos";
				else print "llevaré";
				print " puest", (o) x1;
			10:
				print " (que ";
				if (IsPluralNoun(player)) print "llevaremos";
				else print "llevaré";
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
				if (IsPluralNoun(player)) print "tendremos";
				else print "tendré";
 				" que cerrar ", (the) x1, ".";
			4:
				if (second) {
					"No parecerá", (n) x1, " encajar en la cerradura.";
				} else {
					if (IsPluralNoun(player)) print "Necesitaremos";
					else print "Necesitaré";
					" algún tipo de llave.";
				}
			5:
				if (second) {
					if (IsPluralNoun(player)) print "Cerraremos";
					else print "Cerraré";
					" ", (the) x1, " con ", (the) second, ".";
				} else {
					if (IsPluralNoun(player)) print "Echaremos";
					else print "Echaré";
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
					if (IsPluralNoun(player)) print "podremos";
					else print "podré";
					print " ver ";
				} else {
					if (IsPluralNoun(player)) print "Podremos";
					else print "Podré";
					print " ver ";
				}
				if (n==5) print "también ";
				WriteListFrom(child(x1),
					ENGLISH_BIT + WORKFLAG_BIT + RECURSE_BIT
					+ PARTINV_BIT + TERSE_BIT + CONCEAL_BIT);
				".";
			7:
				print "No ";
				if (IsPluralNoun(player)) print "observaremos";
				else print "observaré";
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
				if (IsPluralNoun(player)) print "veremos";
				else print "veré";
				" nada destacable.";
		}

	Miscellany:
		switch (n) {
			9:
				print "^¡";
				if (IsPluralNoun(player)) print "Nos habremos";
				else print "Me habré";
				" quedado a oscuras!";
			17:
				"Estrá demasiado oscuro como para poder ver algo.";
			18:
				if (IsPluralNoun(player)) print "nosotr", (o) player;
				else print "yo";
				print " mism", (o) player;
			19:
				"Tan buen aspecto como siempre.";
			26:
				print "(Primero ";
				if (IsPluralNoun(player)) print "trataremos";
				else print "trataré";
				" de ", (coge) "r ", (the) x1, ".)";
			32:
				print "No ";
				if (IsPluralNoun(player)) print "tendremos";
				else print "tendré";
				" eso.";
			44:
				if (action_to_be == ##Drop) {
					print "[No ";
					if (IsPluralNoun(player)) print "tendremos";
					else print "tendré";
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
				if (IsPluralNoun(player)) print "Abriremos";
				else print "Abriré";
				print " ", (the) x1, ", descubriendo ";
				if (WriteListFrom(child(x1),
					ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT) == 0) {
					print "que estará", (n) x1, " vací", (o) x1;
				}
				".";
			5:
				if (IsPluralNoun(player)) print "Abriremos";
				else print "Abriré";
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
				if (IsPluralNoun(player)) print "seremos capaces";
				else print "seré capaz";
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
				if (IsPluralNoun(player)) print "creeremos";
				else print "creeré";
				" que empujar", (lo) x1, " sirva de nada.";
			2:
				"Eso no será una dirección.";
			3:
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podré";
				" empujar", (lo) x1, " en esa dirección.";
		}

	PutOn:
		switch (n) {
			1:
				if (x1 has animate) {
					if (IsPluralNoun(player))
						"Antes tendremos que ", (coge)"r", (lo) x1,
						" y no sabremos si se irá", (n) x1, " a dejar.";
					else
						"Antes tendré que ", (coge)"r", (lo) x1,
						" y no sabré si se irá", (n) x1, " a dejar.";
				} else {
					if (IsPluralNoun(player)) print "Necesitaremos";
					else print "Necesitaré";
					" tener ", (the) x1, " para poder poner", (lo) x1,
					" donde fuese.";
				}
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podré";
				" poner un objeto sobre sí mismo.";
			3:
				"Poner cosas sobre ", (the) x1, " no irá a servir de nada.";
			4:
				if (IsPluralNoun(player)) print "Nos faltará";
				else print "Me faltará";
				" destreza.";
			5:
				print "(Primero ";
				if (IsPluralNoun(player)) print "nos ", (lo) x1, " quitaremos";
				else print "me ", (lo) x1, " quitaré";
				").^";
			6:
				"No quedará sitio en ", (the) x1, " para poner nada más.";
			7:
				"Hecho.";
			8:
				if (IsPluralNoun(player)) print "Colocaremos";
				else print "Colocaré";
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
				if (IsPluralNoun(player)) print "encontraremos";
				else print "encontraré";
				" nada interesante.";
			5:
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podré";
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
		if (IsPluralNoun(player)) print "podremos";
		else print "podré";
 		".";

	SetTo:
		"Eso no podrá regularse a ningún valor.";

	Show:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "tendremos";
				else print "tendré";
				" ", (the) x1, ".";
			2:
				"", (The) x1, " no mostrará", (n) x1, " ningún interés.";
		}

	Sing:
		if (IsPluralNoun(player)) print "Cantaremos";
		else print "Cantaré";
		" fatal.";

	Sleep:
		print "No ";
		if (IsPluralNoun(player)) print "estaremos";
		else print "estaré";
		" especialmente somnolient", (o) player, ".";

	Smell:
		print "No ";
		if (IsPluralNoun(player)) print "oleremos";
		else print "oleré";
		" nada extraño.";

	Squeeze:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "se nos ocurrirá";
				else print "se me ocurrirá";
				" hacer algo así.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "conseguiremos";
				else print "conseguiré";
				" nada haciendo eso.";
		}

	Swim:
		"No será el momento ni el lugar para ponerse a nadar.";

	Swing:
		print "No parecerá", (n) x1, " el lugar más adecuado en el que ";
		if (IsPluralNoun(player)) print "columpiarnos";
		else print "columpiarme";
		".";

	SwitchOff:
		switch (n) {
			1:
				"No será algo que se pueda apagar.";
			2:
				"Ya estará", (n) x1, "apagad", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Apagaremos";
				else print "Apagaré";
				" ", (the) x1, ".";
		}

	SwitchOn:
		switch (n) {
			1:
				"No será algo que se pueda encender.";
			2:
				"Ya estará", (n) x1, " encendid", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Encenderemos";
				else print "Encenderé";
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
				if (IsPluralNoun(player)) print "nos tendremos";
				else print "me tendré";
 				" a ", (string) YOURSELF__TX, ".";
			3:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creeremos";
				else print "creeré";
				" que ", (al) x1, " le", (s) x1, " gustase.";
			4:
				if (IsPluralNoun(player)) print "Tendremos";
				else print "Tendré";
				print " que ";
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "bajarnos";
					else print "bajarme";
				}
				else print "salir";
				"", (del) x1, " antes.";
			5:
				print "Ya ";
				if (IsPluralNoun(player)) print "tendremos";
				else print "tendré";
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
				if (IsPluralNoun(player)) print "podremos llevarnos";
				else print "podré llevarme";
				" aquello.";
			11:
				"", (The) x1, "estará", (n) x1, " fij", (o) x1,
				" en el sitio.";
			12:
				print "Ya ";
				if (IsPluralNoun(player)) print "tendremos";
				else print "tendré";
				" las manos ocupadas con demasiadas cosas.";
			13:
				print "(Primero ";
				if (IsPluralNoun(player)) print "colocaremos";
				else print "colocaré";
				" ", (the) x1, " en ", (the) SACK_OBJECT,
				" para hacer sitio).";
		}

	Taste:
		print "No ";
		if (IsPluralNoun(player)) print "saborearemos";
		else print "saborearé";
		" nada inesperado.";

	Tell:
		switch (n) {
			1:
				if (IsPluralNoun(player)) print "Hablaremos";
				else print "Hablaré";
				" sol", (o) player, " durante un rato.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "provocaremos";
				else print "provocaré";
				" ninguna reacción.";
		}

	Think:
		print "Si, eso ";
		if (IsPluralNoun(player)) print "intentaremos";
		else print "intentaré";
		".";

	ThrowAt:
		switch (n) {
			1:
				"No irá a servir de nada.";
			2:
				print "En el último momento ";
				if (IsPluralNoun(player)) print "nos echaremos";
				else print "me echaré";
				" atrás.";
		}

	Touch:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creeremos";
				else print "creeré";
				" que ", (al) x1, " le", (s) x1, " gustase.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "notaremos";
				else print "notaré";
				" nada extraño al tacto.";
			3:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creeremos";
				else print "creeré";
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
					if (IsPluralNoun(player)) print "Necesitaremos";
					else print "Necesitaré";
					" algún tipo de llave.";
				}
			4:
				if (IsPluralNoun(player)) print "Quitaremos";
				else print "Quitaré";
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
				if (IsPluralNoun(player)) print "tendremos";
				else print "tendré";
				" ", (contigo) player, ".";
			2:
				if (IsPluralNoun(player)) print "Nos sentiremos";
				else print "Me sentiré";
				" ridícul", (o) player, " agitando ", (the) x1, ".";
		}

	WaveHands:
		if (IsPluralNoun(player)) print "Nos encontraremos";
		else print "Me encontraré";
		" ridícul", (o) player, " gesticulando así.";

	Wear:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "podremos ponernos";
				else print "podré ponerme";
				" aquello.";
			2:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "tendremos";
				else print "tendré";
 				".";
			3:
				print "Ya ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "llevaremos";
				else print "llevaré";
				" puest", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Nos pondremos";
				else print "Me pondré";
				" ", (the) x1, ".";
		}

	default:
		ThirdPersonPast_ES(n, x1);

];

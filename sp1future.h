

!!==============================================================================
!!
!!	MENSAJES DE LA LIBRER�A EN ESPA�OL
!!	Narrador en primera persona, tiempo futuro
!!
!!==============================================================================
!!
!!	Archivo:		sp1future.inf
!!	Autor(es):		J. Francisco Mart�n <jfm.lisaso@gmail.com>
!!	Idioma:			ES (Espa�ol)
!!	Sistema:		Inform-INFSP 6
!!	Plataforma:		M�quina-Z/Glulx
!!	Versi�n:		0.0
!!	Fecha:			2018/06/08
!!
!!------------------------------------------------------------------------------
!!
!!	HISTORIAL DE VERSIONES
!!
!!	0.0: 2018/06/08	Versi�n en desarrollo.
!!
!!------------------------------------------------------------------------------
!!
!!	Copyright (c) 2018, J. Francisco Mart�n
!!
!!	Este programa es software libre: usted puede redistribuirlo y/o
!!	modificarlo bajo los t�rminos de la Licencia P�blica General GNU
!!	publicada por la Fundaci�n para el Software Libre, ya sea la versi�n
!!	3 de la Licencia, o (a su elecci�n) cualquier versi�n posterior.
!!
!!	Este programa se distribuye con la esperanza de que sea �til, pero
!!	SIN GARANT�A ALGUNA; ni siquiera la garant�a impl�cita MERCANTIL o
!!	de APTITUD PARA UN PROP�SITO DETERMINADO. Consulte los detalles de
!!	la Licencia P�blica General GNU para m�s informaci�n.
!!
!!	Deber�a haber recibido una copia de la Licencia P�blica General GNU
!!	junto a este programa. En caso contrario, consulte
!!	<http://www.gnu.org/licenses/>.
!!
!!------------------------------------------------------------------------------

[ FirstPersonFuture_ES n x1;

	Answer, Ask, AskFor:
		"No habr� respuesta.";

	Attack:
		if (x1 == player) {
			print "No ";
			if (IsPluralNoun(player)) print "nos iremos a autolesionar";
			else print "me ir� a autolesionar";
			" a prop�sito.";
		}
		print "No ir� a servir de nada tratar de ";
		LanguageVerb(verb_word);
		" ", (the) x1, ".";

	Blow:
		if (IsPluralNoun(player)) print "Nuestro";
		else print "Mi";
		" soplido no producir� ning�n efecto.";

	Burn:
		print "Esa ser� una idea peligrosa con la que no ";
		if (IsPluralNoun(player)) print "ir�amos a lograr";
		else print "ir�a a lograr";
		" nada en cualquier caso.";

	Buy:
		if (x1 == 0) "No habr� nada en venta.";
		else {
			print "No ";
			if (IsPluralNoun(player)) print "podremos";
			else print "podr�";
			" comprar ", (the) x1, ".";
		}

	Climb:
		print "No ser� algo a lo que ";
		if (IsPluralNoun(player)) print "podamos";
		else print "pueda";
		print " ";
		LanguageVerb(verb_word);
		".";

	Close:
		switch (n) {
			1:
				"No ser� algo que se pueda cerrar.";
			2:
				"Ya estar�", (n) x1, " cerrad", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Cerraremos";
				else print "Cerrar�";
				" ", (the) x1, ".";
		}

	Consult:
		print "No ";
		if (IsPluralNoun(player)) print "descubriremos";
		else print "descubrir�";
		" nada interesante en ", (the) x1, " sobre ese tema.";

	Cut:
		print "Cort�ndo", (lo) x1, " no ";
		if (IsPluralNoun(player)) print "iremos a lograr";
		else print "ir� a lograr";
		" gran cosa.";

	Dig:
		print "No ir� a servir de nada que ";
		if (IsPluralNoun(player)) print "nos pongamos";
		else print "me ponga";
		print " a ";
		LanguageVerb(verb_word);
		" all�.";

	Disrobe:
		switch (n) {
			1:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "llevaremos";
				else print "llevar�";
				" puest", (o) x1, ".";
			2:
				if (IsPluralNoun(player)) print "Nos quitaremos";
				else print "Me quitar�";
				" ", (the) x1, ".";
		}

	Drink:
		"Eso no parecer� potable.";

	Drop:
		switch (n) {
			1:
				print "Para poder dejar ", (the) x1, " ";
				if (IsPluralNoun(player)) print "deberemos";
				else print "deber�";
				" tener", (lo) x1, ".";
			2:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "tendremos";
				else print "tendr�";
				" ", (contigo) player, ".";
			3:
				print "(Primero ";
				if (IsPluralNoun(player)) print "nos quitaremos";
				else print "me quitar�";
				" ", (the) x1, ".)";
			4:
				"Dejad", (o) x1, ".";
		}

	Eat:
		switch (n) {
			1:
				"Eso no parecer� comestible.";
			2:
				if (IsPluralNoun(player)) print "Nos comeremos";
				else print "Me comer�";
				" ", (the) x1, ".";
		}

	EmptyT:
		switch (n) {
			1:
 				"", (The) x1, " no podr�", (n) x1, " tener cosas dentro.";
			2:
				print "No ";
 				if (IsPluralNoun(player)) print "podremos";
				else print "podr�";
				" hacerlo porque ", (the) x1, " estar�", (n) x1,
				" cerrad", (o) x1, ".";
			3:
				"", (The) x1, " ya estar�", (n) x1, " vac�", (o) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podr�";
				" vaciar un objeto sobre s� mismo.";
		}

	Enter:
		switch (n) {
			1:
				print "Ya ";
				if (IsPluralNoun(player)) print "estaremos";
				else print "estar�";
				print " ";
				if (x1 has supporter) print "sobre";
				else print "en";
				" ", (the) x1, ".";
			2:
				print "No ";
				if (IsPluralNoun(x1)) print "ser�n";
				else print "ser�";
				print " algo donde ";
				if (IsPluralNoun(player)) print "podamos";
				else print "pueda";
				print " ";
				LanguageVerb(verb_word);
				".";
			3:
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podr�";
				print " ";
				LanguageVerb(verb_word);
				print " en ", (the) x1, " porque estar�", (n) x1,
				" cerrad", (o) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podr�";
				print " ";
				LanguageVerb(verb_word);
				print " ah� mientras no ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "soltemos";
				else print "suelte";
				" primero.";
			5:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "Subiremos";
					else print "Subir�";
					print " ", (al) x1;
				} else {
					if (IsPluralNoun(player)) print "Entraremos";
					else print "Entrar�";
					print " en ", (the) x1;
				}
				".";
			6:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "(Nos bajaremos";
					else print "(Me bajar�";
				} else {
					if (IsPluralNoun(player)) print "(Saldremos";
					else print "(Saldr�";
				}
				" ", (del) x1, ").";
			7:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "(Nos subiremos";
					else print "(Me subir�";
					" ", (al) x1, ").^";
				} else if (x1 has container) {
					if (IsPluralNoun(player)) print "(Nos meteremos";
					else print "(Me meter�";
					" en ", (the) x1, ").^";
				} else {
					if (IsPluralNoun(player)) print "(Entraremos";
					else print "(Entrar�";
					" en ", (the) x1, ").^";
				}
		}

	Examine:
		switch (n) {
			1:
				print "Estar� demasiado oscuro. No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podr�";
				" ver nada.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "observaremos";
				else print "observar�";
				"  nada especial en ", (the) x1, ".";
			3:
				print (The) x1, " estar�", (n) x1;
				if (x1 has on) print " encendid", (o) x1;
				else print " apagad", (o) x1;
				".";
		}

	Exit:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "estaremos";
				else print "estar�";
 				print " en ning�n sitio del que ";
				if (IsPluralNoun(player)) print "debi�semos";
				else print "debiese";
				print " ";
				LanguageVerb(verb_word);
				".";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podr�";
				" salir ", (del) x1, " porque estar�", (n) x1,
				" cerrad", (o) x1, ".";
			3:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "Bajaremos";
					else print "Bajar�";
				} else {
					if (IsPluralNoun(player)) print "Saldremos";
					else print "Saldr�";
				}
				" ", (del) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podr�";
				print ". No ";
				if (IsPluralNoun(player)) print "estaremos";
				else print "estar�";
				print " ";
				if (x1 has supporter) print "encima";
				else print "dentro";
				" ", (del) x1, ".";
		}

	Fill:
		print "No ";
		if (IsPluralNoun(player)) print "podremos";
		else print "podr�";
		" llenar", (lo) x1, ".";

	GetOff:
		print "No ";
		if (IsPluralNoun(player)) print "podremos";
		else print "podr�";
		print ". No ";
		if (IsPluralNoun(player)) print "estaremos";
		else print "estar�";
		" en ", (the) x1, ".";

	Give:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "tendremos";
				else print "tendr�";
				" ", (the) x1, ".";
			2:
				if (IsPluralNoun(player)) print "Manosearemos";
				else print "Manosear�";
				" ", (the) x1, " durante unos momentos, sin conseguir nada.";
			3:
				"", (The) x1, " no parecer�", (n) x1, " interesad", (o) x1, ".";
		}

	Go:
		switch (n) {
			1:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Tendremos";
				else print "Tendr�";
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
				else print "podr�";
				" ir por ah�.";
			3:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Seremos incapaces";
				else print "Ser� incapaz";
				" de trepar por ", (the) x1, ".";
			4:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Seremos incapaces";
				else print "Ser� incapaz";
				" de bajar por ", (the) x1, ".";
			5:
				PronounNotice(x1);
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podr�";
				" pasar a trav�s ", (del) x1, ".";
			6:
				PronounNotice(x1);
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podr�";
				" ir porque ", (the) x1, " no llevar�", (n) x1,
				" a ning�n sitio.";
		}

	Insert:
		switch (n) {
			1:
				if (x1 has animate) {
					if (IsPluralNoun(player))
						"Antes tendremos que ", (coge)"r", (lo) x1,
						" y no sabremos si se ir�", (n) x1, " a dejar.";
					else
						"Antes tendr� que ", (coge)"r", (lo) x1,
						" y no sabr� si se ir�", (n) x1, " a dejar.";
				} else {
					if (IsPluralNoun(player)) print "Necesitaremos";
					else print "Necesitar�";
					" tener ", (the) x1, " para poder meter", (lo) x1,
					" donde sea.";
				}
			2:
				"No se podr�n meter cosas dentro ", (del) x1, ".";
			3:
				"", (The) x1, " estar�", (n) x1, " cerrad", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Tendremos que quit�rnos";
				else print "Tendr� que quit�rme";
				"", (lo) x1, " antes.";
			5:
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podr�";
				" poner un objeto dentro de s� mismo.";
			6:
				print "(Primero ";
				if (IsPluralNoun(player)) print "nos ", (lo) x1, " quitaremos";
				else print "me ", (lo) x1, " quitar�";
				").^";
			7:
				"No quedar� sitio en ", (the) x1, ".";
			8:
				"Hecho.";
			9:
				if (IsPluralNoun(player)) print "Meteremos";
				else print "Meter�";
				" ", (the) x1, " dentro ", (del) second, ".";
		}

	Inv:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "llevaremos";
				else print "llevar�";
				" nada.";
			2:
				if (IsPluralNoun(player)) print "Llevaremos";
				else print "Llevar�";
			3:
				print ":^";
			4:
				print ".^";
		}

	Jump:
		if (IsPluralNoun(player)) print "Saltaremos";
		else print "Saltar�";
		" en el sitio, sin ning�n resultado.";

	JumpOver, Tie:
		print "No ";
		if (IsPluralNoun(player)) print "iremos a conseguir";
		else print "ir� a conseguir";
		" nada as�.";

	Kiss:
		print "No ";
		if (IsPluralNoun(player)) print "se nos ocurrir�";
		else print "se me ocurrir�";
		" hacer algo as� en ese momento.";

	Listen:
		print "No ";
		if (IsPluralNoun(player)) print "escucharemos";
		else print "escuchar�";
		" nada fuera de lo com�n.";

	ListMiscellany:
		switch (n) {
			2:
				print " (que estar�", (n) x1, " cerrad", (o) x1, ")";
			4:
				print " (que estar�", (n) x1, " vac�", (o) x1, ")";
			6:
				print " (que estar�", (n) x1, " cerrad", (o) x1,
				" y vac�", (o) x1, ")";
			8:
				print " (alumbrando y que ";
				if (IsPluralNoun(player)) print "llevaremos";
				else print "llevar�";
				print " puest", (o) x1;
			10:
				print " (que ";
				if (IsPluralNoun(player)) print "llevaremos";
				else print "llevar�";
				print " puest", (o) x1;
			11:
				print " (que estar�", (n) x1, " ";
			17:
				print " (que estar�", (n) x1, " vac�", (o) x1, ")";
			18:
				print " que contendr�", (n) x1, " ";
			default:
				ThirdPersonPast_ES(n, x1);
		}

	Lock:
		switch (n) {
			1:
				"No parecer�", (n) x1, " tener ning�n tipo de cerrojo.";
			2:
				if (x1 provides with_key) {
					"", (The) x1, " ya estar�", (n) x1, " cerrad", (o) x1,
					" con llave.";
				}
				else {
					"", (The) x1, " ya tendr�", (n) x1, " echado el cerrojo.";
				}
			3:
				print "Primero ";
				if (IsPluralNoun(player)) print "tendremos";
				else print "tendr�";
 				" que cerrar ", (the) x1, ".";
			4:
				if (second) {
					"No parecer�", (n) x1, " encajar en la cerradura.";
				} else {
					if (IsPluralNoun(player)) print "Necesitaremos";
					else print "Necesitar�";
					" alg�n tipo de llave.";
				}
			5:
				if (second) {
					if (IsPluralNoun(player)) print "Cerraremos";
					else print "Cerrar�";
					" ", (the) x1, " con ", (the) second, ".";
				} else {
					if (IsPluralNoun(player)) print "Echaremos";
					else print "Echar�";
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
					if (IsPluralNoun(player)) print "podremos";
					else print "podr�";
					print " ver ";
				} else {
					if (IsPluralNoun(player)) print "Podremos";
					else print "Podr�";
					print " ver ";
				}
				if (n==5) print "tambi�n ";
				WriteListFrom(child(x1),
					ENGLISH_BIT + WORKFLAG_BIT + RECURSE_BIT
					+ PARTINV_BIT + TERSE_BIT + CONCEAL_BIT);
				".";
			7:
				print "No ";
				if (IsPluralNoun(player)) print "observaremos";
				else print "observar�";
				" nada digno de menci�n al mirar hacia ", (the) x1, ".";
			default:
				ThirdPersonPast_ES(n, x1);
		}

	LookUnder:
		switch (n) {
			1:
				"Estar� demasiado oscuro como para poder ver algo.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "veremos";
				else print "ver�";
				" nada destacable.";
		}

	Miscellany:
		switch (n) {
			9:
				print "^�";
				if (IsPluralNoun(player)) print "Nos habremos";
				else print "Me habr�";
				" quedado a oscuras!";
			17:
				"Estr� demasiado oscuro como para poder ver algo.";
			18:
				if (IsPluralNoun(player)) print "nosotr", (o) player;
				else print "yo";
				print " mism", (o) player;
			19:
				"Tan buen aspecto como siempre.";
			26:
				print "(Primero ";
				if (IsPluralNoun(player)) print "trataremos";
				else print "tratar�";
				" de ", (coge) "r ", (the) x1, ".)";
			32:
				print "No ";
				if (IsPluralNoun(player)) print "tendremos";
				else print "tendr�";
				" eso.";
			44:
				if (action_to_be == ##Drop) {
					print "[No ";
					if (IsPluralNoun(player)) print "tendremos";
					else print "tendr�";
					print " nada que ";
					LanguageVerb(verb_word);
					"].";
				} else {
					print "[No habr� nada que ";
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
				"No ser� algo que se pueda abrir.";
			2:
				"Estar�", (n) x1, " cerrad", (o) x1, " con llave.";
			3:
				"Ya estar�", (n) x1, " abiert", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Abriremos";
				else print "Abrir�";
				print " ", (the) x1, ", descubriendo ";
				if (WriteListFrom(child(x1),
					ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT) == 0) {
					print "que estar�", (n) x1, " vac�", (o) x1;
				}
				".";
			5:
				if (IsPluralNoun(player)) print "Abriremos";
				else print "Abrir�";
				" ", (the) x1, ".";
		}

	Order:
		"", (The) x1, " tendr�", (n) x1, " mejores cosas que hacer.";

	Pray:
		"La fe tal vez podr� resultar �til en una ocasi�n diferente.";

	Pull, Push, Turn:
		switch (n) {
			1:
				"Estar�", (n) x1, " firmemente sujet", (o) x1, ".";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "seremos capaces";
				else print "ser� capaz";
				".";
			3:
				"No ocurrir� nada, aparentemente.";
			4:
				"Eso ser�, como poco, maleducado.";
		}

	PushDir:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creeremos";
				else print "creer�";
				" que empujar", (lo) x1, " sirva de nada.";
			2:
				"Eso no ser� una direcci�n.";
			3:
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podr�";
				" empujar", (lo) x1, " en esa direcci�n.";
		}

	PutOn:
		switch (n) {
			1:
				if (x1 has animate) {
					if (IsPluralNoun(player))
						"Antes tendremos que ", (coge)"r", (lo) x1,
						" y no sabremos si se ir�", (n) x1, " a dejar.";
					else
						"Antes tendr� que ", (coge)"r", (lo) x1,
						" y no sabr� si se ir�", (n) x1, " a dejar.";
				} else {
					if (IsPluralNoun(player)) print "Necesitaremos";
					else print "Necesitar�";
					" tener ", (the) x1, " para poder poner", (lo) x1,
					" donde fuese.";
				}
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podr�";
				" poner un objeto sobre s� mismo.";
			3:
				"Poner cosas sobre ", (the) x1, " no ir� a servir de nada.";
			4:
				if (IsPluralNoun(player)) print "Nos faltar�";
				else print "Me faltar�";
				" destreza.";
			5:
				print "(Primero ";
				if (IsPluralNoun(player)) print "nos ", (lo) x1, " quitaremos";
				else print "me ", (lo) x1, " quitar�";
				").^";
			6:
				"No quedar� sitio en ", (the) x1, " para poner nada m�s.";
			7:
				"Hecho.";
			8:
				if (IsPluralNoun(player)) print "Colocaremos";
				else print "Colocar�";
				" ", (the) x1, " sobre ", (the) second, ".";
		}

	Remove:
		switch (n) {
			1:
				"Por desgracia ", (the) parent(x1), " estar�", (n) parent(x1),
				" cerrad", (o) parent(x1), ".";
			2:
				if (second has animate)
					"�Pero si no ", (lo) x1, " tendr�", (n) second,"!";
				else
					"�Pero si no estar�", (n) x1, " ah� en ese momento!";
			3:
				if (verb_word == 'quita') "Quitad", (o) x1, ".";
				"Sacad", (o) x1, ".";
		}

	Rub:
		"Ya estar�", (n) x1, " bastante limpi", (o) x1, ".";

	Search:
		switch (n) {
			1:
				"Estar� demasiado oscuro como para poder ver algo.";
			2:
				"No habr� nada sobre ", (the) x1, ".";
			3:
				print "Sobre ", (the) x1;
				WriteListFrom(child(x1),
					ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT + ISARE_BIT);
				".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "encontraremos";
				else print "encontrar�";
				" nada interesante.";
			5:
				print "No ";
				if (IsPluralNoun(player)) print "podremos";
				else print "podr�";
				" ver lo que hay dentro ", (del) x1, " porque
				estar�", (n) x1, " cerrad", (o) x1, ".";
			6:
				"", (The) x1, " estar�", (n) x1, " vac�", (o) x1, ".";
			7:
				print "En ", (the) x1;
				WriteListFrom(child(x1),
					TERSE_BIT + ENGLISH_BIT + ISARE_BIT + CONCEAL_BIT);
				".";
		}

	Set:
		print "No, no ";
		if (IsPluralNoun(player)) print "podremos";
		else print "podr�";
 		".";

	SetTo:
		"Eso no podr� regularse a ning�n valor.";

	Show:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "tendremos";
				else print "tendr�";
				" ", (the) x1, ".";
			2:
				"", (The) x1, " no mostrar�", (n) x1, " ning�n inter�s.";
		}

	Sing:
		if (IsPluralNoun(player)) print "Cantaremos";
		else print "Cantar�";
		" fatal.";

	Sleep:
		print "No ";
		if (IsPluralNoun(player)) print "estaremos";
		else print "estar�";
		" especialmente somnolient", (o) player, ".";

	Smell:
		print "No ";
		if (IsPluralNoun(player)) print "oleremos";
		else print "oler�";
		" nada extra�o.";

	Squeeze:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "se nos ocurrir�";
				else print "se me ocurrir�";
				" hacer algo as�.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "conseguiremos";
				else print "conseguir�";
				" nada haciendo eso.";
		}

	Swim:
		"No ser� el momento ni el lugar para ponerse a nadar.";

	Swing:
		print "No parecer�", (n) x1, " el lugar m�s adecuado en el que ";
		if (IsPluralNoun(player)) print "columpiarnos";
		else print "columpiarme";
		".";

	SwitchOff:
		switch (n) {
			1:
				"No ser� algo que se pueda apagar.";
			2:
				"Ya estar�", (n) x1, "apagad", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Apagaremos";
				else print "Apagar�";
				" ", (the) x1, ".";
		}

	SwitchOn:
		switch (n) {
			1:
				"No ser� algo que se pueda encender.";
			2:
				"Ya estar�", (n) x1, " encendid", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Encenderemos";
				else print "Encender�";
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
				else print "me tendr�";
 				" a ", (string) YOURSELF__TX, ".";
			3:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creeremos";
				else print "creer�";
				" que ", (al) x1, " le", (s) x1, " gustase.";
			4:
				if (IsPluralNoun(player)) print "Tendremos";
				else print "Tendr�";
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
				else print "tendr�";
				" ", (the) x1, ".";
			6:
				"Parecer�", (n) noun, " pertenecer ", (al) x1, ".";
			7:
				"Parecer�", (n) noun, " formar parte ", (del) x1, ".";
			8:
				"No estar�", (n) x1, " disponible", (s) x1, ".";
			9:
				"", (The) x1, " no estar�", (n) x1, " abiert", (o) x1, ".";
			10:
				print "Dif�cilmente ";
				if (IsPluralNoun(player)) print "podremos llevarnos";
				else print "podr� llevarme";
				" aquello.";
			11:
				"", (The) x1, "estar�", (n) x1, " fij", (o) x1,
				" en el sitio.";
			12:
				print "Ya ";
				if (IsPluralNoun(player)) print "tendremos";
				else print "tendr�";
				" las manos ocupadas con demasiadas cosas.";
			13:
				print "(Primero ";
				if (IsPluralNoun(player)) print "colocaremos";
				else print "colocar�";
				" ", (the) x1, " en ", (the) SACK_OBJECT,
				" para hacer sitio).";
		}

	Taste:
		print "No ";
		if (IsPluralNoun(player)) print "saborearemos";
		else print "saborear�";
		" nada inesperado.";

	Tell:
		switch (n) {
			1:
				if (IsPluralNoun(player)) print "Hablaremos";
				else print "Hablar�";
				" sol", (o) player, " durante un rato.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "provocaremos";
				else print "provocar�";
				" ninguna reacci�n.";
		}

	Think:
		print "Si, eso ";
		if (IsPluralNoun(player)) print "intentaremos";
		else print "intentar�";
		".";

	ThrowAt:
		switch (n) {
			1:
				"No ir� a servir de nada.";
			2:
				print "En el �ltimo momento ";
				if (IsPluralNoun(player)) print "nos echaremos";
				else print "me echar�";
				" atr�s.";
		}

	Touch:
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creeremos";
				else print "creer�";
				" que ", (al) x1, " le", (s) x1, " gustase.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "notaremos";
				else print "notar�";
				" nada extra�o al tacto.";
			3:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creeremos";
				else print "creer�";
				" que algo as� pueda servir de nada.";
    	}

	Unlock:
		switch (n) {
			1:
				"No parecer�", (n) x1, " tener ning�n tipo de cerrojo.";
			2:
				"", (The) x1, " ya tendr�", (n) x1, " abierto el cerrojo.";
			3:
				if (second) {
					"No parecer�", (n) x1, " encajar en la cerradura.";
				} else {
					if (IsPluralNoun(player)) print "Necesitaremos";
					else print "Necesitar�";
					" alg�n tipo de llave.";
				}
			4:
				if (IsPluralNoun(player)) print "Quitaremos";
				else print "Quitar�";
				print " el cerrojo ", (al) x1;
				if (second) print " con ", (the) second;
				".";
		}

	Wait:
		"Pasar� el tiempo...";

	Wake:
		"La cruda realidad es que eso no ser� un sue�o.";

	WakeOther:
		"No parecer� necesario hacer eso.";

	Wave:
		switch (n) {
			1:
				print "No l", (o) x1, " ";
				if (IsPluralNoun(player)) print "tendremos";
				else print "tendr�";
				" ", (contigo) player, ".";
			2:
				if (IsPluralNoun(player)) print "Nos sentiremos";
				else print "Me sentir�";
				" rid�cul", (o) player, " agitando ", (the) x1, ".";
		}

	WaveHands:
		if (IsPluralNoun(player)) print "Nos encontraremos";
		else print "Me encontrar�";
		" rid�cul", (o) player, " gesticulando as�.";

	Wear:
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "podremos ponernos";
				else print "podr� ponerme";
				" aquello.";
			2:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "tendremos";
				else print "tendr�";
 				".";
			3:
				print "Ya ", (lo) x1;
				if (IsPluralNoun(player)) print "llevaremos";
				else print "llevar�";
				" puest", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Nos pondremos";
				else print "Me pondr�";
				" ", (the) x1, ".";
		}

	default:
		ThirdPersonPast_ES(n, x1);

];
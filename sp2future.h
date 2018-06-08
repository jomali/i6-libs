
[ SecondPersonFuture_ES n x1;

	Answer, Ask, AskFor:
		"No habrá respuesta.";

	!! Ask: @see Answer

	!! AskFor: @see Answer

	Attack:
		if (x1 == player) {
			print "No ";
			if (IsPluralNoun(player)) print "os iréis a autolesionar";
			else print "te irás a autolesionar";
			" a propósito.";
		}
		print "No servirá de nada ";
		LanguageVerb(verb_word);
		" ", (al) x1, ".";

	Blow:
		if (IsPluralNoun(player)) print "Nuestro";
		else print "Mi";
		" soplido no producirá ningún efecto.";

	default:
		ThirdPersonPast_ES(n, x1);
];

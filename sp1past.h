
[ FirstPersonPast_ES n x1;

	Answer, Ask, AskFor:
		"No había respuesta.";

	!! Ask: @see Answer

	!! AskFor: @see Answer

	Attack:
		if (x1 == player) {
			print "No ";
			if (IsPluralNoun(player)) print "nos hubiésemos autolesionado";
			else print "me hubiese autolesionado";
			" a propósito.";
		}
		print "No hubiese servido de nada ";
		LanguageVerb(verb_word);
		" ", (al) x1, ".";

	Blow:
		if (IsPluralNoun(player)) print "Nuestro";
		else print "Mi";
		" soplido no produjo ningún efecto.";

	default:
		ThirdPersonPast_ES(n, x1);
];


[ FirstPersonPresent_ES n x1;

	Answer, Ask, AskFor:
		"No hay respuesta.";

	!! Ask: @see Answer

	!! AskFor: @see Answer

	Attack:
		if (x1 == player) {
			print "No ";
			if (IsPluralNoun(player)) print "nos autolesionaríamos";
			else print "me autolesionaría";
			" a propósito.";
		}
		print "No serviría de nada ";
		LanguageVerb(verb_word);
		" ", (al) x1, ".";

	Blow:
		if (IsPluralNoun(player)) print "Nuestro";
		else print "Mi";
		" soplido no produce ningún efecto.";

	default:
		ThirdPersonPast_ES(n, x1);
];



!!==============================================================================
!!
!!	MENSAJES DE LA LIBRERÍA EN ESPAÑOL
!!	Narrador en tercera persona, tiempo pasado
!!
!!==============================================================================
!!
!!	Archivo:		sp3past.inf
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
!!
!!	La librería de mensajes se basa en la librería española para Inform
!!	'Spanish.h', de Sarganar. Además de las modificaciones en las inflexiones
!!	de persona y tiempo, se han modificado los contenidos de los mensajes para
!!	las siguientes acciones:
!!
!!	-	Attack
!!	-	Burn
!!	-	Buy
!!	-	Climb
!!	-	Cut
!!	-	Dig
!!	-	Disrobe
!!	-	Drop
!!	-	Eat
!!	-	EmptyT
!!	-	Enter
!!	-	GetOff
!!	-	Give
!!	-	Go
!!	-	Kiss
!!	-	LookUnder
!!
!!------------------------------------------------------------------------------

[ ThirdPersonPast_ES n x1
	i;

	Answer, Ask, AskFor:
		"No había respuesta.";

	!! Ask: @see Answer

	!! AskFor: @see Answer

	Attack:
		if (x1 == player) {
			print "No ";
			if (IsPluralNoun(player)) print "se hubiesen autolesionado";
			else print "se hubiese autolesionado";
			" a propósito.";
		}
		print "No hubiese servido de nada tratar de ";
		LanguageVerb(verb_word);
		" ", (the) x1, ".";

	Blow:
		if (IsPluralNoun(player)) print "Su";
		else print "Su";
		" soplido no produjo ningún efecto.";

	Burn:
		print "Aquella era una idea peligrosa con la que no ";
		if (IsPluralNoun(player)) print "hubiesen logrado";
		else print "hubiese logrado";
		" nada en cualquier caso.";

	Buy:
		if (x1 == 0) "No había nada en venta.";
		else {
			print "No ";
			if (IsPluralNoun(player)) print "podían";
			else print "podía";
			" comprar ", (the) x1, ".";
		}

	Climb:
		print "No era algo a lo que ";
		if (IsPluralNoun(player)) print "pudiesen";
		else print "pudiese";
		print " ";
		LanguageVerb(verb_word);
		".";

	Close:
		!!	1:	Error. El objeto no es *openable*.
		!!	2:	Error. El objeto está cerrado.
		!!	3:	Mensaje cuando se cierra el objeto.
		switch (n) {
			1:
				"No era algo que se pudiese cerrar.";
			2:
				"Ya estaba", (n) x1, " cerrad", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Cerraron";
				else print "Cerró";
				" ", (the) x1, ".";
		}

	CommandsOff:
		switch (n) { ![6/11]
			1:
				"[Grabación de órdenes finalizada.]";
			#Ifdef TARGET_GLULX;
			2:
				"[Grabación de órdenes ya finalizada.]";
			#Endif; ! TARGET_
		}

	CommandsOn:
		switch (n) { ![6/11]
			1:
				"[Grabación de órdenes activada.]";
			#Ifdef TARGET_GLULX;
			2:
				"[Órdenes relanzadas.]";
			3:
				"[Grabación de órdenes ya activada.]";
			4:
				"[Fallo en la grabación de órdenes.]";
			#Endif; ! TARGET_
		}

	CommandsRead:
		switch (n) { ![6/11]
			1:
				"[Reejecutando órdenes...]";
			#Ifdef TARGET_GLULX;
			2:
				"[Las órdenes ya están siendo relanzadas.]";
			3:
				"[Fallo en la reejecución de órdenes: grabación en curso.]";
			4:
				"[Fallo en la reejecución de órdenes.]";
			5:
				"[Reejecución de órdenes: fin del proceso.]";
			#Endif; ! TARGET_
		}

	Consult:
		print "No ";
		if (IsPluralNoun(player)) print "descubrieron";
		else print "descubrió";
		" nada interesante en ", (the) x1, " sobre aquel tema.";

	Cut:
		print "Cortándo", (lo) x1, " no ";
		if (IsPluralNoun(player)) print "hubiesen logrado";
		else print "hubiese logrado";
		" gran cosa.";

	Dig:
		print "No hubiese servido de nada que ";
		if (IsPluralNoun(player)) print "se pusiesen";
		else print "se pusiese";
		print " a ";
		LanguageVerb(verb_word);
		" allí.";

	Disrobe:
		!!	1:	Error. El protagonista no lleva el objeto puesto.
		!!	2:	Mensaje cuando el protagonista se quita el objeto.
		switch (n) {
			1:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "llevaban";
				else print "llevaba";
				" puest", (o) x1, ".";
			2:
				if (IsPluralNoun(player)) print "Se quitaron";
				else print "Se quitó";
				" ", (the) x1, ".";
		}

	Drink:
		"Aquello no parecía potable.";

	Drop:
		!!	1:	Error, el objeto dejado no está en poder del protagonista,
		!!		pero está en la localidad.
		!!	2:	Error, el objeto dejado no está en poder del protagonista ni en
		!!		la localidad,
		!!	3:	Aviso, el objeto era una prenda que el protagonista llevaba
		!!		puesta y la librería va a quitársela automáticamente para poder
		!!		dejarla.
		!!	4:	Éxito.
		switch (n) {
			1:
				print "Para poder dejar ", (the) x1, " ";
				if (IsPluralNoun(player)) print "hubiesen debido";
				else print "hubiese debido";
				" tener", (lo) x1, ".";
			2:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "tenían";
				else print "tenía";
				" ", (contigo) player, ".";
			3:
				print "(Primero ";
				if (IsPluralNoun(player)) print "se quitaron";
				else print "se quitó";
				" ", (the) x1, ".)";
			4:
				"Dejad", (o) x1, ".";
		}

	Eat:
		!!	1:	Error, el objeto no tiene el atributo "comestible".
		!!	2:	Éxito. [NOTA: la librería permite por defecto comerse
		!!		cualquier cosa que tenga el atributo "comestible", pero la
		!!		única acción que provoca esto es que el objeto en cuestión
		!!		desaparece del juego al ser comido.]
		switch (n) {
			1:
				"Aquello no parecía comestible.";
			2:
				if (IsPluralNoun(player)) print "Se comieron";
				else print "Se comió";
				" ", (the) x1, ".";
		}

	EmptyT:
		!!	1:	Error, el usuario intenta vaciar un objeto en otro que no es un
		!!		recipiente.
		!!	2:	Error, el usuario intenta vaciar un objeto sobre un recipiente
		!!		cerrado.
		!!	3:	Error, el usuario intenta vaciar un objeto que no tiene nada
		!!		dentro.
		!!	4:	Error, el usuario intenta vaciar un objeto sobre sí mismo.
		!!
		!! [NOTA: No hay mensajes de éxito para esta acción, ya que en caso
		!! de haber superado los test anteriores, la librería genera
		!! finalmente la acción ##Transfer, la cuál, a su vez, generará la
		!! acción ##PutOn o ##Insert, según el segundo objeto sea soporte o
		!! recipiente. Por tanto los mensajes de éxito serán los de las
		!! acciones ##PutOn o ##Insert.]
		switch (n) {
			1:
 				"", (The) x1, " no podía", (n) x1, " tener cosas dentro.";
			2:
				print "No ";
 				if (IsPluralNoun(player)) print "podían";
				else print "podía";
				" hacerlo porque ", (the) x1, " estaba", (n) x1,
				" cerrad", (o) x1, ".";
			3:
				"", (The) x1, " ya estaba", (n) x1, " vací", (o) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podían";
				else print "podía";
				" vaciar un objeto sobre sí mismo.";
		}

	Enter:
		! [infsp] GoIn (Meterse) se cambió por Enter.
		!! CUIDADO. La acción Meterse se genera en muy diversas
		!! circunstancias: VETE HACIA EL PUENTE, VETE AL PUENTE, VETE POR
		!! EL PUENTE, PASA POR EL PUENTE, ENTRA EN EL PUENTE, ENTRA AL
		!! PUENTE, CRUZA EL PUENTE, CRUZA POR EL PUENTE, METETE EN EL
		!! PUENTE, METETE POR EL PUENTE, ATRAVIESA EL PUENTE, BAJA POR EL
		!! PUENTE.  Todas ellas generarían la acción <Meterse Puente>
		!!
		!! Además, los intentos de entrar en un "entrable", también, como
		!! por ejemplo: SIENTATE EN EL BANCO, ECHATE EN EL BANCO, SUBETE AL
		!! BANCO, SUBETE EN EL BANCO, SUBE AL BANCO, SUBE POR EL BANCO,
		!! SALTA AL BANCO. Todas ellas generarían <Meterse Banco>
		!!
		!! Puesto que hay muchos verbos diferentes que dan lugar a la misma
		!! acción, es necesaria alguna forma de imprimir qué verbo concreto
		!! ha sido el que la ha desencadenado, para poder generar mensajes
		!! como "No puedes entrar ahi", "No puedes sentarte ahi", "No
		!! puedes subirte ahi", etc.. según el verbo usado. Para esto puede
		!! usarse una llamada a IdiomaVerbo(palabra_verbo). palabra_verbo
		!! contiene el verbo usado por el usuario (convertido en forma
		!! imperativa), y IdiomaVerbo lo que hace es imprimir la forma
		!! infinitiva.
		!!
		!! Mensajes que puede generar esta acción:
		!!	1:	Error, el protagonista ya está en/sobre el objeto.
		!!	2:	Error, el objeto al que intenta entrar/subirse el usuario
		!!		no tiene el atributo "enterable".
		!!	3:	Error, el objeto al que intenta entrar/subirse el usuario tiene
		!!		los atributos "container" y "enterable", pero está cerrado.
		!!	4:	Error, el objeto al que intenta entrar/subirse el usuario está
		!!		en poder del propio usuario.
		!!	5:	Éxito, el usuario entra/sube al objeto.
		!!	6:	Aviso, el usuario estaba en otro objeto, la lib. intentará la
		!!		acción SALIR automáticamente antes de reintentar entrar el
		!!		nuevo objeto.
		!!	7:	Aviso, el objeto al que intenta entrar/subirse el usuario está
		!!		dentro de otros objeto. La lib. intentará automáticamente meter
		!!		al usuario en el objeto desde el cual pueda acceder al que el
		!!		usuario le ha indicado.
		switch (n) {
			1:
				print "Ya ";
				if (IsPluralNoun(player)) print "estaban";
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
				if (IsPluralNoun(player)) print "pudiesen";
				else print "pudiese";
				print " ";
				LanguageVerb(verb_word);
				".";
			3:
				print "No ";
				if (IsPluralNoun(player)) print "podían";
				else print "podía";
				print " ";
				LanguageVerb(verb_word);
				print " en ", (the) x1, " porque estaba", (n) x1,
				" cerrad", (o) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "iban a poder";
				else print "iba a poder";
				print " ";
				LanguageVerb(verb_word);
				print " ahí mientras no ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "soltasen";
				else print "soltase";
				" primero.";
			5:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "Subieron";
					else print "Subió";
					print " ", (al) x1;
				} else {
					if (IsPluralNoun(player)) print "Entraron";
					else print "Entró";
					print " en ", (the) x1;
				}
				".";
			6:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "(Se bajaron";
					else print "(Se bajó";
				} else {
					if (IsPluralNoun(player)) print "(Salieron";
					else print "(Salió";
				}
				" ", (del) x1, ").";
			7:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "(Se subieron";
					else print "(Se subió";
					" ", (al) x1, ").^";
				} else if (x1 has container) {
					if (IsPluralNoun(player)) print "(Se metieron";
					else print "(Se metió";
					" en ", (the) x1, ").^";
				} else {
					if (IsPluralNoun(player)) print "(Entraron";
					else print "(Entró";
					" en ", (the) x1, ").^";
				}
		}

	Examine:
		!!	1:	Error, el usuario intenta examinar un objeto, pero está a
		!!		oscuras.
		!!	2:	Éxito, pero el objeto examinado no tiene descripcion
		!!	3:	Éxito, pero el objeto examinado no tiene descripcion, aunque
		!!		tiene el atributo conmutable, por lo que la librería genera
		!!		este mensaje para indicar si está apagado o encendido.
		switch (n) {
			1:
				print "Estaba demasiado oscuro. No ";
				if (IsPluralNoun(player)) print "podían";
				else print "podía";
				" ver nada.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "observaron";
				else print "observó";
				"  nada especial en ", (the) x1, ".";
			3:
				print (The) x1, " estaba", (n) x1;
				if (x1 has on) print " encendid", (o) x1;
				else print " apagad", (o) x1;
				".";
		}

	Exit:
		!!	1:	Error, el usuario no está subido/sentado/metido en ningún
		!!		objeto. [Nota, si la localidad tiene la propiedad "afuera",
		!!		entonces la acción Salir lo sacará de la localidad. En caso
		!!		contrario es cuando se genera este error.]
		!!	2:	Error, el usuario está dentro de un recipiente cerrado.
		!!	3:	Éxito, el usuario sale/baja del objeto
		!!	4:	Error, más específico. [6/11]
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "estaban";
				else print "estaba";
 				print " en ningún sitio del que ";
				if (IsPluralNoun(player)) print "debiesen";
				else print "debiese";
				print " ";
				LanguageVerb(verb_word);
				".";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podían";
				else print "podía";
				" salir ", (del) x1, " porque estaba", (n) x1,
				" cerrad", (o) x1, ".";
			3:
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "Bajaron";
					else print "Bajó";
				} else {
					if (IsPluralNoun(player)) print "Salieron";
					else print "Salió";
				}
				" ", (del) x1, ".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "podían";
				else print "podía";
				print ". No ";
				if (IsPluralNoun(player)) print "estaban";
				else print "estaba";
				print " ";
				if (x1 has supporter) print "encima";
				else print "dentro";
				" ", (del) x1, ".";
		}

	Fill:
		print "No ";
		if (IsPluralNoun(player)) print "podían";
		else print "podía";
		" llenar", (lo) x1, ".";

	FullScore:
		!! Puntuación en modo "explicativo". Puede activarse porque el
		!! usuario lo pida con el verbo "PUNTUACION LARGA" o porque el
		!! relato haya terminado (y la constante HAY_TAREAS esté definida).
		!!
		!!	1:	Texto introductorio al desglose de puntos
		!!	2:	Texto de objetos importantes (los que tienen el atributo
		!!		"valepuntos")
		!!	3:	Texto de lugares importantes (los que tienen el atributo
		!!		"valepuntos")
		!!	4:	Texto final, tras la suma total impresa por la librería
		switch (n) {
			1:
				if (deadflag) print "La puntuación se desglosó ";
				else          print "La puntuación se desglosa ";
				"de la siguiente manera:^";
			2:
				"por encontrar objetos importantes";
			3:
				"por visitar lugares importantes";
			4:
				print "total (de ", MAX_SCORE ; ")";
		}

	GetOff:
		!! Esta acción se genera ante la frase SAL DEL ARMARIO o similares.
		!! Ante SAL a secas la acción es Salir. Si el usuario no está en el
		!! objeto indicado, se genera el siguiente mensaje de error. Si está,
		!! la librería generará una acción Salir, por lo que el mensaje de
		!! éxito será el de Salir.
		print "No ";
		if (IsPluralNoun(player)) print "podían";
		else print "podía";
		print ". No ";
		if (IsPluralNoun(player)) print "estaban";
		else print "estaba";
		" en ", (the) x1, ".";

	Give:
		!!	1:	Error, el usuario intenta dar un objeto que no tiene.
		!!	2:	Error, el usuario se da el objeto a sí mismo.
		!!	3:	Aviso, se ha enviado la acción Dar al PNJ, pero este no ha
		!!		respondido. En este caso x1 apunta al PNJ y no al objeto
		!!		que le hemos dado.
		!!
		!! [Observar que por defecto el objeto sigue en poder del
		!! usuario. Si queremos que el PNJ lo acepte, hay que programarlo
		!! como parte de su rutina Vida.]
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "tenían";
				else print "tenía";
				" ", (the) x1, ".";
			2:
				if (IsPluralNoun(player)) print "Manosearon";
				else print "Manoseó";
				" ", (the) x1, " durante unos momentos, sin conseguir nada.";
			3:
				"", (The) x1, " no parecía", (n) x1, " interesad", (o) x1, ".";
		}

	Go:
		!!	1:	Error, el usuario está dentro/subido en un objeto del que
		!!		tiene que salir antes.
		!!	2:	Error, la localidad no tiene salida en esa dirección (y tampoco
		!!		tiene la propiedad "cant_go", ya que en este caso se habría
		!!		impreso el valor de esa propiedad.
		!!	3:	Error, el usuario ha intentado ir hacia arriba, pero allí hay
		!!		una puerta cerrada.
		!!	4:	Error, el usuario ha intentado ir hacia abajo, pero allí hay
		!!		una puerta cerrada.
		!!	5:	Error, en la dirección que ha dicho el usuario hay una
		!!		puerta cerrada.
		!!	6:	Error, en la dirección que ha dicho el usuario hay una puerta,
		!!		pero ésta no tiene una propiedad "door_to" (probablemente un
		!!		error de programación del juego).
		switch (n) {
			1:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Tenían";
				else print "Tenía";
				print " que ";
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "bajarse";
					else print "bajarse";
				}
				else print "salir";
				" ", (del) x1, " antes.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podían";
				else print "podía";
				" ir por ahí.";
			3:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Eran incapaces";
				else print "Era incapaz";
				" de trepar por ", (the) x1, ".";
			4:
				PronounNotice(x1);
				if (IsPluralNoun(player)) print "Eran incapaces";
				else print "Era incapaz";
				" de bajar por ", (the) x1, ".";
			5:
				PronounNotice(x1);
				print "No ";
				if (IsPluralNoun(player)) print "podían";
				else print "podía";
				" pasar a través ", (del) x1, ".";
			6:
				PronounNotice(x1);
				print "No ";
				if (IsPluralNoun(player)) print "podían";
				else print "podía";
				" ir porque ", (the) x1, " no llevaba", (n) x1,
				" a ningún sitio.";
		}

	Insert:
		!!	1:	Error, el objeto no está en poder del usuario. [Nota, conviene
		!!		mirar en este caso si el objeto es animado o no, para generar
		!!		un mensaje más adecuado].
		!!	2:	Error, el usuario intenta meter el objeto en otro que no tiene
		!!		el atributo "container".
		!!	3:	Error, el usuario intenta meter el objeto en un recipiente
		!!		cerrado.
		!!	4:	Error, el objeto es una prenda que el usuario lleva puesta.
		!!		[ESTE MENSAJE NO SE GENERA NUNCA, PARECE UN BUG DE LA LIBRERÍA.
		!!		Véase en su lugar el mensaje 6].
		!!	5:	Error, se intenta poner un objeto dentro de sí mismo.
		!!	6:	Aviso, el objeto es una prenda puesta, la librería va a
		!!		quitársela de forma automática antes de reintentar Insert.
		!!	7:	Error, no queda sitio en el recipiente (el número de objetos
		!!		que un recipiente puede contener se indica en su propiedad
		!!		"capacity").
		!!	8:	Éxito. Mensaje a mostrar para cada objeto metido cuando se
		!!		meten muchos (ej: METE TODO EN LA BOLSA).
		!!	9:	Éxito. Mensaje a mostrar cuando se mete un solo objeto dentro
		!!		de otro.
		switch (n) {
			1:
				if (x1 has animate) {
					if (IsPluralNoun(player))
						"Antes tenían que ", (coge)"r", (lo) x1,
						" y no sabían si se hubiese", (n) x1, " dejado.";
					else
						"Antes tenía que ", (coge)"r", (lo) x1,
						" y no sabía si se hubiese", (n) x1, " dejado.";
				} else {
					if (IsPluralNoun(player)) print "Necesitaban";
					else print "Necesitaba";
					" tener ", (the) x1, " para poder meter", (lo) x1,
					" donde fuese.";
				}
			2:
				"No se podían meter cosas dentro ", (del) x1, ".";
			3:
				"", (The) x1, " estaba", (n) x1, " cerrad", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Tenían que quitárse";
				else print "Tenía que quitárse";
				"", (lo) x1, " antes.";
			5:
				print "No ";
				if (IsPluralNoun(player)) print "podían";
				else print "podía";
				" poner un objeto dentro de sí mismo.";
			6:
				print "(Primero ";
				if (IsPluralNoun(player)) print "se ", (lo) x1, " quitaron";
				else print "se ", (lo) x1, " quitó";
				").^";
			7:
				"No quedaba sitio en ", (the) x1, ".";
			8:
				"Hecho.";
			9:
				if (IsPluralNoun(player)) print "Metieron";
				else print "Metió";
				" ", (the) x1, " dentro ", (del) second, ".";
		}

	Inv:
		!!	1:	Mensaje si el inventario está vacío
		!!	2:	Encabezado del inventario, antes de la lista de objetos
		!!		generada por la librería
		!!	3 y 4: [6/11]
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "llevaban";
				else print "llevaba";
				" nada.";
			2:
				if (IsPluralNoun(player)) print "Llevaban";
				else print "Llevaba";
			3:
				print ":^";
			4:
				print ".^";
		}

	Jump:
		if (IsPluralNoun(player)) print "Saltaron";
		else print "Saltó";
		" en el sitio, sin ningún resultado.";

	JumpOver, Tie:
		print "No ";
		if (IsPluralNoun(player)) print "hubiesen conseguido";
		else print "hubiese conseguido";
		" nada así.";

	Kiss:
		!! TODO - modificar
		print "No ";
		if (IsPluralNoun(player)) print "se les hubiese ocurrido";
		else print "se le hubiese ocurrido";
		" hacer algo así en aquel momento.";

	Listen:
		print "No ";
		if (IsPluralNoun(player)) print "escucharon";
		else print "escuchó";
		" nada fuera de lo común.";

	ListMiscellany:
		!! Los siguientes mensajes se muestran como aclaraciones cuando se está
		!! listando el inventario del usuario, o los objetos que hay en una
		!! localidad. Junto a cada mensaje se comenta qué condiciones deben
		!! darse en ese objeto para que se muestre ese mensaje aclaratorio.
		switch (n) {
			1:	!! El objeto tiene 'light' y la localidad no
				print " (alumbrando)";
			2:	!! El objeto tiene 'container' pero no 'open'
				print " (que estaba", (n) x1, " cerrad", (o) x1, ")";
			3:	!! Casos 2 y 1 juntos
				print " (cerrad", (o) x1, " y alumbrando)";
			4:	!! El objeto es un recipiente abierto (o transparente) y no
				!! tiene nada en su interior
				print " (que estaba", (n) x1, " vací", (o) x1, ")";
			5:	!! Casos 1 y 4 juntos
				print " (vací", (o) x1, " y alumbrando)";
			6:	!! El objeto tiene 'container', no 'open', pero
				!! sí 'transparent'
				print " (que estaba", (n) x1, " cerrad", (o) x1,
				" y vací", (o) x1, ")";
			7:	!! Casos 1 y 6 juntos
				print " (cerrad", (o) x1, ", vací", (o) x1, " y
				alumbrando)";

			!! Los casos siguientes son similares, pero se muestran cuando se
			!! solicita a la rutina EscribirListaDesde la opción INFOTOTAL. La
			!! librería puede combinar varios de estos mensajes, por eso no
			!! deben llevar el cerrado de paréntesis al final, que lo añade la
			!! propia librería. *** NO SE ACONSEJA CAMBIAR ESTOS ***

			8:	!! El objeto tiene 'light' y 'worn'
				print " (alumbrando y que ";
				if (IsPluralNoun(player)) print "llevaban";
				else print "llevaba";
				print " puest", (o) x1;
			9:	!! El objeto tiene 'light' pero no 'worn'
				print " (alumbrando";
			10:	!! El objeto no tiene 'light' pero sí 'worn'
				print " (que ";
				if (IsPluralNoun(player)) print "llevaban";
				else print "llevaba";
				print " puest", (o) x1;
			11:	!! Mensaje introductorio para decir "que está
				!! abierto / cerrado / vacio"...
				print " (que estaba", (n) x1, " ";
			12:	!! Objeto tiene 'container', 'openable' y 'open'
				!! (y cosas dentro)
				print "abiert", (o) x1;
			13:	!! Objeto tiene 'container', 'openable' y 'open'
 				!! (pero vacio)
				print "abiert", (o) x1, ", pero vací", (o) x1;
			14:	!! Objeto tiene 'container', 'openable' y no 'open'
				print "cerrad", (o) x1;
			15:	!! Objeto tiene 'container', 'openable' y 'locked' o 'lockable'
				print "cerrad", (o) x1, " con llave";
			16:	!! Objeto tiene 'container', no 'openable' y 'transparent'
				print " vací", (o) x1;
			17:	!! Como el caso anterior, pero mensaje más "largo" (se activa
				!! si 'WriteListFrom' es llamada sin el modo PARTINV_BIT)
				!! TODO - Comprobar que se trata realmente del modo PARTINV_BIT
				print " (que estaba", (n) x1, " vací", (o) x1, ")";
			18:	!! encabezado a la lista de lo que hay dentro del objeto
				print " que contenía", (n) x1, " ";
			19:	!! Si el objeto tiene 'supporter', la librería va a listar sus
				!! contenidos. Este es el encabezado de la lista
 				print " (sobre ", (el_) x1;
			20:	!! Como e l9, pero en otra modalidad (que se activa si
				!! 'WriteListFrom' es llamada sin el modo PARTINV_BIT)
				print ", encima ", (del_) x1;
			21:	!! Si el contenido tiene 'container' y puede verse su interior
				!! y hay cosas, la librería va a mostrar sus contenidos. Este
				!! es el encabezado de la lista
				print " (en ", (el_) x1;
			22:	!! Como el 21, pero en otra modalidad (que se activa si
				!! 'WriteListFrom' es llamada sin el modo PARTINV_BIT)
				!! TODO - Comprobar que se trata realmente del modo PARTINV_BIT
				print ", dentro ", (del_) x1;
		}

 	LMode1:
	    !! La acción LMode1 se genera ante el comando BREVE (o NORMAL). La
	    !! librería imprime la constante Historia y a continuación este
	    !! mensaje.
		"[", (string) Story, " está ahora en su modo normal @<<breve@>>, que da
		sólo descripciones largas de las localidades la primera vez que son
		visitadas, y descripciones cortas en otro caso].";

	LMode2:
    	!! La acción LMode2 se genera ante el comando LARGO. La librería
		!! imprime la constante Historia y a continuación este mensaje.
		"[", (string) Story, " está ahora en su modo @<<largo@>>, que siempre
		da descripciones largas de las localidades (incluso si ya habías
		estado antes)].";

	LMode3:
    	!! La acción LMode3 se genera ante el comando SUPERBREVE. La librería
		!! imprime la constante Historia y a continuación este mensaje.
		"[", (string) Story, " está ahora en su modo @<<superbreve@>>, que
		siempre da descripciones cortas de las localidades (incluso si nunca
		habías estado antes)].";

	Lock:
		!! Lock se genera con CIERRA <objeto> CON <objeto2>, o
		!! también ante ECHA CERROJO A <objeto> (sin especificar un
		!! segundo objeto en este caso).
		!!
		!!	1:	Error, el objeto al que se intenta echar el cerrojo no tiene la
		!!		propiedad "lockable".
		!!	2:	Error, el objeto al que se intenta echar el cerrojo tiene la
		!!		propiedad "lockable", pero ya tiene también "locked".
		!!	3:	Error, el objeto tiene las propiedades "lockable" y "open". No
		!!		se le puede echar el cerrojo hasta que no se cierre.
		!!	4:	Error, el <objeto2> especificado no coincide con el que el
		!!		objeto indica en su propiedad "with_key".
		!!	5:	Éxito, se echa el cerrojo al objeto (con el <objeto2> si éste
		!!		es especificado y se puede encontrar en la variable "second").
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
				if (IsPluralNoun(player)) print "tenían";
				else print "tenía";
 				" que cerrar ", (the) x1, ".";
			4:
				if (second) {
					"No parecía", (n) x1, " encajar en la cerradura.";
				} else {
					if (IsPluralNoun(player)) print "Necesitaban";
					else print "Necesitaba";
					" algún tipo de llave.";
				}
			5:
				if (second) {
					if (IsPluralNoun(player)) print "Cerraron";
					else print "Cerró";
					" ", (the) x1, " con ", (the) second, ".";
				} else {
					if (IsPluralNoun(player)) print "Echaron";
					else print "Echó";
					" el cerrojo ", (al) x1, ".";
				}
		}

	Look:
		!! La acción ##Look se genera cuando el usuario pone MIRAR, pero
		!! también de forma automática al entrar en una localidad nueva, o
		!! cuando el usuario sale/se baja de un objeto en el que estaba.
		!!
		!! Algunos de los mensajes que se definen aquí aparecen en el "título"
		!! de la localidad (lo que aparece en negrita antes de la descripción
		!! de la localidad).
		!!
		!!	1:	Aclaración a añadir tras el título si el usuario está subido
		!!		en un objeto.
		!!	2:	Aclaración a añadir tras el título si el usuario está dentro
		!!		de un objeto.
		!!	3:	Aclaración a añadir tras el título si el usuario ha sido
		!!		transformado en otro personaje mediante una llamada a
		!!		ChangePlayer(nuevo, 1); (sin el 1, la librería no intentará
		!!		mostrar este mensaje).
		!!	4:	Una vez que la librería ha mostrado la descripción de la
		!!		localidad, si el usuario estaba encima de un supporter, la
		!!		librería generará este mensaje 4 para mostrar qué más cosas
		!!		hay sobre el supporter.
		!!	Restante: 5,6 [6/11] antes 'default'
		!!		Son usados por la librería para listar los objetos "simples"
		!!		que hay en la localidad. Son objetos "simples" los que no
		!!		dan su propia auto-descrcipcion a través de la propiedad
		!!		"describe" o "initial".
		!!	7:	Respuesta estandar para MirarHacia [6/11]
		switch (n) {
			1:
				!! Se puede usar un mensaje de aclaración personalizado
				!! definiendo la propiedad 'look_clarification' en un objeto
				!! ('look_clarification' tiene que devolver un string o ser una
				!! rutina encargada de imprimir un string):
				if (x1 provides look_clarification) {
					if (metaclass(x1.look_clarification) == String) {
						print (string) x1.look_clarification;
					} else if (metaclass(x1.look_clarification) == Routine) {
						RunRoutines(x1, look_clarification);
					}
				} else {
					print ", sobre ", (the) x1;
				}
			2:
				!! Ver comportamiento de Look con n == 1
				if ( x1 provides look_clarification ) {
					if (metaclass(x1.look_clarification) == String) {
						print (string) x1.look_clarification;
					} else if (metaclass(x1.look_clarification) == Routine) {
						RunRoutines(x1, look_clarification);
					}
				} else {
					print ", en ", (the) x1;
				}
			3:
				print " (como ", (object) x1 , ")";
			4:
				print "^Sobre ", (the) x1;
				WriteListFrom(child(x1),
						ENGLISH_BIT + RECURSE_BIT + PARTINV_BIT
						+ TERSE_BIT + ISARE_BIT + CONCEAL_BIT);
				".";
			5,
			6:
				!! La localidad actual puede gestionar de forma personalizada
				!! el listado automático de objetos visibles en caso de tener
				!! definida la propiedad 'list_visible_objects':
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
					if (IsPluralNoun(player)) print "podían";
					else print "podía";
					print " ver ";
				} else {
					if (IsPluralNoun(player)) print "Podían";
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
				if (IsPluralNoun(player)) print "observaron";
				else print "observó";
				" nada digno de mención al mirar hacia ", (the) x1, ".";
			8:
				if (x1 has supporter) print " (sobre "; else print " (en ";
				print (the) x1, ")";
		}

	LookUnder:
		!!	1:	Error, estamos a oscuras.
		!!	2:	Éxito, mensaje por defecto.
		switch (n) {
			1:
				"Estaba demasiado oscuro como para poder ver algo.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "vieron";
				else print "vio";
				" nada destacable.";
		}

	Mild:
		!! Respuesta si se usa como primera palabra algún insulto suave.
		"Bastante.";

	Miscellany:
		!! Esta es una falsa acción, que se usa simplemente para agrupar aquí
		!! todos los mensajes de error del parser, los mensajes ante algunos
		!! metacommandos, o algnouns mensajes de librería no relacionados con
		!! acción alguna. La asignación de números a mensajes es bastante
		!! caprichosa.
		switch (n) {
			1:
				!! El usuario ha especificado objetos multiples, pero el parser
				!! tiene una lista que no admite más de 16, de modo que los
				!! restantes objetos no serán procesados.
				"(Sólo se consideran los dieciséis primeros objetos).";
			2:
				!! El usuario ha usado objetos múltiples, pero por alguna razón
				!! la lista del parser está vacía.
				"[No se pudo determinar a qué objetos te has referido].";
			3:
				!! Mensaje de fin del relato. Muerte del personaje.
				!! En realidad se trata de un mensaje del parser, pero tiene
				!! su propio formato.
				print " Has perdido ";
			4:
				!! Mensaje de fin del relato. Victoria.
				!! Como el anterior, se trata de un mensaje del parser.
				print " Has ganado ";
			5:
				!! Mensaje a mostrar tras el fin del juego, para pedir al
				!! usuario si quiere reniciar, recuperar, anular, puntuación,
				!! curiosidades o terminar.
				print "^¿Quieres REINICIAR, RECUPERAR un juego guardado";
				#IFDEF DEATH_MENTION_UNDO;
					print ", ANULAR tu último movimiento";
				#ENDIF;
				#IFNDEF NO_PUNTUACION;
					if (TASKS_PROVIDED==0)
						print ", ver la PUNTUACIÓN de este juego";
				#ENDIF; ! NO_PUNTUACION
				if (deadflag==2 && AMUSING_PROVIDED==0)
					print ", ver algunas CURIOSIDADES";
				" o TERMINAR?";
			6:
				!! Error si el intérprete no tiene "undo"
				"[Tu intérprete no puede @<<DESHACER@>> acciones].";
			7:
				#Ifdef TARGET_ZCODE; ![6/11]
				!! Otro error si el intérprete no tiene "undo", pero no había
				!! sido detectado correctamente.
				"[@<<DESHACER@>> falló. (Puede que tu intérprete no permita
				realizar esa acción)].";
				#Ifnot; ! TARGET_GLULX
				"[No puedes @<<DESHACER@>> más].";
				#Endif; ! TARGET_
			8:
				!! Si el usuario no responde correctamente a la pregunta del
				!! mensaje [Miscellany,5]
				"[Por favor, introduce una de las respuestas anteriores].";
			9:
				!! TODO - Modificar
				!! Mensaje cuando se detecta, al final del turno, que ya no hay
				!! una fuente de luz en la localidad actual.
				print "^¡";
				if (IsPluralNoun(player)) print "Se habían";
				else print "Se había";
				" quedado a oscuras!";
			10:
				!! Mensaje cuando el usuario introduce una linea en blanco.
				"[No has introducido ninguna instrucción].";
			11:
				!! Si el usuario intenta "undo" al principio del juego
				"[No se puede @<<DESHACER@>> algo que no has hecho].";
			12:
				!! Si el usuario pone "undo" dos veces.
				"[No se puede @<<DESHACER@>> dos veces seguidas].";
			13:
				!! Éxito en el "undo".
				"[Retrocediendo al turno anterior].";
			14:
				!! Si el usuario pone EEPA (verbo para corregir), pero el
				!! parser no recordaba ninguna palabra mal. Ejmplo de uso del
				!! comando EEPA:
				!!		> SACA MAZANA VERDE DE LA CESTA
				!!		No vqeo eso por aquí.
				!!		> EEPA MANZANA
				!!		Sacas la manzana verde de la cesta de mimbre.
				"[Eso no puede corregirse].";
			15:
				!! Se usa EEPA sin especificar la palabra corregida.
				"[Has utilizado @<<EEPA@>> sin especificar qué palabra deseabas
				corregir].";
			16:
				!! Si el usuario pone EEPA seguido de dos o más palabras.
				"[@<<EEPA@>> sólo puede corregir una palabra].";
			17:
				!! Descripción del objeto Oscuridad.
				"Estaba demasiado oscuro como para poder ver algo.";
			18:
				!! Nombre corto del objeto usuario.
				if (IsPluralNoun(player)) print "ell", (o) player;
				else {
					if (IsFemaleNoun(player)) print "ella";
					else print "él";
				}
				print " mism", (o) player;
			19:
				!! Descripción del personaje controlado por el usuario.
				"Tan buen aspecto como siempre.";
			20:
				!! Cuando el usuario pone PNJ, REPITE para que el PNJ haga otra
				!! vez la última acción.
				"[Para repetir un comando como @<<PERSONAJE, SALTA@>>, escribe
				@<<REPITE@>>, en lugar de @<<PERSONAJE, REPITE@>>].";
			21:
				!! Cuando el usuario pone REPITE como primer commando del juego.
				"[No hay comando que repetir].";
			22:
				!! El usuario ha comenzado la frase con una coma.
				"[No se puede empezar una frase con una coma].";
			23:
				!! Cuando el usuario pone, por ejemplo; PEPE, COGE HACHA, pero
				!! no hay un objeto que responda al name PEPE.
				"[Parece que has tratado de hablar con alguien, pero no se pudo
				identificar con quién].";
			24:
				!! Si el usuario intenta hablar con un objeto que no es
				!! "animate" ni "talkable" ("talkable" debe ponerse a objetos
				!! inanimates con los que se podría hablar, como un micrófono).
				"[No es posible hablar con ", (the) x1, "].";
			25:
				!! Hay palabras no comprendidas entre el nombre de un PNJ y la
				!! coma, ej: PEPE ZAFDSRGG, SALTA.
				"[Para iniciar una conversación, intenta órdenes del tipo:
				PERSONAJE, HOLA].";
			26:
				!! La gramática especifica que una acción debe efectuarse sobre
				!! un objeto en poder del usuario (token 'held'), pero el
				!! usuario lo ha intentado sobre un objeto que no tiene, aunque
				!! está a su alcance. El parser intentará automáticamente coger
				!! ese objeto antes de efectuar la acción. En este mensaje se
				!! avisa al usuario de esta intención.
				print "(Primero ";
				if (IsPluralNoun(player)) print "trataron";
				else print "trató";
				" de ", (coge) "r ", (the) x1, ".)";

			!! ERRORES DE PARSING: Estos errores son generados por la librería,
			!! a menos que el programador proporcione su propia función
			!! ParserError para manejo de errores.

			27:
				!! ERROR DE PARSING. El parser se ha atascado. Es el tipo de
				!! error más genérico. Si el parser puede, se generará un error
				!! más concreto.
				"[No se pudo entender esa instrucción.]";

			28:
				!! ERROR DE PARSING. A la instrucción le sobraban palabras,
				!! aunque el parser ha entendido gran parte de su significado.
				print "[Intenta de nuevo porque sólo se pudo entender: @<<";
				PrintCommand();
				print "@>>].^";
				return true;

			29:
				!! ERROR DE PARSING. El parser esperaba un token de tipo
				!! número.
				"[No se pudo comprender ese número].";

			30:
				!! ERROR DE PARSING. El parser no ha comprendido el nombre del
				!! objeto al que se refiere el jugador, o ese objeto no está
				!! aquí.
				"[Te has referido a algo con lo que no se puede interactuar en
				este momento].";

			31:
				!! ERROR DE PARSING. Este error parece que no se genera nunca.
				!! Un posible bug de libreria, o restos de versiones arcaicas.
				"[Parece que falta información en esa instrucción].";

			32:
				!! ERROR DE PARSING. El objeto que el usuario intenta usar no
				!! está en su poder. El parser ha intentado "cogerlo de forma
				!! automatica", pero ha fallado.
				print "No ";
				if (IsPluralNoun(player)) print "tenían";
				else print "tenía";
				" eso.";

			33:
				!! ERROR DE PARSING. El usuario ha intentado usar objetos
				!! múltiples (o "TODO") con un verbo que en su gramática no lo
				!! admite.
				"[No se pueden especificar objetos múltiples con @<<",
				(address) verb_word, "@>>.]";

			34:
				!! ERROR DE PARSING. El usuario ha intentado objetos multiples
				!! para "noun" y para "second", como en METE TODO EN TODO.
				"[Sólo se pueden especificar objetos múltiples una vez en cada
				línea].";

			35:
				!! ERROR DE PARSING. El usuario ha usado un pronombre, como
				!! COMELO, pero el parser no tiene asignado un valor a ese
				!! pronombre.
				"[No está claro a qué te refieres con @<<",
				(address) pronoun_word ,"@>>].";

			36:
				!! ERROR DE PARSING. El usuario ha puesto una lista de objetos
				!! y ha usado la palabra EXCEPTO para exceptuar algo que no
				!! estaba incluido en la lista, por ejemplo: COGE TODAS LAS
				!! MONEDAS EXCEPTO EL SACO.
				"[Has exceptuado algo que no estaba incluido].";

			37:
				!! ERROR DE PARSING. La gramática de un verbo obliga a que el
				!! objeto sobre el que se actúe sea animate (tiene un token de
				!! tipo "creature"), pero el usuario lo ha intentado sobre un
				!! objeto que no es animate.
				"[Sólo se puede hacer eso con seres animados].";

			38:
				!! ERROR DE PARSING. La primera palabra usada por el usuario es
				!! desconocida (o la primera palabra tras la coma, si se trata
				!! de una orden a un PNJ).
				print "[La instrucción @<<";
				for (i = 0: i < WordLength(1): i++) {
					print (char) WordAddress(1) -> i;
				}
				"@>> no está definida].";

			39:
				!! ERROR DE PARSING. El usuario intenta actiones sobre las
				!! palabras que están en la propiedad "irrelevante" de la
				!! localidad.
				"[No es necesario referirse a eso para terminar la historia].";

			40:
				!! ERROR DE PARSING. El usuario ha usado un pronombre, como
				!! EXAMINALO, pero el pronombre se refiere a un objeto que ya
				!! no está visible.
				"[Ahora mismo no se puede encontrar lo que representa el
				pronombre @<<", (address) pronoun_word, "@>> (",
				(the) pronoun_obj, ")].";

			41:
				!! ERROR DE PARSING. Este error no se produce nunca.
				!! Probablemente sigue aquí por razones de compatibilidad, o
				!! por despiste de Graham. ¿Tal vez ha sido sustituido en
				!! versiones mas recientes por el mensaje número 28?
				"[No se pudo entender la última parte de la instrucción].";

			42:
				!! ERROR DE PARSING. El usuario ha solicitado un número de
				!! objetos en una lista de objetos múltiples, pero el parser no
				!! es capaz de encontrar tantos. Por ejemplo:
				!! COGE SEIS MONEDAS.
				if (x1==0) "[No hay suficientes].";
		        else if (x1 == 1) {
			    	print "[Aquí sólo hay un";
			    	if (multiple_object-->1) print (o) multiple_object-->1;
			    	else print "o";
			    	" disponible].";
			    }
				"[Sólo hay ", (number) lm_o, " disponibles para esa acción].";

			43:
				!! ERROR DE PARSING. El usuario ha puesto TODO como objeto
				!! múltiple, pero el parser no ha encontrado ningún objeto. En
				!! realidad este error parece no producirse nunca y el que
				!! acaba generándose siempre es el siguiente
				!! (#44, ASKSCOPE_PE).
				"[No se puede encontrar nada con lo que hacer eso].";

			44:
				!! El usuario ha intentado objetos múltiples usando TODO
				!! pero el parser no ha encontrado ninguno. Por ejemplo, COGE
				!! TODO o DEJA TODO si no hay nada cerca o en el inventario.
				!! Modificado en [020621] para dar un mensaje más coherente
				!! si el usuario tiene algún objeto en su inventario.
				if (action_to_be == ##Drop) {
					print "[No ";
					if (IsPluralNoun(player)) print "tenían";
					else print "tenía";
					print " nada que ";
					LanguageVerb(verb_word);
					"].";
				} else {
					print "[No había nada que ";
					LanguageVerb(verb_word);
					"].";
				}
			45:
				!! El usuario ha nombrado un PNJ ambiguo (hay más de noun con
				!! el mismo name cerca). El parser le pide aclaración. Este
				!! mensaje es la primera parte de la pregunta, el resto lo pone
				!! el parser (que es la lista de PNJs entre los que duda).
				!! Debemos poner a 1 la variable PreguntaCualExactamente cuando
				!! se generan este tipo de preguntas aclaratorias.
				print "[¿Quién concretamente: ";
				PreguntaCualExactamente=1;
				ImprimirListaDudosos("o");
			46:
				!! El usuario ha nombrado un objeto ambiguo (hay más de objeto
				!! con el mismo nombre cerca). El parser le pide aclaración.
				!! Este mensaje es la primera parte de la pregunta, el resto lo
				!! pone el parser (que es la lista de objetos entre los que
				!! duda). Debemos poner a 1 la variable PreguntaCualExactamente
				!! cuando se generan este tipo de preguntas aclaratorias.
				print "[¿Cuál concretamente: ";
				PreguntaCualExactamente=1;
				ImprimirListaDudosos("o");
			47:
				!! El usuario ha respondido "TODOS" o "AMBOS" a una pregunta
				!! aclaratoria como la anterior, pero el verbo no admite
				!! objetos múltiples.
				print "[Desafortunadamente sólo puedes referirte a un objeto
				en este caso. ¿Cuál exactamente?]^";
				PreguntaCualExactamente=1;
			48:
				!! El usuario ha escrito una frase u orden a PSI incompleta,
				!! como BESA (verbo aplicado sobre PSIs normalmente). El parser
				!! le pregunta para que complete la frase.
				PreguntaCualExactamente = 1;
				print "[";
				if (IniciarPregunta() == 0) print "A quién";
				if (actor ~= player) print " tiene que ";
				else print " quieres ";
				IdiomaImprimirComando();
				if (actor ~= player) print " ", (the) actor;
				print "?]";
				new_line;
			49:
				!! FIXME - ¿Qué quieres comerse?
				!! El usuario ha escrito una frase u orden incompleta, como
				!! COGE (verbo aplicado sobre objetos normalmente). El parser
				!! le pregunta para que complete la frase.
				PreguntaCualExactamente = 1;
				print "[";
				if (IniciarPregunta() == 0) print "Qué";
				if (actor ~= player) print " tiene que ";
				else print " quieres ";
				IdiomaImprimirComando();
				if (actor ~= player) print " ", (the) actor;
				print "?]";
				new_line;
			!#IFNDEF NO_PUNTUACION;
			50:
				!! El usuario acaba de realizar una acción que puntúa (la
				!! librería ha detectado que la variable score ha cambiado de
				!! valor). Se informa de ello al player. El parámetro x1
				!! contiene el incremento (o decremento) en la puntuación.
				print "[Tu puntuación ha ";
				if (x1 > 0) print "aumentado";
				else {
					x1 = -x1;
					print "disminuido";
				}
				print " en ", (number) x1, " punto";
				if (x1 > 1) print "s";
			!#ENDIF; ! NO_PUNTUACION
			51:
				!! El usuario ha intentado una acción con objeto múltiple
				!! (como COGE TODO). Esta acción es convertida por el parser en
				!! una serie de actiones COGE OBJETO1, COGE OBJETO2, etc... Si
				!! en la ejecución de alguna de estas actiones encuentra que la
				!! localidad del player ha cambiado, debe abortar el proceso.
				!! Este mensaje informa de ello al usuario.
				"(Se ha producido un evento inesperado que ha obligado a
				recortar la lista de objetos sobre los que actuabas).";
			52:
				!! En los menús, se espera a que el player escriba un número
				!! para mostrar una entrada del menú. Si pulsa un numero
				!! incorrecto, se saca este mensaje. El parámetro x1 contiene
				!! el número más alto válido.
				new_line;
				print "[Escribe un número del 1 al ", x1, ", 0 para volver a
				mostrarlo, o pulsa Intro].";
				new_line;
				return true;
			53:
				!! Mensaje que muestra el sistema de menús cuando espera una
				!! tecla.
				new_line;
				"[Por favor, pulsa ESPACIO].";
			54:
				! TODO - Guardar comentarios sin imprimir mensajes
				"[Comentario guardado].";
			55:
				"[Comentario NO guardado].";
			56:
				print "].^";
			57:
				print "?]^";
		}

	No:
		!! Cuando el usuario pone NO, a secas, se genera esta acción. Está
		!! pensada por si el relato suelta una frase del estilo de "¿Pero tú
		!! eres tonto?" y el usuario responde NO. De todas formas, hay un
		!! problema, y es que NO es normalmente la acción Ir al noroeste. Si
		!! queremos que NO sea provisionalmente la acción No, entonces se debe
		!! poner a 1 la variable PreguntaSiNo antes de escribir el texto
		!! "¿Pero tú eres tonto?". En ese caso, el parser interpretará "NO"
		!! como la acción No, pero únicamente durante el siguiente turno.
		"[Sólo se trataba de una pregunta retórica].";

	NotifyOff:
		"[Notificación de puntuación desactivada].";

	Objects:
		! TODO - mensaje del parser
		!! Ante el verbo "OBJETOS" se genera esta acción, que muestra una
		!! lista de todos los objetos que el usuario ha manipulado a lo largo
		!! del juego, junto con una indicación de qué hizo con ellos.
		!!
		!!	1:	Texto introductorio a la lista.
		!!	2:	Si no ha manejado aún ninguno.
		!!	3:	Indicación de que lo lleva puesto.
		!!	4:	Indicación de que lo lleva en su inventario.
		!!	5:	Indicación de quién lo tiene ahora (si lo tiene un PNJ).
		!!	6:	Indicación de dónde está el objeto (si está en una localidad).
		!!	7:	Indicación de dónde está el objeto (si está en un "entrable").
		!!	8:	Indicación de dónde está el objeto (si está en un recipiente).
		!!	9:	Indicación de dónde está el objeto (si está en un soporte).
		!!	10:	Indicación de que se ha perdido (no está en ninguno de los
		!!		casos anteriores).
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
		!!	1:	Error, el objeto no tiene el atributo "openable".
		!!	2:	Error, el objeto es abrible, pero tiene "locked".
		!!	3:	Error, el objeto es abrible, pero ya tiene el atributo "open".
		!!	4:	Éxito, el objeto se abre, y además era recipiente. Se muestra
		!!		entoces la lista de objetos que había en su interior (si habia
		!!		algo).
		!!	5:	Éxito, el objeto se abre (pero no tiene nada en su
		!!		interior, o no era recipiente).
		switch (n) {
			1:
				"No era algo que se pudiese abrir.";
			2:
				"Estaba", (n) x1, " cerrad", (o) x1, " con llave.";
			3:
				"Ya estaba", (n) x1, " abiert", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Abrieron";
				else print "Abrió";
				print " ", (the) x1, ", descubriendo ";
				if (WriteListFrom(child(x1),
					ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT) == 0) {
					print "que estaba", (n) x1, " vací", (o) x1;
				}
				".";
			5:
				if (IsPluralNoun(player)) print "Abrieron";
				else print "Abrió";
				" ", (the) x1, ".";
		}

	Order:
		"", (The) x1, " tenía", (n) x1, " mejores cosas que hacer.";

	Places:
		!! FIXME - Introducir flexiones
		!! El verbo "LUGARES" muestra un listado de los lugares que el usuario
		!! ha visitado. Aquí debemos escribir el texto introductorio a esa
		!! lista.
		switch (n) {
			1:  print "[Has visitado: ";
			2:  print "].^";
		}

	Pray:
		"La fe tal vez pudiese resultar útil en una ocasión diferente.";

	Prompt:
		!! El prompt aparece justo antes de pedir una nueva línea al usuario.
		!! Puede definirse para que sea una frase, o se genere una frase
		!! aleatoria en cada turno, por ejemplo.
		new_line;
		print "> ";

	Pronouns:
		!! Esta acción (generada por el verbo PRONOMBRES) muestra una lista
		!! de qué significa en ese momento para el parser cada pronombre:
		!! -lo, -la, -los, -las...
		!!
		!!	1:	Texto introductorio.
		!!	2:	La palabra "es".
		!!	3:	Texto a mostrar si el pronombre no está definido.
		!!	4:	Si el juego no define pronombres.
		!!	5:	[6/11].
		switch (n) {
			1:
				print "[En este momento, ";
			2:
				print "es ";
			3:
				print "no está definido";
			4:
				print "el juego no conoce ningún pronombre].";
				new_line;
				return true;
			5:
				print "].";
				new_line;
				return true;
		}

	Pull, Push, Turn:
		!! Las acciones Pull, Push y Turn generan todas ellas los
		!! mismos mensajes, pero pueden darse 4 casos:
		!!	1:	El objeto tiene el atributo 'static'.
		!!	2:	El objeto tiene el atributo 'scenery'.
		!!	3:	El objeto no es 'static' ni 'scenery'.
		!!	4:	El objeto es un ser animado.
		!! [Nota, si el objeto tiene ambos 'estatico' y 'escenario' se
		!! está también en el caso 1.]
		switch (n) {
			1:
				"Estaba", (n) x1, " firmemente sujet", (o) x1, ".";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "fueron capaces";
				else print "fue capaz";
				".";
			3:
				"No ocurrió nada, aparentemente.";
			4:
				"Aquello hubiese sido, como poco, maleducado.";
		}

!!	Push:	see Pull.

	PushDir:
		!! La acción PushDir se genera ante frases como EMPUJA EL COCHE HACIA
		!! EL NORTE. Hay 3 casos posibles:
		!!	1:	Si el juego no ha previsto la posibilidad de empujar ese
		!!		objeto hacia una dirección (o sea, no llama a la rutina
		!!		PermitirEmujarDir). Esta es la respuesta por defecto más
		!!		habitual.
		!!	2:	Si el usuario pone tras HACIA algo que no es una dirección.
		!!		(respuesta por defecto en este caso).
		!!	3:	Si intenta empujar hacia arriba o hacia abajo.
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creían";
				else print "creía";
				" que empujar", (lo) x1, " hubiese servido de nada.";
			2:
				"Aquello no era una dirección.";
			3:
				print "No ";
				if (IsPluralNoun(player)) print "podían";
				else print "podía";
				" empujar", (lo) x1, " en esa dirección.";
		}

	PutOn:
		!!	1:	Error, el objeto no está en poder del usuario. [Nota, conviene
		!!		mirar en este caso si el objeto es animado o no, para generar
		!!		un mensaje más adecuado].
		!!	2:	Error, el usuario intenta poner un objeto sobre sí mismo.
		!!	3:	Error, el usuario intenta poner el objeto sobre otro que no
		!!		tiene el atributo "supporter".
		!!	4:	Error, el usuario intenta poner un objeto sobre el propio
		!!		usuario.
		!!	5:	Aviso, el objeto es una prenda puesta. La librería va a
		!!		quitárselo automáticamente antes de reintentar la acción PutOn.
		!!	6:	Error, se intenta poner el objeto sobre otro en el que ya no
		!!		queda sitio (el número de objetos que caben en el soporte se
		!!		indica en su propiedad "capacity").
		!!	7:	Exito. Mensaje a mostrar para cada objeto puesto cuando se
		!!		ponen muchos (ej: PON TODO SOBRE LA MESA).
		!!	8:	Exito. Mensaje a mostrar cuando se pone un objeto sobre otro.
		switch (n) {
			1:
				if (x1 has animate) {
					if (IsPluralNoun(player))
						"Antes tenían que ", (coge)"r", (lo) x1,
						" y no sabían si se hubiese", (n) x1,
						" dejado.";
					else
						"Antes tenía que ", (coge)"r", (lo) x1,
						" y no sabía si se hubiese", (n) x1, " dejado.";
				} else {
					if (IsPluralNoun(player)) print "Necesitaban";
					else print "Necesitaba";
					" tener ", (the) x1, " para poder poner", (lo) x1,
					" donde fuese.";
				}
			2:
				print "No ";
				if (IsPluralNoun(player)) print "podían";
				else print "podía";
				" poner un objeto sobre sí mismo.";
			3:
				"Poner cosas sobre ", (the) x1, " no hubiese servido de nada.";
			4:
				if (IsPluralNoun(player)) print "Les faltaba";
				else print "Le faltaba";
				" destreza.";
			5:
				print "(Primero ";
				if (IsPluralNoun(player)) print "se ", (lo) x1, " quitaron";
				else print "se ", (lo) x1, " quitó";
				").^";
			6:
				"No quedaba sitio en ", (the) x1, " para poner nada más.";
			7:
				"Hecho.";
			8:
				if (IsPluralNoun(player)) print "Colocaron";
				else print "Colocó";
				" ", (the) x1, " sobre ", (the) second, ".";
		}

	Quit:
		!!	1:	Respuesta al comando FIN.
		!!	2:	Respuesta si el usuario escribe algo distinto de "si" o "no".
		switch (n) {
			1:
				print "[Por favor, responde @<<SI@>> o @<<NO@>>]: ";
			2:
				print "[¿Realmente quieres abandonar el relato?] ";
		}
		return true;

	Remove:
		!!	1:	El recipiente que contiene el objeto que el usuario quiere
		!!		sacar, está cerrado. (x1 apunta al objeto, no al recipiente,
		!!		el cuál puede obtenerse con parent(x1)).
		!!	2:	El objeto no está dentro del recipiente que el usuario ha dicho.
		!!	3:	Éxito.
		switch (n) {
			1:	!! TODO - modificar
				"Por desgracia ", (the) parent(x1), " estaba", (n) parent(x1),
				" cerrad", (o) parent(x1), ".";
			2:	!! TODO - Modificar
				if (second has animate)
					"¡Pero si no ", (lo) x1, " tenía", (n) second, "!";
				else
					"¡Pero si no estaba", (n) x1, " ahí en aquel momento!";
			3:
				if (verb_word == 'quita') "Quitad", (o) x1, ".";
				"Sacad", (o) x1, ".";
		}

	Restart:
		!!	1:	Respuesta al comando REINICIAR.
		!!	2:	Si no se puede reiniciar.
		switch (n) {
			1:
				print "[¿Realmente quieres reiniciar el relato?] ";
			2:
				"[Error al reiniciar la partida].";
		}

	Restore:
		!!	1:	Si no se pudo cargar la partida con LOAD.
		!!	2:	Éxito (no llega a mostrarse, porque en caso de éxito el estado
		!!		del juego cambia al momento en que se salvó. El "Ok" que se ve
		!!		entonces es el del comando Salvar.
		switch (n) {
			1:
				"[Error. No se pudo recuperar la partida].";
			2:
				print "[Partida cargada].^";
				new_line;
				<<Look>>;
		}

	Rub:
		"Ya estaba", (n) x1, " bastante limpi", (o) x1, ".";

	Save:
		!!	1:	Si no se pudo guardar el juego.
		!!	2:	Éxito.
		switch (n) {
			1:
				"[Error. No se pudo guardar la partida].";
			2:
				"[Partida guardada].";
		}

	Score:
		!! TODO - Mensaje del parser
		!! Puntuación del juego. Puede activarse porque el usuario lo pide
		!! (con el verbo "PUNTUACION") o porque el juego ha terminado. En
		!! este ultimo caso, la variable "deadflag" valdrá true.
		switch (n) {
			1:
				if (deadflag)
					print "En esta ficción interactiva, tu puntuación ha
					sido ";
				else
					print "Hasta el momento tu puntuación es ";
				print score, " de un total de ", MAX_SCORE,
				", en ", turns, " turno";
				if (turns == 0 || turns >1) print "s";
				return;
			2:
				"[Esta ficción interactiva no tiene conteo de puntuación].";
		}

	ScriptOff:
		!!	1:	Error ya estaba desactivada la transcrcipción.
		!!	2:	Éxito.
		switch (n) {
			1:
				"[La transcripción ya estaba desactivada].";
			2:
				new_line;
				"[Fin de la transcripción].";
			3:
				"[Error al intentar finalizar la transcripción].";
		}

	ScriptOn:
		!!	1:	Error, ya estaba activada la transcrcipción.
		!!	2:	Éxito (parte inicial del mensaje, la librería imprime a
		!!		continuación un 'Banner' con los créditos de la aplicación.
		switch (n) {
			1:
				"[La transcripción ya estaba activada].";
			2:
				"[Iniciando transcripción...]";
			3:
				"[Error al intentar iniciar la transcripción].";
		}

	Search:
		!! La acción Search se genera ante la frase MIRA EN RECIPIENTE, MIRA EN
		!! SOPORTE, REGISTRA OBJETO.
		!!
		!!	1:	Error, estamos a oscuras.
		!!	2:	Éxito examinando soporte, pero no hay nada sobre él.
		!!	3:	Éxito examinando soporte, listar lo que hay.
		!!	4:	El objeto examinado no es soporte ni recipiente, mensaje
		!!		estándar indicando que no se encuentra nada.
		!!	5:	Error, El objeto examinado es recipiente, pero está cerrado.
		!!	6:	Éxito, el objeto examinado es recipiente abierto, pero no
		!!		tiene nada dentro.
		!!	7:	Éxito, el objeto examinado es recipiente abierto y tiene
		!!		cosas dentro. Se las lista.
		switch (n) {
			1:
				"Estaba demasiado oscuro como para poder ver algo.";
			2:
				"No había nada sobre ", (the) x1, ".";
			3:
				!! TODO - error de Spanish.h?
				print "Sobre ", (the) x1;
				WriteListFrom(child(x1),
					ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT + ISARE_BIT);
				".";
			4:
				print "No ";
				if (IsPluralNoun(player)) print "encontraron";
				else print "encontró";
				" nada interesante.";
			5:
				print "No ";
				if (IsPluralNoun(player)) print "podían";
				else print "podía";
				" ver lo que había dentro ", (del) x1, " porque
				estaba", (n) x1, " cerrad", (o) x1, ".";
			6:
				"", (The) x1, " estaba", (n) x1, " vací", (o) x1, ".";
			7:
				!! TODO - error de Spanish.h?
				print "En ", (the) x1;
				WriteListFrom(child(x1),
					TERSE_BIT + ENGLISH_BIT + ISARE_BIT + CONCEAL_BIT);
				".";
		}

	Set:
		!! Set sale ante la frase FIJA OBJETO o AJUSTA OBJETO
		print "No, no ";
		if (IsPluralNoun(player)) print "podían";
		else print "podía";
 		".";

	SetTo:
		!! SetTo sale ante la frase AJUSTA DIAL A 23 o FIJA CONTROL EN
		!! ACTIVADO, o PON REGULADOR A 30
		"Aquello no podía regularse a ningún valor.";

	Show:
		!!	1:	Error, el usuario intenta mostrar un objeto que no tiene.
		!!	2:	Aviso, se ha enviado la acción Show al PNJ, pero este no ha
		!!		respondido. En este caso x1 apunta al PNJ y no al objeto que
		!!		le hemos mostrado.
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "tenían";
				else print "tenía";
				" ", (the) x1, ".";
			2:
				"", (The) x1, " no mostraba", (n) x1, " ningún interés.";
		}

	Sing: !! TODO - Modificar
		if (IsPluralNoun(player)) print "Cantaban";
		else print "Cantaba";
		" fatal.";

	Sleep:
		print "No ";
		if (IsPluralNoun(player)) print "estaban";
		else print "estaba";
		" especialmente somnolient", (o) player, ".";

	Smell:
		print "No ";
		if (IsPluralNoun(player)) print "olían";
		else print "olía";
		" nada extraño.";

	Sorry:
		!! Esta acción se genera si el usuario introduce "LO SIENTO",
		!! "PERDONA" o cosas similares.
		"[No es necesario que te disculpes].";

	Squeeze:
		!!	1:	Tratar de retorcer un ser animado.
		!!	2:	Cualquier otro objeto.
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "se les hubiese ocurrido";
				else print "se le hubiese ocurrido";
				" hacer algo así.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "consiguieron";
				else print "consiguió";
				" nada haciendo eso.";
		}

	Strong:
		!! Respuesta si se usa como primera palabra algún taco.
		"[No sirve de nada utilizar ese vocabulario].";

	Swim:
		"No era el momento ni el lugar para ponerse a nadar.";

	Swing:
		print "No parecía", (n) x1, " el lugar más adecuado en el que ";
		if (IsPluralNoun(player)) print "columpiarse";
		else print "columpiarse";
		".";

	SwitchOff:
		!!	1:	Error, el objeto no tiene el atributo "switchable".
		!!	2:	Error, el objeto ya tenia desactivado el atributo "on".
		!!	3:	Éxito, el objeto tiene ahora desactivado "on".
		switch (n) {
			1:
				"No era algo que se pudiese apagar.";
			2:
				"Ya estaba", (n) x1, "apagad", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Apagaron";
				else print "Apagó";
				" ", (the) x1, ".";
		}

	SwitchOn:
		!! Generada al intentar ENCIENDE OBJETO si el objeto tiene el
		!! atributo "conmutable". Observar que si no lo tiene, la acción
		!! que se genera será sin embargo Quemar.
		!!	1:	Error, el objeto no es conmutable (este error no aparecerá
		!!		si el usuario pone ENCIENDE OBJETO, ya que en este caso la
		!!		acción generada será Quemar objeto, pero puede aparecer si
		!!		pone CONECTA OBJETO).
		!!	2:	Error, el objeto ya tenía el atributo "on".
		!!	3:	Éxito, el objeto tiene ahora activado "on".
		switch (n) {
			1:
				"No era algo que se pudiese encender.";
			2:
				"Ya estaba", (n) x1, " encendid", (o) x1, ".";
			3:
				if (IsPluralNoun(player)) print "Encendieron";
				else print "Encendió";
				" ", (the) x1, ".";
		}

	Take:
		!! Hay 13 casos diferentes. Se trata de 1 mensaje de éxito y 11
		!! mensajes de error y un aviso:
		!!	1:	Éxito.
		!!	2:	Error, el objeto cogido es el propio usuario.
		!!	3:	Error, el objeto cogido es un objeto animado.
		!!	4:	Error, el usuario está subido o metido en el objeto que intenta
		!!		coger.
		!!	5:	Error, el usuario ya tenía ese objeto en su inventario.
		!!	6:	Error, el objeto está en poder de un ser animado [x1 apunta
		!!		al ser, no al objeto, el cual puede obtenerse en la variable
		!!		"noun"].
		!!	7:	Error, el objeto es un sub-objeto de otro (está dentro de un
		!!		objeto que tiene el atributo "transparent", pero no tiene el
		!!		atributo "container" ni "supporter").
		!!	8:	Error, el objeto está dentro de otro, pero este otro no tiene
		!!		el atributo "container" ni "supporter" ni "transparent"
		!!		(probablemente un error de programación).
		!!	9:	Error, el objeto está dentro de un recipiente cerrado.
		!!	10:	Error, el objeto tiene el atributo "scenery".
		!!	11:	Error, el objeto tiene el atributo "static".
		!!	12:	Error, el usuario lleva demasiados objetos.
		!!	13: Mensaje de aviso, la librería ha decidido mover objetos del
		!!		inventario al "objeto saco" para hacer sitio y que el usuario
		!!		pueda coger el objeto. [El objeto saco es uno que puede
		!!		declarar el programador. Si el usuario lo coge y lo lleva
		!!		consigo, la librería lo usará automáticamente como mochila
		!!		para descargar al usuario cuando sea necesario].
		switch (n) {
			1:
				if (dialecto_sudamericano) print "Tomad";
				else print "Cogid";
				"", (o) noun, ".";
			2:
				print "Siempre ";
				if (IsPluralNoun(player)) print "se tenían";
				else print "se tenía";
 				" a ", (string) YOURSELF__TX, ".";
			3:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creían";
				else print "creía";
				" que ", (al) x1, " le", (s) x1, " hubiese gustado.";
			4:
				if (IsPluralNoun(player)) print "Tenían";
				else print "Tenía";
				print " que ";
				if (x1 has supporter) {
					if (IsPluralNoun(player)) print "bajarse";
					else print "bajarse";
				}
				else print "salir";
				"", (del) x1, " antes.";
			5:
				print "Ya ";
				if (IsPluralNoun(player)) print "tenían";
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
				if (IsPluralNoun(player)) print "hubiesen podido llevarse";
				else print "hubiese podido llevarse";
				" aquello.";
			11:
				"", (The) x1, "estaba", (n) x1, " fij", (o) x1,
				" en el sitio.";
			12:
				print "Ya ";
				if (IsPluralNoun(player)) print "tenían";
				else print "tenía";
				" las manos ocupadas con demasiadas cosas.";
			13:
				print "(Primero ";
				if (IsPluralNoun(player)) print "colocaron";
				else print "colocó";
				" ", (the) x1, " en ", (the) SACK_OBJECT,
				" para hacer sitio).";
		}

	Taste:
		print "No ";
		if (IsPluralNoun(player)) print "saborearon";
		else print "saboreó";
		" nada inesperado.";

	Tell:
		!!	1:	El usuario habla consigo mismo.
		!!	2:	Hablar con cualquier otro ser animado.
		!! [Nota: Hablar con un objeto inanimado no está permitido por el
		!! parser, que da un error y no llega a generar la acción.]
		!! [Los errores de parser se tratan en la sección "Miscelánea" de
		!! esta rutina, al final.]
		switch (n) {
			1:
				if (IsPluralNoun(player)) print "Hablaron";
				else print "Habló";
				" sol", (o) player, " durante un rato.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "provocaron";
				else print "provocó";
				" ninguna reacción.";
		}

	Think: !! TODO - Modificar
		print "Si, eso ";
		if (IsPluralNoun(player)) print "intentaban";
		else print "intentaba";
		".";

	ThrowAt:
		!!  1:	Lanzar cosas a objetos inanimados.
		!!	2:	Lanzar cosas a objetos animados.
		switch (n) {
			1:
				"No hubiese servido de nada.";
			2:
				print "En el último momento ";
				if (IsPluralNoun(player)) print "se echaron";
				else print "se echó";
				" atrás.";
		}

!!	Tie: see JumpOver

	Touch:
		!!	1:	Si se intenta tocar a un ser animado.
		!!	2:	Tocar un objeto normal del juego.
		!!	3:	Tocarse a si mismo.
		switch (n) {
			1:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creían";
				else print "creía";
				" que ", (al) x1, " le", (s) x1, " hubiese gustado.";
			2:
				print "No ";
				if (IsPluralNoun(player)) print "notaron";
				else print "notó";
				" nada extraño al tacto.";
			3:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creían";
				else print "creía";
				" que algo así hubiese servido de nada.";
    	}

!!	Turn:	see Pull

	Unlock:
		!! Unlock se genera ante ABRE <objeto> CON <objeto2>, o también
		!! ante QUITA CERROJO A <objeto> (en este segundo caso no se
		!! especifica la "llave" que abre la puerta).
		!!
		!!	1:	Error, el objeto que se intenta abrir, no tiene el atributo
		!!		cerrojo.
		!!	2:	Error, el objeto que se intenta abrir tiene atributo "cerrojo",
		!!		pero no tiene atributo "cerrojoechado".
		!!	3:	Error, el <objeto2> que se intenta usar como llave, no coincide
		!!		con la propiedad "con_llave" del <objeto> que intenta ser
		!!		abierto.
		!!	4:	Éxito. El <objeto> se abre (con <objeto2> si éste ha sido
		!!		especificado, el cual podemos encontrarlo en la variable
		!!		"otro".
		switch (n) {
			1:
				"No parecía", (n) x1, " tener ningún tipo de cerrojo.";
			2:
				"", (The) x1, " ya tenía", (n) x1, " abierto el cerrojo.";
			3:
				if (second) {
					"No parecía", (n) x1, " encajar en la cerradura.";
				} else {
					if (IsPluralNoun(player)) print "Necesitaban";
					else print "Necesitaba";
					" algún tipo de llave.";
				}
			4:
				if (IsPluralNoun(player)) print "Quitaron";
				else print "Quitó";
				print " el cerrojo ", (al) x1;
				if (second) print " con ", (the) second;
				".";
		}

	VagueGo:
		!! El usuario ha dicho IR sin especificar a dónde
		"[Tienes que especificar en qué dirección ir].";

	Verify:
		!!	1:	Éxito.
		!!	2:	Error en la verificación.
		switch (n) {
			1:
				"[Fichero de la partida verificado e intacto].";
			2:
				"[El fichero de la partida no parece intacto. Puede estar
				corrompido (a menos que estés utilizando un intérprete muy
				básico que no sea capaz de realizar la comprobación)].";
		}

	Wait:
		"Pasaba el tiempo...";

	Wake: !! TODO - Modificar
		"La cruda realidad es que aquello no era un sueño.";

	WakeOther:
		"No parecía necesario hacer aquello.";

	Wave:
		!!	1:	Si se intenta agitar un objeto que no está en el inventario.
		!!	2:	Si se agita un objeto que sí está en el inventario.
		switch (n) {
			1:
				print "No l", (o) x1, " ";
				if (IsPluralNoun(player)) print "tenían";
				else print "tenía";
				" ", (contigo) player, ".";
			2:
				if (IsPluralNoun(player)) print "Se sentían";
				else print "Se sentía";
				" ridícul", (o) player, " agitando ", (the) x1, ".";
		}

	WaveHands:
		!! La acción WaveHands se genera ante las frases "gesticula", "agita la
		!! mano", "sacude la mano", "saluda con la mano", etc.
		if (IsPluralNoun(player)) print "Se encontraban";
		else print "Se encontraba";
		" ridícul", (o) player, " gesticulando así.";

	Wear:
		!! 1: Error, el objeto no tiene el atributo "clothing".
		!! 2: Error, el usuario no tiene el objeto.
		!! 3: Error, el objeto ya tiene el atributo "worn".
		!! 4: Éxito.
		switch (n) {
			1:
				print "No ";
				if (IsPluralNoun(player)) print "podían ponerse";
				else print "podía ponerse";
				" aquello.";
			2:
				print "No ", (lo) x1, " ";
				if (IsPluralNoun(player)) print "tenían";
				else print "tenía";
 				".";
			3:
				print "Ya ", (lo) x1;
				if (IsPluralNoun(player)) print "llevaban";
				else print "llevaba";
				" puest", (o) x1, ".";
			4:
				if (IsPluralNoun(player)) print "Se pusieron";
				else print "Se puso";
				" ", (the) x1, ".";
		}

	Yes:
		"[La instrucción @<<SÍ@>> no tiene sentido en esta situación].";

];



!!==============================================================================
!!
!!	RECEPTACLES
!!	Contenedores (con capacidad definida)
!!
!!==============================================================================
!!
!!	File:			receptacles.h
!!	Author(s):		Peer Schaefer <peer@wolldingwacht.de> (lib. recept.h)
!!					J. Francisco Martín <jfm.lisaso@gmail.com> (traducción)
!!	Language:		ES (Castellano)
!!	System:			Inform-INFSP 6
!!	Platform:		Máquina-Z / GLULX
!!	Version:		2.1
!!	Released:		2014/02/06
!!	Notes:			Las funciones pueden no comportarse como se espera si se 
!!					utiliza una versión del compilador Inform igual o anterior 
!!					a la 6.15.
!!
!!------------------------------------------------------------------------------
!!
!!	# HISTORIAL DE VERSIONES
!!
!!	2.1: 2014/02/06	Traducción completa de la documentación.
!!	2.0: 2012/05/03	Correcciones y creación de la propiedad error_messages 
!!					sobre la clase Receptacle para separar la lógica y los 
!!					mensajes.
!!	1.0				Traducción de la librería original recept.h v1.0 de Peer 
!!					Schaefer, para implementar contenedores con capacidades 
!!					definidas.
!!
!!------------------------------------------------------------------------------
!!
!!	Copyright (c) 2002, 2006, Peer Schaefer
!!	Copyright (c) 2012, 2014, J. Francisco Martín
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
!!	# REFERENCIA
!!
!!	Esta librería implementa una nueva clase de objeto, llamada Receptacle. Los 
!!	receptáculos son contenedores o soportes con ciertas capacidades definidas 
!!	sobre el peso, volumen, tamaño y número de objetos que pueden albergar en 
!!	su interior o sobre ellos. Cada vez que se intenta colocar un objeto en un 
!!	Receptacle, éste comprobará si sus parámetros de capacidad son suficientes 
!!	para albergar o no al nuevo objeto.
!!
!!	Para indicar su peso, volumen y tamaño, los objetos del juego pueden tener 
!!	definidas las siguientes propiedades (no son obligatorias):
!!
!!	 *	weight	(peso)
!!	 *	volume	(volumen)
!!	 *	size	(tamaño. Representa la longitud máxima en cualquier eje. Ej: 
!!				la longitud de una flecha o de un bastón. Resulta obvio que la 
!!				capacidad de volumen de un carcaj termina "agotándose" cuando 
!!				se introducen suficientes flechas en él, pero la capacidad de 
!!				tamaño del carcaj no se agota con la suma de tamaños de las 
!!				flechas almacenadas en él: la capacidad de tamaño indica si una 
!!				flecha es o no demasiado larga para el carcaj.)
!!
!!	Cada una de estas tres propiedades puede ser un valor numérico o una rutina 
!!	que retorne un valor numérico. Si alguna de las tres propiedades no está 
!!	definida o tiene el valor 0 (cero), se interpretará que esa característica 
!!	del objeto será 0 (lo que indicaría que el objeto carece de peso, volumen, 
!!	o tamaño, o que se trata de una medida despreciable).
!!
!!	*** Nota: weight, volume y size se miden en unidades abstractas (son 
!!	simples números sin dimensión). Que una unidad se refiera, por ejemplo, a 
!!	un gramo, una libra, una tonelada, o la masa del sol, es decisión exclusiva 
!!	del programador.
!!
!!	Para crear un receptáculo que compruebe automáticamente peso, volumen y 
!!	tamaño de los objetos que se intenten introducir en él, se crea una nueva 
!!	clase Receptacle. Estos receptáculos pueden definir tres nuevas propiedades 
!!	(de nuevo, no son obligatorias):
!!
!!	 *	capacity_weight
!!	 *	capacity_volume
!!	 *	capacity_size
!!
!!	Cada una de estas tres propiedades puede ser un valor numérico o una rutina 
!!	que retorne un valor numérico. Si alguna de estas propiedades no está 
!!	definida o tiene el valor INFINITE_CAPACITY (una constante predefinida por 
!!	la librería), la capacidad respectiva para esa medida del receptáculo se 
!!	considerará infinita. 
!!
!!	Desde luego, los contenedores/soportes pueden tener también definidos un 
!!	peso, volumen y tamaño (ya que no se tratan sólo de contenedores/soportes, 
!!	si no también de objetos que pueden ser colocados en otros receptáculos).
!!
!!	En resumen:
!!
!!	 *	El jugador puede almacenar múltiples objetos en un Receptacle, siempre 
!!		que el peso total no exceda el valor capacity_weight del receptáculo.
!!	 *	El jugador puede almacenar múltiples objetos en un Receptacle, siempre 
!!		que el volumen total no exceda el valor capacity_volume del receptáculo.
!!	 *	Dicho de otra forma: capacity_weight y capacity_volume son valores que 
!!		acaban "agotándose" conforme se almacenan objetos en el receptáculo.
!!	 *	La propiedad capacity_size se comporta de forma diferente: no se trata 
!!		de un límite que se agote a medida que se va añadiendo más peso o 
!!		volumen al receptáculo, si no que se tiene que comprobar por separado 
!!		cada vez que se intenta introducir un nuevo objeto en él.
!!
!!	Por último, un Receptacle puede también tener definida una nueva propiedad 
!!	capacity_number. Este atributo tiene que ser bien un valor númerico o una 
!!	rutina que devuelva un valor numérico, e indica cuántos objetos (como 
!!	máximo) se pueden almacenar dentro de un receptáculo. Se mostrará un 
!!	mensaje de error cada vez que se intente introducir cualquier objeto una 
!!	vez se haya alcanzado ese máximo.
!!
!!
!!	# DETALLES TÉCNICOS
!!
!!	 *	Calcular el peso de un contenedor/soporte es un proceso recursivo: los 
!!		pesos de todos los objetos inmediatamente contenidos en él se añaden al 
!!		peso del propio contenedor/soporte. Ocurre igual con los objetos que 
!!		hay en el contenedor/soporte, si éstos a su vez albergan otros objetos, 
!!		y así sucesivamente.
!!	 *	Si el peso de un objeto viene dado por una rutina, esta rutina debería 
!!		devolver el peso TOTAL del objeto, incluyendo los pesos de todos los 
!!		objetos que alberga directa e indirectamente en él. En este caso, los 
!!		pesos de los objetos contenidos en el receptáculo NO se calculan 
!!		automáticamente. Esto añade flexibilidad a la hora de crear 
!!		receptáculos especiales (ej: una bolsa mágica cuyo peso es menor que el 
!!		de los objetos que contiene en su interior).
!!	 *	El volumen y los tamaños de los objetos que alberga un receptáculo NO 
!!		se añaden al volumen o tamaño del Receptacle (se asume que un 
!!		receptáculo estándar no es flexible y tiene unas proporciones fijas y 
!!		predeterminadas). Para reescribir este comportamiento se pueden definir 
!!		nuevas propiedades VOLUME y SIZE, de forma que calculen el volumen y 
!!		tamaño del receptáculo en tiempo de ejecución (ver EJEMPLO 3).
!!	 *	Es perfectamente posible crear un receptáculo cuya capacidad sea 
!!		superior a sus propias medidas (un comportamiento altamente improbable 
!!		en un objeto, pero que permite la creación de cajas mágicas, agujeros 
!!		negros y otros objetos extraños).
!!
!!
!!	# VERBOS DE DEPURACIÓN
!!
!!	Al compilar en modo depuración (con la constante DEBUG), la librería define 
!!	tres meta-acciones nuevas:
!!
!!	 *	xpeso OBJETO			imprime el peso del objeto
!!	 *	xdimensiones OBJETO		imprime todas las dimensiones del objeto
!!	 *	xcapacidad OBJETO		imprime todas laas capacidades del objeto
!!
!!------------------------------------------------------------------------------
!!
!!	# EJEMPLO 1
!!
!!	Creación de una caja con un volumen de 10 y una capacidad de volumen de 9, 
!!	y una piedra con un volumen de 2. El jugador puede poner hasta 4 piedras en 
!!	la caja (cuyo volumen total sería 2*4 = 8). Una quinta piedra no podría ser 
!!	introducida en la caja, puesto que su capacidad es 9 y el volumen total de 
!!	5 piedras sería de 10:
!!
!!		Receptacle -> box "caja"
!!		 with	name 'caja',
!!				volume 10,			! el volumen de la propia caja
!!				capacity_volume 9,	! la capacidad de la caja
!!		 has	container;
!!
!!		Object -> stone "piedra"
!!		 with	name 'piedra',
!!				volume 2;			! el volumen de la piedra
!!
!!------------------------------------------------------------------------------
!!
!!	# EJEMPLO 2
!!
!!	El siguiente ejemplo crea una caja de madera y una caja de acero:
!!
!!		Receptacle -> wooden_box "caja de madera"
!!		 with	name 'caja' 'madera',
!!				volume 10,			! volumen del objeto
!!				capacity_volume 9,	! capacidad de volumen del objeto
!!		 has	container;
!!
!!		Receptacle -> stell_box "caja de acero"
!!		 with	name 'caja' 'acero',
!!				volume 8,			! volumen del objeto
!!				capacity_volume 7,	! capacidad de volumen del objeto
!!		 has	container;
!!
!!	El jugador puede introducir la caja de acero (volumen 8) dentro de la caja 
!!	de madera (capacidad 9), pero la caja de madera (volumen 10) no se puede 
!!	introducir en la caja de acero (capacidad 7). Si se introduce un objeto de 
!!	volumen igual o mayor a 2 dentro de la caja de madera (como la piedra del 
!!	EJEMPLO 1), ya no se podría introducir la caja de acero en su interior, 
!!	porque ésta requiere un espacio libre de 8 o más.
!!
!!------------------------------------------------------------------------------
!!
!!	# EJEMPLO 3
!!
!!	El volumen y tamaño de los objetos contenidos en un receptáculo NO se 
!!	añaden a su volumen y tamaño total (se asume que los receptáculos no son 
!!	flexibles y tienen proporciones fijas). Si se desea crear una bolsa 
!!	flexible cuyo volumen aumente conforme se introducen objetos en su 
!!	interior, se debe implementar la rutina apropiada en su propiedad volume:
!!
!!		Receptacle -> bag "bolsa flexible"
!!		 with	name 'bolsa' 'flexible',
!!				capacity_volume 20,
!!				capacity_size 5,
!!				volume [ result i;
!!					!! Volumen mínimo de la bolsa (cuando está vacía):
!!					result = 1;
!!					!! Se suman los volúmenes de los objetos que contiene:
!!					objectloop (i in self)
!!						result = result + VolumeOf(i);
!!					!! Retorna el volumen total acumulado:
!!					return result;
!!				],
!!				size [ result i;
!!					!! Tamaño mínimo de la bolsa (cuando está vacía):
!!					result = 1;
!!					!! Se obtiene el objeto contenido de mayor tamaño:
!!					objectloop(i in self) 
!!						if (SizeOf(i) > result) result = SizeOf(i);
!!					!! El tamaño del mayor objeto contenido en ella determina 
!!					!! el tamaño actual de la bolsa:
!!					return result;
!!				],
!!		 has	container;
!!
!!------------------------------------------------------------------------------
!!
!!	# EJEMPLO 4
!!
!!	Los pesos de los objetos contenidos en él se añaden automáticamente al peso 
!!	total del receptáculo. Se puede sobreescribir este comportamiento 
!!	definiendo la propiedad weight como una rutina. El siguiente ejemplo crea 
!!	una bolsa mágica cuyo peso total es sólo la mitad del peso de los objetos 
!!	contenidos en su interior:
!!
!!		Receptacle -> magic_bag "bolsa mágica"
!!		 with	name 'bolsa' 'magica' 'maravillosa',
!!				capcity_volume 100,
!!				weight [ result i;
!!					!! Peso base de la bolsa (cuando está vacía):
!!					result = 1;
!!					!! Se suman los pesos de los objetos que contiene:
!!					objectloop(i in self)
!!						result = result + WeightOf(i);
!!					!! Retorna el 50% del peso total:
!!					return (result/2);
!!				],
!!		 has	container;
!!
!!------------------------------------------------------------------------------
System_file;

Class	FAKE_RECEPT					! Se definen las siete nuevas
 with	weight	0,					! propiedades sin usar espacio
		size	0,					! de programa ni memoria en
		volume	0,					! tiempo de ejecución
		capacity_weight	0,
		capacity_size	0,
		capacity_volume	0,
		capacity_number	0;

Constant INFINITE_CAPACITY -1;		! (-1) simboliza una capacidad infinita

!!==============================================================================
!! Funciones para calcular el peso, volumen y tamaño de cualquier objeto dado
!!------------------------------------------------------------------------------

[ WeightOf obj		w i;
	if (obj provides weight) {
		if (metaclass(obj.weight) == Routine) return indirect (obj.weight);
		w = obj.weight;
	} else  w = 0;
	if ((obj has container) || (obj has supporter))
		! Add weight of child-objects
		objectloop (i in obj) w = w + WeightOf (i);
	return w;
];

[ SizeOf obj;
	if (obj provides size) {
		if (metaclass(obj.size) == Routine) return indirect (obj.size);
		return obj.size;
	}
	return 0;
];

[ VolumeOf obj;
	if (obj provides volume) {
		if (metaclass(obj.volume) == Routine) return indirect (obj.volume);
		return obj.volume;
	}
	return 0;
];

!!==============================================================================
!! Funciones para calcular la capacidad de cualquier contenedor o soporte dado
!!------------------------------------------------------------------------------

[ CapacityWeightOf obj;
	if (obj provides capacity_weight) {
		if (metaclass(obj.capacity_weight) == Routine)
			return indirect (obj.capacity_weight);
		return obj.capacity_weight;
	}
	return INFINITE_CAPACITY;	! Unlimited weight capacity
];

[ CapacityVolumeOf obj;
	if (obj provides capacity_volume) {
		if (metaclass(obj.capacity_volume) == Routine)
			return indirect (obj.capacity_volume);
		return obj.capacity_volume;
	}
	return INFINITE_CAPACITY;	! Unlimited volume capacity
];

[ CapacitySizeOf obj;
	if (obj provides capacity_size) {
		if (metaclass(obj.capacity_size) == Routine)
			return indirect (obj.capacity_size);
		return obj.capacity_size;
	}
	return INFINITE_CAPACITY;	! Unlimited size capacity
];

[ CapacityNumberOf obj;
	if (obj provides capacity_number) {
		if (metaclass(obj.capacity_number) == Routine)
			return indirect (obj.capacity_number);
		return obj.capacity_number;
	}
	return INFINITE_CAPACITY;	! Unlimited number of objects
];

!!==============================================================================
!! Función auxiliar para comprobar si un contenedor o soporte tiene capacidad 
!! para soportar un objeto, dados ambos como argumentos. Retorna falso si el 
!! objeto no entra, verdadero en caso contrario.
!!------------------------------------------------------------------------------

[ CheckIfObjectFits receiver obj	s i;
	!! Se comprueba si el peso de obj está dentro de los límites de receiver:
	if ( CapacityWeightOf( receiver ) ~= INFINITE_CAPACITY ) {
		if ( WeightOf(obj) > CapacityWeightOf( receiver ))
			return false;
		s = 0; objectloop (i in receiver) s = s + WeightOf(i);
		if ( (s + WeightOf(obj)) > CapacityWeightOf (receiver) )
			return false;
	}
	!! Se comprueba si el volumen de obj está dentro de los límites de receiver:
	if ( CapacityVolumeOf (receiver) ~= INFINITE_CAPACITY ) {
		if ( VolumeOf(obj) > CapacityVolumeOf( receiver ))
			return false;
		s = 0; objectloop (i in receiver) s = s + VolumeOf(i);
		if ( (s + VolumeOf(obj)) > CapacityVolumeOf( receiver ))
			return false;
	}
	!! Se comprueba si el tamaño de obj está dentro de los límites de receiver:
	if ( CapacitySizeOf (receiver) ~= INFINITE_CAPACITY ) {
		if ( SizeOf(obj) > CapacitySizeOf( receiver ))
			return false;
	}
	!! Se comprueba el límite de número de objetos de receiver:
	if ( CapacityNumberOf (receiver) ~= INFINITE_CAPACITY ) {
		s = 0; objectloop (i in receiver) s++;
		if ( (s+1) > CapacityNumberOf( receiver ))
			return false;
	}
	!! El objeto encaja en el receptor:
	return true;
];

!!==============================================================================
!! Definición de la nueva clase Receptacle
!!------------------------------------------------------------------------------

Class	Receptacle
 with	before [ s i;
			Receive:
				!! Se comprueba el peso (si su capacidad no es infinita):
				if ( CapacityWeightOf( self ) ~= INFINITE_CAPACITY ) {
					if ( WeightOf(noun) > CapacityWeightOf( self ))
						return self.error_messages(1, noun);
					!! Se calcula el peso de todo el contenido
					s = 0; objectloop (i in self) s = s + WeightOf(i);
					if ( (s + WeightOf(noun)) > CapacityWeightOf (self) )
						return self.error_messages(2);
				}

				!! Se comprueba el volumen (si su capacidad no es infinita):
				if ( CapacityVolumeOf (self) ~= INFINITE_CAPACITY ) {
					if ( VolumeOf(noun) > CapacityVolumeOf( self ))
						return self.error_messages(3, noun);
					!! Se calcula el volumen de todo el contenido
					s = 0; objectloop (i in self) s = s + VolumeOf(i);
					if ( (s + VolumeOf(noun)) > CapacityVolumeOf( self ))
						return self.error_messages(4);
				}

				!! Se comprueba el tamaño (si su capacidad no es infinita):
				if ( CapacitySizeOf (self) ~= INFINITE_CAPACITY ) {
					if ( SizeOf(noun) > CapacitySizeOf( self ))
						return self.error_messages(5, noun);
				}

				!! Se comprueba el número (si su capacidad no es infinita):
				if ( CapacityNumberOf (self) ~= INFINITE_CAPACITY ) {
					s = 0; objectloop (i in self) s++;
					if ( (s+1) > CapacityNumberOf( self ))
						return self.error_messages(6);
				}

				return false;
		],
		!! Mensajes de error. Se producen al intentar meter en el receptáculo 
		!! un objeto que viola alguno de los límites de capacidad definidos
		error_messages [ id obj;
			switch (id) {
				1:
					!! Intentar meter en el bolsillo un objeto cuyo peso supera 
					!! el límite permitido
					print_ret (The) obj, " ", (es) obj, " demasiado pesad", 
					(o) obj ," para ", (the) obj ,".";
				2:
					!! Intentar meter en el bolsillo un objeto cuyo peso, unido 
					!! al del resto de objetos que hay ya en el bolsillo, 
					!! superan el límite permitido
					print_ret (The) self ," ha", (n) self ," alcanzado su 
					capacidad máxima.";
				3:
					!! Intentar meter en el bolsillo un objeto cuyo volumen 
					!! supera el límite permitido
					print_ret (The) obj ," no encaja", (n) obj ," dentro de ", 
					(the) self ,".";
				4:
					!! Intentar meter en el bolsillo un objeto cuyo volumen, 
					!! unido al del resto de objetos que hay ya en el bolsillo, 
					!! superan el límite permitido
					print_ret (The) self ," ha", (n) self ," alcanzado su 
					capacidad máxima.";
				5:
					!! Intentar meter en el bolsillo un objeto cuyo tamaño 
					!! supera el límite permitido
					print_ret (The) obj ," ", (es) obj ," demasiado grande", 
					(s) obj ," para ", (the) self ,".";
				6:
					!! Intentar meter en el bolsillo un objeto después de haber 
					!! alcanzado el límite de objetos introducidos permitido
					"En ", (the) self ," no entran ya más cosas.";
			}
		];

!!==============================================================================
!! Verbos de depuración
!!------------------------------------------------------------------------------

#Ifdef DEBUG;

Verb meta 'xpeso' 'xweight'			* noun	-> MetaWeight;
Verb meta 'xdimensiones' 'xmeasure'	* noun	-> MetaMeasure;
Verb meta 'xcapacidad' 'xcapacity'	* noun	-> MetaCapacity;

[ MetaWeightSub;
	print (The) noun, " pesa", (n) noun ," ",
	WeightOf (noun), " unidad";
	if ( WeightOf( noun ) ~= 1 ) print "es";
	new_line;
	return true;
];

[ MetaMeasureSub;
	print (The) noun, ":^";
	spaces(6);	print "Peso: ",		WeightOf(noun),	" unidades^";
	spaces(6);	print "Tamaño: ",	SizeOf(noun),	" unidades^";
	spaces(6);	print "Volumen: ",	VolumeOf(noun),	" unidades^";
	return true;
];

[ MetaCapacitySub;
	print (The) noun, ":^";

	spaces(6); print "Capacidad (peso): ";
	if (CapacityWeightOf(noun) == INFINITE_CAPACITY) print "infinita^";
	else print CapacityWeightOf(noun), " unidades^";

	spaces(6); print "Capacidad (tamaño): ";
	if (CapacitySizeOf(noun) == INFINITE_CAPACITY) print "infinita^";
	else print CapacitySizeOf(noun), " unidades^";

	spaces(6); print "Capacidad (volumen): ";
	if (CapacityVolumeOf(noun) == INFINITE_CAPACITY) print "infinita^";
	else print CapacityVolumeOf(noun), " unidades^";

	spaces(6); print "Capacidad (número de objetos): ";
	if (CapacityNumberOf(noun) == INFINITE_CAPACITY) print "infinita^";
	else print CapacityNumberOf(noun), "^";

	return true;
];

#Endif; ! DEBUG;



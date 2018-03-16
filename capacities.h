

!!==============================================================================
!!
!!	CAPACITIES
!!	Extensión a las reglas de capacidad para contenedores y soportes
!!
!!==============================================================================
!!
!!	Archivo:		capacities.h
!!	Autor(es):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!					Peer Schaefer
!!	Idioma:			ES (Español)
!!	Sistema:		Inform-INFSP 6
!!	Plataforma:		Máquina-Z/Glulx
!!	Versión:		1.0
!!	Fecha:			2018/03/08
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
!!	HISTORIAL DE VERSIONES
!!
!!	1.0: 2018/03/08	Versión inicial de la extensión.
!!
!!------------------------------------------------------------------------------
!!
!!	INTRODUCCIÓN
!!
!!	La extensión 'capacities.h' implementa un conjunto de rutinas que extienden
!!	el comportamiento por defecto de la librería para tratar las reglas de
!!	capacidad de contenedores y soportes. En concreto, además del límite de la
!!	librería que establece el número máximo de objetos que pueden ser
!!	contenidos por un contenedor/soporte, se añade lógica para tratar límites
!!	de peso, volumen y tamaño. Está basada en la extensión 'recept.h' de Peer
!!	Schaefer <peer@wolldingwacht.de>.
!!
!!	Para utilizar la extensión hay que añadir la siguiente línea en el fichero
!!	principal de la obra, después de la línea 'Include "Parser";':
!!
!!		Include "capacities";
!!
!!------------------------------------------------------------------------------
System_file;

#Ifndef CAPACITIES;
Constant CAPACITIES;
Message "Incluyendo 'capacities' v1.0";

Constant CAPACITIES_INFINITE	-1;
Constant CAPACITIES_NUMBER		0;
Constant CAPACITIES_SIZE		1;
Constant CAPACITIES_VOLUME		2;
Constant CAPACITIES_WEIGHT		3;

!! Clase falsa para definir las 6 nuevas propiedades utilizadas por la
!! extensión sin consumir memoria adicional:

Class	capacities_dummy
 with	capacity_size 0,
		capacity_volume 0,
		capacity_weight 0,
		size 0,
		volume 0,
		weight 0;

!!------------------------------------------------------------------------------
!! Calcula el número de objetos contenidos por él, el tamaño, volumen o el peso
!! de un objeto dado. La medida concreta que se calcula depende del código
!! pasado como parámetro.
!!
!!	@param {integer} measure_code - Código que identifica la medida concreta
!!		que se quiere calcular. Sus posibles valores son:
!!		0.	Número de objetos contenidos directamente por 'obj'
!!		1.	Tamaño de 'obj'
!!		2.	Volumen de 'obj'
!!		3.	Peso total de 'obj' (incluye el peso de los objetos contenidos)
!!	@param {Object} obj - Objeto del que se desea calcular una medida
!!	@returns {integer} Número de objetos contenidos por 'obj', su tamaño,
!!		volumen o su peso total, en función del código 'measure_code'
!!------------------------------------------------------------------------------
[ GetMeasure measure_code obj
	i result;
	result = 0;
	switch (measure_code) {
		CAPACITIES_NUMBER:
			objectloop(i in obj) result++;
		CAPACITIES_SIZE:
			if (obj provides size) {
				if (metaclass(obj.size) == Routine) {
					return indirect(obj.size);
				}
				result = obj.size;
			}
		CAPACITIES_VOLUME:
			if (obj provides volume) {
				if (metaclass(obj.volume) == Routine) {
					return indirect(obj.volume);
				}
				result = obj.volume;
			}
		CAPACITIES_WEIGHT:
			if (obj provides weight) {
				if (metaclass(obj.weight) == Routine) {
					return indirect(obj.weight);
				}
				result = obj.weight;
			}
			if ((obj has container) || (obj has supporter)) {
				!! Llamada recursiva para agregar el peso de sus contenidos
				objectloop(i in obj)
					result = result + GetMeasure(CAPACITIES_WEIGHT, i);
			}
	}
	return result;
];

!!------------------------------------------------------------------------------
!! Calcula la capacidad de número de objetos, tamaño, volumen o peso de un
!! objeto dado. La medida de capacidad concreta que se calcula depende del
!! código pasado como parámetro.
!!
!!	@param {integer} measure_code - Código que identifica la capacidad concreta
!!		que se quiere calcular. Sus posibles valores son:
!!		0.	Número de objetos total que puede contener 'obj'
!!		1.	Tamaño máximo de los objetos que puede contener 'obj'
!!		2.	Volumen máximo total que puede contener 'obj'
!!		3.	Peso máximo total que puede contener 'obj'
!!	@param {Object} obj - Objeto del que se quiere conocer un lím. de capacidad
!!	@returns {integer} Capacidad de 'obj' en número de objetos, tamaño, volumen
!!		o peso, en función del código 'measure_code'
!!------------------------------------------------------------------------------
[ GetCapacity measure_code obj
	result;
	result = CAPACITIES_INFINITE;
	switch (measure_code) {
		CAPACITIES_NUMBER:
			if (obj provides capacity) {
				if (metaclass(obj.capacity) == Routine) {
					return indirect(obj.capacity);
				}
				result = obj.capacity;
			}
		CAPACITIES_SIZE:
			if (obj provides capacity_size) {
				if (metaclass(obj.capacity_size) == Routine) {
					return indirect(obj.capacity_size);
				}
				result = obj.capacity_size;
			}
		CAPACITIES_VOLUME:
			if (obj provides capacity_volume) {
				if (metaclass(obj.capacity_volume) == Routine) {
					return indirect(obj.capacity_volume);
				}
				result = obj.capacity_volume;
			}
		CAPACITIES_WEIGHT:
			if (obj provides capacity_weight) {
				if (metaclass(obj.capacity_weight) == Routine) {
					return indirect(obj.capacity_weight);
				}
				result = obj.capacity_weight;
			}
	}
	return result;
];

!!------------------------------------------------------------------------------
!! Comprueba si un objeto tiene capacidad suficiente para albergar a otro,
!! pasados ambos como parámetro. El resultado es un código numérico positivo
!! si tiene capacidad suficiente, o negativo en caso contrario.
!!
!!	@param {Object} receiver - Objeto del que se comprueba si tiene capacidad
!!		suficiente para albergar a 'obj'
!!	@param {Object} obj - Objeto con posibles propiedades de tamaño, volumen y
!!		peso que se compara con los límites de capacidad de 'receiver'
!!	@returns {integer} Código numérico con el resultado de la comprobación:
!!		 1)	'receiver' puede albergar al objeto 'obj'
!!		-1)	se supera la cantidad máxima de objetos que puede tener 'receiver'
!!		-2) 'obj' supera el tamaño máximo admitido por 'receiver'
!!		-3) 'obj' supera el volumen máximo admitido por 'receiver'
!!		-4) el volumen agregado supera el volumen total admitido por 'receiver'
!!		-5)	'obj' supera el peso máximo admitido por 'receiver'
!!		-6) el peso agregado supera el peso total admitido por 'receiver'
!!------------------------------------------------------------------------------
[ CheckIfObjectFits receiver obj
	receiver_capacity measure i;
	!! 0) Se comprueba la cantidad máxima de objetos admitida:
	receiver_capacity = GetCapacity(CAPACITIES_NUMBER, receiver);
	measure = 1;
	objectloop(i in receiver) measure++;
	if (measure > receiver_capacity) return -1;
	!! 1) Se comprueba el límite de tamaño:
	receiver_capacity = GetCapacity(CAPACITIES_SIZE, receiver);
	if (receiver_capacity ~= CAPACITIES_INFINITE) {
		if (GetMeasure(CAPACITIES_SIZE, obj) > receiver_capacity) return -2;
	}
	!! 2) Se comprueba el límite de volumen:
	receiver_capacity = GetCapacity(CAPACITIES_VOLUME, receiver);
	if (receiver_capacity ~= CAPACITIES_INFINITE) {
		measure = GetMeasure(CAPACITIES_VOLUME, obj);
		if (measure > receiver_capacity) return -3;
		else {
			objectloop(i in receiver) {
				measure = measure + GetMeasure(CAPACITIES_VOLUME, i);
			}
			if (measure > receiver_capacity) return -4;
		}
	}
	!! 3) Se comprueba el límite de peso:
	receiver_capacity = GetCapacity(CAPACITIES_WEIGHT, receiver);
	if (receiver_capacity ~= CAPACITIES_INFINITE) {
		measure = GetMeasure(CAPACITIES_WEIGHT, obj);
		if (measure > receiver_capacity) return -5;
		else {
			objectloop(i in receiver) {
				measure = measure + GetMeasure(CAPACITIES_WEIGHT, i);
			}
			if (measure > receiver_capacity) return -6;
		}
	}
	return 1;
];

!!------------------------------------------------------------------------------

#Ifdef DEBUG;
Verb meta	'dimensiones' 'measure'	* noun -> DebugMeasure;
Verb meta	'capacidad' 'capacity'	* noun -> DebugCapacity;

[ DebugMeasureSub;
	print (The) noun, ":^";
	spaces(6); print "Tamaño: ", GetMeasure(CAPACITIES_SIZE, noun), " ud(s)^";
	spaces(6); print "Volumen: ", GetMeasure(CAPACITIES_VOLUME, noun)," ud(s)^";
	spaces(6); print "Peso: ", GetMeasure(CAPACITIES_WEIGHT, noun), " ud(s)^";
	return true;
];

[ DebugCapacitySub
	i;
	print (The) noun, ":^";
	i = GetCapacity(CAPACITIES_NUMBER);
	spaces(6); print "Capacidad (número de objetos): ";
	if (i == CAPACITIES_INFINITE) print "infinita^";
	else print i, "^";
	i = GetCapacity(CAPACITIES_SIZE);
	spaces(6); print "Capacidad (tamaño): ";
	if (i == CAPACITIES_INFINITE) print "infinita^";
	else print i, "^";
	i = GetCapacity(CAPACITIES_VOLUME);
	spaces(6); print "Capacidad (volumen): ";
	if (i == CAPACITIES_INFINITE) print "infinita^";
	else print i, "^";
	i = GetCapacity(CAPACITIES_WEIGHT);
	spaces(6); print "Capacidad (peso): ";
	if (i == CAPACITIES_INFINITE) print "infinita^";
	else print i, "^";
];
#Endif; ! DEBUG;

#Endif; ! CAPACITIES;

!------------------------------------------------------------------------------
! ALGORITMO DE BUSQUEDA DE CAMINOS
! (método breath first)
! 2009 por Mastodon
!
! Implementa la funcion "calcula_ruta" entre dos localidades:
!
!	- Permite especificar áreas de búsqueda (para optimizar los cálculos), para
!     lo cual se debe definir la propiedad area en las localidades (area "Pueblo" o
!     area "Bosque", etc)... Si se especifica AREA_TODO, se pillan todas las localidades
!     pero entonces podría ser lento, dependiendo de las locs de la aventura.
! 	- Todas las localidades que se deseen tener en cuenta deben heredar de la 
!     clase 'Enrutable'
!	- Implementa el algoritmo de búsqueda Breath-First para el camino más corto 
!     (algoritmo óptimo y completo)
!	- Las localidades que implementen una rutina como dirección, deberán definir
!     en la propiedad ruta_dir_to una función o valor que devuelva la localidad
!     de destino SIN imprimir ningún mensaje.
!   - Debe definirse la constante MAX_LON_RUTA con el número máximo de pasos
!     para un camino (por defecto 20)
!
!   Uso:
!
!   calcula_ruta(loc_origen, loc_destino, NOMBRE_AREA, array_destino, almacenar_locs)
!
!   Parámetros:
!      - loc_origen/loc_destino : nombres de las localidades origen y destino
!      - NOMBRE_AREA : potencia de dos (o suma de) que identifica las áreas a 
!        buscar, o bien AREA_TODO para buscar en todo el mapa.
!      - array_destino(opc) : array donde se almacenan las direcciones, tendrá
!        tamaño MAX_LON_RUTA+1. O bien no especificar para que el resultado
!        se almacene en el array global "ruta_calculada"
!      - almacenar_locs(opc) : si se especifica un valor diferente de 0, se almacenarán
!        las localidades por las que hay que pasar, en vez de las direcciones
!--------------------------------------------------------------------------------

!Constant DEBUG_RUTA;
!Constant DEBUG_RUTA_2; ! para probar con el maze de Zork (al final)

Ifndef MAX_LON_RUTA;
Constant MAX_LON_RUTA 20;
Endif;

! ruta_calculada-->0 = longitud de la ruta
! en ruta_calculada-->1 al MAX_LON, las direcciones en las que hay que moverse
! por ejemplo n_obj s_obj s_obj ....
Array ruta_calculada --> MAX_LON_RUTA+1; 

! Se puede definir un área al que pertenezca una localidad, para optimizar las búsquedas dentro de
! una o varias áreas en vez de todo el mapa. Definir las áreas como constantes potencias de 2, ejemplo:
! Constant AREA_PUEBLO 1;
! Constant AREA_BOSQUE 2;
! Constant AREA_CUEVAS 4;
! ..etc..
! Por defecto las localidades se definen como AREA_TODO
! Se puede hacer la búsqueda sobre varias áreas sumándolas (AREA_BOSQUE+AREA_CUEVA)

Constant AREA_TODO 0;

class Enrutable
with
	area AREA_TODO, ! redefinir
	funcOValor [dir; 
		switch (metaclass(self.dir))
		{
			Object:
				return self.dir;
			default:
				return 0;
		}
	],
	ruta_padre 0,     ! Padre del nodo en la ruta
	ruta_prof 0,      ! Número de pasos desde el origen
	ruta_dir_from 0,       ! Dirección desde el padre en la ruta
	ruta_n_to [; return self.funcOValor(n_to); ],
	ruta_s_to [; return self.funcOValor(s_to); ],
	ruta_e_to [; return self.funcOValor(e_to); ],
	ruta_w_to [; return self.funcOValor(w_to); ],
	ruta_ne_to [; return self.funcOValor(ne_to); ],
	ruta_nw_to [; return self.funcOValor(nw_to); ],
	ruta_se_to [; return self.funcOValor(se_to); ],
	ruta_sw_to [; return self.funcOValor(sw_to); ],
	ruta_u_to [; return self.funcOValor(u_to); ],
	ruta_d_to [; return self.funcOValor(d_to); ],
	ruta_in_to [; return self.funcOValor(in_to); ],
	ruta_out_to [; return self.funcOValor(out_to); ]
;

[ calcula_ruta loc_origen loc_destino nombre_area array_destino almacenar_locs nivel tmp;
	#Ifdef DEBUG_RUTA;
	print "[RT: Búsqueda de ruta entre ~", (name) loc_origen, "~ y ~", (name) loc_destino, "~]^";
	#EndIf;
	InicializarRuta(nombre_area, array_destino); ! pone a cero todos los nodos
	nivel = 1;
	if (loc_origen == loc_destino) 
	{
		#Ifdef DEBUG_RUTA;
		print "[RT: Origen y destino coinciden]^";
		#EndIf;
		return;
	}
	
	loc_origen.ruta_padre = loc_origen;
	tmp = crear_hijos(loc_origen, loc_destino, nombre_area, nivel);
	switch (tmp)
	{
		0: ! No hay nodos => no se encuentra ruta
			#Ifdef DEBUG_RUTA;
			print "[RT: El nodo inicial no tiene hijos]^";
			#EndIf;
			rfalse;
		2: ! Se encontró el destino
			#Ifdef DEBUG_RUTA;
			print "[RT: Se encontró el destino en el nodo inicial]^";
			#EndIf;
			trazar_ruta(loc_origen, loc_destino, array_destino, almacenar_locs);
			rtrue;
	}
	
	while (nivel < MAX_LON_RUTA)
	{
		nivel++;
		#Ifdef DEBUG_RUTA;
		print "[RT: Nivel de búsqueda:", nivel, "]^";
		#EndIf;
		tmp = establecer_siguiente_nivel(loc_destino, nombre_area, nivel);
		switch (tmp)
		{
			0: ! No hay nodos => no se encuentra ruta
				#Ifdef DEBUG_RUTA;
				print "[RT: No se encontraron nodos en el nivel actual]^";
				#EndIf;
				rfalse;
			2: ! Se encontró el destino
				#Ifdef DEBUG_RUTA;
				print "[RT: Se encontró el destino en el nivel actual]^";
				#EndIf;
				trazar_ruta(loc_origen, loc_destino, array_destino, almacenar_locs);
				rtrue;
		}
	}
	#Ifdef DEBUG_RUTA;
	print "[RT: Superada la longitud máxima sin haber encontrado el destino]^";
	#EndIf;
	
];

[ InicializarRuta nombre_area array_destino o;
	if (array_destino == 0) array_destino = ruta_calculada;
	array_destino-->0 = 0;
	objectloop (o ofclass Enrutable && 
	            (nombre_area == AREA_TODO || (nombre_area&o.area)))
	{
		o.ruta_padre = 0;
		o.ruta_prof = 0;
		o.ruta_dir_from = 0;
	}
];

! Devuelve 0->no hay hijos; 1->Hay hijos; 2->Hay hijos y uno de ellos es el destino
[ crear_hijos loc_origen loc_destino nombre_area nivel tmp hijos;
	#Ifdef DEBUG_RUTA;
	print "[RT: Buscando destinos para ~", (name) loc_origen, "~]^";
	#EndIf;
    hijos = 0;
    
    tmp = crear_hijo(loc_origen, loc_destino, nombre_area, nivel, ruta_n_to);
    if (tmp == 2) return 2;
    hijos = hijos + tmp;
    tmp = crear_hijo(loc_origen, loc_destino, nombre_area, nivel, ruta_s_to);
    if (tmp == 2) return 2;
    hijos = hijos + tmp;
    tmp = crear_hijo(loc_origen, loc_destino, nombre_area, nivel, ruta_e_to);
    if (tmp == 2) return 2;
    hijos = hijos + tmp;
    tmp = crear_hijo(loc_origen, loc_destino, nombre_area, nivel, ruta_w_to);
    if (tmp == 2) return 2;
    hijos = hijos + tmp;
    tmp = crear_hijo(loc_origen, loc_destino, nombre_area, nivel, ruta_ne_to);
    if (tmp == 2) return 2;
    hijos = hijos + tmp;
    tmp = crear_hijo(loc_origen, loc_destino, nombre_area, nivel, ruta_nw_to);
    if (tmp == 2) return 2;
    hijos = hijos + tmp;
    tmp = crear_hijo(loc_origen, loc_destino, nombre_area, nivel, ruta_se_to);
    if (tmp == 2) return 2;
    hijos = hijos + tmp;
    tmp = crear_hijo(loc_origen, loc_destino, nombre_area, nivel, ruta_sw_to);
    if (tmp == 2) return 2;
    hijos = hijos + tmp;
    tmp = crear_hijo(loc_origen, loc_destino, nombre_area, nivel, ruta_u_to);
    if (tmp == 2) return 2;
    hijos = hijos + tmp;
    tmp = crear_hijo(loc_origen, loc_destino, nombre_area, nivel, ruta_d_to);
    if (tmp == 2) return 2;
    hijos = hijos + tmp;
    tmp = crear_hijo(loc_origen, loc_destino, nombre_area, nivel, ruta_in_to);
    if (tmp == 2) return 2;
    hijos = hijos + tmp;
    tmp = crear_hijo(loc_origen, loc_destino, nombre_area, nivel, ruta_out_to);
    if (tmp == 2) return 2;
    hijos = hijos + tmp;
	
	if (hijos) 
		return 1;
	else
		return 0;
];

[ crear_hijo loc_origen loc_destino nombre_area nivel dir tmp;
	tmp = loc_origen.dir();
	
	if ((tmp ofclass Enrutable) && 
	    (nombre_area==AREA_TODO || (tmp.area&nombre_area)) &&
	    tmp.ruta_padre == 0)
	{
		#Ifdef DEBUG_RUTA;
		print "  [RT: Encontrada localidad ~", (name) tmp, "~ al ", (name)dir_to_obj(dir), "]^";
		#EndIf;
		tmp.ruta_padre = loc_origen;
		tmp.ruta_prof = nivel;
		tmp.ruta_dir_from = dir_to_obj(dir);
		if (tmp == loc_destino) 
			return 2;
		else
			return 1;
	}
	return 0;
];

[ dir_to_obj dir;
	switch (dir)
	{
		ruta_n_to: return n_obj;
		ruta_s_to: return s_obj;
		ruta_e_to: return e_obj;
		ruta_w_to: return w_obj;
		ruta_ne_to: return ne_obj;
		ruta_nw_to: return nw_obj;
		ruta_se_to: return se_obj;
		ruta_sw_to: return sw_obj;
		ruta_u_to: return u_obj;
		ruta_d_to: return d_obj;
		ruta_in_to: return in_obj;
		ruta_out_to: return out_obj;
		#Ifdef DEBUG_RUTA;
		default: print "[RT: dir_to_obj ERROR]^";
		#EndIf;
	}
];
	
[ trazar_ruta loc_origen loc_destino array_destino almacenar_locs;
	if (array_destino == 0)
		array_destino = ruta_calculada;
	if (array_destino-->0 == 0)
	{
		array_destino-->0 = loc_destino.ruta_prof;
		#Ifdef DEBUG_RUTA;
		print "[RT: Ruta conseguida de longitud:", ruta_calculada-->0, "]^";
		#EndIf;
	}
	if (loc_destino.ruta_padre == loc_origen)
	{
		if (almacenar_locs)
			array_destino-->loc_destino.ruta_prof = loc_destino;
		else
			array_destino-->loc_destino.ruta_prof = loc_destino.ruta_dir_from;
		#Ifdef DEBUG_RUTA;
		print "[RT: Paso de ruta ~", (name) loc_destino.ruta_dir_from, "~]^";
		#EndIf;
		
	}
	else
	{
		trazar_ruta(loc_origen, loc_destino.ruta_padre, array_destino, almacenar_locs);
		if (almacenar_locs)
			array_destino-->loc_destino.ruta_prof = loc_destino;
		else
			array_destino-->loc_destino.ruta_prof = loc_destino.ruta_dir_from;
		#Ifdef DEBUG_RUTA;
		print "[RT: Paso de ruta ~", (name) loc_destino.ruta_dir_from, "~]^";
		#EndIf;
	}
];

! Devuelve 0->no hay hijos; 1->Hay hijos; 2->Hay hijos y uno de ellos es el destino
[ establecer_siguiente_nivel loc_destino nombre_area nivel o tmp hijos;
    hijos = 0;
	objectloop (o ofclass Enrutable &&
	            (nombre_area == AREA_TODO || (nombre_area&o.area)) &&
	            o.ruta_prof==nivel-1)
	{
		tmp = crear_hijos(o, loc_destino, nombre_area, nivel);
		switch (tmp)
		{
			1: 
				hijos = 1;
			2:
				return 2;
		}	
	}
	
	return hijos;
];

[ pintar_ruta array_destino i;
	if (array_destino == 0)
		array_destino = ruta_calculada;
	print "[ ";
	if (array_destino-->0 == 0)
	{
		print "RUTA VACIA ";
	}
	else
		for (i = 1: i <= array_destino-->0: i++)
		{
			print (name)array_destino-->i, " ";
		}
	print "]";
];


!--------------------------------------------------------------------
! Un pequeño mapa para probar en modo DEBUG.... El laberinto de Zork
!---------------------------------------------------------------------


#Ifdef DEBUG_RUTA_2;

Enrutable Maze_1 "Maze [1]"
with n_to maze_1, s_to maze_4, w_to maze_2;
	
Enrutable Dead_End_1 "Dead End [1]"
with s_to maze_2;

Enrutable Maze_2 "Maze [2]"
with n_to maze_1, e_to dead_end_1, w_to maze_3;

Enrutable maze_4 "Maze [4]"
with d_to maze_2, e_to maze_3, s_to maze_1;

Enrutable maze_3 "Maze [3]"
with w_to maze_4, u_to maze_5, n_to maze_2;

Enrutable maze_5 "Maze [5]"
with n_to maze_3, e_to dead_end_2, sw_to maze_6;

Enrutable dead_end_2 "Dead End [2]"
with w_to maze_5;

Enrutable maze_6 "Maze [6]"
with u_to maze_11, e_to maze_7, w_to maze_6;

Enrutable maze_7 "Maze [7]"
with w_to maze_6, e_to maze_8, s_to maze_10, u_to maze_9, d_to dead_end_1;

Enrutable dead_end_4 "Dead End [4]"
with s_to maze_14;

Enrutable maze_14 "Maze [14]"
with d_to maze_5, u_to maze_11, n_to dead_end_4;

Enrutable maze_11 "Maze [11]"
with s_to maze_13, w_to maze_14, d_to maze_15, nw_to maze_11;

Enrutable maze_9 "Maze [9]"
with ne_to maze_7, s_to maze_7, nw_to maze_9, w_to maze_10;

Enrutable maze_8 "Maze [8]"
with ne_to maze_7, se_to dead_end_3, w_to maze_8;

Enrutable maze_13 "Maze [13]"
with e_to maze_11, s_to maze_12, w_to maze_15, d_to maze_14;

Enrutable maze_10 "Maze [10]"
with w_to maze_9, s_to maze_7, se_to cyclops_room;

Enrutable treasure_room "Treasure Room"
with d_to cyclops_room;

Enrutable dead_end_3 "Dead End [3]"
with n_to maze_8;

Enrutable maze_12 "Maze [12]"
with w_to maze_13, e_to maze_11, u_to maze_15;

Enrutable grating_room "Grating Room"
with sw_to maze_15;

Enrutable maze_15 "Maze [15]"
with d_to maze_12, nw_to maze_13, sw_to maze_14, ne_to grating_room;

Enrutable cyclops_room "Cyclops Room"
with nw_to maze_10, u_to treasure_room, e_to strange_passage;

Enrutable strange_passage "Strange Passage"
with w_to cyclops_room;

#EndIf;


!!==============================================================================
!!
!!	AIM AND FIRE
!!	Sistema de apuntado y disparo
!!
!!==============================================================================
!!
!!	File:			aimAndFire.h
!!	Author(s):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!	Language:		ES (Castellano)
!!	System:			Inform-INFSP 6
!!	Platform:		Máquina-Z / GLULX
!!	Version:		5.0
!!	Released:		2018/01/17
!!
!!------------------------------------------------------------------------------
!!
!!	Copyright (c) 2012, 2018, J. Francisco Martín
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
!!	# HISTORIAL DE VERSIONES
!!
!!	5.0: 2018/01/17	Redefinición de la interfaz del objeto gestor. Adición de
!!					nivel de dificultad, modo de operación probabilista (usado
!!					en Máquina-Z), formato del resultado basado en una división
!!					en zonas de la ventana de estado.
!!	4.4: 2017/08/04	Revisión de comentarios de la extensión.
!!	4.3: 2016/10/04	Parametrización del posicionamiento de las guías centrales
!!					en la animación de apuntado. Extensión de la interfaz:
!!					'get_is_distance():integer', 'set_is_distance(integer)'.
!!	4.2: 2014/08/12 Extensión de la interfaz del gestor: método
!!					'get_status_window_width()'.
!!	4.1: 2014/07/28	Refactorización de la lógica de apuntado y disparo en el
!!					objeto gestor para evitar interferencias con otros sistemas
!!					que puedan hacer uso del temporizador Glk.
!!	4.0: 2014/03/19	Desactivada la lógica del Movimiento Armónico Simple.
!!					Ventana de estado parametrizada.
!!	3.0: 2012/07/05	Pruebas con las ecuaciones del Movimiento Armónico Simple.
!!					Modo de depuración.
!!	2.0: 2012/		Refactorización general, correcciones de lógica y adición
!!					comentarios.
!!	1.0: 2012/		Sistema de apuntado y disparo basado en una animación
!!					interactiva usando el temporizador Glk.
!!
!!------------------------------------------------------------------------------
!!
!!	# INTRODUCCIÓN
!!
!!	'AimAndFire' es una extensión para la librería Inform que implementa un
!!	sistema de apuntado y disparo basado en una animación interactiva en la
!!	máquina virtual GLULX. Para facilitar la portabilidad de las obras a
!!	Máquina-Z, implementa además un método alternativo basado en
!!	probabilidades que no requiere del temporizador Glk exclusivo de GLULX.
!!
!!
!!	# 'AIM AND FIRE' EN GLULX
!!
!!	Aprovechando las funciones de tiempo real de GLULX, el mecanismo principal
!!	de 'AimAndFire' utiliza una animación para representar la acción de
!!	apuntar, y determina el éxito del disparo en función de la entrada del
!!	usuario y el estado de la animación. Al iniciar el mecanismo, los
!!	contenidos de la ventana de estado de la obra se reemplazan por una
!!	retícula de apuntado animada con un movimiento de desplazamiento de extremo
!!	a extremo de la ventana hasta que el usuario pulsa una tecla. El resultado
!!	de la acción se determina en función de lo lejos del centro de la ventana
!!	de estado que se haya conseguido detener la retícula.
!!
!!	Para utilizar el sistema, el desarrollador de la obra debe incluir la
!!	siguiente llamada dentro del punto de entrada 'HandleGlkEvent':
!!
!!		[ HandleGlkEvent ev;
!!			if (ev-->0 == 1) ! evtype_Timer
!!				AimingManager.tick();
!!		];
!!
!!
!!	# 'AIM AND FIRE' EN MÁQUINA-Z
!!
!!	Como se ha indicado anteriormente, el uso del temporizador Glk es exclusivo
!!	de GLULX así que las obras compiladas para Máquina-Z no pueden hacer uso de
!!	él. Para facilitar la creación de obras biplataforma, 'AimAndFire'
!!	implementa una aproximación simplificada de la funcionalidad basada en
!!	probabilidades dependientes de la dificultad del sistema. Además esta
!!	dificultad, modificable en tiempo de ejecución, permite al desarrollador la
!!	posibilidad de establecer probabilidades de 0 o 1 ---indicando porcentajes
!!	de dificultad del 100% y del 0%, respectivamente--- que fuerzan el fallo o
!!	el acierto del sistema, de modo que puede eliminarse el factor probabilista
!!	y hacer que el resultado dependa exclusivamente de algún parámetro
!!	arbitrario como la resolución de un 'puzzle' o un desafío lógico por parte
!!	del usuario, por ejemplo.
!!
!!	En GLULX se puede utilizar también este modo de funcionamiento.
!!
!!
!!	# OBJETO GESTOR
!!
!!	La extensión define un objeto gestor 'AimingManager' en el que se
!!	implementan todas las funcionalidades del sistema. A continuación se ofrece
!!	una relación de métodos que conforman la interfaz pública del gestor. En la
!!	propia definición del objeto se incluye documentación exhaustiva:
!!
!!	-	aim_and_fire(probabilistic:boolean, reset_position_flag:boolean)
!!			: integer
!!	-	get_delay_value() : integer
!!	-	get_difficulty() : integer
!!	-	get_format_type() : integer
!!	-	get_grid() : String|integer
!!	-	get_grid_max_vx_factor() : integer
!!	-	get_grid_min_vx() : integer
!!	-	get_iron_sight_distance() : integer
!!	-	get_iron_sight_symbol() : character|integer
!!	-	get_status_window() : Object
!!	-	reset()
!!	-	set_delay_value(a:integer) : integer
!!	-	set_difficulty(a:integer) : integer
!!	-	set_format_type(a:integer) : integer
!!	-	set_grid(a:String) : String|integer
!!	-	set_grid_max_vx_factor(a:integer) : integer
!!	-	set_grid_min_vx(a:integer) : integer
!!	-	set_iron_sight_distance(a:integer) : integer
!!	-	set_iron_sight_symbol(a:character) : character|integer
!!	-	set_status_window(a:Object) : Object
!!	-	tick() : boolean
!!
!!------------------------------------------------------------------------------
System_file;

!! Descomentar para obtener información de depuración:
! Constant DEBUG_AIMANDFIRE;

!! Array para operar con cadenas de caracteres:
Constant _AIM_AND_FIRE_BUFFER_SIZE = 16;
Array _aim_and_fire_temp_buffer --> _AIM_AND_FIRE_BUFFER_SIZE;

!! Objeto gestor del sistema
Object	AimingManager "(Aiming Manager)"
 with	!!----------------------------------------------------------------------
		!! MÉTODOS PÚBLICOS:
		!!----------------------------------------------------------------------
		!! Método principal que implementa el sistema de apuntado y disparo.
		!! Tiene 2 modos de operación, seleccionables a través del parámetro
		!! opcional 'probabilistic':
		!!	0)	Utilizando una animación de apuntado interactiva (sólo en
		!!		GLULX). Al invocar al método se inicia la animación ---una
		!!		retícula moviéndose de extremo a extremo de la ventana de
		!!		estado--- con una velocidad que se determina en función del
		!!		nivel de dificultad del sistema, y que se detiene cuando el
		!!		usuario pulsa una tecla. El resultado indica bien la distancia
		!!		en número de columnas entre la posición final de la retícula y
		!!		el centro de la ventana de estado o la zona de la ventana de
		!!		estado en la que se ha detenido, en función del formato
		!!		establecido en el sistema.
		!!	1)	Método probabilista (único modo posible en Máquina-Z).
		!!		Determina fallo con una probabilidad P(Q) que depende del nivel
		!!		de dificultad 'difficulty' del sistema:
		!!		P(Q) = 1 - P(difficulty/100). El valor retornado se selecciona
		!!		aleatoriamente en función de si se ha producido un acierto o un
		!!		fallo de entre conjuntos de valores que varían a su vez en
		!!		función del formato establecido en el sistema.
		!! Para establecer el formato de los resultados hay que invocar al
		!! método 'set_format()' del gestor.
		!!
		!!	@param {boolean} [probabilistic=false] - Por defecto en GLULX el
		!!		sistema utiliza el modo de operación 0, pero si se invoca al
		!!		método con este parámetro verdadero se utiliza el modo 1. En
		!!		Máquina-Z el parámetro se ignora totalmente y se utiliza en
		!!		cualquier caso el modo de operación 1 probabilista
		!!	@param {boolean} [reset_position_flag=false] - Sólo cuando se
		!!		utiliza el modo de operación 0, al invocar el método con este
		!!		parámetro verdadero evita que la retícula de apuntado inicie
		!!		la animación desde el extremo izquierdo de la ventana y
		!!		desplazándose hacia la derecha y, en su lugar, iniciaría la
		!!		animación desde la posición y con el sentido con el que se
		!!		detuvo la última vez que la rutina fue invocada
		!!	@result {integer} Valores positivos cuando se considera que el
		!!		resultado ha sido un acierto; negativos si se considera un
		!!		fallo. El valor concreto del resultado depende del tipo de
		!!		formato del sistema
		!!----------------------------------------------------------------------
		aim_and_fire [ probabilistic reset_position_flag
			status_window_width i result;
			#Ifdef TARGET_ZCODE;
			probabilistic = true;
			#Endif; ! TARGET_ZCODE;
			!! MODO DE OPERACIÓN 1 ---------------------------------------------
			!! FIXME - Comprobar lógica. Es posible conseguir aciertos con
			!! dificultad = 100
			if (probabilistic) {
				!! Acierto:
				if (random(100) > self.difficulty) {
					i = self.iron_sight_distance + 1;
					result = random(i) - 1;
				}
				!! Fallo:
				else {
					glk($0025, self.status_window, gg_arguments,
						gg_arguments + 4);
					status_window_width = gg_arguments-->0;
					i = status_window_width - self.iron_sight_distance;
					result = random(i);
				}
			}
			!! MODO DE OPERACIÓN 0 ---------------------------------------------
			else {
				!! Asegura la correcta inicialización de atributos del gestor:
				if (self.grid_vx == 0)
					self.set_difficulty(self.initial_difficulty);
				if (self.status_window == 0)
					self.status_window = gg_statuswin;
				self.delay_counter = 0;
				self.end_flag = false;
				!! Establece el punto de inicio y el sentido del movimiento de
				!! la retícula:
				if (~~reset_position_flag) {
					if (self.grid_vx < 0) self.grid_vx = self.grid_vx * -1;
					self.grid_x = 0;
				}
				!! Inicia el temporizador glk y activa la animación:
				glk(214, self.timer_frequency); ! glk_request_timer_events(f);
				give self on;
				#Ifdef DEBUG_AIMANDFIRE;
				print "** AIM&FIRE: Velocidad ", self.grid_vx, " **^";
				#Endif; ! DEBUG_AIMANDFIRE;
				!! La animación se detiene cuando el usuario pulsa una tecla:
				KeyCharPrimitive();
				self.end_flag = true;
				!! Calcula la distancia absoluta en número de columnas entre la
				!! posición final de la retícula y el centro de la ventana de
				!! estado:
				glk($0025, self.status_window, gg_arguments, gg_arguments + 4);
				status_window_width = gg_arguments-->0;
				result = (self.grid_x / 1000) + (self.grid_length / 2)
					- (status_window_width / 2);
				if (result < 0) result = -result;
				!! Retorna el resultado de la operación con el formato adecuado:
				#Ifdef DEBUG_AIMANDFIRE;
				print "** AIM&FIRE: Pos. final retícula = ", result, " **^";
				print "** AIM&FIRE: Ancho ventana = ", status_window_width,
					" / ", (status_window_width/2), " **^";
				print "** AIM&FIRE: Resultado = ", self.format_result(result),
					" **^";
				#Endif; ! DEBUG_AIMANDFIRE;
			}
			return self.format_result(result);
		],
		!!----------------------------------------------------------------------
		!!	@returns {integer} Milisegundos que se sigue mostrando la posición
		!!		final de la retícula una vez detenida la animación de apuntado.
		!!		-1 en Máquina-Z
		!!----------------------------------------------------------------------
		get_delay_value [;
			#Ifdef TARGET_ZCODE;
			return -1;
			#Ifnot; ! TARGET_GLULX;
			return self.delay_value;
			#Endif; ! TARGET_
		],
		!!----------------------------------------------------------------------
		!!	@returns {integer} Dificultad establecida en el sistema
		!!----------------------------------------------------------------------
		get_difficulty [;
			return self.difficulty;
		],
		!!----------------------------------------------------------------------
		!!	@returns {integer} Tipo de formato de los resultados establecido en
		!!		el sistema [0-1]
		!!----------------------------------------------------------------------
		get_format_type [;
			return format_type;
		],
		!!----------------------------------------------------------------------
		!!	@returns {String|integer} Retícula de apuntado. -1 en Máquina-Z
		!!----------------------------------------------------------------------
		get_grid [;
			#Ifdef TARGET_ZCODE;
			return -1;
			#Ifnot; ! TARGET_GLULX;
			return self.grid;
			#Endif; ! TARGET_
		],
		!!----------------------------------------------------------------------
		!!	@returns {integer} Factor de multiplicación a la velocidad mínima
		!!		con el que se calcula la velocidad máxima de la retícula. -1
		!!		en Máquina-Z
		!!----------------------------------------------------------------------
		get_grid_max_vx_factor [;
			#Ifdef TARGET_ZCODE;
			return -1;
			#Ifnot; ! TARGET_GLULX;
			return self.grid_max_vx_factor;
			#Endif; ! TARGET_
		],
		!!----------------------------------------------------------------------
		!!	@returns {integer} Velocidad mínima de la retícula. -1 en Máquina-Z
		!!----------------------------------------------------------------------
		get_grid_min_vx [;
			#Ifdef TARGET_ZCODE;
			return -1;
			#Ifnot; ! TARGET_GLULX;
			return self.grid_min_vx;
			#Endif; ! TARGET_
		],
		!!----------------------------------------------------------------------
		!!	@returns {integer} Distancia al centro de la ventana de estado, en
		!!		número de columnas, a la que se imprimen las guías centrales.
		!!		-1 en Máquina-Z
		!!----------------------------------------------------------------------
		get_iron_sight_distance [;
			#Ifdef TARGET_ZCODE;
			return -1;
			#Ifnot; ! TARGET_GLULX;
			return self.iron_sight_distance;
			#Endif; ! TARGET_
		],
		!!----------------------------------------------------------------------
		!!	@returns {character|integer} Caracter con el que se representan las
		!!		guías centrales. -1 en Máquina-Z
		!!----------------------------------------------------------------------
		get_iron_sight_symbol [;
			#Ifdef TARGET_ZCODE;
			return -1;
			#Ifnot; ! TARGET_GLULX;
			return self.iron_sight_symbol;
			#Endif; ! TARGET_
		],
		!!----------------------------------------------------------------------
		!!	@returns {Object} Ventana de estado establecida en el sistema
		!!----------------------------------------------------------------------
		get_status_window [;
			return self.status_window;
		],
		!!----------------------------------------------------------------------
		!! Reestablece los parámetros iniciales del sistema.
		!!----------------------------------------------------------------------
		reset [;
			self.delay_value = self.initial_delay_value;
			self.difficulty = self.initial_difficulty;
			self.format_type = self.initial_format_type;
			self.grid = self.initial_grid;
			self.grid_max_vx_factor = self.initial_grid_max_vx_factor;
			self.grid_min_vx = self.initial_grid_min_vx;
			self.grid_vx = self.initial_grid_vx;
			self.grid_x = self.initial_grid_x;
			self.grid_length = self.initial_grid_length;
			self.iron_sight_distance = self.initial_iron_sight_distance;
			self.iron_sight_symbol = self.initial_iron_sight_symbol;
			self.motion_type = self.initial_motion_type;
			self.status_window = self.initial_status_window;
		],
		!!----------------------------------------------------------------------
		!! Establece el número de milisegundos que se sigue mostrando la
		!! posición final de la retícula una vez detenida la animación de
		!! apuntado. En Máquina-Z no realiza ningún cambio.
		!!
		!!	@param {integer} a - Nuevo tiempo de espera (en ms)
		!!	@returns {integer} El tiempo de espera previo (en ms)
		!!----------------------------------------------------------------------
		set_delay_value [ a
			result;
			result = self.delay_value;
			#Ifdef TARGET_GLULX;
			self.delay_value = a;
			#Endif; ! TARGET_GLULX;
			return result;
		],
		!!----------------------------------------------------------------------
		!! Establece la dificultad del sistema. En GLULX se modifica además la
		!! velocidad de la retícula de apuntado atendiendo a que antes de
		!! modificar el valor de la velocidad es necesario registrar el sentido
		!! del movimiento previo de modo que el nuevo valor tenga el mismo
		!! sentido (mismo signo).
		!!
		!!	@param {integer} a - Valor comprendido en el rango [0-100] que se
		!!		establece como nueva dificultad del sistema
		!!	@returns {integer} El valor de dificultad previo. -1 si el
		!!		parámetro 'a' se sale del rango válido y no se produce el
 		!!		cambio de dificultad
		!!----------------------------------------------------------------------
		set_difficulty [ a
			negative_v result;
			if (a < 0 || a > 100) return -1;
			result = self.difficulty;
			self.difficulty = a;
			#Ifdef TARGET_GLULX;
			if (self.grid_vx < 0) negative_v = true;
			self.grid_vx = ((self.difficulty * (self.grid_min_vx
				* self.grid_max_vx_factor)) / 100) + self.grid_min_vx;
			if (negative_v) self.grid_vx = self.grid_vx * -1;
			#Endif; ! TARGET_GLULX;
			return result;
		],
		!!----------------------------------------------------------------------
		!! Establece el tipo de formato de los resultados.
		!!
		!!	@param {integer} a - Nuevo tipo de formato [0-1]
		!!	@returns {integer} El tipo de formato previo. -1 si el parámetro
		!!		'a' se sale del rango válido y no se produce el cambio de
		!!		formato
		!!----------------------------------------------------------------------
		set_format_type [ a
			result;
			if (a < 0 || a > 1) return -1;
			result = self.format_type;
			self.format_type = a;
			return result;
		],
		!!----------------------------------------------------------------------
		!! Establece la retícula de apuntado (calcula además el ancho de la
		!! nueva retícula). En Máquina-Z no realiza ningún cambio.
		!!
		!!	@param {String} a - Nueva retícula de apuntado
		!!	@returns {String|integer} La retícula de apuntado previa
		!!----------------------------------------------------------------------
		set_grid [ a
			result;
			result = self.grid;
			#Ifdef TARGET_GLULX;
			self.grid = a;
			PrintToBuffer(
				_aim_and_fire_temp_buffer, _AIM_AND_FIRE_BUFFER_SIZE, a);
			self.grid_length = _aim_and_fire_temp_buffer->(WORDSIZE-1);
			#Ifdef DEBUG_AIMANDFIRE;
			print "** AIM&FIRE: Retícula/Tam. = ", (string) self.grid, " / ",
				self.grid_length, " **^";
			#Endif; ! DEBUG_AIMANDFIRE;
			#Endif; ! TARGET_GLULX;
			return result;
		],
		!!----------------------------------------------------------------------
		!! Establece el factor de multiplicación a la velocidad mínima con el
		!! que se calcula la velocidad máxima de la retícula.
		!!
		!!	@param {integer} a - Nuevo factor de multiplicación
		!!	@returns {integer} El factor de multiplicación previo
		!!----------------------------------------------------------------------
		set_grid_max_vx_factor [ a
			result;
			result = self.grid_max_vx_factor;
			#Ifdef TARGET_GLULX;
			self.grid_max_vx_factor = a;
			#Endif; ! TARGET_GLULX;
			return result;
		],
		!!----------------------------------------------------------------------
		!! Establece la velocidad mínima de la retícula.
		!!
		!!	@param {integer} a - Nueva velocidad mínima de la retícula
		!!	@returns {integer} La velocidad mínima previa de la retícula
		!!----------------------------------------------------------------------
		set_grid_min_vx [ a
			result;
			result = self.grid_min_vx;
			#Ifdef TARGET_GLULX;
			self.grid_min_vx = a;
			#Endif; ! TARGET_GLULX;
			return result;
		],
		!!----------------------------------------------------------------------
		!! Establece la distancia al centro de la ventana de estado, en número
		!! de columnas, a la que se imprimen las guías centrales. En Máquina-Z
		!! no realiza ningún cambio.
		!!
		!!	@param {integer} a - Nueva distancia al centro de la ventana de
		!!		estado de las guías centrales (en número de columnas)
		!!	@returns {integer} La distancia previa
		!!----------------------------------------------------------------------
		set_iron_sight_distance [ a
			result;
			result = self.iron_sight_distance;
			#Ifdef TARGET_GLULX;
			self.iron_sight_distance = a;
			#Endif; ! TARGET_GLULX;
			return result;
		],
		!!----------------------------------------------------------------------
		!! Establece el caracter con el que se representan las guías centrales.
		!! En Máquina-Z no realiza ningún cambio.
		!!
		!!	@param {character} a - Nuevo caracter para representar las guías
		!!		centrales
		!!	@returns {character|integer} El caracter con el que se
		!!		representaban las guías centrales previamente
		!!----------------------------------------------------------------------
		set_iron_sight_symbol [ a
			result;
			result = self.iron_sight_symbol;
			#Ifdef TARGET_GLULX;
			self.iron_sight_symbol = a;
			#Endif; ! TARGET_GLULX;
			return result;
		],
		!!----------------------------------------------------------------------
		!! Establece la ventana de estado del sistema.
		!!
		!!	@param {Object} a - Nueva ventana de estado
		!!	@returns {Object} La ventana de estado previa
		!!----------------------------------------------------------------------
		set_status_window [ a
			result;
			result = self.status_window;
			self.status_window = a;
			return result;
		],
		!!----------------------------------------------------------------------
		!! Operación encargada de realizar la animación en la ventana de
		!! estado. Debe invocarse desde el punto de entrada 'HandleGlkEvent()'
		!! para que se ejecute en cada ciclo del temporizador glk:
		!!
		!!		[ HandleGlkEvent ev;
		!!			if (ev-->0 == 1) ! evtype_Timer
		!!				AimingManager.tick();
		!!		];
		!!
		!!	@returns {boolean} Falso si el gestor no está preparado para
		!!		mostrar la animación. Verdadero en otro caso
		!!----------------------------------------------------------------------
		tick [
			status_window_width;
			#Ifdef TARGET_ZCODE;
			return false;
			#Ifnot; ! TARGET_GLULX;
			!! Si el sistema no está activado o no tiene definida una ventana
			!! de estado en la mostrar la animación de apuntado, retorna
			if (self hasnt on || self.status_window == 0) {
				glk(214, 0); ! glk_request_timer_events(0)
				return false;
			}
			!! Se calcula el ancho de la ventana de estado (debe calcularse en
			!! cada evento del temporizador por si la ventana ha sido
			!! redimensionada por el usuario)
			glk($0025, self.status_window, gg_arguments, gg_arguments + 4);
			status_window_width = gg_arguments-->0;
			!! Mientras el usuario no detenga la animación, se muestra
			if (~~self.end_flag) {
				switch (self.motion_type) {
					0:	self.update_grid_position_LM(status_window_width);
					1:	self.update_grid_position_SHM(status_window_width);
				}
				#Ifdef DEBUG_AIMANDFIRE;
				print "** AIM&FIRE: Pos. retícula = ", self.grid_x, " / ",
					(self.grid_x/1000), " **^";
				#Endif; ! DEBUG_AIMANDFIRE;
				self.draw_aiming_line(status_window_width);
			}
			!! Tras ser detenida, la posición final de la retícula aún se
			!! muestra en la ventana de estado durante unos milisegundos
			else {
				self.draw_aiming_line(status_window_width);
				self.delay_counter++;
				if (self.delay_counter > self.delay_value
					/ self.timer_frequency) {
					glk(214, 0); ! glk_request_timer_events(0)
					self.delay_counter = 0;
					give self ~on;
					DrawStatusLine();
				}
			}
			#Endif; ! TARGET_
		],
 private
		!!----------------------------------------------------------------------
		!! MÉTODOS PRIVADOS:
		!!----------------------------------------------------------------------
		!! Dibuja la animación de apuntado.
		!!
		!!	@param {integer} status_window_width - Ancho de la ventana de estado
		!!	@returns {boolean} Verdadero si imprime el estado actual de la
		!!		animación con éxito. Falso en caso contrario
		!!----------------------------------------------------------------------
		draw_aiming_line [ status_window_width;
			!! En Máquina-Z, retorna
			#Ifdef TARRGET_ZCODE;
			return false;
			#Endif; ! TARGET_ZCODE;
			!! Si no hay ventana de estado definida, retorna
			if (self.status_window == 0) {
				#Ifdef DEBUG_AIMANDFIRE;
				print "** AIM&FIRE: No hay definida ventana de estado para
				pintar la animación de apuntado. **^";
				#Endif; ! DEBUG_AIMANDFIRE;
				return false;
			}
			!! Inicializa la ventana de estado
			glk($002F, self.status_window); ! set_window
			!! TODO - Las ventanas de estado tienen habitualmente una altura de
			!! 1 fila, pero pueden ser mayores. Actualmente la animación se
			!! imprime en la primera fila de la ventana de estado. Añadir
			!! lógica para imprimir la animación en el centro de la ventana de
			!! estado cuando ésta tiene un tamaño superior a 1 fila.
			glk($002A, self.status_window); ! window_clear
			!! Imprime las guías
			glk($002B, self.status_window, ((status_window_width / 2)
				- self.iron_sight_distance), 0); ! window_move_cursor
			print (char) self.iron_sight_symbol;
			glk($002B, self.status_window, ((status_window_width / 2)
				+ self.iron_sight_distance), 0); ! window_move_cursor
			print (char) self.iron_sight_symbol;
			!! Imprime la retícula
			glk($002B, self.status_window, (self.grid_x/1000), 0);
			print (string) self.grid;
			!! Reestablece la ventana principal
			glk($002F, gg_mainwin);
			return true;
		],
		!!----------------------------------------------------------------------
		!! Formatea el resultado de la operación de apuntado y disparo de
		!! acuerdo al formato establecido en el sistema (consultar
		!! documentación del atributo 'format_type').
		!!
		!!	@param {integer} a - Valor absoluto en número de columnas de la
		!!		distancia entre la posición final de la retícula y el centro de
		!!		la ventana de estado
		!!	@returns {integer} Resultado de la operación de apuntado y disparo
		!!		formateado adecuadamente
		!!----------------------------------------------------------------------
		format_result [ a
			result;
			switch (self.format_type) {
				0:	! División de la ventana de estado en zonas
					if (a == 0) result = 0;
					else if (a <= self.iron_sight_distance) result = 1;
					else if (a <= (self.iron_sight_distance * 4)) result = -2;
					else result = -3;
				1:	! División de la ventana de estado en columnas
					if (a <= self.iron_sight_distance) result = a;
					else result = self.iron_sight_distance - a;
			}
			return result;
		],
		!!----------------------------------------------------------------------
		!! Actualiza la posición de la retícula (Movimiento Rectilíneo
		!! Uniforme).
		!!
		!!	@param {integer} status_window_width - Ancho de la ventana de estado
		!!----------------------------------------------------------------------
		update_grid_position_LM [ status_window_width; ! Linear Motion
			if ((self.grid_x / 1000) < 0 || (self.grid_x / 1000)
				> status_window_width - self.grid_length) {
				self.grid_vx = self.grid_vx * -1;
			}
			self.grid_x = self.grid_x + self.grid_vx;
		],
		!!----------------------------------------------------------------------
		!! XXX - Código GLULX para mover la posición de la retícula utilizando
		!! Movimiento Armónico Simple. Para hacerlo funcional, habría que
		!! modificar el algoritmo para ajustar el tiempo a la frecuencia del
		!! temporizador glk, de modo que no se produjesen saltos entre
		!! posiciones consecutivas y simplemente se modificase el número de
		!! ticks de reloj en cada posición.
		!!
		!!	@param {integer} status_window_width - Ancho de la ventana de estado
		!!----------------------------------------------------------------------
		update_grid_position_SHM [ status_window_width ! Simple Harmonic Motion
			i ini sini aux gp;
			status_window_width = i + ini + sini + aux + gp;
			!! aux = WIN_WIDTH/2;
			!! @numtof aux ini; ! ini: centro de la ventana
			!! @numtof GRID_COUNTER i; ! i: contador
			!! @sin i sini; ! sini: seno de GRID_COUNTER
			!! @fmul ini sini aux; ! aux: (WIN_WIDTH/2)*sin(GRID_COUNTER)
			!!
			!! if (GRID_MOVEMENT == 0) @fadd ini aux gp;
			!! else @fsub ini aux gp;
			!! @ftonumn gp GRID_POS;
			!!
			!! GRID_COUNTER++;
			!! if (GRID_COUNTER == 180)
			!! {	GRID_COUNTER = 0;
			!! 	if (GRID_MOVEMENT == 0) GRID_MOVEMENT = 1;
			!! 	else GRID_MOVEMENT = 0;
			!! }
		],
		!!----------------------------------------------------------------------
		!! ATRIBUTOS:
		!!----------------------------------------------------------------------
		!! Número de milisegundos que se sigue mostrando la posición final de
		!! la retícula tras haber detenido la animación:
		delay_value 1000,
		initial_delay_value 1000,
		!! Valor numérico comprendido en el rango [0-100] que expresa la
		!! dificultad para conseguir un acierto;
		!!	-	En GLULX afecta a la velocidad de movimiento de la retícula;
		!!		con 0 indicando velocidad mínima, y 100 velocidad máxima.
		!!	-	En Máquina-Z afecta a la probabilidad P(Q) de NO conseguir un
		!!		resultado positivo: P(Q) = 1 - difficulty/100
		difficulty 50,
		initial_difficulty 50,
		!! Indicador del formato utilizado para los resultados de la operación
		!! de apuntado y disparo:
		!!	0)	División de la ventana de estado en las siguientes zonas:
		!!		0)	Centro exacto de la ventana.
		!!		1)	Zona comprendida dentro de las dos guías centrales.
		!!		-2)	Fuera de las guías centrales, a una distancia igual o
		!!			inferior a la que hay entre el centro de la ventana y
		!!			cualquiera de las dos guías.
		!!		-3)	Fuera de las guías centrales, a una distancia superior a
		!!			la delimitada por la zona 2.
		!!		Cuando se usa el modo de operación 0, usando una animación
		!!		interactiva, el resultado indica el número de zona en el que el
		!!		usuario ha conseguido detener la retícula de apuntado. En el
		!!		modo de operación 1, probabilista, se retorna aleatoriamente
		!!		{0,1} o {-2,-3} en función de si se logra un acierto o un
		!!		fallo, respectivamente.
		!!	1)	División de la ventana de estado en columnas. En el modo de
		!!		operación 0, usando una animación interactiva, el resultado es
		!!		la distancia absoluta en número de columnas de la posición
		!!		final en la que se ha detenido la retícula y el centro de la
		!!		ventana de estado si se ha producido un acierto; o la distancia
		!!		absoluta con valor negativo entre la posición final de la
		!!		retícula y la posición de la guía central más próxima. En el
		!!		modo de operación 1, probabilista, el resultado se selecciona
		!!		aleatoriamente de entre el conjunto [0, iron_sight_distance],
		!!		si es un acierto, y entre (0, <ancho de la ventana de estado> -
		!!		iron_sight_distance), con valor negativo, si es un fallo.
		format_type 0,
		initial_format_type 0,
		!! Cadena que forma la retícula de apuntado:
		grid "[+]",
		initial_grid "[+]",
		!! Factor de multiplicación a la velocidad mínima con el que se calcula
		!! la velocidad máxima (con 'difficulty' == 100) de la retícula, de
		!! forma que la velocidad máxima es 'grid_min_vx * grid_max_vx_factor':
		grid_max_vx_factor 25, initial_grid_max_vx_factor 25,
		!! Velocidad mínima (con 'difficulty' == 0) de la retícula:
		grid_min_vx 60, initial_grid_min_vx 60,
		!! Velocidad actual de la retícula. Es relativa a la frecuencia con que
 		!! se activa el temporizador Glk e indica el número de columnas que se
		!! mueve la retícula en cada evento del temporizador a razón
		!! 'grid_vx/1000':
		grid_vx 0,
		initial_grid_vx 0,
		!! Posición de la retícula (valor/1000):
		grid_x 0,
		initial_grid_x 0,
		!! Longitud de la retícula en número de caracteres:
		grid_length 3,
		initial_grid_length 3,
		!! Distancia al centro de la ventana de estado en número de columnas a
		!! la que se imprimen las guías centrales (valor absoluto utilizado por
		!! las dos guías; en positivo y negativo):
		iron_sight_distance 3,
		initial_iron_sight_distance 3,
		!! Caracter con el que se representan las guías centrales:
		iron_sight_symbol '·',
		initial_iron_sight_symbol '·',
		!! Código numérico del tipo de movimiento de la animación de apuntado:
		!!	0)	Movimiento Rectilíneo Uniforme
		!!	1)	Movimiento Armónico Simple
		motion_type 0,
		initial_motion_type 0,
		!! Ventana de estado sobre la que se muestra la animación de apuntado:
		status_window 0,
		initial_status_window 0,
		!!----------------------------------------------------------------------
		!! Contador interno para la pausa final de la animación:
		delay_counter 0,
		!! Indica si el usuario ha detenido la animación de la retícula:
		end_flag false,
		!! Frecuencia con que se activa el temporizador Glk (en ms). Puesto que
		!! la ventana de estado se divide en columnas y no en píxeles es
		!! imposible conseguir una animación fluida. Para aumentar el número de
		!! columnas en las que se hace impresión e intentar reducir mínimamente
		!! el movimiento entrecortado de la animación se dobla el objetivo
		!! habitual de 60 FPS:
		timer_frequency 8, ! 125 FPS
;

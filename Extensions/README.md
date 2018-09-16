
# Extensiones

Salvo aquellas en las que se especifica una autoría diferente, las siguientes extensiones a la librería Inform 6 son obra de J. Francisco Martín. Se puede consultar más información en la propia documentación de cada extensión.

- **aimAndFire.h**

   Sistema de apuntado y disparo a través de un mecanismo QTE (*Quick Time Event*). Utiliza la ventana de estado de la obra para mostrar la animación de una retícula desplazándose de un extremo a otro de la ventana. El usuario debe detener la retícula lo más cerca posible del centro de la pantalla. El éxito o fracaso de la acción se determina en función de lo cerca o lejos del centro de la pantalla que el jugador haya acertado a detener la retícula.

- **capacities.h**

   Nuevo conjunto de reglas de capacidad para contenedores y soportes del modelo de mundo. Al de introducir objetos sobre un contenedor, o colocarlos sobre un soporte, se comprueba antes que no se vulneren los límites de peso, volumen, tamaño o número de objetos máximo permitido. Basada en la extensión **Rrecept.h** de Peer Schaefer.

- **choiceSet.h**

   Sistema de selección sobre un conjunto de opciones, utilizando análisis no estricto de la entrada de usuario para el reconocimiento de patrones. Permite implementar sistemas de conversación con inventario de temas, como el propuesto por Eric Eve en sus notas acerca de sistemas de conversación en ficción interactiva: <http://www.tads.org/howto/convbkg.htm>. Construída sobre la extensión **NPC_Conversacion.h** v1.0 de *Mastodon*.

- **dainunek.h**

   *DreamBytes Adventures -- Inicialización unificada de extensiones en Glk*. Facilita un objeto capaz de implementar y gestionar automáticamente los puntos de entrada para Glk: ``IdentifyGlkObject()`` y ``HandleGlkEvent()``.

   Autor(es): *Eliuk Blau*.

- **damusix.h**

   *DreamBytes Adventures -- Administrador unificado de sonido en Glulx. Proporciona un objeto administrador encargado de gestionar todas las funciones necesarias para la reproducción de música y efectos de sonido en la máquina virtual Glulx.

   Autor(es): *Eliuk Blau*.

- **infglk.h**

   Facilita el acceso de las funciones glk en Glulx para el desarrollo con Inform 6.

- **gstatusX.h**

   Módulo de ventana de estado para la librería **GWindows**, de *L. Ross Raszewski*. Define una ventana de estado en la que únicamente se imprime el nombre de la localidad actual del personaje controlado por el usuario.

- **gWindowsGUI.h**

   Interfaz gráfica adaptativa al ancho de la ventana con *GWindows*.

- **hyperlinks.h**

   Rutinas para facilitar la interacción a través de hipervínculos.

- **pPreprocessor.h**

   Preprocesador de la entrada de teclado del usuario utilizando análisis no estricto para el reconocimiento de patrones. Trata de identificar la entrada de usuario con alguno de los objetos modelados en el entorno simulado de la obra (facilita la utilización de comandos con una sintaxis reducida a sólo el nombre de un objeto al alcance del usuario, sin necesidad de especificar un verbo concreto).

- **shuffle.h**

   Retorna un número entero aleatorio entre 1 y N, como la rutina `random()` de Inform. A diferencia de ésta última, retorna un valor diferente cada vez que es invocada, hasta que todos los posibles N números han sido retornados, momento en el que se inicia un nuevo ciclo.

   Autor(es): *Roger Firth*.

- **SpanishEG.h**

   Gramática española extendida (*Spanish Extended Grammar*). Define un nuevo conjunto de acciones (así como sinónimos ya definidas en la gramática por defecto). Los mensajes por defecto de estas nuevas acciones contemplan inflexiones de género y número del actor y tiempo verbal del narrador, por lo que puede ser utilizada por si sola o en combinación con la extensión **SpanishLM.h**. Basada en extensiones previas de *Emily Short* y *Mapache*.

- **SpanishLM.h**

   Redefinición de los mensajes por defecto de la librería de idioma INFSP6 (*Spanish Library Messages*). Implementa funcionalidad para cambiar de tiempo y persona del narrador en tiempo de ejecución de una obra. Incluye:

  + **sp1future.h**, mensajes en 1ª persona, futuro.
  + **sp1past.h**, mensajes en 1ª persona, pasado.
  + **sp1present.h**, mensajes en 1ª persona, presente.
  + **sp2future.h**, mensajes en 2ª persona, futuro.
  + **sp2past.h**, mensajes en 2ª persona, pasado.
  + **sp2present.h**, mensajes en 2ª persona, presente.
  + **sp3future.h**, mensajes en 3ª persona, futuro.
  + **sp3past.h**, mensajes en 3ª persona, pasado.
  + **sp3present.h**, mensajes en 3ª persona, presente.

- **textStyles.h**

   Rutinas biplataforma para imprimir texto con diferentes formatos.

***

Se incluye además un directorio **diogenes/** con diversas extensiones y ejemplos de código antiguos o no probados, pero que pueden implementar algunos conceptos o soluciones de interés.

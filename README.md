# Wing-War
Game of planes

Gameplay video: https://youtu.be/wUD10yfHHX0?t=6

MUNDO/SCENE: En nuestro juego parseamos y cargamos 8 tipos de meshes, la isla, el cielo (se mueve con nuestra cámara),  el agua (con un shader simple para que tenga un color más realista), 3 tipos de aviones (m38 y bomber como ia, y el spitfire como player) y 2 tipos de barcos (un barco normal como enemigo, y un aircraft carrier como aliado). 

CONTROL AVION: El avión puede moverse tanto en el eje Z como en el eje X (pensamos que el movimiento de el eje Y es innecesario en un avión). Va a una velocidad constante, tiene un turbo, puede disparar y cambiar la posición de la cámara para ver en distintas direcciones.

	SPITFIRE: Tiene 100 HP , y empieza con 0p de score, sus balas, tanto como las de la ia, quitan 5 de HP.

IA: Contamos con diferentes tipos de IA , todos siguen un caracter general, siguen a un punto (waypoint). Tenemos los aviones enemigos que siguen a unos waypoints repartidos por el mapa, en cuanto te acercas te empiezan a seguir a ti, si estan a una distancia adecuada y con un ángulo adecuado hacia ti disparan. Un barco enemigo, que recorre un camino de waypoints, cuando llega a uno empieza a ir hacia el siguiente, hasta que el último punto es el aircraft carrier aliado. Este barco enemigo es seguido por dos aviones, que actuan igual que los demas, pero simplemente tienen como objetivo seguir al barco.

	M38: Tienen 25 HP , y dan 25p de puntuación.
	BOMBER: Tienen 50 HP , y dan 50p de puntuación.
	BOMBERS (los 2 que defienden el barco) : Tienen 100 HP , y dan 200p de puntuación.
	BARCO : Tiene 400 HP , da 500p de puntuación , cuando muere ganas el juego.
	AIRCRAFT CARRIER: Cuando el barco enemigo colisiona contra él, se pierde el juego.


COLISIONES: Mayoritariamente hemos utilizado las colisiones de tipo esfera, tanto en las colisiones de dinámico a dinámico, como en las colisiones de bala a dinámico. Para las colisiones entre nuestro avión y un estático (isla, agua) hemos utilizado la colisión con mesh.

STAGES: Utilizamos la estructura de stages para representar los diferentes estados de nuestro juego, contamos con 5 stages diferentes.
	
	FIRSTSCREEN: Es donde empieza, se muestra una simple imagen del juego.
	MENUSTAGE: En este estado se representa el menú, muy simple, para moverse por él se usa el teclado.
	CONTROLSTAGE: Una imagen donde se ven los controles de el mando.
	GAMESTAGE: La escena principal donde se renderiza el juego, y donde el usuario lo juega.
	ENDSTAGE: La pantalla de game over o mission succes , donde puedes volver al menú.

DESTRUCCIÓN Y RESET: Cuando se termina el juego (superado o no), es necesario eliminar las entidades y limpiar las listas de static y dynamic colliders, en nuestro caso utilizamos un vector donde añadimos las entidades a eliminar, en nuestro caso el root y el cielo (el cielo no es hijo de root), y luego llamamos una función que recorre el vector y borra las entidades que contiene, junto con las de sus hijos. También hacemos un clear de dynamic y static colliders, ya que sino luego al volver a empezar el juego estarán las entidades repetidas y habrá colisiones con ellas mismas.

AUDIO: Hemos utilizado bastantes sonidos en nuestro juego, ya que pensamos que es algo importante por una mejor experiencia Contamos con música de ambiente tanto en el menú como en el juego, sonido de motor, de balas, explosiones,  algunos efectos al terminar la partida y una música de tensión junto con una alarma cuando se esta a punto de perder.

OBJETIVO DEL JUEGO: El objetivo del juego es simple, destruir un barco enemigo que se dirige cargado de explosivos a nuestro portaaviones aliado. Si en menos 3 minutos y 36 segundos no es destruido, el barco enemigo colisionará con el portaaviones y el juego no se superará.

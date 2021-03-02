# Cliente/Visual

## CGame

El cliente implementado modela una partida con la clase CGame la cual puede reaccionar a las diferentes actualizaciones proporcionadas por el servidor. Dicha clase se encarga de contener a los jugadores, el estado del mapa y los renderizables.

## GameScreen

GameScreen es un atributo de la clase CGame y se encarga de la parte grafica del Cliente. Utiliza la libreria de SDL para dibujar en pantalla. Es quien ordena a los diferentes apartados de CGame a dibujarse y contiene tambien la UI del juego.

## Camera

La camara es un atributo del jugador activo y es el sistema de referencia para dibujar todas las cosas. Todos los elementos dibujables dependen de la posicion de la camara para ser dibujados. Utiliza la tecnica de RayCasting para simular un efecto 3D.

## BagOfSprites

CGame a su vez contiene una bolsa de sprites la cual pre-carga al iniciar la partida todas las texturas de objetos y paredes. Esta clase es accedida a la hora de crear renderizables y animaciones.

## Renderable/Sprite/AnimatedSprite

Son las clases base para dibujar objetos en la pantalla y animaciones. Renderable vincula una textura (sprite) a una posicion puntual y AnimatedSprite es una secuencia de sprites.

## EnemyPlayer/CWeapon

Ambas clases son contenedores de animaciones. Para los enemigos contienen sus diversos sprites y acciones animadas mientras que CWeapon contiene las animaciones para el jugador activo.

## Ray

La clase Ray es utilizada para la tecnica de RayCasting, calculando distancias a las paredes. Usando dichas distancias luego se define si algo es dibujado en pantalla o no.


## SoundManager

Finalmente SoundManager es la clase encargada de reproducir los efectos de sonido al recoger objetos o disparar, asi como para tambien reproducir la musica. Utiliza SDL_Mixer.

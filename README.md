# Wolfenstein3D - Trabajo práctico final

## Instrucciones de compilación y ejecución del realese v5.0 desde raíz (en Linux).
### Para compilar los programas servidor y cliente (desde raíz)
    mkdir build
    cd build 
    cmake ..

### Para ejecutar el programa cliente (desde raíz)
    cd build
    cd client
    ./client
    
### Para ejecutar el programa servidor (desde raíz)
    cd build
    cd server
    ./server ../../config.yaml

### Para compilar y ejecutar el programa Editor (desde raíz)
    cd Editor
    mkdir build
    cd build
    cmake ..
    make
    ./Editor

## ¿Como jugar?
    -Ejecutar el programa servidor. Es posible cambiar la configuración de las partidas y los balances del juego desde el archivo config.yaml ubicado en raiz
    -Ejecutar el programa cliente e ingresar los datos brindados por el servidor para conectarse.
    -Si la conexión es exitosa se solicitará un nombre de usuario, los nombres de usuario disponibles son aquellos no repetidos y no vacíos.
    -En caso de ingresar un nombre válido se mostrará la ventana de partidas, desde aquí se pueden crear partidas o unirse a partidas existentes.
    -Al ingresar join el programa quedará bloqueado hasta que el creador de la partida decida iniciarla, hacer multiples clicks en join puede llevar a errores.
    -Una vez que se acabaron las vidas o que solo un jugador quedó en pie, se terminará la partida y se mostrará automaticamente una ventana con las estadisticas del juego hasta ese momento.

## Librerias necesarias
### SDL:
- apt-cache search libsdl2
- apt-get install libsdl2-dev
- apt-cache search libsdl2-image
- apt-get install libsdl2-image-dev
- apt-get install libsdl2-ttf-dev
- apt-get install libsdl2-mixer-dev

### QT:
- sudo apt-get install build-essential
- sudo apt-get install qtcreator
- sudo apt-get install qt5-default

## Lógica:

- La lógica del juego se desarrolló en la clase Game interactuando con el mapa del juego y los jugadores, desarrollando las acciones que fueron recibidas del GameStage. El GameStage se encarga de recibir los eventos del Match y  a su vez de encolar a las colas de usuarios los eventos generados a lo largo de la lógíca del juego.  
- Para representar el mapa se utilizó un vector de vectores conteniendo CellMaps. Estos CellMaps son una clase que funciona como contenedora de los ítems, puertas y jugadores que pueden encontrarse en esa posición, ya que al existir el RayCasting los valores matriciales son escalados a una matriz más grande donde cada cuadrado se escala por 32, pudiendo posicionarse varios elementos en una misma posición escalada. 
- Para la consumisión de ítems se utilizó una clase madre Items y cada objeto consumible por el jugador es hija de ésta. Este diseño facilitó el uso de polimorfismo para que cada vez que el jugador se moviese a una nueva posición el jugador pudiera polimórficamente encargarse de decidir si le era posible o no agarrarlo, y en cuyo caso aplicar el cambio necesario e informar al cliente a través de un evento. 
- Para el caso de las armas y los disparos, se verificaba primero si se podía realizar el disparo o no. Para esto primero se verificaba el arma que se estaba utilizando y si ésta contenía las balas necesarias para realizar el disparo, luego se lanzaba un rayo de implementación parecida al cliente para poder verificar la distancia a la pared a donde está mirando el jugador y verificando a su vez la distancia con los otros jugadores para saber si le puede impactar o no.

## Comunicaciones:
   ![communication_diagram](https://github.com/SCAPELLI/Wolfenstein3D/blob/main/images/communicationsThreads.png?raw=true)

## Ai
- Objetivo: Implementar un enemigo controlado por el juego, su funcion serà perseguir y atacar al primer jugador que se acerque a una distancia minima a partir de 
la cual quedará marcado y será perseguido hasta ser eliminado.

- Estrategia: La ai persigue al jugador una vez que se encuentra a una distancia suficientemente cercana. 
La estrategia implementada consiste en modelar todas las posiciones transitables del mapa como nodos de un grafo, 
en donde los nodos son adyacentes si se trata de dos posiciones consecutivas del mapa.
A partir de este grafo, se definio una estructura con informacion de los pasos ideales que se deben dar si el jugador marcado se encuentra en A posicion 
para y el bot enemigo se encuentra en la posicion B.

  Ejemplo de mapa con jugador y bot:

  ![ai_0](https://github.com/SCAPELLI/Wolfenstein3D/blob/main/images/ai_0.png?raw=true)

  Interpretacion del mapa como grafo:
  
  ![ai_1](https://github.com/SCAPELLI/Wolfenstein3D/blob/main/images/ai_1.png?raw=true)


 La manera de recolectar esta informacion se baso en el Algoritmo de Dijkstra para la obtencion de caminos minimos de grafos ponderados, donde se consideró 
que el peso de cada arista era 1.
Esta informacion se recolecta en la etapa previa al comienzo de una partida. de forma tal que durante el desarrollo del juego, se modelò una interfaz entre c++ 
y lua la cual consistia en que desde el programa en c++ se le envia a lua las posiciones de los jugadores y la maquina virtual de lua decide e informa la accion 
pertinente a tomar


## Editor:

Es una aplicación independiente del juego que permite diseñar mapas nuevos o cargar mapas ya existentes para su edición. Estos mapas pueden ser cargados en el juego. El editor solo permite mapas de dimensiones nxm, que contengan identificadores válidos que correspondan a los sprites listados en sprites.yamp y posean el formato correspondiente en el .yaml. En la carpeta Editor/maps/invalidos hay ejemplos de mapas que no pueden ser editados.

- Coordinate: representa una posición de coordenadas (x, y) enteras en el mapa.

- EditorScreen: es la clase que contiene los objetos con los que interacciona el usuario en la creación de un mapa. Su deber es comunicar a los distintos objetos participantes en la edición del mapa el input del usuario para que puedan responder a este.

- MenuWindow: pantalla de inicio del menú. Contiene un botón que te conduce a la pantalla de edición.

- Mode: clase virtual que representa el modo de edición en la que se encuentra el editor. Las clases que heredan de ella son DrawMode, en la cual el usuario puede dibujar tiles en el mapa, y EraseMode, que le permite al usuario borrar tiles.

- NewMapDialog: esta clase representa una ventana que verifica las dimensiones ingresadas por un usuario para la creación de un nuevo mapa y le comunica al usuario en caso de haber ingresado un input inválido.

- ScreenManager: se encarga de cambiar las pantallas que ve el usuario. Actualmente, las pantallas que puede ver son la pantalla de inicio (MenuWindow) y la pantalla que muestra las herramientas de edición (EditorScreen).

- SpriteFileManager: lee el archivo .yaml y crea vectores en base a ella. También, puede verificar que los identificadores en un mapa sean válidos según el .yaml que contiene la información de los sprites.

- SpriteTabs: esta clase contiene listas de sprites, separadas por categorías (texturas, items, armas, tiles bloqueantes y tiles no bloqueantes).

- Texture: contiene el id y el path de la textura correspondiente al sprite.

- TextureList: contiene sprites pertenecientes a una categoria para que el usuario pueda seleccionarlos en caso de desear dibujarlos en el mapa.

- Tile: representa un cuadrado en el mapa. Contiene la información de su ubicación y de su sprite.

- TilemapScene: clase que representa la parte gráfica del mapa. Le permite al usuario visualizar las dimensiones del mapa y poder efectuar cambios sobre él.

- Diagrama Editor:

![Diagrama - Editor 1](https://github.com/SCAPELLI/Wolfenstein3D/blob/main/images//editorDiagrama1.jpeg?raw=true)

![Diagrama - Editor 2](https://github.com/SCAPELLI/Wolfenstein3D/blob/main/images/editorDiagrama2.jpeg?raw=true)



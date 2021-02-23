# Wolfenstein3D
Trabajo práctico final - El juego

## Introducción

## Librerías:

### YAML:

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

### LUA:


## Clases

### Editor:

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
![Diagrama - Editor 1](https://github.com/SCAPELLI/Wolfenstein3D/blob/readmeEdit/report/editorDiagrama1.jpeg?raw=true)

![Diagrama - Editor 2](https://github.com/SCAPELLI/Wolfenstein3D/blob/readmeEdit/report/editorDiagrama2.jpeg?raw=true)

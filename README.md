#Wolfenstein 3d - Trabajo práctico final

-Cliente

-Servidor

-Comunicaciones

-Ai
Objetivo: Implementar un enemigo controlado por el juego, su funcion serà perseguir y atacar al primer jugador que se acerque a una distancia minima a partir de 
la cual quedará marcado y será perseguido hasta ser eliminado. 
Estrategia: La ai persigue al jugador una vez que se encuentra a una distancia suficientemente cercana. 
La estrategia implementada consiste en modelar todas las posiciones transitables del mapa como nodos de un grafo, 
en donde los nodos son adyacentes si se trata de dos posiciones consecutivas del mapa.
A partir de este grafo, se definio una nueva estructura con informacion de los pasos ideales que se deben dar si el jugador marcado se encuentra en x posicion 
para llegar a y 
posicion. La manera de recolectar esta informacion se baso en el Algoritmo de Dijkstra para la obtencion de caminos minimos de grafos ponderados, donde se consideró 
que el peso de cada arista era 1.
Esta informacion se recolecta en la etapa previa al comienzo de una partida. de forma tal que durante el desarrollo del juego, se modelò una interfaz entre c++ 
y lua la cual consistia en que desde el programa en c++ se le envia a lua las posiciones de los jugadores y la maquina virtual de lua decide e informa la accion 
pertinente a tomar  

-



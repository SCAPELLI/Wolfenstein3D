local map  =
{
	{0, 0, 0},
	{0, 1, 0},
	{0, 1, 0},
	{0, 0, 0}
}

--[[   
	DIJKSTRA (Grafo G, nodo_fuente s)       
       para u ∈ V[G] hacer
           distancia[u] = INFINITO
           padre[u] = NULL
		   visto[u] = false
		   IdealStep[u] = s 
       distancia[s] = 0
       adicionar (cola, (s, distancia[s]))
       mientras que cola no es vacía hacer
           u = extraer_mínimo(cola)
           visto[u] = true
           para todos v ∈ adyacencia[u] hacer
               si ¬ visto[v]      
                   si distancia[v] > distancia[u] + peso (u, v) hacer
                       distancia[v] = distancia[u] + peso (u, v)
                       padre[v] = u
					   adicionar(cola,(v, distancia[v]))
					   
		for todos v e grafo:
			pasoIdeal = 
			while padre[v] != fuente:

					   ]]

dofile("ExportMapToGraph.lua")
dofile("priority_queue.lua")

INFINITE = 99999999
NONE = "this node does not have a father"

graph = exportMapAsGraph(map)
priorityQueue = PriorityQueue:new()

distance = {}
father = {}
visited = {}
idealStep = {}

function idealStepsCalculator(graph, sourceNode)
	for nodeId,_ in pairs(graph.nodes) do
		distance[nodeId] = INFINITE
		father[nodeId] = NONE
		visited[nodeId] = false
		idealStep[nodeId] = sourceNode.id
	end
	distance[sourceNode.id] = 0
	priorityQueue:push(sourceNode.id, distance[sourceNode.id])
	while not priorityQueue:empty() do
		nodeId = priorityQueue:pop()
		visited[nodeId] = true
		for neighborId,_ in pairs(graph:getNeighbors(nodeId)) do
			if not visited[neighborId] then
				if distance[neighborId] > distance[nodeId] + 1 then
					distance[neighborId] = distance[nodeId] + 1
					father[neighborId] = nodeId
					priorityQueue:push(neighborId, distance[neighborId])
					
				end
			end
		end
	end

	
	
	for nodeId,_ in pairs(graph.nodes) do
		print("Nodo: ", nodeId)
		print("  distance:", distance[nodeId])
		print("  padre:",father[nodeId])
		print("  fue visitado:",visited[nodeId])
		print("  pasoIdeal para llegar a",nodeId,idealStep[nodeId])
	end
end

graph:print()
idealStepsCalculator(graph, Node:new(1, 1))
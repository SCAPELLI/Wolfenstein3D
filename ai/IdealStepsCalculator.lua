local map  =
{
	{0, 1, 1},
	{1, 1, 1},
	{0, 0, 1},
	{1, 1, 0}
}

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
	

	for nodeId,_ in pairs(graph.nodes) do
		print("Nodo: ", nodeId)
		print("  distance:", distance[nodeId])
		print("  padre:",father[nodeId])
		print("  fue visitado:",visited[nodeId])
		print("  pasoIdeal para llegar a",nodeId,idealStep[nodeId])
	end
end

idealStepsCalculator(graph, Node:new(1, 1))
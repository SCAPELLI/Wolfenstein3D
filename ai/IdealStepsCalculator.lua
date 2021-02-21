dofile("../ai/ExportMapToGraph.lua")
dofile("../ai/priority_queue.lua")

INFINITE = 99999999
NONE = "this node does not have a father"

function idealStepsCalculator(graph, sourceNodeId)
	local distance = {}
	local father = {}
	local visited = {}
	local idealStep = {}
	local priorityQueue = PriorityQueue:new()

	for nodeId,_ in pairs(graph.nodes) do
		distance[nodeId] = INFINITE
		father[nodeId] = NONE
		visited[nodeId] = false
		idealStep[nodeId] = sourceNodeId
	end
	distance[sourceNodeId] = 0
	father[sourceNodeId] = sourceNodeId 
	priorityQueue:push(sourceNodeId, distance[sourceNodeId])
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
		local aNodeId = father[nodeId]
		if aNodeId ~= NONE then
			while (father[aNodeId] ~= sourceNodeId) do
				aNodeId = father[aNodeId]
			end
			idealStep[nodeId] = aNodeId 
		end
	end
	return idealStep
end

function getIdealStepsForAllTiles(map)
	local idealStepsForAllTiles = {}
	local graph = exportMapAsGraph(map)

	for nodeId,_ in pairs(graph.nodes) do
		idealStepsForAllTiles[nodeId] = idealStepsCalculator(graph, nodeId)
	end

	return idealStepsForAllTiles
end
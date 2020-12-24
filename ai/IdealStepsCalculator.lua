local map  =
{
	{0, 1, 0, 1, 0, 1, 0},
	{0, 0, 0, 1, 0, 1, 0},
	{0, 1, 0, 0, 0, 1, 0},
	{0, 1, 0, 1, 0, 1, 0}
}

dofile("ExportMapToGraph.lua")
dofile("priority_queue.lua")

INFINITE = 99999999
NONE = "this node does not have a father"

graph = exportMapAsGraph(map)
priorityQueue = PriorityQueue:new()


function idealStepsCalculator(graph, sourceNodeId)
	local distance = {}
	local father = {}
	local visited = {}
	local idealStep = {}

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

local idealStepsForAllNodes = {}

for nodeId,_ in pairs(graph.nodes) do
	idealStepsForAllNodes[nodeId] = idealStepsCalculator(graph, nodeId)
end

for nodeId,idealStepsForANode in pairs(idealStepsForAllNodes) do
	for destinationNodeId,idealStepNodeId in pairs(idealStepsForANode) do
		print(string.format("El paso ideal para ir desde %s hasta %s es %s",
			nodeId, destinationNodeId, idealStepNodeId))
	end
end

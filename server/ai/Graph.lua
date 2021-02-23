dofile("../ai/Node.lua")

Graph = {}

function Graph:new()
	local graph = {}
	setmetatable(graph, self)
	self.__index = self

	graph.nodes = {}
	return graph
end
--nodes: key = aNodeId, value = table of neighborsIdsFromNode
--  table of neighborsIdsFromNode: key = aNeighborId, value = 1 if exists, nil otherwise

function Graph:addNode(node)
	if self.nodes[node.id] == nil then
		self.nodes[node.id] = {}
	end
end

function Graph:addNeighbor(node, neighbor)
	self.nodes[node.id][neighbor.id] = 1
  
  if self.nodes[neighbor.id] == nil then
    self:addNode(neighbor)
  end  
  self.nodes[neighbor.id][node.id] = 1
end

function Graph:getNeighbors(nodeId)
	return self.nodes[nodeId]
end

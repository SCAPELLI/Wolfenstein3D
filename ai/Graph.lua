dofile("Node.lua")

Graph = {}

function Graph:new()
	local graph = {}
	setmetatable(graph, self)
	self.__index = self

	graph.nodes = {}
	return graph
end

--nodes: key = aNode(id), value = table of neighborsFromNode

-- nodes[node]: key = aNeighbor(id) value = 1 if exists, nil otherswise

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

function Graph:getNeighbors(node)
	return self.nodes[node.id]
end

function Graph:print()
	for k,v in pairs(self.nodes) do
		print("Nodo: ", k)
		for k1,v1 in pairs(self.nodes[k]) do
			print("   Vecino de :", k1)
		end
	end
end
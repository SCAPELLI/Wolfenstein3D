Node = {}

function Node:new(x, y)
	local node = {}
	setmetatable(node, self)
	self.__index  = self
	node.x = x
	node.y = y
	node.id = x .. "," .. y
	--node.neighbors = {}
	return node
end

function Node:equals(node)
	return self.x == node.x and self.y == node.y
end

--[[
function Node:addNeighbor(neighbor)
	found = false
	for _, aNeighbor in pairs(self.neighbors) do
		if (aNeighbor:equals(neighbor)) then
			found = true
			break
		end
	end
	if not found then 
		self.neighbors[#self.neighbors + 1] = neighbor
		neighbor.neighbors[#neighbor.neighbors + 1] = self
	end
end


nodo0 = Node:new(1, 1)
nodo2 = Node:new(1, 3)
nodo1 = Node:new(3, 2)

nodo0:addNeighbor(nodo1)
nodo0:addNeighbor(nodo2)
nodo0:addNeighbor(nodo1)

print(nodo0.neighbors)
print(nodo1.neighbors)
print(nodo2.neighbors)
-----------------------
print(#nodo0.neighbors)
print(#nodo1.neighbors)
print(#nodo2.neighbors)
]]
Node = {}

function Node:new(x, y)
	local node = {}
	setmetatable(node, self)
	self.__index  = self
	node.x = x
	node.y = y
	node.id = x .. "," .. y
	return node
end

function Node:equals(node)
	return self.x == node.x and self.y == node.y
end

function Node:getCoordinatesFromId(nodeId)
	print (nodeId)
	io.read()
	local commaPosition = string.find(nodeId,",")
	local x = string.sub(nodeId, 1 , commaPosition-1)
	local y = string.sub(nodeId, commaPosition+1)
	return tonumber(x), tonumber(y)
end

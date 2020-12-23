PriorityQueue = {}

function PriorityQueue:new()
	local queue = {}
	setmetatable(queue, self)
	self.__index = self

	queue.heap = {}

	return queue
end

function PriorityQueue:push(priority, value)
	self.heap[#heap + 1] = {priority, value}
	
	size = #self.heap
	local halfSize = math.floor(size/2)
	while halfSize > 0 do
		if self.heap[size][2] < self.heap[halfSize][2] then
			heap[size] = heap[halfSize]
			heap[halfSize] = heap[size]
		end
		size = halfSize
	end
end

--EN CONSTRUCCION PARA EL 2021
function PriorityQueue:pop()
	priorityElement = self.heap[1][1]
	self.heap[1] = self.heap[#self.heap]
	self.heap[#self.heap] = nil


	local i = 1
	while (i * 2) <= #self.heap do
		local mc = self
	end

	return priorityElement
end
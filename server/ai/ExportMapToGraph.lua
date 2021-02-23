dofile("../../ai/Graph.lua")

GROUND = 0
WALL = 1
LEFT = -1
RIGHT = 1
CENTER = 0
UP = 1
DOWN = -1

function addAdyacentTileIfItIsValid(graph, map, row, column, rowShifting, columnShifting)
	if map[row + rowShifting] ~= nil 
		and map[row + rowShifting][column + columnShifting] ~= nil 
			and map[row + rowShifting][column + columnShifting] == GROUND then
		graph:addNeighbor(Node:new(row, column), 
			Node:new(row + rowShifting, column + columnShifting))
	end
end

function searchForAdyacenteTiles(graph, map, row, column)
	addAdyacentTileIfItIsValid(graph, map, row, column, LEFT, CENTER)
	addAdyacentTileIfItIsValid(graph, map, row, column, RIGHT, CENTER)
	addAdyacentTileIfItIsValid(graph, map, row, column, CENTER, UP)
	addAdyacentTileIfItIsValid(graph, map, row, column, CENTER, DOWN)
end

function exportMapAsGraph(map)
	local graph = Graph:new()

	for rowNumber,row in ipairs(map) do
		for columnNumber,tile in ipairs(row) do

			if tile == GROUND then
				graph:addNode(Node:new(rowNumber, columnNumber))
				searchForAdyacenteTiles(graph, map, rowNumber, columnNumber)
			end
		end
	end
	return graph
end

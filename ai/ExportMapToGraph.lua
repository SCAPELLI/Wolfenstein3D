dofile("Graph.lua")

GROUND = 0
WALL = 1

function addAdyacentTileIfItIsValid(graph, map, row, column, rowShifting, columnShifting)
	if map[row + rowShifting] ~= nil 
		and map[row + rowShifting][column + columnShifting] ~= nil 
			and map[row + rowShifting][column + columnShifting] == GROUND then
		graph:addNeighbor(Node:new(row, column), 
			Node:new(row + rowShifting, column + columnShifting))
	end
end

function searchForAdyacenteTiles(graph, map, row, column)
	addAdyacentTileIfItIsValid(graph, map, row, column, -1, 0)
	addAdyacentTileIfItIsValid(graph, map, row, column, 1, 0)
	addAdyacentTileIfItIsValid(graph, map, row, column, 0, 1)
	addAdyacentTileIfItIsValid(graph, map, row, column, 0, -1)
end

function exportMapAsGraph(map)
	graph = Graph:new()

	for rowNumber,row in ipairs(map) do
		for columnNumber,tile in ipairs(row) do

			if tile == GROUND then
				graph:addNode(Node:new(rowNumber, columnNumber))
				searchForAdyacenteTiles(graph, map, rowNumber, columnNumber)
			end
			--io.write(string.format("%d,%d ", rowNumber, columnNumber))
		end
		--io.write("\n")
	end
	return graph
end

--graph:print()
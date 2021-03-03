dofile("../../server/ai/IdealStepsCalculator.lua")
dofile("../../server/ai/TurnOrMoveAnalysis.lua")

TILE = 32
ATTACK_DISTANCE = 64
SIGHTING_DISTANCE = 96
NONE_PLAYER = "none player has been spotted"

MOVE_BACKWARD = 0
MOVE_FOWARD = 1
TURN_ANTICLOCKWISE = 2
TURN_CLOCKWISE = 3
ATTACK = 4
DO_NOTHING = 5

function initializeGameContext(map, id)
	botId = id
	markedPlayerId = NONE_PLAYER
	markedPlayerIdLife = -1
	idealStepsForAllTiles = getIdealStepsForAllTiles(map)
end

function distace(botPosition, playerPosition)
	local x0 = botPosition.x
	local y0 = botPosition.y
	local x1 = playerPosition.x
	local y1 = playerPosition.y


	return math.sqrt((x0-x1)^2+(y0-y1)^2)
end


function detectPlayersInASightingDistance(players, markedPlayerId)
	if markedPlayerId == NONE_PLAYER then
		for playerId,playerInfo in pairs(players) do
			if playerId ~= botId then
				if distace(players[botId].position, playerInfo.position) < SIGHTING_DISTANCE then
					markedPlayerId = playerId
					markedPlayerIdLife = playerInfo.life
					break
				end
			end
		end
	else
		if markedPlayerIdLife ~= players[markedPlayerId].life then
			markedPlayerId = NONE_PLAYER
		end
	end
return markedPlayerId
end

function getBotActionId(players)

	markedPlayerId = detectPlayersInASightingDistance(players, markedPlayerId)
	if markedPlayerId ~= NONE_PLAYER then
		if distace(players[markedPlayerId].position, players[botId].position) > ATTACK_DISTANCE then
			
			local botX = math.floor(players[botId].position.x / TILE) + 1
			local botY = math.floor(players[botId].position.y / TILE) + 1

			local playerX = math.floor(players[markedPlayerId].position.x / TILE) + 1
			local playerY = math.floor(players[markedPlayerId].position.y / TILE) + 1

			local idealStepId = 
				idealStepsForAllTiles[botX .. "," .. botY][playerX .. "," .. playerY]
			local xTile, yTile = Node:getCoordinatesFromId(idealStepId)

			idealX = xTile * TILE - TILE/2
			idealY = yTile * TILE - TILE/2

			local resultId = turnOrMoveAnalyzer(players[botId], idealX, idealY)
			return resultId
		else
			
			local action = turnOrMoveAnalyzer(
				players[botId], 
				players[markedPlayerId].position.x, 
				players[markedPlayerId].position.y)
			if action == MOVE_FOWARD then
	      		return ATTACK
	    	else
	      		return action
	    	end
		end
	else
		return ( math.random(0,3))
	end
end

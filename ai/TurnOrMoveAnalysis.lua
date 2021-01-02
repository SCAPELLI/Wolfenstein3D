PI = 3.14159265358979323846

MOVE_FOWARD = 1
TURN_ANTICLOCKWISE = 2
TURN_CLOCKWISE = 3

function valueIsInRange(value, lowerBound, upperBound)
    return lowerBound <= value and value < upperBound
end

function botAngleIsInTolerableRange(botAngle, idealAngle)
    tolerance = PI/10
    if idealAngle + tolerance >= 2 * PI then
        return 
            valueIsInRange(botAngle, 0, idealAngle+tolerance-2*PI) 
            or
            valueIsInRange(botAngle, idealAngle-tolerance, 2*PI)
    else 
        if idealAngle - tolerance < 0 then
        return 
            valueIsInRange(botAngle, 0, idealAngle+tolerance)
            or
            valueIsInRange(botAngle, idealAngle-tolerance+2*PI, 2*PI)
        else
            return valueIsInRange(botAngle, idealAngle-tolerance, idealAngle+tolerance)
        end
    end
end

function turnAnalyzer(botAngle, idealAngle)
    local alfa = botAngle - idealAngle
    local beta = alfa + 2*PI
    local gamma = alfa - 2*PI
    
    local minimum = alfa
    if math.abs(minimum) > math.abs(beta) then
      minimum = beta
    end
    if math.abs(minimum) > math.abs(gamma) then
      minimum = gamma
    end
    
    if minimum > 0 then 
    	return TURN_CLOCKWISE
    else
    	return TURN_ANTICLOCKWISE
    end
end

function getIdealAngle(botPosition, idealPosition)
  local idealAngle = math.atan ( (idealPosition["y"] - botPosition["y"])
	                             /
	                             (idealPosition["x"] - botPosition["x"]))
  local adjusment = 0
  
  if 
    (botPosition["x"] > idealPosition["x"] and botPosition["y"] <= idealPosition["y"]) 
    or
    (botPosition["x"] > idealPosition["x"] and botPosition["y"] > idealPosition["y"])
  then
      adjusment = PI
  else 
    if (botPosition["x"] <= idealPosition["x"] and botPosition["y"] > idealPosition["y"]) then
      adjusment = 2*PI
    end
  end
  
  return idealAngle + adjusment
end

function turnOrMoveAnalyzer(bot, idealXPosition, idealYPosition)
    local idealPosition = {}
    idealPosition["x"] = idealXPosition
    idealPosition["y"] = idealYPosition
	
    local botPosition = bot["position"] --tener harcodeado el (0,0)
	local botAngle = bot["angle"] --En angulo debe estar "normarlizado" entre 0 y 2PI

	local idealAngle = getIdealAngle(botPosition, idealPosition)

	if botAngleIsInTolerableRange(botAngle, idealAngle) then
	    return MOVE_FOWARD
    else
    	return turnAnalyzer(botAngle, idealAngle)
	end
end

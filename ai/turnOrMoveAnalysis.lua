PI = 3.14159265358979323846

players = { 
    ["1"] = {
        ["position"] = { ["x"] = 3, ["y"] = 4 },
        ["angle"] = 0
    },
    ["bot"] = {
        ["position"] = { ["x"] = 16, ["y"] = 16 },
        ["angle"] = PI/2-PI/11
    }
}

------------------------------------------------------

function botAngleIsGreaterThanMinimumAngle(idealStepAngle, botAngle)
    minimumAngle = idealStepAngle - PI / 10
    if minimumAngle < 0 then 
        return minimumAngle > botAngle - 2*PI
    else
        return minimumAngle < botAngle
    end
end

function botAngleIsSmallerThanMaximumAngle(idealStepAngle, botAngle)
    maximumAngle = idealStepAngle + PI / 10
    if maximumAngle > 2*PI then 
        return botAngle + 2*PI < maximumAngle 
    else 
        return botAngle < maximumAngle
    end
end
------------------------------------------------------

idealTilePosition = {}
idealTilePosition["x"] = 16
idealTilePosition["y"] = 48

botPosition = players["bot"]["position"] --tener harcodeado el (0,0)
botAngle = players["bot"]["angle"] --En angulo debe estar "normarlizado" entre 0 y 2PI

idealStepAngle = math.atan ( (idealTilePosition["y"] - botPosition["y"])
                             /
                             (idealTilePosition["x"] - botPosition["x"]))

if 
    botAngleIsGreaterThanMinimumAngle(idealStepAngle, botAngle) 
    and
    botAngleIsSmallerThanMaximumAngle(idealStepAngle, botAngle)
then
    print("lauch the move event")
else
    print("launch a turn event")
end

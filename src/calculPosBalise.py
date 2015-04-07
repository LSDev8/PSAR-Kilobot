import math

def calculPosition(longueur, nbBalise):
    angle = 360/nbBalise
    radians = angle*math.pi/180
    seg = math.sqrt(math.pow(longueur,2) + math.pow(longueur,2) - (2*longueur*longueur*math.cos(radians)))
    return seg

print(calculPosition(4.7,5))

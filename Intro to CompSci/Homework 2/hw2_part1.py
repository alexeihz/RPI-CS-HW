import math

def find_sphere_volume(radius):
    return (4/3)*math.pi*radius**3

def find_cube_volume(side):
    return side**3

sideLen = float(input("Enter the side length of the cube (in.) => "))
if int(sideLen) == sideLen:
    sideLen = int(sideLen)

print(sideLen)

rad = float(input("Enter the radius of the gum ball (in.) => "))
if int(rad) == rad:
    rad = int(rad)
print(rad)


numGumball = int(sideLen/(rad*2))**3
totalVolume = find_cube_volume(sideLen)
gumballSpace = find_sphere_volume(rad)*numGumball
percentage = (gumballSpace/totalVolume)*100
bigSphere = find_sphere_volume(sideLen/2)
numGumball2 = int((bigSphere*numGumball)/totalVolume)


rad = float(rad)
print("A box of side length {0:.1f} will hold {1:.0f} gum balls of radius {2:}.".format(sideLen,numGumball,rad))

print("The gum balls will take up {0:.2f} in^3".format(gumballSpace))
print("of the total volume of {0:.2f} in^3 or {1:.2f}%".format(totalVolume,percentage))
print("A sphere with a diameter of {0:.1f} would have volume {1:.2f} in^3".format(sideLen,bigSphere))
print("It would hold {0:.0f} gum balls at the same density.".format(numGumball2))

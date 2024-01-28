import math
radiusSun = input("Enter the radius of the Sun (miles) -> ")
print(radiusSun)
radiusMoon = input("Enter the radius of the Moon (miles) -> ")
print(radiusMoon)
maxDistToSun = input("Enter the maximum distance to the Sun (miles) -> ")
print(maxDistToSun)
maxDistToMoon = input("Enter the minimum distance to the Moon (miles) -> ")
print(maxDistToMoon)
rateMoonAway = input("Enter the rate the Moon is moving away (in/year) -> ")
print(rateMoonAway)


distMoonToEarth = float(maxDistToSun)*(float(radiusMoon)/float(radiusSun))
moonRecede = float(distMoonToEarth) - float(maxDistToMoon)
moonSameSizeSun = (moonRecede * 5280 * 12)/float(rateMoonAway)
print("The Moon will have exactly the same apparent size as the Sun when it is {0:.2f} miles away.".format(distMoonToEarth))
print("The Moon will need to recede another {0:.2f} miles".format(moonRecede))
print("Which will occur in {0:.0f} years at the current rate.".format(moonSameSizeSun))
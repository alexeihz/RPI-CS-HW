#this function calculates a new altitude and new speed based on gravity, thrust, old altitude, and old speed
def next_step(g, thrust, altitude, speed):
    new_speed = speed + (g-(thrust*g))
    new_altitude = altitude - new_speed
    return (new_altitude,new_speed)

#variable initialization
altitude = float(input("Enter starting altitude (meters) => "))
print(altitude)
gravity = float(input("Enter the gravitational acceleration (m/second^2) => "))
print(gravity)
fuel = float(input("Enter the total units of fuel => "))
print(fuel)
time = 0
speed = 0.0
thrust = 0
altitudeList = []
speedList = []
thrustList = []

#loops until altitude = 0
while(altitude > 0):
    print("Time",time,"- Altitude: {0:.2f}, Speed: {1:.2f}".format(altitude,speed))
    if(fuel>0):
        thrust = float(input("Enter the thrust => "))
        print(thrust)
        if(thrust>fuel):
            thrust = fuel
            print("Out of fuel, able to use thrust of {0:.2f}".format(thrust))
    elif(fuel<=0):
        thrust = 0
    altitudeList.append(altitude)
    speedList.append(speed)
    thrustList.append(thrust)
    fuel = fuel - thrust
    altitude = max(next_step(gravity, thrust, altitude, speed)[0],0)
    speed = next_step(gravity, thrust, altitude, speed)[1]
    time = time + 1


print("Time",time,"- Altitude: {0:.2f}, Speed: {1:.2f}".format(altitude,speed))
altitudeList.append(altitude)
speedList.append(speed)
#if landing speed is greater than 2.2 then it crashed. if not, then it didnt
if(speed > 2.2):
    print("Crashed ... ")
    print("Kapow ... ")
    print("... All astronauts are now shorter and you owe us a lander... ")
else:
    print("Nice landing!")
    print("The world salutes you!")

maxSpeed = max(speedList)
timeMaxSpeed = speedList.index(maxSpeed)
altMaxSpeed = altitudeList[timeMaxSpeed]
i = timeMaxSpeed
fuelUsed = 0
while(i < len(thrustList)):
    fuelUsed = thrustList[i] + fuelUsed
    i = i + 1
print()
print("Maximum speed of {0:.2f} was reached at time {1:.0f} and an altitude of {2:.2f}.".format(maxSpeed,timeMaxSpeed,altMaxSpeed))
print('After that you used {0:.2f} units of fuel.'.format(fuelUsed))
print("At the end you had {0:.2f} units of fuel left.".format(fuel))
import math
def time_to_seconds(hours,mins,secs):
    return hours*3600 + mins*60 + secs

def seconds_to_str(secs):
    newHour = math.floor(secs/3600)
    newMinute = math.floor((secs - newHour*3600)/60)
    newSec = math.floor((secs - newHour*3600 - newMinute*60))    
    return str(newHour) + " hours " + str(newMinute) + " mins " + str(newSec) + " secs"

print("A day in 2017 is 23 hours 56 minutes and 4 seconds long.")
sec2017 = time_to_seconds(23,56,4)
print("Which is equivalent to", sec2017, "seconds." )
theFuture = int(input("Enter a future year => "))
print(theFuture)
futureTotalSec = math.floor(sec2017 + (((6*60*60)/(900000000))*(theFuture-2017)))
#futureNewHour = math.floor(futureTotalSec/3600)
#futureNewMinute = math.floor((futureTotalSec - futureNewHour*3600)/60)
#futureNewSec = math.floor((futureTotalSec - futureNewHour*3600 - futureNewMinute*60))

print("A day in year", theFuture, "will be", futureTotalSec , "seconds long")
print("which is equivalent to", seconds_to_str(futureTotalSec))
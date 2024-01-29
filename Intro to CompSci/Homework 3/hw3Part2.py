import math
#this function returns the new number of bears and new berry area as a tuple, using the old number of bears, berry area, and number of tourists
def find_next(bears,berries,tourists):
    bears_next = berries/(50*(bears+1)) + bears*0.60 - (math.log(1+tourists,10)*0.1)
    berries_next = (berries*1.5) - (bears+1)*(berries/14) - (math.log(1+tourists,10)*0.05)
    tuply = (bears_next,berries_next)
    return tuply

#this function returns the number of tourists based on the number of bears
def find_tourists(bears):
    people = 0
    if(bears<4 or bears>15):
        people = 0    
    else:
        people = 10000*bears - max((bears-10),0)*10000 + max((bears-10),0)*20000
    return people

#variable creations
bearsNum = int(input("Number of bears => "))
print(bearsNum)
berrySize = int(input("Size of berry area => "))
print(berrySize)
tourists = 0
listBears=[]
listBerries=[]
listtourists=[]
i = 1
berrySize = float(berrySize)
print("Year\tBears\tBerries\tTourists")
#while loop runs as long as i(years) is less than or equal to 10
#while loop prints bears, berry area, and tourists for 10 years
while(i<=10):
    tourists = find_tourists(bearsNum)
    listBears.append(bearsNum)
    listBerries.append(berrySize)
    listtourists.append(tourists)
    print(i,"\t",bearsNum,"\t",round(berrySize,1),"\t",tourists,sep="")
    tupleNext = find_next(bearsNum,berrySize,tourists)    
    bearsNum = max(math.floor(tupleNext[0]),0)
    berrySize = max(tupleNext[1],0.0)
    i = i + 1
    
#finds max and min of all values
print()
print("Min:\t",min(listBears),"\t{0:.1f}\t".format(min(listBerries)),min(listtourists),sep="")
print("Max:\t",max(listBears),"\t{0:.1f}\t".format(max(listBerries)),max(listtourists),sep="")
#"\t{0:.1f}\t".format(berrySize)
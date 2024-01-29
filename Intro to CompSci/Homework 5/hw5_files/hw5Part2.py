#variable initializations
file = input("Filename => ")
print(file)
month = input("Month => ")
print(month)
openFile = open(file)
minTmin = []
maxTmax = []
avgTavg = []
avgTavg2 = []
years = []
yearRanges = []
weatherList = []

#Loops until the last element in the list is empty and then removes that element
k = 1
while k == 1:
    weatherList.append(openFile.readline().split(','))
    if(weatherList[-1]==['']):
        weatherList.pop()
        break
    
#checks the length of the month, loops through weatherList. If the element in the list matches the month, and there are no empty elements, adds elements to respective lists 
monthLen = len(str(month))
for i in range(len(weatherList)):
    weatherList[i][10] = weatherList[i][10].strip('\n')
    weatherList[i][11] = weatherList[i][11].strip('\n')
    if(monthLen == 1):
        if(weatherList[i][1][-1] == str(month) and weatherList[i][1][-2] == '0'):
            if(weatherList[i][9] != ''):
                avgTavg2.append(float(weatherList[i][9]))           
                avgTavg.append((weatherList[i][9],weatherList[i][1][0:4]))
                years.append(weatherList[i][1][0:4])
            if(weatherList[i][11] != ''):
                minTmin.append((weatherList[i][11],weatherList[i][1][0:4]))
            if(weatherList[i][10] != ''):
                maxTmax.append((weatherList[i][10],weatherList[i][1][0:4]))

    if(monthLen == 2):
        if(weatherList[i][1][-1] == str(month)[1] and weatherList[i][1][-2] == str(month)[0]):
            if(weatherList[i][9] != ''):
                avgTavg2.append(float(weatherList[i][9]))      
                avgTavg.append((weatherList[i][9],weatherList[i][1][0:4]))
                years.append(weatherList[i][1][0:4])
            if(weatherList[i][11] != ''):
                
                minTmin.append((weatherList[i][11],weatherList[i][1][0:4]))
            if(weatherList[i][10] != ''):
               
                maxTmax.append((weatherList[i][10],weatherList[i][1][0:4]))   
  
#makes a variable to find the min value of minTmin
minOfMin = minTmin[0][0]
minYear = []
for i in range(len(minTmin)):
    if(minTmin[i][0]<=minOfMin):
        minOfMin = minTmin[i][0]

for i in range(len(minTmin)):
    if(minTmin[i][0] == minOfMin):
        minYear.append(minTmin[i][1])

#makes a variable to find the max value of maxTmax
maxOfMax = maxTmax[0][0]
maxYear = []
for i in range(len(maxTmax)):
    if(maxTmax[i][0]>=maxOfMax):
        maxOfMax = maxTmax[i][0]
        
for i in range(len(maxTmax)):
    if(maxTmax[i][0] == maxOfMax):
        maxYear.append(maxTmax[i][1])
    
print("Earliest recorded average {0:.2f}".format(float(avgTavg[0][0])), "in", avgTavg[0][1])
print("Latest recorded average {0:.2f}".format(float(avgTavg[-1][0])), "in", avgTavg[-1][1])
print("Average temperature: {0:.2f}".format(sum(avgTavg2)/len(avgTavg2)))
print("Lowest min value recorded: {0:.2f}".format(float(minOfMin)),"in year(s): ",end="")
#Loops to print years if there are multiple min years
for i in minYear:
    print(i,sep=",",end="")
print()
#Loops to print years if there are multiple max years
print("Highest max value recorded: {0:.2f}".format(float(maxOfMax)),"in year(s): ",end="")
for i in maxYear:
    print(i,sep=",",end="")
print()

#Prints histogram
print("Histogram of average temperature")
if(len(years)<=10):
    print(years[0],"-",years[-1],": "+"*"*int(sum(avgTavg2)/len(avgTavg2)),sep="")
if(len(years)>10):
    for i in range(0,len(years),10):
        if(i+9<len(years)):
            yearRanges.append((years[i],years[i+9]))
        else:
            yearRanges.append((years[i],years[-1]))
avgRanges = 0
count = 0
for i in range(len(yearRanges)):
    avgRanges = 0
    count = 0
    for j in range(1,len(years)):
        if(int(years[j])>=int(yearRanges[i][0]) and int(years[j]) <= int(yearRanges[i][1])):
            avgRanges = avgRanges + float(avgTavg[j][0])
            count = count + 1
    print(yearRanges[i][0],"-",yearRanges[i][1],": "+"*"*int(avgRanges/count),sep="")
import hw4_util

#function finds index of university
def find_university(data, uname):
    i=1
    uIndex = -1
    while(i<len(data)):
        if(uname == data[i][0]):
            uIndex = i
            return uIndex
        i = i + 1 
    return uIndex
    
#variable initialization
data = hw4_util.read_university_file("university_data.csv")
uname = input("University name => ")
print(uname)
compare1 = int(input("Line number for first university to compare (1-1000) => "))
print(compare1)
compare2 = int(input("Line number for second university to compare (1-1000) => "))
print(compare2)

#if the university is in the list, it compares it with 2 other universities. if not then a message is printed
locateU = find_university(data,uname)
if(locateU != -1):
    uni1 = data[compare1][0]
    uni2 = data[compare2][0]
    print("First university:",uni1)
    print("Second university:",uni2)
    
    i = 1
    print()
    print("{0:>37}{1:>12}{2:>12}".format("First","Second","Yours"))
    while(i<14):
        print("{0:>25}{1:>12}{2:>12}{3:>12}".format(data[0][i],data[compare1][i],data[compare2][i],data[locateU][i]))
        i = i +1
    
else:
    print("University not found")
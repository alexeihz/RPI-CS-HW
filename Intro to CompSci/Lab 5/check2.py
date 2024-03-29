import lab05_util

def print_info(restaurants,i):
    i = i-1
    name1 = restaurants[i][0].split(",")[0]
    address1 = restaurants[i][3].split("+")[0]
    address2 = restaurants[i][3].split("+")[1]
    name2 = restaurants[i][5].split(",")[0]
    avgLen = len(restaurants[i][6])
    if(avgLen <=3):
        avg = sum(restaurants[i][6])/avgLen
    if(avgLen >3):
        avgLen = avgLen - 2
        minAvg = min(restaurants[i][6])
        maxAvg = max(restaurants[i][6])
        avg = (sum(restaurants[i][6])- maxAvg - minAvg)/avgLen
    print(name1 + " (" + name2 + ")")
    print(address1)
    print(address2)
    if(avg>=0 and avg <2):
        print("This restaurant is rated bad, based on", avgLen ,"reviews.")
    if(avg>=2 and avg <3):
        print("This restaurant is rated average, based on", avgLen ,"reviews.")  
    if(avg>=3 and avg <4):
        print("This restaurant is rated above average, based on", avgLen ,"reviews.")
    if(avg>=4 and avg <5):
        print("This restaurant is rated very good, based on", avgLen ,"reviews.")
restaurants = lab05_util.read_yelp('yelp.txt')
length = len(restaurants)
index = int(input("Enter resturant id => " ))
if(index<1 or index>length):
    print("Resturant index out of range")
else:
    print_info(restaurants,index)
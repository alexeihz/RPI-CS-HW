import lab05_util

def print_info(restaurant):
    name1 = restaurant[0].split(",")[0]
    address1 = restaurant[3].split("+")[0]
    address2 = restaurant[3].split("+")[1]
    name2 = restaurant[5].split(",")[0]
    avg = sum(restaurant[6])/len(restaurant[6])
    print(name1 + " (" + name2 + ")")
    print(address1)
    print(address2)
    print("Average Score: {0:.2f}".format(avg))
    
    
restaurants = lab05_util.read_yelp('yelp.txt')
print_info(restaurants[1])
imdb_file = input("Enter the name of the IMDB file ==> ").strip()
print(imdb_file)
counts = dict()
for line in open(imdb_file, encoding = "ISO-8859-1"):
    words = line.strip().split('|')
    name = words[0].strip()
    if name in counts:
        counts[name] += 1
    else:
        counts[name] = 1
        
names = sorted(counts)
#limit = min(100, len(names))
print(names)
maxMovies = 0
maxName = ""
once = 0
for index in range(len(names)):
    name = names[index]
    if(counts[name]==1):
        once +=1
    if(counts[name]>maxMovies):
        maxMovies=counts[name]
        maxName = name
    #print("{} appeared in {} movies".format(name, counts[name]))   

print("{} appears most often: {} times".format(maxName, maxMovies))  
print("{} people appear once".format(once))  
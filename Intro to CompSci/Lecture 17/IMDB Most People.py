imdb_file = input("Enter the name of the IMDB file ==> ").strip()
print(imdb_file)
counts = dict()
for line in open(imdb_file, encoding = "ISO-8859-1"):
    words = line.strip().split('|')
    name = words[1].strip()
    actor = words[0].strip()    
    if not(name in counts):
        counts[name] = set()
    if name in counts:
        counts[name].add(actor)
maxMovies = 0
maxName = ""
once = 0
for index in counts:
    if len(counts[index]) > maxMovies:
        maxMovies = len(counts[index])
        maxName = index
    if(len(counts[index])==1):
        once +=1        

print(maxMovies)  
print(maxName)
print(once)

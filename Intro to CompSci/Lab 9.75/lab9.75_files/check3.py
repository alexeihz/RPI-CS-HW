def update_scores(current_scores,graph):
    new_scores = dict()
    N = len(current_scores)
    for i in current_scores.keys():
        new_scores[i] = 0.15/N

    for p in graph.keys():
        M = len(graph[p])
        for q in graph[p]:
            new_scores[q] += 0.85 * current_scores[q]/M
    return new_scores

fileName = input("File ==> ")
print(fileName)
file = open(fileName)
line = file.readline()
graph = dict()
while line != "":
    lineSplit = line.strip("\n").split(" ")
    graph[lineSplit[0]] = set(lineSplit[1:])
    line = file.readline()

scores = dict()
for i in graph.keys():
    scores[i] = 1/len(graph.keys())
    
print("Initial Scores")
for j in scores.keys():
    print(str(j)+": {0:.4f}".format(scores[i]))
    
newScores = update_scores(scores,graph)
print("Computed Scores")
for j in newScores.keys():
    print(str(j)+": {0:.4f}".format(newScores[j]))

threshold = float(input("Computing scores with threshold "))
    

count = 0

converged = False
while converged == False:
    count+=1
    newScores = dict()
    newScores = update_scores(scores, graph)
    diff = 0
    for k in newScores.keys():
        print(abs(scores[k] - newScores[k]))
        diff = diff + abs(scores[k] - newScores[k])
    print("Iteration ", count,"(diff ",str(diff)+")")
    for j in newScores.keys():
        print(str(j)+": {0:.4f}".format(newScores[j]),end = " ")
    if diff < threshold:
        converged = True
    else:
        scores = dict() 
        scores = newScores
    if(count==27):
        break
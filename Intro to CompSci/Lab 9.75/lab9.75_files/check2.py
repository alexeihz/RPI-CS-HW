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
    
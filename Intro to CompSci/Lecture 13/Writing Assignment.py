file = input("Enter the scores file: ")
print(file)
scores = open(file)
splitScores = scores.read().split("\n")
if(splitScores[len(splitScores)-1]==''):
    splitScores.pop()
for i in range(len(splitScores)):
    splitScores[i] = int(splitScores[i])
sortScores = sorted(splitScores)
word = ""
for i in range(len(sortScores)):
    word = word + (str(i) + ":"+" " *(4-len(str(sortScores[i]))) + str(sortScores[i])) + "\n"
outFile = input("Enter the output file: ")
print(outFile)
sorted_Scores = open(outFile,"w")
sorted_Scores.write(word)
sorted_Scores.close()
sorted_Scores = open(outFile)
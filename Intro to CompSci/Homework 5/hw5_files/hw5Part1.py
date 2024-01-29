import hw5util
#variable initializations
fileName = input("Enter the filename => ")
print(fileName)
games, players, predictions = hw5util.read_predictions(fileName)
playerScore = []
gamePoints = []
gamePoints2 = []
#Prints player points
print("Player points:")
for i in range(len(players)):
    count = 0
    for j in range(len(predictions[0])):
        if(predictions[i][j][0] == games[j][-2]):
            count = count + 1
        if(predictions[i][j][1] == games[j][-1]):
            count = count + 1
        if(games[j][-2] > games[j][-1]):
            if(predictions[i][j][0] > predictions[i][j][1]):
                count = count + 2
        if(games[j][-2] < games[j][-1]):
            if(predictions[i][j][1] > predictions[i][j][0]):
                count = count + 2
        if(games[j][-2] == games[j][-1]):
            if(predictions[i][j][1] == predictions[i][j][0]):
                count = count + 2 
    print(players[i]," " *(8-len(players[i])), ":"," " *(2-len(str(count))), count)
    playerScore.append(count)

#collects game points
for i in range(len(predictions[0])):
    count1 = 0
    for j in range(len(players)):
        if(predictions[j][i][0] == games[i][-2]):
            count1 = count1 + 1
        if(predictions[j][i][1] == games[i][-1]):
            count1 = count1 + 1
        if(games[i][-2] > games[i][-1]):
            if(predictions[j][i][0] > predictions[j][i][1]):
                count1 = count1 + 2
        if(games[i][-2] < games[i][-1]):
            if(predictions[j][i][1] > predictions[j][i][0]):
                count1 = count1 + 2
        if(games[i][-2] == games[i][-1]):
            if(predictions[j][i][1] == predictions[j][i][0]):
                count1 = count1 + 2
    gamePoints.append(count1)    
print()

#prints winner
print("Winner(s): (max points: " + str(max(playerScore)) + ")")
for i in range(len(playerScore)):
    winner = max(playerScore)
    if(playerScore[i]==winner):
        print(players[i])
print()
#prints game points
print("Game points:")
for i in range(len(predictions[0])):
    spaces1 = len(str(games[i][3]) + "vs"+ str(games[i][4]))
    spaces2 = len(str(gamePoints[i]))
    print(games[i][3], "vs", games[i][4]," " * (26 - spaces1),":"," " *(2-spaces2),gamePoints[i])
    
#finds min of game points
minPoints = gamePoints[0]
for i in range(1,len(predictions[0])):
    if(gamePoints[i] <= minPoints):
        minPoints = gamePoints[i] 
print()
print("Hardest game(s) (min points: " + str(minPoints) +")")
for i in range(0,len(predictions[0])):
    if(gamePoints[i] <= minPoints):
        minPoints = gamePoints[i]
        print(games[i][3], "vs", games[i][4])
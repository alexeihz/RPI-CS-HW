"""
This module reads a file containing predictions.
First line in the file contains the names of columns, including
names of players
Remaining lines contain each a soccer game, real score, followed by
the predicted scores by each player

Example first line:

Nr.,Date,Group,Side A,Side B,REAL,REAL,Eleven,Eleven,Dustin,Dustin

Example game line:

2,11-Jun,A,Albania,Switzerland,0,1,0,1,0,1
"""

import csv

def read_predictions(filename):
    """ Returns three lists

    games: list of tuples, each containing information for a game of
           the form: (1, '10-Jun', 'A', 'France', 'Romania', 2, 1)
           The last two items is the score of the game for first
           and second teams

    players: list of strings containing name of players
 
    predictions: list of lists,
                 each list is for a different player and contains
                 one tuple for each game of the form: (x,y) 
                  where x,y are the scores for the first and second teams
    """
    lineno = 0
    data = []
    filereader = csv.reader(open(filename, 'rU', encoding="utf-8"), delimiter=",", quotechar='"')
    games = []
    players = []
    predictions = []
    for line in filereader:
        lineno += 1
        if lineno == 1:
            for i in range(7, len(line),2):
                players.append( line[i] )
                predictions.append( [] )
            continue
        games.append( (int(line[0]),line[1],line[2],line[3],line[4],int(line[5]), int(line[6])) )
        j = 0
        for i in range(7, len(line),2):
            predictions[j].append( (int(line[i]),int(line[i+1])) )
            j += 1
    return games, players, predictions


if __name__ == "__main__":
    games, players, predictions = read_predictions('predictions_short.txt')
    print (games)
    print (players)
    print (predictions)

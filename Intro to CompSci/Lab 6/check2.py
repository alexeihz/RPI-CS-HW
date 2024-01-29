def ok_to_add(row,column,number,board):
    r =(row%3)*3
    c = (column%3)*3
    if(row<0 or row>8 or column<0 or column>8 or number>9 or number<1):
        return False
    if(board[row][column]!="."):
        #return False
        return("This number cannot be added")
    if(str(number) in board[row]):
        #return False
        return("This number cannot be added")
    for j in range(0,9):
        if(str(number) == board[j][column]): 
            #return False
            return("This number cannot be added")
    for k in range(r,r+3):
        for l in range(c,r+3):
            if(board[k][l]==number):
                #return False
                return("This number cannot be added")
    return True
    #return number

    


rows = int(input("Enter a column => "))
cols = int(input("Enter a row => "))
num = int(input("Enter a number => "))
bd = [ [ '1', '.', '.', '.', '2', '.', '.', '3', '7'],
       [ '.', '6', '.', '.', '.', '5', '1', '4', '.'],
       [ '.', '5', '.', '.', '.', '.', '.', '2', '9'],
       [ '.', '.', '.', '9', '.', '.', '4', '.', '.'],
       [ '.', '.', '4', '1', '.', '3', '7', '.', '.'],
       [ '.', '.', '1', '.', '.', '4', '.', '.', '.'],
       [ '4', '3', '.', '.', '.', '.', '.', '1', '.'],
       [ '.', '1', '7', '5', '.', '.', '.', '8', '.'],
       [ '2', '8', '.', '.', '4', '.', '.', '.', '6'] ]
border = "- " * 18
print(ok_to_add(cols,rows,num,bd))
print(border)
for i in range(len(bd)):
    print("|",end="")
    for j in range(len(bd[i])):
        print(" "+ str(bd[i][j]) + " ",end='')
        if(j==2 or j == 5):
            print(" | ",end="")
    print(" | ")
    if(i==2 or i==5):
        print(border)
print(border)
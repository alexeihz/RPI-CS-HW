import lab06_util

def verify_board(board):
    for i in range(0,9):
        for j in range(0,9):
            if(board[i][j]=='.'):
                return False
    return True

def ok_to_add(row,column,number,board):
    r =(row%3)*3
    c = (column%3)*3
    if(row<0 or row>8 or column<0 or column>8 or number>9 or number<1):
        return False
    if(board[row][column]!="."):
        return False
        #return("This number cannot be added")
    if(str(number) in board[row]):
        return False
        #return("This number cannot be added")
    for j in range(0,9):
        if(str(number) == board[j][column]): 
            return False
            #return("This number cannot be added")
    for k in range(r,r+3):
        for l in range(c,r+3):
            if(board[k][l]==number):
                return False
                #return("This number cannot be added")
    return True


fname = input("Please enter a file name ==> ")
print(fname)
bd = lab06_util.read_sudoku(fname)
border = "- " * 18
verify = verify_board(bd)
for i in range(len(bd)):
    print("|",end="")
    for j in range(len(bd[i])):
        print(" "+ bd[i][j] + " ",end='')
        if(j==2 or j == 5):
            print(" | ",end="")
    print(" | ")
    if(i==2 or i==5):
        print(border)
print(border)
while(verify==False):
    rows = int(input("Enter a row => "))
    cols = int(input("Enter a column => "))
    num = int(input("Enter a number => "))
    print(ok_to_add(rows, cols, num, bd))
    if(ok_to_add(rows, cols, num, bd)):
        bd[rows][cols]=num
    verify = verify_board(bd)
    print(verify)
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
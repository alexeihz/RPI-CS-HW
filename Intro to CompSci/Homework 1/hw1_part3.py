import math


word = input("Word => ")
print(word)
cols = input("#columns => ")
print(cols)
rows = input("#rows => ")
print(rows)
print("Your word is:", word)
print()

print("(a)",end="")
cols = int(cols)
rows = int(rows)
colsMultiply = "*** "*cols
colsMultiply = colsMultiply.strip(" ")
rowsMultiply = ("\n" + colsMultiply)*rows
print(rowsMultiply)
print()



print("(b)",end="")
rowsMultiply1 = ("\n" + colsMultiply)*int((rows-1)/2)
print(rowsMultiply1)
print(int(cols/2)*"*** "+"CS1"+" ***"*int(cols/2))
print((colsMultiply + "\n")*int((rows-1)/2),end="\n")



print("(c)")
colsMultiply1 = "*** "*int((cols-1)/2) + " |  " + "*** "*int((cols-1)/2)
colsMultiply1 = colsMultiply1.strip(" ")
rowsMultiply2 = ("\n" + colsMultiply)*int((rows-1)/3)
print(colsMultiply1 + rowsMultiply2)
print(" |  " + (int(cols/2) -1)*"*** "+"CS1"+" ***"*(int(cols/2) -1) + "  | " + rowsMultiply2)
print(colsMultiply1)
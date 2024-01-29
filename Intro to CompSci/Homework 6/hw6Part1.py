#method checks if word exists in the dictionary
def found(word,dictionary):
    if(word in dictionary):
        return word
    return "False"    

#method checks if dropping a letter causes the word to exist in the dictionary
#loops through every letter in the word
def drop(word,dictionary):
    realWords = []
    for i in range(len(word)):
        word2 = list(word)
        word2.pop(i)
        if("".join(word2) in dictionary):
            realWords.append("".join(word2))
        if(len(realWords)>1 and realWords[0]<=realWords[1]):
            realWords.pop(1)
        if(len(realWords)>1 and realWords[0]>=realWords[1]):
            realWords.pop(0)
    if(len(realWords)!=0):
        return realWords[0]
    return "False"


#method checks if swapping a letter with the one right next to it causes the word to exist in the dictionary
#loops through every letter in the word
def swap(word,dictionary):
    realWords = []
    for i in range(len(word)-1):
        word2 = list(word)
        swap = word[i+1]
        word2.pop(i+1)
        word2.insert(i+1,word[i])
        word2.pop(i)
        word2.insert(i,swap)
        if("".join(word2) in dictionary):
            realWords.append("".join(word2))
        if(len(realWords)>1 and realWords[0]<=realWords[1]):
            realWords.pop(1)
        if(len(realWords)>1 and realWords[0]>=realWords[1]):
            realWords.pop(0)
    if(len(realWords)!=0):
        return realWords[0]
    return "False"

#method checks if replacing a letter with any letter in the alphabet causes the word to exist in the dictionary
#loops through every letter in the word
def replace(word,dictionary):
    letters = [ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'y', 'z' ]
    realWords = []
    for i in range(len(word)):
        for k in range(len(letters)):
            word2 = list(word)
            word2.insert(i,letters[k])
            word2.pop(i+1)
            if("".join(word2) in dictionary):
                realWords.append("".join(word2))
        if(len(realWords)>1 and realWords[0]<=realWords[1]):
            realWords.pop(1)
        if(len(realWords)>1 and realWords[0]>=realWords[1]):
            realWords.pop(0)
    if(len(realWords)!=0):
        return realWords[0]
    return "False"


#variable initialization
webster = input("Dictionary file => ")
print(webster)
words = input("Input file => ")
print(words)
webster2 = set()
websterOpen = open(webster)
wordsOpen = open(words)
line = websterOpen.readline()

#reads the dictionary file, line by line, and adds each line to a set until there aren't any lines left in the file
while line != '':
    webster2.add(line.strip("\n"))
    line = websterOpen.readline()

#reads the input file, line by line, and adds each line to a list until there aren't any lines left in the file
line2 = wordsOpen.readline()
words2 = []
while line2 != '':
    words2.append(line2.strip("\n"))
    line2 = wordsOpen.readline()

#goes through each word in the input file list and checks if its in the dictionary set and if not goes through the methods to try and fix it
for p in words2:
    if(found(p,webster2)!="False"):
        print(p+" "* (15 - len(p)),"->",found(p,webster2) + " "* (15 - len(p)),":FOUND")
    elif(drop(p,webster2)!="False"):
        print(p+" "* (15 - len(p)),"->",drop(p,webster2) + " "* (16 - len(p)),":DROP")
    elif(swap(p,webster2)!="False"):
        print(p+" "* (15 - len(p)),"->",swap(p,webster2) + " "* (15 - len(p)),":SWAP")
    elif(replace(p,webster2)!="False"):
        print(p +" "* (15 - len(p)), "->",replace(p,webster2) + " "* (15 - len(p)),":REPLACE")
    else:
        print(p + " "* (15 - len(p)),"->",p + " "* (15 - len(p)),":NO MATCH")
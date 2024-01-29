#method checks if word exists in the dictionary
def found(word,dictionary):
    if(word in dictionary.keys()):
        return word
    return "False"    

#method checks if dropping a letter causes the word to exist in the dictionary
#loops through every letter in the word
def drop(word,dictionary):
    realWords = set()
    for i in range(len(word)):
        word2 = list(word)
        word2.pop(i)
        if("".join(word2) in dictionary):
            realWords.add((dictionary["".join(word2)].strip('\n'),"".join(word2)))
    if(len(realWords)!=0):
        #print(realWords)
        return list(realWords)
    return "False"

#method checks if swapping a letter with the one right next to it causes the word to exist in the dictionary
#loops through every letter in the word
def swap(word,dictionary):
    realWords = set()
    for i in range(len(word)-1):
        word2 = list(word)
        swap = word[i+1]
        word2.pop(i+1)
        word2.insert(i+1,word[i])
        word2.pop(i)
        word2.insert(i,swap)
        if("".join(word2) in dictionary):
            realWords.add((dictionary["".join(word2)].strip('\n'),"".join(word2)))
    if(len(realWords)!=0):
        #print(realWords)
        return list(realWords)
    return "False"

#method checks if replacing a letter with any letter close to that letter on a QWERTY keyboard causes the word to exist in the dictionary
#loops through every letter in the word
def replace(word,dictionary,keyboard):
    realWords = set()
    keys = keyboard.read().split("\n")
    keys.pop()
    for i in range(len(word)):
        for k in range(len(keys)):
            word2 = list(word)
            keySplit = keys[k].split(" ")
            if(keySplit[0]==word2[i]):
                for j in range(1,len(keySplit)):
                    word2.insert(i,keySplit[j])
                    word2.pop(i+1)
                    if("".join(word2) in dictionary.keys()):
                        realWords.add((dictionary["".join(word2)].strip('\n'),"".join(word2)))    
    if(len(realWords)!=0):
        return list(realWords)
    return "False"


#variable initialization
webster = input("Dictionary file => ")
print(webster)
words = input("Input file => ")
print(words)
keyboard = input("Keyboard file => ")
print(keyboard)
webster2 = dict()
websterOpen = open(webster)
wordsOpen = open(words)
line = websterOpen.readline()

#reads the dictionary file, line by line, and adds each line to a set until there aren't any lines left in the file
while line != '':
    lineSplit = line.split(",")
    webster2[lineSplit[0]]=lineSplit[1]
    line = websterOpen.readline()

#reads the input file, line by line, and adds each line to a list until there aren't any lines left in the file
line2 = wordsOpen.readline()
words2 = []
while line2 != '':
    words2.append(line2.strip("\n").strip())
    line2 = wordsOpen.readline()

#goes through each word in the input file list and checks if its in the dictionary and if not goes through the methods to try and fix it
print("Spellcheck results:")
for p in words2:
    matchWords = dict()
    keyOpen = open(keyboard)
    checkReplace = replace(p,webster2,keyOpen)
    if(found(p,webster2)!="False"):
        print("{:15} -> {:15} :{}".format(p,found(p,webster2),"FOUND"))    
    else:
        if(drop(p,webster2)!="False"):
            for i in range(len(drop(p,webster2))):
                matchWords[drop(p,webster2)[i]] = i
        if(swap(p,webster2)!="False"):
            for i in range(len(swap(p,webster2))):
                matchWords[swap(p,webster2)[i]] = i
        if(checkReplace!="False"):
            for i in range(len(checkReplace)):
                matchWords[checkReplace[i]] = i
            keyOpen.close()
        matchWords2 = list(matchWords.keys())
        matchWords2.sort(reverse=True)
        minLen = min(3,len(matchWords2))
        for n in range(minLen):
            print("{:15} -> {:15} :{}".format(p,matchWords2[n][1],"MATCH " + str(n+1)))
        if len(matchWords2) == 0:
            print("{:15} -> {:15} :{}".format(p,p,"NO MATCH"))
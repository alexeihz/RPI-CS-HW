import syllables

#variable creation
para = input("Enter a paragraph => ")
print(para)
#splits paragraph into list of words
paraSplit = para.split()
hardWords = 0
hardList = []
i = 0
ASL = 0
wordCount = 0
sentenceCount = 0
syllablesCount = 0

#while loop runs until the end of the paragraph
#while loop computes number of sentences, number of words, and hard words
while(i<len(paraSplit)):
    syllablesCount = syllablesCount + syllables.find_num_syllables(paraSplit[i])
    wordCount = wordCount + 1
    if(paraSplit[i][len(paraSplit[i])-1]=="."):
        ASL = ASL + wordCount
        sentenceCount = sentenceCount + 1
        wordCount = 0
    m = syllables.remove_punctuation(paraSplit[i],[".",",",":","-","!","?","'"])
    if(paraSplit[i].find("-")==(-1)):
        if(syllables.find_num_syllables(paraSplit[i])>=3):
            if(not(m[len(m)-2]=="e" and m[len(m)-1]=="d") or not(m[len(m)-2]=="e" and m[len(m)-1]=="s")):
                hardWords = hardWords + 1
                hardList.append(paraSplit[i])
    i = i + 1
        
ASL = (ASL/sentenceCount)
PHW = (hardWords/len(paraSplit))*100
GFRI = 0.4*(ASL + PHW)
ASYL = syllablesCount/len(paraSplit)
FKRI = 206.835-1.015*ASL-86.4*ASYL

#outputs
print("Here are the hard words in this paragraph:")
print(hardList)
print("Statistics: ASL:{0:.2f} PHW:{1:.2f}% ASYL:{2:.2f}".format(ASL,PHW,ASYL))
print("Readability index (GFRI): {0:.2f}".format(GFRI))
print("Readability index (FKRI): {0:.2f}".format(FKRI))

#There is a theory which states that if ever anyone discovers exactly what the Universe is for and why it is here, it will instantly disappear and be replaced by something even more bizarre and inexplicable. There is another theory which states that this has already happened.

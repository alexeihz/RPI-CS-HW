def get_words(description):
    punctuation = [".",",","()",'"']
    description = description.lower().strip("\n")
    descList = description.split(" ")
    i = 0
    while i < (len(descList)):
        for punc in punctuation:
            descList[i] = descList[i].replace(punc," ")                
        if(descList[i].strip(" ").isalpha()==False or len(descList[i].strip(" "))<4):
            descList.pop(i)
            i= i -1
            continue
        i = i+1
    return set(descList)

file = input("Enter file: ")
fileOpen = open(file)
line = fileOpen.read().split("|")
clubName = line[0]
clubDesc = line[1]
print(get_words(clubDesc))
#print(len(get_words(clubDesc)))
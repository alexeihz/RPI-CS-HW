def get_words(description):
    punctuation = [".",",","()",'"']
    description = description.lower().strip("\n")
    descList = description.split(" ")
    i = 0
    while i < (len(descList)):
        for punc in punctuation:
            descList[i] = descList[i].replace(punc," ") 
        descList[i] = descList[i].strip(" ")
        if(descList[i].strip(" ").isalpha()==False or len(descList[i])<4):
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

file1 = input("Enter file: ")
fileOpen1 = open(file1)
line1 = fileOpen1.read().split("|")
clubName1 = line1[0]
clubDesc1 = line1[1]

words1 = get_words(clubDesc)
words2 = get_words(clubDesc1)
intersect = words2 & words1
print("Same words:",intersect)
print("Unique to wrpi:", words1 - intersect)
print("Unique to csa:", words2 - intersect)
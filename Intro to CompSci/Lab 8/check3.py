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
words2 = get_words(clubDesc)

allClubs = open("allclubs.txt")
lineClubs = allClubs.read().split("\n")
listClubs = []
similarClubs = []
for i in range(len(lineClubs)):
    clubSplit = lineClubs[i].split("|")
    if(clubSplit==['']):
        break
    name = clubSplit[0]
    desc = clubSplit[1]
    words1 = get_words(desc)
    listClubs.append((name,words1))

for i in range(len(listClubs)):
    if(clubName != listClubs[i][0]):
        similarClubs.append((len(listClubs[i][1] & words2),listClubs[i][0]))

similarClubs.sort(reverse=True)
for k in range(5):
    print(similarClubs[k][1])
import textwrap

#variable initialization
title = input("Enter a title (stop to end) => ")
print(title,end="\n"*2)
beasts = []
otherTitles = set()
onlyBeasts = []
realTitle = ''
noExist = False

#loops until stop is inputed
while title != "stop":
    file = open("titles.txt")
    line = file.readline()
    
    #finds the title, if it exists, and all the beasts in the title
    while line != "":
        lineSplit = line.split("|")
        if(title in lineSplit[0].lower()):
            realTitle = lineSplit[0]
            print("Found the following title:",lineSplit[0])
            for i in range(1,len(lineSplit),1):
                beasts.append(lineSplit[i].strip("\n"))
            beasts = sorted(beasts)
            addLine = "Beasts in this title: " + ", ".join(beasts)
            lines = textwrap.wrap(addLine)
            for j in lines:
                print(j)            
            break
        line = file.readline()
    if(line==""):
        print("This title is not found!")
        noExist = True
    file.close()
    
    
    #if the title exists, loops until there are no more lines in the file and looks for other titles with beasts in common with the original title
    if(noExist==False):
        print()
        file = open("titles.txt")
        line = file.readline()
        while line != "":
            lineSplit = line.split("|")
            if(lineSplit[0]!=realTitle):
                for i in range(1,len(lineSplit)):
                    if(lineSplit[i].strip('\n') in beasts):
                        otherTitles.add(lineSplit[0])
            line = file.readline()
        otherTitles = sorted(otherTitles)
        addLine = "Other titles containing beasts in common: " + ", ".join(otherTitles)
        lines = textwrap.wrap(addLine)
        for j in lines:
            print(j)
        file.close()
        
        print()
        
        #if the orginal title exists, loops and removes beasts that are common to other titles from the list beasts
        file = open("titles.txt")
        line = file.readline()
        while line != "":
            lineSplit = line.split("|")
            if(lineSplit[0]!=realTitle):
                for i in range(1,len(lineSplit),1):
                    if(lineSplit[i].strip('\n') in beasts):
                        beasts.remove(lineSplit[i].strip('\n'))
            line = file.readline()
        addLine = "Beasts appearing only in this title: " + ", ".join(beasts)
        lines = textwrap.wrap(addLine)
        for j in lines:
            print(j)           
        file.close()
        
        print()
        
    #resets all variables and asks for another input
    beasts.clear()
    otherTitles = set()
    onlyBeasts.clear()
    realTitle = ''    
    title = input("Enter a title (stop to end) => ")
    print(title,end="\n"*2)
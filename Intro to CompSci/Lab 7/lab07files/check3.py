def parse_line(text):
    listy = text.split("/")
    listy2 = []
    if(listy[-1].isnumeric()==False or listy[-2].isnumeric()==False or listy[-3].isnumeric()==False):
        return None
    for i in range(0,3):
        listy2.append(listy.pop())
    return str(listy2[-1]) + ", " + str(listy2[-2]) + ", " + str(listy2[-3]) + ", '" + "/".join(listy)+"'"

def get_line(fname,parno,lineno):
    f = open(fname+".txt")
    paraCount = 0
    lineCount = 0
    spaceCount = 0
    while lineCount<lineno:
        line = f.readline().strip("\n")
        #print(line)
        if(line==""):
            spaceCount +=1
            #print(spaceCount)
            if(spaceCount>1):
                paraCount-=1
            paraCount+=1
        if(line!=""):
            spaceCount=0
            #print(paraCount)
        if(paraCount==parno-1):
            if(line==""):
                lineCount-=1
            lineCount+=1
            #print(lineCount)
    return line

file = input("Please enter the file number ==> ")
paragraph = int(input("Please enter the paragraph number ==> "))
line = int(input("Please enter the line  number ==> "))
f = open("program.py","w")
while(get_line(file,paragraph,line)!="END/0/0/0"):
    output = (parse_line(get_line(file,paragraph,line))).split(",")
    #print(output[-1].strip(" ").strip("'"))
    f.write(output[-1].strip(" ").strip("'"))
    f.write("\n")
    file2 = output[0].strip(" ")
    paragraph2 = int(output[1].strip(" "))
    line2 = int(output[2].strip(" "))
    file = file2
    paragraph = paragraph2
    line = line2
f.close()
def parse_line(text):
    listy = text.split("/")
    listy2 = []
    if(listy[-1].isnumeric()==False or listy[-2].isnumeric()==False or listy[-3].isnumeric()==False):
        return None
    for i in range(0,3):
        listy2.append(listy.pop())
    return str(listy2[-1]) + ", " + str(listy2[-2]) + ", " + str(listy2[-3]) + ", " + "/".join(listy)

print(parse_line("Here is some random text, like 5/3=/4./12/3/4"))
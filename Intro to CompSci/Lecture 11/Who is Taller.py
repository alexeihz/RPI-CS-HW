hd = int(input("Enter Dale's height: "))
print(hd)
he = int(input("Enter Erin's height: "))
print(he)
hs = int(input("Enter Sam's height: "))
print(hs)
if(hd>he):
    if(hd<hs):
        print("Sam\nDale\nErin")
    if(hd>hs):
        if(hs>he):
            print("Dale\nSam\nErin")
        if(hs<he):
            print("Dale\nErin\nSam")
if(he>hd):
    if(he<hs):
        print("Sam\nErin\nDale")
    if(he>hs):
        if(hs>hd):
            print("Erin\nSam\nDale")
        if(hs<hd):
            print("Erin\nDale\nSam")    
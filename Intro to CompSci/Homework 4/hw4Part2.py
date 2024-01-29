password = input("Enter a password => ")
print(password)
rule1 = False
rule2 = False
rule3 = False
rule4 = True
rule5 = True

#checks if the password is between 10 and 25 characters and begins with a letter
if(len(password) >=10 and len(password) <= 25 and password[0].lower().islower()):
    rule1 = True
    print("Rule 1 is satisfied")
else:
    print("Rule 1 is not satisfied")
    
#checks to make sure there is a @ or a $ but no %
if(password.find("@") != -1 or password.find("$") != -1 and password.find("%") == -1):
    rule2 = True
    print("Rule 2 is satisfied")
else:
    print("Rule 2 is not satisfied")
    
#checks if 1,2,3, or 4 is in the password or if it has at least one uppercase letter and lowercase letter
if((password.find("1") != -1 or password.find("2") != -1 or password.find("3") != -1 or password.find("4") != -1) or (password.islower()==False and password.isupper()==False)):
    rule3 = True
    print("Rule 3 is satisfied")
else:
    print("Rule 3 is not satisfied")
    
#checks to make sure that every uppercase letter is followed by at least one _
i = 0    
while(i < len(password)-1):
    if(password[i].isupper() == True):
        if(password[i+1].find("_") != -1):
            rule4 = True
            i = i +1
        else:
            rule4 = False
            break
    if(password[len(password)-1].isupper() == True):
        rule4 = False
        break
    i = i +1
#checks to make sure there are no numbers greater than 4
i = 0
while(i < len(password)-1):
    if(password[i].isnumeric() == True):
        if(int(password[i])>4):
            rule5 = False
            break
        elif(password[i+1].isnumeric() == True):
            if((password[i]=='0' and int(password[i])>4)):
                rule5 = False
                break
    i = i+1

if(rule4==True):
    print("Rule 4 is satisfied")
else:
    print("Rule 4 is not satisfied")
    
if(rule5==True):
    print("Rule 5 is satisfied")
else:
    print("Rule 5 is not satisfied")
    
#suggests the new password
str1=""
str2=""
listStr=[]
if(rule1 == True and (rule2 == False or rule3 == False or rule4 == False or rule5 == False)):
    i=0
    while(i<8):
        str1 = str1 + password[i]
        i = i+1
        
    j=len(password)-1
    while(j>=len(password)-8):
        listStr.insert(0,password[j])
        j=j-1
        
    k = 0
    while(k<len(listStr)):
        str2 = str2 + listStr[k]
        k=k+1    
    print("A suggested password is " + str1 + "42" + str2)

if(rule1 and rule2 and rule3 and rule4 and rule5):
    print("The password is valid")
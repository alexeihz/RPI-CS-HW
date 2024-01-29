import math
firstName = input("Please enter your first name: ")
print(firstName)
lastName = input("Please enter your last name: ")
print(lastName)
lastName = lastName + "!"
firstNameLen = len(firstName)
lastNameLen = len(lastName)
helloLen = len("Hello,")
maxLen = max(firstNameLen,lastNameLen,helloLen)

print("***" + "*"*maxLen +"***")
print("** Hello," + " "*(maxLen-helloLen) + " **")
print("** " + firstName + " "*(maxLen-firstNameLen)+ " **")
print("** " + lastName + " "*(maxLen-lastNameLen)+ " **")
print("***" + "*"*maxLen +"***")
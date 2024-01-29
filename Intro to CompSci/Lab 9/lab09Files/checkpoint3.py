from Date import *
birthdaysOpen = open("birthdays.txt")
birthdays = []
line = birthdaysOpen.readline()
while line!="":
    line = line.strip("\n")
    lineSplit = line.split(" ")
    birthdays.append(tuple(lineSplit))
    line = birthdaysOpen.readline()

earliest_Bday = Date(sorted(birthdays)[0][0], sorted(birthdays)[0][1], sorted(birthdays)[0][2])
latest_Bday = Date(sorted(birthdays,reverse=True)[0][0], sorted(birthdays,reverse=True)[0][1], sorted(birthdays,reverse=True)[0][2])


#print(sorted(birthdays))
print("The Earliest Birthday:",str(earliest_Bday))
print("The Latest Birthday:",str(latest_Bday))

birthdayList = []
for i in range(len(birthdays)):
    date2 = Date(birthdays[i][0], birthdays[i][1], birthdays[i][2])
    birthdayList.append(int(birthdays[i][1]))
#print(sorted(birthdayList))
most_Bdays = set()
for j in range(1,13):
    count = birthdayList.count(j)
    most_Bdays.add((count,j))
    
print("Month with most birthdays:", month_names[sorted(most_Bdays, reverse=True)[0][1]])
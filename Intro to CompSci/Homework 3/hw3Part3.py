#name of robot, its energy, and its (x,y) location
name = input("Name of robot => ")
print(name)
x = int(input("X location => "))
print(x)
y = int(input("Y location => "))
print(y)
energy = 10
print("Robot ",name," is at (",x,",",y,") with energy: ", energy,sep="")
#starting command so while loop will run
command = input("Enter a command (up/left/right/down/attack/end) => ")
print(command)
#while loop runs until end is inputted
#while loop controls how robot moves and its energy change
while(command.lower() != "end"):
    if(command.lower() == "attack" and energy>=3):
        energy= energy-3
    elif(command.lower() == "up"):
        if(energy<1):
            energy = energy + 1 
        else:
            y = max(0,y-10)
            energy = min(energy+1,10)
    elif(command.lower() == "down"):
        if(energy<1):
            energy = energy + 1 
        else:
            y = min(100,y+10)
            energy = min(energy+1,10)
    elif(command.lower() == "right"):
        if(energy<1):
            energy = energy + 1  
        else:
            x = min(100,x+10)
            energy = min(energy+1,10)
    elif(command.lower() == "left"):
        if(energy<1):
            energy = energy + 1  
        else:
            x = max(0,x-10)
            energy = min(energy+1,10)
    print("Robot ",name," is at (",x,",",y,") with energy: ", energy,sep="")
    command = input("Enter a command (up/left/right/down/attack/end) => ")
    print(command)    
        
    
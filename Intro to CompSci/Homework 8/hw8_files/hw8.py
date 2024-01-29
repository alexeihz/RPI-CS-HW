from Person import *
from Universe import *
import math   


inputFile = input("Input file => ")
print(inputFile)
data=json.loads(open(inputFile).read())

individuals = []
universes = []
portals = []
rewards = []
rewarddict = dict()

#creates lists to have get universes and people into appropriate lists 
for i in range(len(data)):
    universes.append(data[i]["universe_name"])
    portals.append(data[i]["portals"])
    rewards.append((data[i]["rewards"]))
    individuals.append((data[i]["individuals"]))

uniList = []
individualList = []
for j in range(len(universes)):
    uniList.append(Universe(universes[j],rewards[j],portals[j]))
    for l in range(len(rewards[j])):
        rewarddict[rewards[j][l][3]] = [True,universes[j]]
        
for i in range(len(individuals)):
    for j in range(len(individuals[i])):
        individualList.append(Person(individuals[i][j][0],individuals[i][j][1],universes[i],individuals[i][j][2],individuals[i][j][3],individuals[i][j][4],individuals[i][j][5]))

copyIndividualList = individualList.copy()
print("All universes")
print("-"*40)
for k in range(len(uniList)):
    print(str(uniList[k]))
    
print()
print("All individuals")
print("-"*40)
for k in range(len(individualList)):
    print(str(individualList[k]))
  
print()
#starts the simulations
print("Start simulation")
print("-"*40)
continueTrue = False
is_stopped_count = len(individualList)
turnCount = 0
crashList = []
#checks if people can move at the beginning
for person in individualList:
    if(person.stop_move()==False and turnCount==0):
        print(person.person + " stopped at simulation step", turnCount , "at location (" + str(round(person.x,1))+ "," + str(round(person.y,1)) + ")\n")
        individualList.remove(person)
    
turnCount = turnCount + 1

#loops until everyone stops or simulation reaches 100 steps
while True:
    #checks if person can move
    for person in individualList:
        if(person.stop_move()==False):
            continueTrue = True
            turnCount = turnCount - 1
            print(person.person + " stopped at simulation step", turnCount , "at location (" + str(round(person.x,1))+ "," + str(round(person.y,1)) + ")\n")
            individualList.remove(person)
            break
            
        person.move()
        #checks if reward is at the person and the person picks up the reward
    for person in individualList:
        for uni in uniList:
            for reward in uni.rewards:
                if rewarddict[reward[3]][0]==True and person.current_universe == rewarddict[reward[3]][1] and math.sqrt((person.x-reward[0])**2+(person.y-reward[1])**2)<= person.radius :
                    person.add_reward(reward)
                    person.add_points(reward[2])
                    print(person.person+ ' picked up "' + reward[3] + '" at simulation step {}'.format(turnCount))
                    print(str(person))
                    print()
                    rewarddict[reward[3]][0] = False
    #checks if 2 people crash and drops rewards and changes speed accordingly
    for person in individualList:
        for crash in individualList:
            if person != crash and crash.current_universe == person.current_universe and math.sqrt((person.x-crash.x)**2+(person.y-crash.y)**2)<= person.radius + crash.radius and (person.crash==False and crash.crash==False or person.crash != crash.crash):
                print(person.person +" and " + crash.person + " crashed at simulation step",turnCount,"in universe " + crash.current_universe)
                person.crash = True
                crash.crash = True
                if len(person.reward)>0:
                    person.sub_points(person.reward[0][2])
                    drop1 = person.collision()
                    for i in rewarddict.keys():
                        if drop1[3] == i:
                            print(person.person + ' dropped "' + drop1[3] + '", reward returned to '  + rewarddict[i][1] + " at (" + str(drop1[0]) +","+str(drop1[1])+")")
                            rewarddict[i][0] = True
                #else:
                    #drop1 =person.collision()
                if len(crash.reward)>0:
                    crash.sub_points(crash.reward[0][2])
                    drop2 = crash.collision()
                    for i in rewarddict.keys():
                        if drop2[3] == i:
                            print(crash.person + ' dropped "' + drop2[3] + '", reward returned to '  + rewarddict[i][1] + " at (" + str(drop2[0]) +","+str(drop2[1])+")")
                            rewarddict[i][0] = True
                #else: 
                    #drop2 = crash.collision()
                print(person)
                print(crash)
                print()
    #checks for portal near to person and makes the person pass through it 
    for person in individualList:
        for uni in uniList:
            for portal in uni.portals:
                if math.sqrt((person.x-portal[0])**2+(person.y-portal[1])**2)<= person.radius and uni.name == person.current_universe:
                    print(person.person + " passed through a portal at simulation step {}".format(turnCount))
                    person.update_universe(portal[2])
                    person.x = float(portal[3])
                    person.y = float(portal[4])
                    print(person)
                    print()
                break    
        
    
    if(len(individualList)==0 or turnCount==100):
        break 
    turnCount = turnCount +1

#ends the simulation and prints out the winners 
print()
print("-"*40)
print("Simulation stopped at step {}".format(turnCount))
print(len(individualList),"individuals still moving")
maxpoints = 0
for person in copyIndividualList:
    if person.points >= maxpoints:
        maxpoints = person.points
print("Winners:")

for person in copyIndividualList:
    if person.points >= maxpoints:
        print(person)
        print("Rewards:")
        person.str_rewards()
        print()
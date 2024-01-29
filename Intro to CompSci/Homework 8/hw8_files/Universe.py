import json

class Universe(object):
    def __init__(self,name,rewards,portal):
        self.name = name
        self.rewards = rewards
        self.portals = portal
    
    def strUniverse(self):
        return str(self.name) + " ("+ str(len(self.rewards))+" rewards and " + str(len(self.portals)) + " portals)"
    
    def strRewards(self):
        str1 = ""
        for reward in self.rewards:
            str1 = str1 + "at (" + str(reward[0]) + ',' + str(reward[1]) + ") for " + str(reward[2]) + " points: " + str(reward[3]) + "\n"
        if(str1==''):
            return "None\n"
        str1.strip("\n")
        return str1
    
    def strPortals(self):
        str1 = ''
        for portal in self.portals:
            str1 = str1 + str(self.name) + ':(' + str(portal[0]) + ',' + str(portal[1]) + ') -> ' + portal[2] + ":(" + str(portal[3]) + ',' + str(portal[4]) + ")\n"
        if(str1==''):
            return "None"
        str1.strip("\n")
        return str1
    
    
    def remove_reward(self,reward):
        for i in self.rewards:
            if reward == i:
                return False
        return True
    
    #def return_reward(self,reward):
        
    #combines str functions from before into one str function
    def __str__(self):
        return "Universe: " + self.strUniverse() + "\nRewards:\n" + self.strRewards() + "Portals:\n" + self.strPortals()
    
if __name__ == "__main__":
    file = "file1.txt"
    data=json.loads(open(file).read())
    test = Universe(data[0]["universe_name"], data[0]['rewards'], data[0]['portals'])
    #print("Portals")
    #print(test.strPortals())
    #print("Rewards")
    #print(test.strRewards())
    #print("Universe")
    #print(test.strUniverse())
    print(str(test))
    #print(test.rewards[0])
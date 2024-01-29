import json

class Person(object):
    def __init__(self,person, radius, home_universe, x,y, dx, dy):
        self.person = person
        self.radius = radius
        self.home_universe = home_universe
        self.x = float(x)
        self.y = float(y)
        self.dx = float(dx)
        self.dy = float(dy)
        self.current_universe = home_universe
        self.reward = []
        self.points = 0
        self.crash = False
    
    #updates current universe
    def update_universe(self,universe):
        self.current_universe = universe
    
    #add rewards to players
    def add_reward(self, reward):
        self.reward.append(reward)
        n = len(self.reward)
        self.dx = self.dx - (n%2)* (n/6)*self.dx
        self.dy = self.dy - ((n+1)%2)* (n/6)*self.dy
        

    #def sub_reward(self, reward, points):
        #if(len(self.reward)>0):
            #self.reward.pop(0)
        #else:
            #self.reward = self.reward
    
    #add_points to players
    def add_points(self, points):
        self.points = self.points + points
        
    #subtract points from players
    def sub_points(self, points):
        if(self.points>0):
            self.points = self.points - points
        else:
            self.points = self.points
    
    #checks to see if person can move
    def stop_move(self):
        if self.x >= 1000 or self.x <= 0 or self.y >= 1000 or self.y <= 0:
            return False
        if abs(self.dx) < 10 or abs(self.dy) < 10:
            return False
        return True
    
    #moves person if they can move
    def move(self):
        if self.stop_move() == True:
            self.x = self.x + self.dx
            self.y = self.y + self.dy
    
    #flips direction of person and if they have rewards, makes them drop one and adjusts speed accordingly
    def collision(self):
        self.dx = -1* self.dx
        self.dy = -1*self.dy
        if len(self.reward) > 0:
            n = len(self.reward)-1
            self.dx = self.dx + (n%2)* (n/6)*self.dx
            self.dy = self.dy + ((n+1)%2)* (n/6)*self.dy            
            return self.reward.pop(0)
        else:
            return 0
    
    #converts reward into string
    def str_rewards(self):
        for reward in self.reward:
            print ("    " + reward[3])
    #puts person into string function
    
    def __str__(self):
        str1 = "{} of {} in universe {}".format(self.person, self.home_universe, self.current_universe)
        str2 = "\n    at ({},{}) speed ({},{}) with {} rewards and {} points".format(round(self.x,1),round(self.y,1),round(self.dx,1),round(self.dy,1),len(self.reward),self.points)
        return str1 + str2

if __name__ == "__main__":
    file = "file3.txt"
    data=json.loads(open(file).read())
    test = Person(data[0]["individuals"][0][0],data[0]["individuals"][0][1],data[0]["universe_name"],data[0]["individuals"][0][2],data[0]["individuals"][0][3],data[0]["individuals"][0][4],data[0]["individuals"][0][5])
    #print("Portals")
    #print(test.strPortals())
    #print("Rewards")
    #print(test.strRewards())
    #print("Universe")
    #print(test.strUniverse())
    
    #print(test.str_rewards())
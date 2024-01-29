import random
class Ball(object):
    def __init__(self,x,y,dx,dy,radius,color):
        self.x = x
        self.y = y
        self.dx = dx
        self.dy = dy
        self.radius = radius
        self.color = color
    
    def position(self):
        return (self.x,self.y)
    
    def move(self):
        self.x = self.x + self.dx
        self.y = self.y + self.dy

    def bounding_box(self):
        return (self.x-self.radius, self.y-self.radius, self.x+self.radius, self.y+self.radius)         


    def get_color(self):
        return self.color
    
    def check_and_reverse(self,maxx,maxy):
        if(self.x - self.radius == maxx):
            self.dx = self.dx*-1
        if(self.y - self.radius == maxy):
            self.dy = self.dy*-1
        if(self.x + self.radius == 0):
            self.dx = self.dx*-1
        if(self.y + self.radius == 0):
            self.dy = self.dy*-1
    
    def some_inside(self,maxx,maxy):
        if (0 < self.x + self.radius and self.x - self.radius < maxx and 0 < self.y + self.radius and self.y - self.radius < maxy):
            return True
        return False
    
    
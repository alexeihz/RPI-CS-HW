"""
This program experiments with the use of functions
and also learning error checking.


"""
import math

## Function returns the length of a line 
## starting at (x1,y1) and ending at (x2,y2)
def line_length(x1,y1,x2,y2):
    length = (x1-x2)**2 + (y1-y2)**2
    length = math.sqrt(length)
    return length


initial_x = 10
initial_y = 10
next_x = float(input("The next x value ==> "))
next_y = float(input("The next y value ==> "))
if int(next_x) == next_x:
    next_x = int(next_x)

if int(next_y) == next_y:
    next_y = int(next_y)


print("The point has moved from ({:d},{:d})".format(initial_x, initial_y),\
    "to (" + str(next_x) + "," + str(next_y) + ")")

print("Total length traveled is", round(line_length(initial_x, initial_y, next_x, next_y),2))


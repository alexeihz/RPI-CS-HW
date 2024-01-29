
points = [ (4,2), (1,-3), (-4, -6), (4,9), (-7,8), (-5,2), (6,2) ]
s_points = sorted( points, key = lambda p: abs(p[0]) + abs(p[1]), reverse=True)
print(s_points)

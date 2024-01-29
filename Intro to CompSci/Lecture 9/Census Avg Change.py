census = [ 340, 589, 959, 1372, 1918, 2428, 3097, 3880, 4382, 5082, \
           5997, 7268, 9113, 10385, 12588, 13479, 14830, 16782, \
            8236, 17558, 17990, 18976, 19378 ]
i = 0
j = 1
add = 0
while(i<len(census)-1 and j<len(census)):
    count = (((census[j]-census[i])/census[i])*100)
    
    add = add + count
      
    i=i+1
    j=j+1

avg = round(add/(len(census)-1),1)
print("Average = ", avg ,"%",sep="")
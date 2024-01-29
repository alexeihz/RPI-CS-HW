def increase(fraction,L1):
    for i in range(len(L1)):
        L1[i] = L1[i]*(1+fraction)
    
    return L1


co2_levels = [ 320.03, 322.16, 328.07, 333.91, 341.47, \
               348.92, 357.29, 363.77, 371.51, 382.47, 392.95 ]


fraction = float(input("Enter the fraction: "))
print(fraction)
increase(fraction,co2_levels)
print('First: {:.2f}'.format(co2_levels[0]))
print('Last: {:.2f}'.format(co2_levels[-1]))
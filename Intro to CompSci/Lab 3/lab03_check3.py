def rabbits(bunnies,foxes):
    bunnpop =  int((10*bunnies)/(1+0.1*bunnies) - 0.05*bunnies*foxes)
    return bunnpop

def wily_foxes(bunnies,foxes):
    foxpop = int(0.4 * foxes + 0.02 * foxes * bunnies)
    return foxpop


bpop = int(input("Number of bunnies ==> "))
print(bpop)
fpop = int(input("Number of foxes ==> "))
print(fpop)

print("Year 1:",bpop,fpop)
bpop_next = max(rabbits(bpop,fpop),0)
fpop_next = max(wily_foxes(bpop,fpop),0)

print("Year 2:",bpop_next,fpop_next)
bpop = max(rabbits(bpop_next,fpop_next),0)
fpop = max(wily_foxes(bpop_next,fpop_next),0)

print("Year 3:",bpop,fpop)
bpop_next = max(rabbits(bpop,fpop),0)
fpop_next = max(wily_foxes(bpop,fpop),0)

print("Year 4:",bpop_next,fpop_next)
bpop = max(rabbits(bpop_next,fpop_next),0)
fpop = max(wily_foxes(bpop_next,fpop_next),0)

print("Year 5:",bpop,fpop)
bpop_next = max(rabbits(bpop,fpop),0)
fpop_next = max(wily_foxes(bpop,fpop),0)
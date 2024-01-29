import time
import random
def closest1(L):
    '''
    >>> closest1([ 15.1, -12.1, 5.4, 11.8, 17.4, 4.3, 6.9 ])
    (5.4, 4.3)
    
    >>> closest1([ 12.1, 12.1, 5.4, 11.8, 17.4, 4.3, 6.9 ])
    (12.1, 12.1)
    
    >>> closest1([])
    (None, None)
    '''            
    
    
    dist = 999999999999999999999999999999
    if len(L)<2:
        return (None,None)
    for i in range(len(L)):
        for j in range(len(L)):
            if(abs(L[i]-L[j])<dist and i!=j):
                closest = (L[i],L[j])
                dist = abs(L[i]-L[j])
    return closest

def closest2(L):
    '''
    >>> closest2([ 15.1, -12.1, 5.4, 11.8, 17.4, 4.3, 6.9 ])
    (4.3, 5.4)
    
    >>> closest2([ 12.1, 12.1, 5.4, 11.8, 17.4, 4.3, 6.9 ])
    (12.1, 12.1)
    
    >>> closest2([ 4.3, 6.9 ])
    (4.3, 6.9)
    
    '''        
    L1 = L.copy()
    L1 = sorted(L1)
    dist = abs(L1[0]-L1[1])
    closest = (L1[0],L1[1])
    for k in range(len(L1)-1):
        if(abs(L1[k]-L1[k+1])<dist):
            closest = (L1[k],L1[k+1])
            dist = abs(L1[k]-L1[k+1])
    return closest


'''
First way takes N^2 executions
Second way takes N executions
'''
    
if __name__ == "__main__":
    L1 = []
    L2 = []
    L3 = []
    for i in range(100):
        L1.append(random.uniform(0.0, 1000.0))
    for j in range(1000):
        L2.append(random.uniform(0.0, 1000.0))
    for j in range(10000):
        L3.append(random.uniform(0.0, 1000.0))
    
    start = time.time()
    (x,y) = closest1(L1)
    end = time.time()
    print("List of 100 (closest1):", end - start)
    
    start = time.time()
    (x,y) = closest2(L1)
    end = time.time()
    print("List of 100 (closest2):", end - start)
    
    
    
    start = time.time()
    (x,y) = closest1(L2)
    end = time.time()
    print("List of 1000 (closest1):", end - start)
    
    start = time.time()
    (x,y) = closest2(L2)
    end = time.time()
    print("List of 1000 (closest2):", end - start)   
    
    
    
    start = time.time()
    (x,y) = closest1(L3)
    end = time.time()
    print("List of 10000 (closest1):", end - start)
    
    start = time.time()
    (x,y) = closest2(L3)
    end = time.time()
    print("List of 10000 (closest2):", end - start)
    
    
    
    
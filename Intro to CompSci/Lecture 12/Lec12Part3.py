def find_min(L1):                       
    totalMin = L1[0][0]
    for i in range(len(L1)):
        listMin = min(L1[i])
        totalMin = min(listMin,totalMin)
    return totalMin

if __name__ == "__main__":
    v = [ [ 11,12,3], [6, 8, 4], [ 17, 2, 18, 14] ]
    print("Min of list v: {}".format(find_min(v)) )
    u = [ [ 'car', 'tailor', 'ball' ], ['dress'], ['can', 'cheese', 'ring' ], \
              [ 'rain', 'snow', 'sun' ] ]
    print("Min of list u: {}".format(find_min(u)) )
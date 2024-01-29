def fib(n):
    i = 0
    j=1
    n1 = 0
    n2 = 1
    if(n==0):
        return 0
    while i<n-1:
        j = n1 + n2
        n3 = n2
        n1 = n3
        n2 = j
        i = i +1
    return j

if __name__ == "__main__":
    print( fib(0) )
    print( fib(1) )
    print( fib(2) )
    print( fib(5) )
    print( fib(10))

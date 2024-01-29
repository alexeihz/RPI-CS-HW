def add(m,n):
    if n == 0:
        return m
    else:
        return add(m,n-1) + 1
    
def mult(m,n):
    if n == 0 or m==0:
        return 0   
    return mult(m,n-1) + m

def power(m,n):
    if n == 0:
        return 1
    return power(m,n-1)*m
    
if __name__ == "__main__":
    print(mult(3,5))
    print(power(6,4))
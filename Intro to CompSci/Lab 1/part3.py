base10size= input()
print("Disk size in GB => "+ base10size)
base2size= (int(base10size)*10**9)/2**30
lost_size = int(base10size) - int(base2size)
#print(lost_size)
print(base10size , "GB in base 10 is actually" , int(base2size) , "GB in base 2," , int(lost_size) , "GB less than advertised.")
print('Input:  ' + "*"*int(base10size))
print('Actual: ' + "*"*int(base2size))
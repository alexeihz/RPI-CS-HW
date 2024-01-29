num = int(input("Enter a value (0 to end): "))
print(num)
listo = []
add = 0
while(num!=0):
    listo.append(num)
    add+=num
    num = int(input("Enter a value (0 to end): "))
    print(num)
    

listo2 = sorted(listo)
minimum = listo2[0]
maximum = listo2[len(listo2)-1]
avg = round(add/len(listo2),1)
print("Min:", minimum)
print("Max:", maximum)
print("Avg:", avg)
num1 = float (input("Enter the first number: "))

print(num1)
num2 = float (input("Enter the second number: "))
num2 = float(num2)
print(num2)

if num1 > 10 and num2 > 10:
    print("Both are above 10.")
    
elif num1 < 10 and num2 < 10:
    print("Both are below 10.")
    
avg = (num1 + num2)/2
avg = round(float(avg),2)
#print("Average is {0:.2f}".format(avg))
print("Average is", avg)
values = [ 14, 10, 8, 19, 7, 13 ]
num1 = int(input("Enter a value: "))
print(num1)
values.append(num1)
num2 = int(input("Enter another value: "))
print(num2)
values.insert(2,num2)
print(values[3], values[-1])
values2 = sorted(values)
print("Difference:", values2[len(values2)-1]-values2[0])

print("Average: {0:.1f}".format( sum(values) / len(values) ))
print("Median:",(values2[int(len(values2)/2)-1] + values2[int(len(values2)/2)])/2 )
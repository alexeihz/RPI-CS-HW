def convert2fahren(celsius):
    fahrenheit = celsius*(9/5)+32
    return fahrenheit
a = convert2fahren(0)
b = convert2fahren(32)
c = convert2fahren(100)
print("0 -> " + str(a))
print("32 -> " + str(b))
print("100 -> " + str(c))

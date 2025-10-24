# First = input("First Value: ")
# Second = input("Second Value: ")
# Total = int(First) + int(Second)
# print("%d" % Total)
weight = int(input("Weight: "))
Unit = input("(K)g or (L)lbs: ")
dim = Unit.lower()
if dim == "k": #unit is in kg
    print("Weight in Kg:",weight)
elif dim == "l":
    KG = weight / 2.2
    print(f"Weight in Kg: {KG: .2f}")
else:
    print("input K or L only")

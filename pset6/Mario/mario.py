from cs50 import get_int

while True:
    x = get_int("Enter a number between 1 and 8 \n")
    if x <= 0 or x >= 9:
        x = get_int("Enter a number between 1 and 8 \n")
    else:
        break;

for l in range(x):
    print (" " * (x-l-1), end = "")
    print ("#" * (l + 1), end = "")
    print ("  ", end = "")
    print ("#" * (l + 1))
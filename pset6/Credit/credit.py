from cs50 import get_int

creditNumber = get_int("enter a credit card number\n")
loopDouble = [100]
loopSingle = [10]
sum = 0
holder = 0
holderS = 0
divider = 0
dividerS = 0

while True:
    if loopDouble[len(loopDouble) - 1] < creditNumber * 10:
        loopDouble.append(loopDouble[len(loopDouble) - 1] * 100)
    else:
        break

while True:
    if loopSingle[len(loopSingle) - 1] < creditNumber:
        loopSingle.append(loopSingle[len(loopSingle) - 1] * 100)
    else:
        break

for i in loopDouble:
    holder = creditNumber % i
    divider = i // 10
    holder = int(holder) // int(divider)
    holder *= 2
    holder = int(holder)

    if holder > 9:
        holder %= 10
        holder += 1

    sum += holder
    holder = 0

for i in loopSingle:
    holderS = creditNumber % i
    dividerS = i // 10
    holderS = int(holderS) // int(dividerS)
    holderS = int(holderS)
    sum += holderS

#if creditNumber // 10000000000000 == 34 or creditNumber // 10000000000000 == 37:
  #  sum += 3

if sum % 10 == 0 and (creditNumber // 10000000000000 == 34 or creditNumber // 10000000000000 == 37 or creditNumber // 100000000000000 == 51 or creditNumber // 100000000000000 == 52 or creditNumber // 100000000000000 == 53 or creditNumber // 100000000000000 == 54 or creditNumber // 100000000000000 == 55 or creditNumber // 1000000000000 == 4 or creditNumber // 1000000000000000 == 4):
    if creditNumber // 10000000000000 == 34 or creditNumber // 10000000000000 == 37:
        print("AMEX")
    if creditNumber // 100000000000000 == 51 or creditNumber // 100000000000000 == 52 or creditNumber // 100000000000000 == 53 or creditNumber // 100000000000000 == 54 or creditNumber // 100000000000000 == 55:
        print("MASTERCARD")
    if creditNumber // 1000000000000 == 4 or creditNumber // 1000000000000000 == 4:
        print("VISA")
else:
    print("INVALID")
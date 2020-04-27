from csv import reader, DictReader
from sys import argv

current = 0
currentHigh = 0
i = 0
dna = []

if len(argv) < 3:
    print("wrong Usage")
    exit(1)

with open(argv[1]) as people:
    peopleFile = reader(people)
    for row in peopleFile:
        dna.append(row)

with open(argv[2]) as DNA:
    DNAfile = reader(DNA)
    for row in DNAfile:
        strand = row


highArray = []

for x in range(len(dna[0])-1):
    currentHigh = 0
    current = 0
    i = 0
    while i < len(strand[0]):
        if strand[0][i:i+len(dna[0][x+1])] == dna[0][x+1]:
            current += 1
            i += len(dna[0][x+1])
        else:
            i += 1
            if(current > currentHigh):
                currentHigh = current
            current = 0

    highArray.append(currentHigh)

isMatch = True
dnaCarrier = "No Match"

for x in range(len(dna)-1):
    isMatch = True
    for y in range(len(highArray)):
        if isMatch:
            if(highArray[y] == int(dna[x+1][y+1])):
                isMatch = True
            else:
                isMatch = False

    if isMatch:
        dnaCarrier = dna[x+1][0]

print(dnaCarrier)

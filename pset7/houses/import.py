import csv
from sys import argv, exit
from cs50 import SQL

if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit(1)
firstName = midName = lastName = house = birth = ""

db = SQL("sqlite:///students.db")

# Open CSV file
with open(argv[1]) as file:
    # Create DictReader
    reader = csv.DictReader(file)
    for row in reader:
        name = row["name"].split()
        if len(name) == 2:
            firstName = name[0]
            midName = None
            lastName = name[1]
        elif len(name) == 3:
            firstName = name[0]
            midName = name[1]
            lastName = name[2]
        house = row["house"]
        birth = row["birth"]
        rows = db.execute("INSERT INTO students ('first', 'middle', 'last', 'house', 'birth') VALUES (?, ?, ?, ?, ?)",
                   firstName, midName, lastName, house, int(birth))
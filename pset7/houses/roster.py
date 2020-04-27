import csv
from sys import argv, exit
from cs50 import SQL

if len(argv) != 2:
    print("Usage: python roster.py house_name")
    exit(1)

db = SQL("sqlite:///students.db")

rows = db.execute("SELECT * FROM students WHERE house = ? order by last, first", argv[1])
for row in rows:
    if row["middle"] == None:
        print(f'{row["first"]} {row["last"]}, born {row["birth"]}')
    else:
        print(f'{row["first"]} {row["middle"]} {row["last"]}, born {row["birth"]}')

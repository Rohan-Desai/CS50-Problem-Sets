from cs50 import get_string

text = get_string("Enter in text: ")
sentances = 0
letters = 0
words = 0
for i in text:
    if i == " ":
        words += 1
    elif i == "." or i == "?" or i == "!":
        sentances += 1
    elif i.isalpha():
        letters += 1

words += 1
L = (100 * letters) / words
S = (100 * sentances) / words
index = 0.0588 * L - 0.296 * S - 15.8
index = round(index)

if index > 0 and index < 16:
    print(f"Grade, {index}")
elif index > 15 :
    print("Grade 16+")
else:
    print("Before Grade 1")
# 0.0588 * L - 0.296 * S - 15.8

text = input("Text: ")


def count(text, l):
    c = 0
    for i in l:
        c += text.count(i)
    return c


sents, letters, words = 0, 0, 0

sents = count(text, ['.', '?', '!'])

words = text.count(' ') + 1

puncs = count(text, ['"', ',', ';', ':', '/', "\\", "'", '(', ')'])

letters = len(text) - (words + sents + puncs) + 1

L = (letters / words) * 100
S = (sents / words) * 100

grade = round(0.0588 * L - 0.296 * S - 15.8)

if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")

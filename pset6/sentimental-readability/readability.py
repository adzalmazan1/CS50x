import string

text = input("Text: ")

# The sum() function accumulates 1 for every character in 'text' that is found in ...
sentences = sum(1 for ch in text if ch in ["!", "?", "."])

punc = sum(1 for ch in text if ch in string.punctuation)  # punctuation counter

letters = len(text.replace(" ", "")) - punc
words = sum(1 for ch in text if ch in [" "]) + 1

L = (letters / words) * 100
S = (sentences / words) * 100

index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")
elif index in range(1, 17):
    print(f"Grade: {index}")
else:
    print("Grade 16+")

# Note: word count is correct

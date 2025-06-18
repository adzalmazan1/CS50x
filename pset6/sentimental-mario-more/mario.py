from cs50 import get_int

while True:
    height = get_int("Height: ")

    # If height is in range of numbers 1-8
    if height in range(1, 9):
        break
    else:
        print("Invalid input.")

i = height - 1  # SPACES
j = 1  # HASHES

# Use height value here
for _ in range(height):
    # Left side
    print(" " * i, end='')
    print("#" * j, end='')

    print(" " * 2, end='')

    # Right side
    print("#" * j)

    # Value updates
    i -= 1
    j += 1

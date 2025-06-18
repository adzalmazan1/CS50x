from cs50 import get_string


def valid_checksum(number):
    sum = 0
    tmp = number

    # Logic from previous implementation
    while True:
        if tmp <= 0:
            break

        at_twos = ((tmp % 100) // 10) * 2
        at_ones = (tmp % 100) % 10

        if (at_twos >= 10):
            sum += at_twos // 10
            sum += at_twos % 10
        else:
            sum += at_twos

        sum += at_ones
        tmp //= 100

    if sum % 10 == 0:
        return True

    print("INVALID")
    return False


# Prompt for input
number = get_string("Number: ")

# Calculate checksum
cardnum = int(number)

if valid_checksum(cardnum):
    length = len(number)
    first_two = int(number[:2])
    first = int(number[:1])

    if (first_two in [34, 37] and length == 15):
        print("AMEX")
    elif (first_two in range(51, 56) and length == 16):
        print("MASTERCARD")
    elif (first == 4 and length in [13, 16]):
        print("VISA")
    else:
        print("INVALID")

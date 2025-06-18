#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int checkLength(long number);
bool checkSum(long number);
bool validLength(int length);

int main()
{
    // prompt for input
    // calculate checksum
    // check for card length and starting digits
    long cardNumber = get_long("Number: ");
    int length = checkLength(cardNumber);

    // printf("Checksum: %b\n", checkSum(cardNumber));

    if (checkSum(cardNumber) && validLength(length))
    {
        // printf("Length: %d\n", length);

        long temp = cardNumber;
        for (int i = 0; i < length - 2; i++)
        {
            temp /= 10;
        }

        if ((temp == 34 || temp == 37) && length == 15)
        {
            printf("AMEX\n");
        }
        else if ((temp > 50 && temp < 56) && length == 16)
        {
            printf("MASTERCARD\n");
        }
        else if ((temp > 39 && temp < 50) && (length == 13 || length == 16))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

int checkLength(long number)
{
    int length = 0;
    long quotient = number;

    while (quotient != 0)
    {
        quotient /= 10;
        length++;
    }

    return length;
}

bool checkSum(long number)
{
    long tempNumber = number;
    int everyOtherSum = 0, untouched = 0, eosChecker, total;

    while (tempNumber != 0)
    {
        untouched += (tempNumber % 100) % 10;

        printf("untouched: %d\n", untouched);

        eosChecker = (tempNumber % 100 / 10) * 2;

        printf("eos: %d\n", eosChecker);
        if (eosChecker >= 10)
        {
            everyOtherSum += eosChecker % 10;
            everyOtherSum += eosChecker / 10;
        }
        else
        {
            everyOtherSum += eosChecker;
        }

        tempNumber /= 100;
    }

    total = everyOtherSum + untouched;

    printf("Total: %d\n", total);

    if (total % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool validLength(int length)
{
    if (length == 13 || length == 15 || length == 16)
    {
        return true;
    }
    return false;
}

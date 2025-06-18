#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void substitute(string word, string key);
bool validKey(string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int length = strlen(argv[1]);

    if (length < 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string keyArray = argv[1];
    if (!validKey(keyArray))
    {
        return 1;
    }

    string plainText = get_string("plaintext: ");
    printf("ciphertext: ");
    substitute(plainText, keyArray);
}

void substitute(string word, string key)
{
    int length = strlen(word);

    for (int i = 0; i < length; i++)
    {
        if (isupper(word[i]))
        {
            printf("%c", toupper(key[word[i] - 65]));
        }
        else if (islower(word[i]))
        {
            printf("%c", tolower(key[word[i] - 97]));
        }
        else
        {
            printf("%c", word[i]);
        }
    }
    printf("\n");
}

bool validKey(string key)
{
    int length = strlen(key);

    // key can only contain alpha chars
    for (int i = 0; i < length; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return false;
        }
    }
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (tolower(key[i]) == tolower(key[j]))
            {
                printf("Key must not contain repeated characters.\n");
                return false;
            }
        }
    }
    return true;
}

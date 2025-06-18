#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// note of alphabet sequence
int score[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int computeScore(string word);

int main()
{
    // using ASCII
    string p1Word = get_string("Player 1: ");
    string p2Word = get_string("Player 2: ");

    int p1Score = computeScore(p1Word);
    int p2Score = computeScore(p2Word);

    if (p1Score > p2Score)
    {
        printf("Player 1 wins!\n");
    }
    else if (p2Score > p1Score)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie\n");
    }

    // print the result
}

int computeScore(string word)
{
    int total = 0, wordLength = strlen(word);

    for (int i = 0; i < wordLength; i++)
    {
        if (islower(word[i]))
        {
            total += score[word[i] - 97];
        }
        else if (isupper(word[i]))
        {
            total += score[word[i] - 65];
        }
        else
        {
            total += 0;
        }
    }

    // printf("%d\n", wordLength);
    return total;
}

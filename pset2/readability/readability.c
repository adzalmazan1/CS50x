#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int letterCount(string word, int length);
int wordCount(string word, int length);
int sentenceCount(string word, int length);

int main()
{
    string word = get_string("Text: ");
    int length = strlen(word);

    int letters = letterCount(word, length);
    int words = wordCount(word, length);
    int sentences = sentenceCount(word, length);

    // order of operation is OK
    double L = (float) letters / (float) words * 100;
    double S = (float) sentences / (float) words * 100;

    // round index to nearest whole number as well
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    printf("%d\n", index);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }
}

int letterCount(string word, int length)
{
    int letterCount = 0;
    for (int i = 0; i < length; i++)
    {
        if (isalpha(word[i]))
        {
            letterCount++;
        }
    }
    printf("%d\n", letterCount);
    return letterCount;
}

int wordCount(string word, int length)
{
    int wordCount = 1;
    for (int i = 0; i < length; i++)
    {
        if (isspace(word[i]))
        {
            wordCount++;
        }
    }
    printf("%d\n", wordCount);
    return wordCount;
}

int sentenceCount(string word, int length)
{
    int sentenceCount = 0;
    for (int i = 0; i < length; i++)
    {
        if (word[i] == '!' || word[i] == '?' || word[i] == '.')
        {
            sentenceCount++;
        }
    }
    printf("%d\n", sentenceCount);
    return sentenceCount;
}

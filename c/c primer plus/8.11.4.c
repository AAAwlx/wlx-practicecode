#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

int main(void)
{
    float count;
    bool inword = false;
    int ch, words, letter;
    words = letter = 0;

    printf("Please enter some words (EOF to quit):\n");
    while ((ch = getchar()) != EOF)
    {
        if (ispunct(ch))
        {
            continue;
        }
        if (isalpha(ch))
        {
            letter++;
        }
        if (!isspace(ch) && !inword)
        {
            inword = true;
            words++;
        }
        if (isspace(ch) && inword)
        {
            inword = false;
        }
    }
    count = (float)letter / words;
    printf("Total words: %d.\n", words);
    printf("Total letters: %d.\n", letter);
    printf("Average letters of words: %g.\n", count);

    return 0;
}

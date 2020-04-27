#include <cs50.h>
#include <stdio.h>
#include <string.h>
int main(void)
{
    int spaces = 0;
    int letters = 0;
    int sentances = 0;
    string text = get_string("Text: ");
    for (int i = 0, n = strlen(text); i < n; i++)
    {

        if (text[i] == ' ')
        {
            spaces++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentances++;
        }
        else
        {
            letters++;
        }

    }
    int words = spaces + 1;
    long L = (100 * letters) / words;
    long S = (100 * sentances) / words;
    long index = 0.0588 * L - 0.296 * S - 15.8;
    if (index - .5 > (int)index)
    {
        index = (int)(index + 1);
    }
    else
    {
        index = (int)index;
    }
    if (index < 16 && index > 0)
    {
        printf("Grade %i\n", (int)index);
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }
}
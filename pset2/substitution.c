#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage: %s Key\n", argv[0]);
        return 1;
    }
    int strl = strlen(argv[1]);

    if (strl != 26)
    {
        printf("Usage: %s Key\n", argv[0]);
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: %s Key\n", argv[0]);
            return 1;
        }
    }

    int counter = 0;
    int cnt = 0;
    for (int i = 0; i < strl; i++)
    {
        for (int j = 0; argv[1][j] != '\0'; j++)
        {
            cnt++;
            if (argv[1][j] == argv[1][i])
            {
                counter++;
            }
        }
    }

    if (counter != strl)
    {
        printf("Usage: %s Key\n", argv[0]);
        return 1;
    }
    int keyIndex = 0;

    string plain = get_string("plaintext: ");
    int w = strlen(plain);
    char cipher[w];

    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        if (plain[i] >= 97 && plain[i] <= 122)
        {
            keyIndex = plain[i] - 97;

            if (argv[1][keyIndex] >= 97 && argv[1][keyIndex] <= 122)
            {
                cipher[i] = argv[1][keyIndex];
            }
            else
            {
                cipher[i] = argv[1][keyIndex] + 32;
            }
        }
        if (plain[i] >= 65 && plain[i] <= 90)
        {
            keyIndex = plain[i] - 65;
            cipher[i]  = argv[1][keyIndex];

            if (argv[1][keyIndex] >= 97 && argv[1][keyIndex] <= 122)
            {
                cipher[i] = argv[1][keyIndex] - 32;
            }
            else
            {
                cipher[i] = argv[1][keyIndex];
            }
        }
        if (!(plain[i] >= 65 && plain[i] <= 90) && !(plain[i] >= 97 && plain[i] <= 122))
        {
            cipher[i]  = plain[i];
        }
    }
    cipher[w] = '\0';
    printf("ciphertext: %s\n", cipher);
    return 0;
}
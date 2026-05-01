#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //checks input
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    int len = strlen(argv[1]);
    //checks key length
    if (len != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    //checks for non-alphabetical characters
    char chars[26];
    //checks for repeated characters(case insensitive)
    //for each char in key, store in array
    //for loops goes through key and compares to array, if match +1 to counter, if counter > 1 return 1
    for (int i = 0; i < 26; i++)
    {
        int match = 0;
        if (isdigit(argv[1][i]))
        {
            printf("Key must only contain alphabetical characters.");
            return 1;
        }
        else
        {
            chars[i] = argv[1][i];
        }
        for (int j = 0; j < 26; j++)
        {
            if (argv[1][i] == chars[j])
            {
                match++;
            }
        }
        if (match > 1)
        {
            printf("Key must not contain repreated characters.\n");
            return 1;
        }
    }

    string text = get_string("plaintext: ");
    printf("ciphertext: ");

    string alpha = "abcdefghijklmnopqrstuvwxyz";
    int pos[strlen(text)];

    //for each letter in text go through alpha
    //if match store position in pos array
    //converts the plaintext to position in alphabet
    int l = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            char letter;
            if (isalpha(text[l]))
            {
                if (isupper(text[l]))
                {
                    letter = toupper(alpha[j]);
                }
                else
                {
                    letter = alpha[j];
                }
                if (letter == text[l])
                {
                    pos[l] = j;
                    l++;
                }
            }
            else //skips over it if non alphabetical
            {
                l++;
            }
        }
    }

    //outputs encrypted message
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]) && isupper(text[i]))
        {
            printf("%c", toupper(argv[1][pos[i]]));
        }
        else if (isalpha(text[i]) && islower(text[i]))
        {
            printf("%c", tolower(argv[1][pos[i]]));
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
    return 0;
}

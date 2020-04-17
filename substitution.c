#include <cs50.h>
#include <stdio.h>
#include <string.h>

char tranformUpper(char ch)
{
    if (ch >= 'a' && ch <= 'z')
    {
        ch = ch - 32;
    }
    return ch;
}
char tranformLower(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
    {
        ch = ch + 32;
    }
    return ch;
}

int getPos(string long1, char char1)
{
    for (int i = 0, n = strlen(long1); i < n; i++)
    {
        if (long1[i] == char1)
        {
            return i;
        }
    }
    return -1;
}

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    if (strlen(key) != 26)
    {
        printf("key must contain 26 characters.\n");
        return 1;
    }

    bool isError = false;
    for (int i = 0; i < strlen(key); i++)
    {
        if (!(key[i] >= 'A' && key[i] <= 'Z') && !(key[i] >= 'a' && key[i] <= 'z'))
        {
            printf("%c", key[i]);
            printf("key must contain alphabetic characters.\n");
            isError = true;
            break;
        }
        for (int j = i + 1; j < strlen(key); j++)
        {
            if (key[i] == key[j])
            {
                printf("key must not contain repeated characters.\n");
                isError = true;
                break;
            }
        }
    }
    if (isError == true)
    {
        return 1;
    }

    string plain = get_string("plaintext: ");
    string origin = "abcdefghijklmnopqrstuvwxyz";

    printf("ciphertext: ");
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        bool isUpper = true;
        char ch = plain[i];
        if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch + 32;
        }
        else if (ch >= 'a' && ch <= 'z')
        {
            isUpper = false;
        }

        int pos = getPos(origin, ch);

        if (pos == -1)
        {
            printf("%c", ch);
        }
        else
        {
            char res;
            if (isUpper == true)
            {
                res = tranformUpper(key[pos]);
            }
            else
            {
                res = tranformLower(key[pos]);
            }
            printf("%c", res);
        }
    }
    printf("\n");
    return 0;
}

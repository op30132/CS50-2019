#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string s = get_string("text: ");

    float letterNum = 0;
    float wordNum = 1;
    float sentenceNum = 0;

    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        if (s[i] == ' ')
        {
            wordNum = wordNum + 1;
        }
        else if ((s[i] == '.') || (s[i] == '!'))
        {
            sentenceNum = sentenceNum + 1;
        }
        else if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_') || (s[i] >= 'a' && s[i] <= 'z'))
        {
            letterNum = letterNum + 1;
        }
    }
    float hun = wordNum / 100.0f;

    float L = letterNum / hun;
    float S = sentenceNum / hun;
    float pre = 0.0588 * L - 0.296 * S - 15.8;
    int index = round(pre);

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

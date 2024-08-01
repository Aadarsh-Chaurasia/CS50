#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string lower(string str);
int get_val(string str, string code[]);

int main(void)
{
    // Getting input and lowercasing all characters !
    string player1 = lower(get_string("Player 1: "));
    string player2 = lower(get_string("Player 2: "));
    // printf("%s\n%s", player1, player2);

    // char l1[10], l2[2], l3[4], l4[5], l5[1], l8[2], l10[2];
    string code[] = {"aeilnorstu", "dg", "bcmp", "fhvwy", "k", "", "", "jx", "", "qz"};

    int val1 = get_val(player1, code);
    int val2 = get_val(player2, code);

    // Comparing players
    if (val1 > val2)
    {
        printf("Player 1 wins!");
    }
    else if (val1 < val2)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
}

string lower(string str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

int get_val(string str, string code[])
{
    int val = 0;
    int matched = 0;

    // selecting a letter from str and matching it with all letters of code.
    for (int i = 0; str[i]; i++)
    {
        matched = 0;
        // selecting sections of 'code'
        for (int j = 0; code[j]; j++)
        {
            if (matched == 1)
            {
                // if letter is matched already, go directly to first loop and check next letter.
                break;
            }
            else
            {
                // looping in chars of selected section of 'code'
                for (int k = 0; code[j][k]; k++)
                {
                    char c = code[j][k];
                    if (str[i] == code[j][k])
                    {
                        matched = 1;
                        val += j + 1;
                        break;
                    }
                }
            }
        }
    }
    return val;
}

// Coleman-Liau index: index = 0.0588 * L - 0.296 * S - 15.8
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count(string text, char c);

int main(void)
{
    // ask of text
    string text = get_string("Text: ");

    // count no. of sentence.
    int sent;
    int stop = count(text, '.');
    int excl = count(text, '!');
    int ques = count(text, '?');
    sent = stop + excl + ques;

    // count no. of words
    float words = (float) count(text, ' ') + 1;

    // count no of letters
    char punctuations[] = ",;:/\\\"'()";
    int punc = 0;

    // Counting punctuations so that they are not counted as letters.
    for (int i = 0; punctuations[i]; i++)
    {
        punc += count(text, punctuations[i]);
    }

    float letters = (float) (strlen(text) - (words + sent + punc) + 1);

    // Finding L and S
    float L = (letters / words) * 100;
    float S = (sent / words) * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    int grade = round(index);

    // printing grade
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

int count(string text, char c)
{
    int count = 0;
    for (int i = 0; text[i]; i++)
    {
        if (text[i] == c)
        {
            count++;
        }
    }
    return count;
}

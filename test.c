#include <stdio.h>
#include <cs50.h>
#include <ctype.h>


string lower(string str);
void int_to_string(int c);
int print_from_file(char *file_name);


int main(void){
    print_from_file("text.txt");
}

string lower(string str)
{
    for (int i = 0; str[i]; i++) // last value of string is NUL so str[i] becomes false here and loop is terminat
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

void int_to_string(int c)
{
    // this will add 2 as 002 in string named buffer.
    printf("%03d ", c);
    char buffer[4];
    for(int i=0; i<2; i++)
    {
        sprintf(buffer, "%03d", i); // null is added automatically at the end so we coockin' !
    }
}

int print_from_file(char *file_name)
{
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        // error in loading file.
        return 1;
    }

    // Read each word in file
    char wordlist[10];
    while (fscanf(file, "%s", wordlist) != EOF)
    {
        printf("%s", wordlist);
    }
    fclose(file);
    return 0;
}

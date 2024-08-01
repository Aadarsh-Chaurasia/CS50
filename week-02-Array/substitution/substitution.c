#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string lower(string str);
int is_upper(char c);
bool is_valid(string key);
char encrypt(char c, string key);

int main(int argc, string argv[])
{
    // printf("%s", argv[0]);
    // printf("%s", argv[1]);
    // printf("%i", argc);

    // Getting the key
    string key;
    if (argc == 2)
    {
        if (is_valid(argv[1]))
        {
            key = argv[1];
            // printf("Key recieved !");
        }
        else
        {
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key");
        return 1;
    }

    // Getting the Plain text
    string plntxt = get_string("plaintext:  ");

    // Encrypting each letter
    // char encrypted[strlen(plntxt)-1];
    for (int i = 0; plntxt[i]; i++)
    {
        plntxt[i] = encrypt(plntxt[i], key);
        // printf("%c", encrypted[i]);
    }

    // printing encypted key
    printf("ciphertext: %s\n", plntxt);
    return 0;
}

string lower(string str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

char encrypt(char c, string key)
{
    int keyindex = 65;
    // check lower/upper
    int upper = is_upper(c);
    if (upper == -1)
    {
        keyindex += 32;
    }
    else if (upper == 0)
    {
        return c;
    }

    // sustitute letters
    int i = (int) c - keyindex;
    char e = toupper(key[i]);

    // turn into lower/upper
    if (upper == -1)
    {
        return tolower(e);
    }
    else
    {
        return e;
    }
}

int is_upper(char c)
{
    // upper 1, lower -1, neither 0
    int upper;
    if (c >= 'A' && c <= 'Z')
    {
        upper = 1;
    }
    else if (c >= 'a' && c <= 'z')
    {
        upper = -1;
    }
    else
    {
        upper = 0;
    }
    return upper;
}

bool is_valid(string key)
{
    // Conditions : must be 26 must bs alphabatic
    if (strlen(key) == 26)
    {
        for (int i = 0; key[i]; i++)
        {
            int temp = is_upper(key[i]);

            // Checking non alphabatic characters
            if (temp == 0)
            {
                printf("Key is invalid !");
                return false;
            }

            // Checking Repitition
            else
            {
                for (int j = 0; key[j]; j++)
                {
                    if (key[i] == key[j] && i != j)
                    {
                        printf("Key have repition");
                        return false;
                    }
                }
            }
        }
        return true;
    }
    else
    {
        printf("Key must contain 26 characters.");
        return false;
    }
}

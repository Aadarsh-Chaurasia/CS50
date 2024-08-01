#include <stdio.h>


int main (void)
{
    char *s = "HI!";
    printf("%p\n", s);
    // printf("%p", *s);
    printf("%p\n", &s);
    // printf("%p", *(s+1));
    printf("%p\n", &s[0]);
    printf("%p\n", &s[1]);

}

#include <stdio.h>
#include <cs50.h>

int takeHeight(){
    int height = get_int("Height: ");
    int stop = 0;
    while(stop==0)
    {
        if(height>0 && height<9){
            stop=1;
        }
        else{
            int h = get_int("Height: ");
            height = h;
        }
    }
    return height;
}

void printHash(int i)
{
    for(int k=i; k>0; k--)
        {
            printf("#");
        }
}

void printPattern(int val)
{
    for(int i=1; i<=val; i++)
    {
        for(int j=val-i; j>0; j--)
        {
            printf(" ");
        }
        printHash(i);
        printf("  ");
        printHash(i);
        printf("\n");
    }
}

int main(void){
    int height = takeHeight();
    printPattern(height);
}

#include <stdio.h>
#include <cs50.h>

int main(void){
    int change;
    do{
        change = get_int("Change owed: ");
        // printf("%i", change);
    }
    while(change<0);

    int coins=0;
    while(change>0)
    {
        if(change>=25)
        {
            coins += change/25;
            change = change%25;
        }
        else if(change<=25 && change>=10)
        {
            coins += change/10;
            change = change%10;
        }
        else if(change<=10 && change>=5)
        {
            coins += change/5;
            change = change%5;
        }
        else
        {
            coins += change;
            change=0;
        }
    }
    printf("%i\n", coins);

}

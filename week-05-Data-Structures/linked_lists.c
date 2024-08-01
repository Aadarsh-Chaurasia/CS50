#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}node;

void print_list(node *list);
int add_front(node **list, int num);
int add_back(node **list, int num);
int iterating_in_list(node **list);

int main (int argc, char *argv[])
{
    node *list = NULL;
    // list->next = NULL;

    // Adding element from front
    int num = 1;
    add_back(&list, num);
    add_front(&list, 2);
    add_back(&list, 3);

    print_list(list);

}


void print_list(node *list)
{
    // Print list
    // Don't use ptr->next != NULL as condition this will not print last digit as address in it is null.
    for(node *ptr = list; ptr != NULL; ptr = ptr->next)
    {
        printf("%i", ptr->number);
    }
}

int add_front(node **list, int num)
{
    node *new = malloc(sizeof(node));
    if (new == NULL)
    {
        return 1;
    }
    new->number = num;

    // adding in front by setting address in list as next for new node and new node as list
    new->next = *list;
    *list = new;
    return 0;
}

int add_back(node **list, int num)
{
    node *new = malloc(sizeof(node));
    if (new == NULL)
    {
        return 1;
    }

    new->number = num;

    // Checking if list is empty
    if (*list == NULL)
    {
        *list = new;
    }
    else
    {
        for(node *ptr = *list; ptr != NULL; ptr = ptr->next)
        {
            if (ptr->next == NULL)
            {
                ptr->next = new;
                // Since the last pointer has been updated and it does not point to null yet so there is no node with null yet so it'll go in infinite loop, to stop this we break here.
                break;
            }
        }
    }
    // Pointing the last node to NULL
    new->next = NULL;

    return 0;
}

int iterating_in_list(node **list)
{
    // TODO
    node *temp = NULL;
    node *cursor = NULL;
    cursor = *list[i];
    while (cursor != NULL)
    {
        tmp = cursor;
        cursor = cursor->next;
        // free(tmp); printf("in new node hehe. ");// Do whatever you want to do.
        }
    }
    return 0;
}

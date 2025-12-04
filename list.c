#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int init_list(t_list *list, int max_nb)
{
    list->data = malloc(sizeof(int) * max_nb);
    if (!list->data)
    {
        fprintf(stderr, "Error creating list\n");
        return 1;
    }

    list->index = 0;
    list->max_nb = max_nb;

    return 0;
}

void    free_list(t_list *list)
{
    free(list->data);
}

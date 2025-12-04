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

    if (pthread_mutex_init(&list->mutex, NULL) != 0)
    {
        fprintf(stderr, "Error initializing mutex\n");
        free(list->data);
        return 1;
    }

    return 0;
}

void    free_list(t_list *list)
{
    free(list->data);
    pthread_mutex_destroy(&list->mutex);
}

void    print_list(t_list *list)
{
    for (int i = 0; i < list->index; i++)
        printf("[%d] = %d\n", i, list->data[i]);
}

int insert_list(t_list *list, int value)
{
    pthread_mutex_lock(&list->mutex);

    if (list->index >= list->max_nb)
    {
        pthread_mutex_unlock(&list->mutex);
        return 1;
    }

    list->data[list->index++] = value;
    pthread_mutex_unlock(&list->mutex);

    return 0;
}
#ifndef LIST_H
#define LIST_H

#include <pthread.h>

typedef struct list {
    int *data;
    int index;
    int max_nb;
    pthread_mutex_t mutex;
} t_list;

int     init_list(t_list *list, int max_nb);
void    free_list(t_list *list);
void    print_list(t_list *list);
int     insert_list(t_list *list, int value);
void    sort_list(t_list *list);

#endif
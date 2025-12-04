#ifndef LIST_H
#define LIST_H

typedef struct list {
    int *data;
    int index;
    int max_nb;
} t_list;

int     init_list(t_list *list, int max_nb);
void    free_list(t_list *list);

#endif
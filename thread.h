#ifndef THREAD_H
#define THREAD_H

#include "list.h"

typedef struct thread {
    int     max_nb;
    t_list *positive;
    t_list *negative;
} t_thread;

void    *start_threads(void *arg);
int     run_threads(int nb_thread, int numbers, t_list *positive, t_list *negative);

#endif
#ifndef THREAD_H
#define THREAD_H

#include "list.h"

typedef struct thread {
    int     max_nb;
    int     id;
    t_list *positive;
    t_list *negative;
} t_thread;

void *start_threads(void *arg);

#endif
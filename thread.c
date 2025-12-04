#include "thread.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>

void *start_threads(void *arg)
{
    t_thread *args = (t_thread *)arg;

    unsigned int seed = time(NULL) ^ pthread_self();

    for (int i = 0; i < args->max_nb; i++)
    {
        int num = (int)rand_r(&seed) - (RAND_MAX / 2);

        int ret;
        if (num >= 0)
            ret = insert_list(args->positive, num);
        else
            ret = insert_list(args->negative, num);

        if (ret == 0)
        {
            printf("Thread %d inserted %d\n", args->id, num);
        }
        else
        {
            printf("Thread %d: failed to insert %d (list full)\n", args->id, num);
        }
    }

    return NULL;
}
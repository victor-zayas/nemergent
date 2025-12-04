#include "thread.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>

void *start_threads(void *arg)
{
    t_thread *args = (t_thread *)arg;

    unsigned int seed = time(NULL) ^ (unsigned int)pthread_self();

    for (int i = 0; i < args->max_nb; i++)
    {
        int num = (int)rand_r(&seed) - (RAND_MAX / 2);

        if (num >= 0)
             insert_list(args->positive, num);
        else
            insert_list(args->negative, num);
    }

    return NULL;
}

int run_threads(int nb_thread, int numbers, t_list *positive, t_list *negative)
{
    pthread_t *threads = malloc(sizeof(pthread_t) * nb_thread);
    if (!threads)
    {
        fprintf(stderr, "Error on malloc threads\n");
        return 1;
    }

    if (init_list(positive, nb_thread * numbers) != 0 || init_list(negative, nb_thread * numbers) != 0)
    {
        fprintf(stderr, "Error initializing lists\n");
        free(threads);
        return 1;
    }

     t_thread args = {numbers, positive, negative};

     for (int i = 0; i < nb_thread; i++)
     {
        if (pthread_create(&threads[i], NULL, start_threads, &args) != 0)
        {
            fprintf(stderr, "Error creating thread: %d\n", i);
            free(threads);
            return 1;
        }
     }

    for (int j = 0; j < nb_thread; j++)
    {
        if (pthread_join(threads[j], NULL) != 0)
        {
            fprintf(stderr, "Error joining thread %d\n", j);
            free(threads);
            return 1;
        }
    }

    free(threads);
    return 0;
}
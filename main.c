#include "thread.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr,"Usage: %s <number of threads> <quantity of numbers per thread>\n", argv[0]);
        return 1;
    }

    int nb_threads = atoi(argv[1]);
    int num_per_thread = atoi(argv[2]);

    if (nb_threads <= 0 || num_per_thread <= 0)
    {
        fprintf(stderr, "Error: can't have negative or empty values\n");
        return 1;
    }

    // Allocate threads
    pthread_t *threads = malloc(sizeof(pthread_t) * nb_threads);
    if (!threads)
    {
        fprintf(stderr, "Error allocating threads\n");
        return 1;
    }

    t_thread *args = malloc(sizeof(t_thread) * nb_threads);
    if (!args)
    {
        fprintf(stderr, "Error allocating thread args\n");
        free(threads);
        return 1;
    }

    // Create lists
    t_list positive;
    t_list negative;
    if (init_list(&positive, nb_threads * num_per_thread) != 0)
    {
        fprintf(stderr, "Error initializing positive list\n");
        free(threads);
        free(args);
        return 1;
    }

    if (init_list(&negative, nb_threads * num_per_thread) != 0)
    {
        fprintf(stderr, "Error initializing negative list\n");
        free_list(&positive);
        free(threads);
        free(args);
        return 1;
    }

    // Create threads
    for (int i = 0; i < nb_threads; i++)
    {
        args[i].max_nb = num_per_thread;
        args[i].id = i;
        args[i].positive = &positive;
        args[i].negative = &negative;

        if (pthread_create(&threads[i], NULL, start_threads, &args[i]) != 0)
        {
            fprintf(stderr, "Error creating thread %d\n", i);
            free_list(&positive);
            free_list(&negative);
            free(threads);
            free(args);
            return 1;
        }
    }

    // Join threads
    for (int i = 0; i < nb_threads; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            fprintf(stderr, "Error joining thread %d\n", i);
            return 1;
        }
    }

    free(threads);
    free(args);

    free_list(&positive);
    free_list(&negative);

    return 0;
}
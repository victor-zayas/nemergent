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

    t_list positive_list, negative_list;
    if (run_threads(nb_threads, num_per_thread, &positive_list, &negative_list) != 0)
        return 1;

    sort_list(&positive_list);
    sort_list(&negative_list);

    print_list(&positive_list, "Positive");
    print_list(&negative_list, "Negative");

    free_list(&positive_list);
    free_list(&negative_list);

    return 0;
}
#include "thread.h"
#include <stdio.h>

int main(void)
{
    t_list  list;

    init_list(&list, 3);
    insert_list(&list, 1);
    insert_list(&list, 3);
    insert_list(&list, 2);

    print_list(&list);

    free_list(&list);

    return 0;
}
#include "thread.h"
#include <stdio.h>

int main(void)
{
    t_list  list;

    init_list(&list, 3);
    list.data[0] = 1;
    list.data[1] = 3;
    list.data[2] = 2;

    list.index = 3;
    for (int i = 0; i < list.index; i++)
    {
        printf("[%d] = %d\n", i, list.data[i]);
    }

    free_list(&list);

    return 0;
}
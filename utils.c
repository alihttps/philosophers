#include "philosophers.h"

long ft_atol(char *av)
{
    long num = 0;
    int i = 0;
    while (av[i])
    {
        num = (num * 10) + (av[i] - '0');
        i++;
    }
    return num;
}

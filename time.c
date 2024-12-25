#include "philosophers.h"

long get_time_sec ()
{
    struct timeval tv;

    gettimeofday(&tv, NULL );
    return (tv.tv_sec + (tv.tv_usec / 1e6));
}

long get_time_milli ()
{
    struct timeval tv;

    gettimeofday(&tv, NULL );
    return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}

long get_time_micro ()
{
    struct timeval tv;

    gettimeofday(&tv, NULL );
    return ((tv.tv_sec * 1e6) + tv.tv_usec);
}


void precise_usleep(long usec, t_table *table) 
{
    long start = get_time_micro();
    long elapsed;
    long rem;

    while (get_time_micro() - start < usec)
    {
        if (simulation_ended(table))
            break;
        elapsed = get_time_micro() - start;
        rem = usec - elapsed;
        if (rem > 1e3)
            usleep(rem / 2);
        else
        {
            while (get_time_micro() - start < usec)
                ;
        }
    }
}
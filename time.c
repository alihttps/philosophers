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

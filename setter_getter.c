#include "philosophers.h"

void set_bool(pthread_mutex_t *mtx, bool *dest, bool value)
{
    pthread_mutex_lock(mtx);
    *dest = value;
    pthread_mutex_unlock(mtx);
}

bool get_bool(pthread_mutex_t *mtx, bool *value)
{
    bool val;

    pthread_mutex_lock(mtx);
    val = *value;
    pthread_mutex_unlock(mtx);
    return val;
}

void set_long(pthread_mutex_t *mtx, long *dest, long value)
{
    pthread_mutex_lock(mtx);
    *dest = value;
    pthread_mutex_unlock(mtx);
}
bool get_long(pthread_mutex_t *mtx, long *value)
{
    long val;

    pthread_mutex_lock(mtx);
    val = *value;
    pthread_mutex_unlock(mtx);
    return val;
}

bool simulation_ended(t_table *table)
{
    return get_bool(&table->table_mutx ,&table->end_of_simulation);
}
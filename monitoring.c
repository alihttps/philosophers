#include "philosophers.h"

bool all_thrads_are_running (pthread_mutex_t *mtx , long *threads, long thread_nbr)
{
    bool ret = false;

    pthread_mutex_lock(mtx);
    if (*threads == thread_nbr)
        ret = true;
    pthread_mutex_unlock(mtx);
    return ret;
}

bool philo_died(t_philo *philo)
{
    long elapsed;
    
    if (get_bool(&philo->philo_mutx , &philo->full))
        return false;

    elapsed = get_time_milli() - get_long(&philo->philo_mutx, &philo->last_meal_time);
    
    if (elapsed > (philo->table->time_to_die / 1e3))
        return true;
    return false;
}

void *monitor_dinner(void *data)
{
    t_table *table;
    int i;
    table = (t_table *)data;

    while (!all_thrads_are_running(&table->table_mutx, &table->threads_running_count, table->philo_number))
    ;
    while (!simulation_ended(table))
    {
        i = 0;
        while (i < table->philo_number && !simulation_ended(table))
        {
            if (philo_died(&table->philos[i]))
            {
                set_bool(&table->table_mutx, &table->end_of_simulation, true);
                print_status(DIED, &table->philos[i]);
            }
            i++; 
        }
    }
    return NULL;
}

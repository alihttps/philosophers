#include "philosophers.h"

bool all_threads_are_running (pthread_mutex_t *mtx , atomic_long *threads, long thread_nbr)
{
    (void) mtx;
    bool ret = false;

    if (*threads == thread_nbr)
        ret = true;
    return ret;
}

bool philo_died(t_philo *philo)
{
    long elapsed;
    if (philo->full)
    {
        philo->table->full_count++;
        return false;
    }

    elapsed = get_time_milli() - philo->last_meal_time;
    if (elapsed >= (philo->table->time_to_die))
        return true;
    return false;
}

void *monitor_dinner(void *data)
{
    t_table *table;
    int i;
    table = (t_table *)data;

    while (!all_threads_are_running(&table->table_mutx, &table->threads_running_count, table->philo_number))
    ;
    while (!table->end_of_simulation)
    {
        i = 0;
        while (i < table->philo_number && !table->end_of_simulation)
        {
            if (philo_died(&table->philos[i]))
            {
                table->end_of_simulation = true;
                print_status(DIED, &table->philos[i]);
            }
            if (table->num_of_meals > 0 && table->full_count == table->philo_number)
            {
                table->end_of_simulation = true;
            }
            i++; 
        }
        usleep(500);
    }
    return NULL;
}

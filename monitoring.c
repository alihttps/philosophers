#include "philosophers.h"

bool all_threads_are_running (pthread_mutex_t *mtx , long *threads, long thread_nbr)
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
    {
        increment_long(&philo->table->table_mutx, &philo->table->full_count);
        return false;
    }

    pthread_mutex_lock(&philo->philo_mutx);
    elapsed = get_time_milli() - get_long(&philo->philo_mutx, &philo->last_meal_time);
    printf ("elapsed %ld\n",elapsed);
    pthread_mutex_unlock(&philo->philo_mutx);
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
    while (!simulation_ended(table))
    {
        usleep(100);
        i = 0;
        while (i < table->philo_number && !simulation_ended(table))
        {
            if (philo_died(&table->philos[i]))
            {
                set_bool(&table->table_mutx, &table->end_of_simulation, true);
                print_status(DIED, &table->philos[i]);
            }
            if (table->num_of_meals > 0 && table->full_count == table->philo_number)
            {
                set_bool(&table->table_mutx, &table->end_of_simulation, true);
            }
            i++; 
        }
    }
    return NULL;
}

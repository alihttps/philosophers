#include "philosophers.h"

void clean_table (t_table *table)
{
    int i = 0;
    while (i < table->philo_number)
    {
        pthread_mutex_destroy(&table->philos[i].philo_mutx);
        i++;
    }
    pthread_mutex_destroy(&table->table_mutx);
    pthread_mutex_destroy(&table->write_mutx);
    free(table->forks);
    free(table->philos);
}
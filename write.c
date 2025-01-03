#include "philosophers.h"

void print_status(philo_status stat, t_philo *philo)
{
    if (philo->full)
        return;
    long elapsed = get_time_milli() - philo->table->start_of_simulation;
    
    // pthread_mutex_lock(&philo->table->write_mutx);

    if (stat == DIED)
        printf ("%ld %d died\n", elapsed , philo->id);
    if ((stat == TAKE_FIRST_FORK || stat == TAKE_SECOND_FORK) && !philo->table->end_of_simulation)
        printf ("%ld %d has taken a fork\n", elapsed, philo->id);
    if (stat == EATING && !philo->table->end_of_simulation)
        printf ("%ld %d is eating\n", elapsed , philo->id);
    if (stat == SLEEPING && !philo->table->end_of_simulation)
        printf ("%ld %d is sleeping\n", elapsed , philo->id);
    if (stat == THINKING && !philo->table->end_of_simulation)
        printf ("%ld %d is thinking\n", elapsed , philo->id);
    // pthread_mutex_unlock(&philo->table->write_mutx);
}

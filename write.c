#include "philosophers.h"

void print_status(philo_status stat, t_philo *philo)
{
    if (philo->full)
        return;
    
    pthread_mutex_lock(&philo->table->write_mutx);
    // printf("%ld\n",philo->table->start_of_simulation);
    // sleep (18);
    long elapsed = get_time_milli() - philo->table->start_of_simulation;
    if ((stat == TAKE_FIRST_FORK || stat == TAKE_SECOND_FORK) && !simulation_ended(philo->table))
        printf ("%ld %d has taken a fork\n", elapsed, philo->id);
    else if (stat == EATING && !simulation_ended(philo->table))
        printf ("%ld %d is eating\n", elapsed , philo->id);
    else if (stat == SLEEPING && !simulation_ended(philo->table))
        printf ("%ld %d is sleeping\n", elapsed , philo->id);
    else if (stat == THINKING && !simulation_ended(philo->table))
        printf ("%ld %d is thinking\n", elapsed , philo->id);
    else if (stat == DIED)
        printf ("%ld %d died\n", elapsed , philo->id);
    pthread_mutex_unlock(&philo->table->write_mutx);
}

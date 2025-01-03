#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>
#include <stdbool.h>
#include <stdatomic.h>

typedef struct s_table t_table;

typedef enum status
{
    TAKE_FIRST_FORK,
    TAKE_SECOND_FORK,
    EATING,
    THINKING,
    SLEEPING,
    DIED,
}   philo_status;

typedef struct s_fork
{
    int id;
    pthread_mutex_t fork;

} t_fork;

typedef struct s_philo
{
    atomic_int id;
    atomic_long meal_counter;
    atomic_bool full;
    atomic_long last_meal_time;
    pthread_mutex_t philo_mutx;
    t_fork *first_fork;
    t_fork *second_fork;
    pthread_t thread_id;
    t_table *table;

} t_philo;

typedef struct s_table
{
    atomic_long full_count;
    atomic_long num_of_meals;
    atomic_long philo_number;
    atomic_long time_to_die;
    atomic_long time_to_eat;
    atomic_long time_to_sleep;
    atomic_long start_of_simulation;
    atomic_bool ready_to_sync;
    atomic_bool end_of_simulation;
    atomic_long threads_running_count;
    pthread_t monitor;
    pthread_mutex_t table_mutx;
    pthread_mutex_t write_mutx;
    t_fork *forks;
    t_philo *philos;

} t_table;

void parse_input (char **av);

////////////setters_getters////////////
void set_bool(pthread_mutex_t *mtx, bool *dest, bool value);
bool get_bool(pthread_mutex_t *mtx, bool *value);
void set_long(pthread_mutex_t *mtx, long *dest, long value);
bool simulation_ended(t_table *table);
long get_long(pthread_mutex_t *mtx, long *value);
void increment_long (pthread_mutex_t *mtx, long *value);

/////////////time////////////////
long get_time_sec ();
long get_time_milli ();
long get_time_micro ();

void print_status(philo_status stat, t_philo *philo);

long ft_atol(char *av);

void *monitor_dinner(void *data);

void clean_table (t_table *table);

int	precise_usleep(size_t milliseconds);

bool valid_input(int ac , char **av);

#endif
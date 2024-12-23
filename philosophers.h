#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>
#include <stdbool.h>

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
    int id;
    int meal_counter;
    bool full;
    long last_meal_time;
    pthread_mutex_t philo_mutx;
    t_fork *first_fork;
    t_fork *second_fork;
    pthread_t thread_id;
    t_table *table;

} t_philo;

typedef struct s_table
{
    long num_of_meals;
    long philo_number;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long start_of_simulation;
    bool ready_to_sync;
    bool end_of_simulation;
    pthread_mutex_t table_mutx;
    pthread_mutex_t write_mutx;
    t_fork *forks;
    t_philo *philos;

} t_table;

////////////setters_getters////////////
void set_bool(pthread_mutex_t *mtx, bool *dest, bool value);
bool get_bool(pthread_mutex_t *mtx, bool *value);
void set_long(pthread_mutex_t *mtx, long *dest, long value);
bool simulation_ended(t_table *table);
bool get_long(pthread_mutex_t *mtx, long *value);

/////////////time////////////////
long get_time_sec ();
long get_time_milli ();
long get_time_micro ();

void print_status(philo_status stat, t_philo *philo);

long ft_atol(char *av);

#endif
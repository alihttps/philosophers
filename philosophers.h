#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>

typedef struct s_fork
{
    int id;
    pthread_mutex_t fork;

} t_fork;

typedef struct s_philo
{
    int id;
    int meal_conter;
    bool full;
    long last_meal_time;
    t_fork *first_fork;
    t_fork *second_fork;
    pthread_t thread_id;
    t_table *table;

} t_philo;

typedef struct s_table
{
    int num_of_meals;
    int philo_number;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int start_of_simulation;
    bool ready_to_sync;
    bool end_simulation;
    pthread_mutex_t table_mutx;
    t_fork *forks;
    t_philo *philos;

} t_table;

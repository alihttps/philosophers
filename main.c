#include "philosophers.h"

void *dinner_simulation (void *data)
{
    t_philo *philo = (t_philo *)data;


    return NULL;
}

void start_simulation (t_table *table)
{
    int i = 0;
    if (table->num_of_meals == 0)
        return;
    else if (table->philo_number == 1)
        ;//todo
    else
    {
        while (i < table->philo_number)
        {
            pthread_create(table->philos[i].thread_id, NULL, dinner_simulation, &table->philos[i]);
            i++;
        }
    }
    

}

void assign_forks (t_philo *philo, t_fork *fork, int position)
{
    philo->first_fork = &fork[(position + 1) % philo->table->philo_number];//left
    philo->second_fork = &fork[position];//right
    if (philo->id % 2 == 0)
    {
        philo->first_fork = &fork[position]; // right
        philo->second_fork = &fork[(position + 1) % philo->table->philo_number];// left
    }
}

void philo_init(t_table *table)
{
    int i = 0;
    t_philo *philo;
    while (i < table->philo_number)
    {
        philo = table->philos + i;
        philo->id = i + 1;
        philo->full = false;
        philo->meal_conter = 0;
        philo->table = table;
        assign_forks(philo, table->forks, i);
    }
}

void init_table(t_table *table)
{
    table->end_simulation = false;
    table->ready_to_sync = false;
    table->philos = malloc (sizeof(t_philo) * table->philo_number);
    table->forks = malloc (sizeof(t_fork) * table->philo_number);
    pthread_mutex_init(&table->table_mutx, NULL);
    int i = 0;
    while (i < table->philo_number)
    {
        pthread_mutex_init(&table->forks[i], NULL);
        table->forks[i].id = i;
        i++;
    }
    philo_iunit (table);
}

void fill_table (t_table *table, char **av)
{
    table->philo_number = atoi(av[1]);
    table->time_to_die = atoi(av[2]) * 1e3;
    table->time_to_eat =atoi(av[3]) * 1e3;
    table->time_to_sleep = atoi(av[4]) * 1e3;
    if (table->time_to_die < 6e4 || table->time_to_eat < 6e4 || table->time_to_sleep < 6e4)
        printf ("use values larger than 60ms\n");
    if (av[5])
        table->num_of_meals = atoi(av[5]);
    else
        table->num_of_meals = -1;
}

int main (int ac, char **av)
{
    t_table table;
    if (ac == 5 || ac == 6)
    {
        fill_table(&table, av);
        init_table(&table);
        start_simulation (&table);
        clean_table(&table);
    }
    else
        printf ("error\n");
}

#include "philosophers.h"

void wait_all_threads(t_table *table)
{
    while (!get_bool(&table->table_mutx, &table->ready_to_sync))
        ;
}

void think (t_philo *philo)
{
    print_status(THINKING, philo);
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->first_fork->fork);
    print_status(TAKE_FIRST_FORK, philo);
    pthread_mutex_lock(&philo->second_fork->fork);
    print_status(TAKE_SECOND_FORK, philo);

    //update last meal time
    set_long(&philo->philo_mutx, &philo->last_meal_time, get_time_milli());
    philo->meal_counter++;
    print_status(EATING, philo);
    usleep(philo->table->time_to_eat);
    if (philo->table->num_of_meals > 0 && philo->meal_counter == philo->table->num_of_meals)
    {
        set_bool(&philo->philo_mutx, &philo->full, true);
    }
    pthread_mutex_unlock(&philo->first_fork->fork);
    pthread_mutex_unlock(&philo->second_fork->fork);
}

void *dinner_simulation (void *data)
{
    t_philo *philo = (t_philo *)data;

    wait_all_threads(philo->table);

    while (!simulation_ended(philo->table))
    {
        //eat
        eat(philo);
        //sleep
        print_status(SLEEPING, philo);
        usleep(philo->table->time_to_sleep);
        //think
        think(philo);
    }
    return NULL;
}

void start_dinner (t_table *table)
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
            pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation, &table->philos[i]);
            i++;
        }
    }
    table->start_of_simulation = get_time_milli();
    set_bool(&table->table_mutx, &table->ready_to_sync, true);
    i = 0;
    while (i < table->philo_number)
    {
        pthread_join(table->philos[i].thread_id, NULL);
        i++;
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
        philo->meal_counter = 0;
        philo->table = table;
        pthread_mutex_init(&philo->philo_mutx, NULL);
        assign_forks(philo, table->forks, i);
        i++;
    }
}

void init_table(t_table *table)
{
    table->end_of_simulation = false;
    table->ready_to_sync = false;
    table->philos = malloc (sizeof(t_philo) * table->philo_number);
    table->forks = malloc (sizeof(t_fork) * table->philo_number);
    pthread_mutex_init(&table->table_mutx, NULL);
    pthread_mutex_init(&table->write_mutx, NULL);
    int i = 0;
    while (i < table->philo_number)
    {
        pthread_mutex_init(&table->forks[i].fork, NULL);
        table->forks[i].id = i;
        i++;
    }
    philo_init (table);
}

void fill_table (t_table *table, char **av)
{
    table->philo_number = ft_atol(av[1]);
    table->time_to_die = ft_atol(av[2]) * 1e3;
    table->time_to_eat =ft_atol(av[3]) * 1e3;
    table->time_to_sleep = ft_atol(av[4]) * 1e3;
    if (table->time_to_die < 6e4 || table->time_to_eat < 6e4 || table->time_to_sleep < 6e4)
        printf ("use values larger than 60ms\n");
    if (av[5])
        table->num_of_meals = atol(av[5]);
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
        start_dinner (&table);
        // clean_table(&table);
    }
    else
        printf ("error\n");
}

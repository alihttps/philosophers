#include "philosophers.h"

void think(t_philo *philo);

// void de_synchronise(t_philo *philo)
// {
//     if (philo->table->philo_number % 2 == 0)
//     {
//         // long delay = (30 * 50) / philo->table->philo_number;
//         // if (delay < 50)
//         //     delay = 50;
//         // precise_usleep(delay);
//         precise_usleep(50);
//     }
//     else
//         think(philo);
// }

void	sim_start_delay(time_t start_time)
{
	while (get_time_milli() < start_time)
		continue ;
}

void wait_all_threads(t_table *table)
{
    while (!get_bool(&table->table_mutx, &table->ready_to_sync))
        ;
}
void *loner (void *data)
{
    t_philo *philo = (t_philo *)data;

    wait_all_threads(philo->table);
    set_long(&philo->philo_mutx, &philo->last_meal_time, get_time_milli());
    increment_long(&philo->table->table_mutx, &philo->table->threads_running_count);
    set_long(&philo->philo_mutx, &philo->table->start_of_simulation, get_time_milli());
    print_status(TAKE_FIRST_FORK, philo);
    while (!simulation_ended(philo->table))
        usleep(200);
    return NULL;
}

void think (t_philo *philo)
{
    print_status(THINKING, philo);
    return;
    // precise_usleep((philo->table->time_to_eat - philo->table->time_to_sleep * 2) * 42);   
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->first_fork->fork);
    print_status(TAKE_FIRST_FORK, philo);
    pthread_mutex_lock(&philo->second_fork->fork);
    print_status(TAKE_SECOND_FORK, philo);

    set_long(&philo->philo_mutx, &philo->last_meal_time, get_time_milli());
    if (!simulation_ended(philo->table))
    {
        int i = philo->meal_counter + 1;
        set_long(&philo->philo_mutx,&philo->meal_counter, i);
    }

    print_status(EATING, philo);
    precise_usleep(philo->table->time_to_eat);
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

    sim_start_delay(philo->table->start_of_simulation);

    pthread_mutex_lock(&philo->philo_mutx);
    philo->last_meal_time = get_time_milli();
    pthread_mutex_unlock(&philo->philo_mutx);

    increment_long(&philo->table->table_mutx, &philo->table->threads_running_count);


    set_long(&philo->table->table_mutx, &philo->table->start_of_simulation, get_time_milli());
    while (1)
    {
        eat(philo);
        print_status(SLEEPING, philo);
        precise_usleep(philo->table->time_to_sleep);
        think(philo);
        if(simulation_ended(philo->table))
            return (NULL);
    }
    return NULL;
}

void start_dinner (t_table *table)
{
    int i = 0;
        set_long(&table->table_mutx, &table->start_of_simulation, get_time_milli());
    if (table->num_of_meals == 0)
        return;
    else if (table->philo_number == 1)
        pthread_create(&table->philos[0].thread_id, NULL, loner, &table->philos[0]);
    else
    {
        while (i < table->philo_number)
        {
            pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation, &table->philos[i]);
            i++;
        }
    }
    // de_synchronise(table->philos);
    pthread_create(&table->monitor, NULL, monitor_dinner, table);
    set_bool(&table->table_mutx, &table->ready_to_sync, true);
    i = 0;
    while (i < table->philo_number)
    {
        pthread_join(table->philos[i].thread_id, NULL);
        i++;
    }
    i = 0;
    pthread_join(table->monitor, NULL);
    set_bool(&table->table_mutx, &table->end_of_simulation, true);
}

void assign_forks(t_philo *philo, t_fork *fork, int position)
{
    philo->first_fork = &fork[position];
    philo->second_fork = &fork[(position + 1 )% philo->table->philo_number];
    if (philo->id % 2 == 0)
    {
        philo->first_fork = &fork[(position + 1 )% philo->table->philo_number];
        philo->second_fork = &fork[position];
    }
}

void init_philo(t_table *table)
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
    table->threads_running_count = 0;
    table->full_count = 0;
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
    init_philo (table);
}

void fill_table (t_table *table, int ac, char **av)
{
    int i = 1;
    while (i < ac)
    {
        if (ft_atol(av[i]) < 0)
        {
            printf ("not a valid value\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    table->philo_number = ft_atol(av[1]);
    table->time_to_die = ft_atol(av[2]);
    table->time_to_eat =ft_atol(av[3]);
    table->time_to_sleep = ft_atol(av[4]);
    if (table->time_to_die < 60 || table->time_to_eat < 60 || table->time_to_sleep < 60)
    {
        printf ("use values larger than 60ms\n");
        exit(EXIT_FAILURE);
    }
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
        if (!valid_input(ac, av))
            return(EXIT_FAILURE);
        fill_table(&table, ac, av);
        init_table(&table);
        start_dinner (&table);
        clean_table(&table);
    }
    else
        printf ("error\n");
    return 0;
}

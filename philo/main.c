/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 06:45:55 by aait-bou          #+#    #+#             */
/*   Updated: 2025/01/10 19:48:07 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_table	table;
	int		i;

	if (ac == 5 || ac == 6)
	{
		if (!valid_input(ac, av))
			return (EXIT_FAILURE);
		fill_table(&table, av);
		init_table(&table);
		start_dinner(&table);
		i = 0;
		while (i < table.philo_number)
		{
			pthread_mutex_destroy(&table.philos->first_fork->fork);
			pthread_mutex_destroy(&table.philos->second_fork->fork);
			i++;
		}
		free((&table)->forks);
		free((&table)->philos);
	}
	else
		printf("invalid number of arguments\n");
	return (0);
}

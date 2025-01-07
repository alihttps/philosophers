/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 06:46:15 by aait-bou          #+#    #+#             */
/*   Updated: 2025/01/07 22:41:57 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	de_synchronise(t_philo *philo)
{
	if (philo->table->philo_number % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(30, philo->table);
	}
	else
	{
		if (philo->id)
			think(philo);
	}
}

void	wait_all_threads(t_table *table)
{
	while (!table->ready_to_sync)
		;
}

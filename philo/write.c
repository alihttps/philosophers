/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 06:46:21 by aait-bou          #+#    #+#             */
/*   Updated: 2025/01/07 06:56:24 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_status stat, t_philo *philo)
{
	long	elapsed;

	if (philo->full)
		return ;
	elapsed = get_time_milli() - philo->table->start_of_simulation;
	if (stat == DIED)
		printf("%ld %d died\n", elapsed, philo->id);
	else if (stat == EATING && !philo->table->end_of_simulation)
		printf("%ld %d is eating\n", elapsed, philo->id);
	else if ((stat == TAKE_FIRST_FORK || stat == TAKE_SECOND_FORK)
		&& !philo->table->end_of_simulation)
		printf("%ld %d has taken a fork\n", elapsed, philo->id);
	else if (stat == SLEEPING && !philo->table->end_of_simulation)
		printf("%ld %d is sleeping\n", elapsed, philo->id);
	else if (stat == THINKING && !philo->table->end_of_simulation)
		printf("%ld %d is thinking\n", elapsed, philo->id);
}

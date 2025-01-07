/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 06:46:18 by aait-bou          #+#    #+#             */
/*   Updated: 2025/01/07 22:48:37 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_sec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + (tv.tv_usec / 1e6));
}

long	get_time_milli(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}

int	precise_usleep(size_t milliseconds, t_table *table)
{
	size_t	start;

	start = get_time_milli();
	while (!table->end_of_simulation && \
	(get_time_milli() - start) < milliseconds)
		usleep(50);
	return (0);
}

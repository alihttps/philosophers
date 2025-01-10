/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 06:46:02 by aait-bou          #+#    #+#             */
/*   Updated: 2025/01/10 19:47:34 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_digits(char *av)
{
	int	i;

	i = 0;
	while (av[i] && (av[i] >= '0' && av[i] <= '9'))
		i++;
	if (!av[i])
		return (1);
	return (0);
}

void	parse_input(char **av)
{
	int	i;

	i = 1;
	while (av[i] && is_digits(av[i]))
		i++;
	if (av)
		return ;
}

long	ft_atol(char *str)
{
	unsigned long long int	nb;
	int						i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}

bool	digits_only(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	valid_input(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (i == 1 && ft_atol(av[i]) <= 0)
			return (printf("invalid number of philos\n"), false);
		if (!digits_only(av[i]))
			return (printf("only digits\n"), false);
		if ((i > 1 && i <= 4) && ft_atol(av[i]) < 60)
			return (printf("use values larger than 60ms\n"), false);
		i++;
	}
	return (true);
}

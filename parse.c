#include "philosophers.h"

// static int	ft_isspace(char c)
// {
// 	if ((c >= 9 && c <= 13) || c == 32)
// 		return (1);
// 	return (0);
// }
int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int is_digits(char *av)
{
    int i = 0;
    while (av[i] && is_digit(av[i]))
        i++;
    if (!av[i])
        return 1;
    return 0;
}

void parse_input (char **av)
{
    int i = 1;
    while (av[i] && is_digits(av[i]))
        i++;
    if (av)
        return;
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
bool	only_digits(char *str)
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

bool valid_input(int ac , char **av)
{
	int i = 1;
	while (i < ac)
	{
		if (!only_digits(av[i]))
		{
			return (printf("only digits\n"), false);
		}
		i++;
	}
	return true;
}
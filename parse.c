#include "philosophers.h"

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
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
	long long		result;
	int				sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		str++;
		sign = -1;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + *str - '0';
		str++;
	}
	return (long)(sign * result);
}

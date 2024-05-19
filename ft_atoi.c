#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);

}
static char	*skip_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ((s[i] >= 9 && s[i] <= 13) || (s[i] == ' ')))
		i++;
	return (s + i);
}

static void	assign(int *sign, int *neg, long *holder)
{
	*sign = 1;
	*neg = 0;
	*holder = 0;
}

int	ft_atoi(const char *s, unsigned long *num)
{
	long	holder;
	int		neg;
	int		sign;
	char	*str;

	assign(&sign, &neg, &holder);
	str = skip_spaces((char *)s);
	if (str[0] == '-')
	{
		neg = 1;
		sign = -1;
	}
	if (str[0] == '+')
		neg = 1;
	while (str[neg] != '\0')
	{
		holder = (holder * 10) + (str[neg] - '0');
		if (!ft_isdigit(str[neg])
			|| (sign * holder) > (INT_MAX) || (sign * holder)
			< (0))
			return (0);
		neg++;
	}
	*num = (holder * sign);
	return ((str[neg - 1] != '-' && str[neg - 1] != '+') * 1);
}

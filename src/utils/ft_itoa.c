#include "minishell.h"

static int	count_n(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	ft_signal(long *n, int *i)
{
	if (*n < 0)
	{
		*n *= -1;
		(*i)++;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nlong;

	nlong = n;
	i = count_n(nlong);
	ft_signal(&nlong, &i);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	str[i] = '\0';
	if (nlong == 0)
		str[0] = '0';
	while (nlong > 0)
	{
		i--;
		str[i] = (nlong % 10) + '0';
		nlong /= 10;
	}
	return (str);
}

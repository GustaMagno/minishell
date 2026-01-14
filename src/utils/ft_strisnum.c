#include "minishell.h"

int	ft_strisnum(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[0] < '0' || str[0] > '9')
			return (0);
		i++;
	}
	return (1);
}
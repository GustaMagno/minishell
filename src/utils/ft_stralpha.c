#include "minishell.h"

int	ft_stralpha(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	if (str[0] >= '0' && str[0] <= '9')
		return (0);
	while (str[i])
	{
		if ((str[i] > 122 || str[i] < 65) && str[i] != '_' && !(str[i] >= '0' && str[i] <= '9'))
			return (0);
		if (str[i] > 90 && str[i] < 97 && str[i] != '_' && !(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

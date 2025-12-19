#include "minishell.h"

int	ft_stralpha(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] > 122 || str[i] < 65)
			return (0);
		if (str[i] > 90 && str[i] < 97)
			return (0);
		i++;
	}
	return (1);
}
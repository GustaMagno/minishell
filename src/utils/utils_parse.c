#include "minishell.h"

int	ft_argslen(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
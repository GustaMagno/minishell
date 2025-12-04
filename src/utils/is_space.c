#include "minishell.h"

int	is_space(char *line)
{
	int i;

	i = 0;
	while (line[i] == 32)
		i++;
	if (!line[i])
		return (1);
	return (0);
}
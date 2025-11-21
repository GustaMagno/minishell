#include "minishell.h"

int	len_line(char *line)
{
	int len;
	int redir_space;

	len = 0;
	redir_space = 0;
	while (line[len])
	{
		if (!ft_strncmp(&line[len], ">>", 2) || !ft_strncmp(&line[len], "<<", 2)
			|| !ft_strncmp(&line[len], "<", 1) || !ft_strncmp(&line[len], ">", 1))
			redir_space += 2;
		len++;
	}
	len += redir_space;
	return (len);
}

int	ft_argslen(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

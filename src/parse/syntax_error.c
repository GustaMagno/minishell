#include "minishell.h"

int	error_in_pipe(char *line)
{
	int i;
	int j;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\3')
		{
			j = i + 1;
			while (line[j] == 32)
				i++;
			if (line[j] == '\0' || line[j] == '\3')
				return (1);
		}
		i++;
	}
	return (0);
}

int	find_error(char	**args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if ((!ft_strcmp(args[i], "<<") || !ft_strcmp(args[i], ">>")) 
			&& (!args[i + 1] || !ft_strcmp(args[i], "<") || !ft_strcmp(args[i], ">")))
			return (1);
		if (!ft_strcmp(args[i], "<") && (!args[i + 1] || !ft_strcmp(args[i + 1], ">")))
			return (1);
		if (!ft_strcmp(args[i], ">") && (!args[i + 1] || !ft_strcmp(args[i + 1], "<")))
			return (1);
		i++;
	}
	return (0);
}

int	syntax_error(t_cmd *head, char *line)
{
	t_cmd	*cmd;
	
	if (!head)
		return (free(line), 0);
	if (error_in_pipe(line))
		return (free(line), free_structs(head), 1);
	printf("%s\n", line);
	cmd = head;
	while (cmd)
	{
		if (find_error(cmd->args))
			return (free(line), free_structs(head), 1);
		cmd = cmd->next;
	}
	return (free(line), 0);
}

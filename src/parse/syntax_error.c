#include "minishell.h"

int	redircmp(char *str)
{
	//se <<< exitstatus 0
	if (!ft_strcmp(str, "<<"))
		return (1);
	if (!ft_strcmp(str, ">>"))
		return (1);
	if (!ft_strcmp(str, "<"))
		return (1);
	if (!ft_strcmp(str, ">"))
		return (1);
	return (0);
}

int	error_in_pipe(char *line)
{
	int i;
	int j;

	i = 0;
	if (line[0] == '\3')
		return (1);
	while (line[i])
	{
		if (line[i] == '\3')
		{
			j = i + 1;
			while (line[j] == 32 || line[j] == '\2')
				j++;
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
		if (redircmp(args[i]) && (!args[i + 1] || redircmp(args[i + 1])))
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
	cmd = head;
	while (cmd)
	{
		if (find_error(cmd->args))
			return (free(line), free_structs(head), 1);
		cmd = cmd->next;
	}
	return (free(line), 0);
}

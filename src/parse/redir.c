#include "minishell.h"

t_redir	*new_redir(char *args[2])
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->args[0] = args[0];
	redir->args[1] = args[1];
	redir->next = NULL;
	return (redir);
}

//test more redir e retirar do cmd o redir

int	redir_in_cmd(char **cmd_arg, char *redir_arg[2])
{
	int	i;

	i = 0;
	while (cmd_arg[i])
	{
		if (!ft_strcmp(cmd_arg[i], ">>") || !ft_strcmp(cmd_arg[i], "<<"))
		{
			redir_arg[0] = cmd_arg[i];
			if (!cmd_arg[++i])
				return (-1);
			redir_arg[1] = cmd_arg[i];
			return (1);
		}
		i++;
	}
	return (0);
}

t_redir	*parsing_redir(t_cmd *cmd)
{
	t_redir	*redir;
	char	*args[2];
	t_cmd	*node;

	node = cmd;
	redir = NULL;
	while (node)
	{
		if (redir_in_cmd(node->args, args))
		{
			if (redir_in_cmd(node->args, args) == -1)
				return (NULL);
			redir = new_redir(args);
			if (!redir)
				return (NULL);
		}
		node = node->next;
	}
	return (redir);
}

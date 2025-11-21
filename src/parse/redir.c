#include "minishell.h"

t_redir	*new_redir(char *arg1, char *arg2)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->args[0] = ft_strdup(arg1);
	if (!arg2)
		redir->args[1] = NULL;
	else
		redir->args[1] = ft_strdup(arg2);
	redir->args[2] = NULL;
	redir->next = NULL;
	return (redir);
}

int	redir_in_cmd(char *cmd_arg)
{
	if (!ft_strcmp(cmd_arg, ">>") || !ft_strcmp(cmd_arg, "<<")
	|| !ft_strcmp(cmd_arg, "<") || !ft_strcmp(cmd_arg, ">"))
		return (1);
	return (0);
}

char	**clean_cmd(char **args)
{
	char	**new_args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	
	new_args = ft_calloc(ft_argslen(args) + 1, sizeof(char *));
	if (!new_args)
		return (0);
	while (args[i])
	{
		if (!redir_in_cmd(args[i]))
		{
			new_args[j++] = ft_strdup(args[i]);
			i++;
		}
		else
			i += 2;
	}
	new_args[j] = NULL;
	free_split(args);
	return (new_args);
}

int	create_redir_node(t_cmd *node, t_redir **node_red, t_redir **bnode, int i)
{
	if (!node->redir)
	{
		node->redir = new_redir(node->args[i], node->args[i + 1]);
		if (!node->redir)
			return (0);
		*node_red = node->redir->next;
		*bnode = node->redir;
	}
	else
	{
		*node_red = new_redir(node->args[i], node->args[i + 1]);
		if (!*node_red)
			return (0);
		(*bnode)->next = *node_red;
		*bnode = *node_red;
		*node_red = (*node_red)->next;
	}
	return (1);
}

int	parsing_redir(t_cmd *cmd)
{
	int		i;
	t_cmd	*node;
	t_redir	*node_red;
	t_redir	*bnode;

	node = cmd;
	bnode = NULL;
	while (node)
	{
		i = -1;
		while (node->args[++i])
		{
			if (redir_in_cmd(node->args[i]))
			{
				if (!create_redir_node(node, &node_red, &bnode, i))
					return (0);
			}
		}
		node->args = clean_cmd(node->args);
		if (!node->args)
			return (0);
		node = node->next;
	}
	return (1);
}

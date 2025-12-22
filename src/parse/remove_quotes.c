#include "minishell.h"


char	*new_str(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = ft_calloc(ft_strlen(str) + 1, 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		//if (condition_quote(str, i))
		//	new_str[j++] = str[i];
		i++;
	}
	return (new_str);
}

char	**new_args(char **args)
{
	int		i;
	char	**new_args;

	i = -1;
	new_args = ft_calloc(ft_argslen(args) + 1, sizeof(char *));
	if (!new_args)
		return (NULL);
	while (args[++i])
	{
		new_args[i] = new_str(args[i]);
		if (!new_args[i])
			return (NULL);
	}
	return (free_split(args), new_args);
}

int	remove_quotes(t_cmd *cmd)
{
	t_cmd	*node;
	int		i;

	node = cmd;
	i = 0;
	while (node)
	{
		node->args = new_args(node->args);
		if (!node->args)
			return (0);
		node = node->next;
	}
	return (1);
}
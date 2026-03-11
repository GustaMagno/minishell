#include "minishell.h"

int	char_flag(char c)
{
	if (c == '"' || c == '\'' || c == '\2')
		return (1);
	return (0);
}

char	*str_noquote(char *str)
{
	int		i;
	int		j;
	int		f;
	char	*new_str;

	i = -1;
	j = 0;
	f = 0;
	new_str = ft_calloc(ft_strlen(str) + 1, 1);
	if (!new_str)
		return (NULL);
	while (str[++i])
	{
		if (char_flag(str[i]) && (!f || f == str[i]))
		{
			f = str[i] * (f == '\0');
			continue ;
		}
		if ((str[i] == '"' && f != '\'' && f != '\2' && str[i - 1] != '\\')
			|| (str[i] == '\'' && f != '"' && f != '\2' && str[i - 1] != '\\'))
			continue ;
		i += (str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '"'));
		new_str[j++] = str[i];
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
		new_args[i] = str_noquote(args[i]);
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

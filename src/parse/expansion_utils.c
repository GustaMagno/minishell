#include "minishell.h"
#include "map.h"

void	split_words(char *arg, char **new_args, int *j)
{
	char	**split_arg;
	int		i;
	int		k;

	i = 0;
	k = *j;
	split_arg = ft_split(arg, ' ');
	if (!split_arg)
		return ;
	while (split_arg[i])
		new_args[k++] = ft_strdup(split_arg[i++]);
	*j = k;
	free_split(split_arg);
}

int	count_new_split(char **cmd_args)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (cmd_args[i])
	{
		count += count_words(cmd_args[i], ' ');
		if (!count_words(cmd_args[i], ' '))
			count++;
		i++;
	}
	return (count);
}

int	out_quotes(char *arg)
{
	int		i;
	char	in_quote;

	i = 0;
	in_quote = 0;
	while (arg[i])
	{
		if ((arg[i] == '"') && (!in_quote || in_quote == arg[i]))
			in_quote = arg[i] * (in_quote == 0);
		if (arg[i] == ' ' && !in_quote)
			return (1);
		i++;
	}
	return (0);
}

int	remove_null_node(t_cmd *cmd)
{
	t_cmd	*node;

	node = cmd;
	if (cmd->redir && *(cmd->redir->args))
		return (1);
	if (!*(node->args) || !node->args[0][0])
		return (0);
	while (node)
	{
		if (!node->args[0][0])
		{
			remove_node(&cmd, node);
			node = cmd;
			continue ;
		}
		node = node->next;
	}
	return (1);
}

char	*set_expansion(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = ft_calloc(ft_strlen(str) + 3, 1);
	if (!str)
		return (NULL);
	new_str[0] = '\2';
	new_str[ft_strlen(str) + 1] = '\2';
	i = 0;
	j = 1;
	while (str[i])
		new_str[j++] = str[i++];
	return (new_str);
}

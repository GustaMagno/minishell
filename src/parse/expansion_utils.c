#include "minishell.h"
#include "map.h"

int	count_new_split(char **cmd_args)
{
	int count;
	int i;

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
int		out_quotes(char *arg)
{
	int		i;
	int		in_quote;

	i = 0;
	in_quote = 0;
	while (arg[i])
	{
		if (arg[i] == '"')
			in_quote = (in_quote == 0);
		if (arg[i] == ' ' && !in_quote)
			return (1);
		i++;
	}
	return (0);
}

int remove_null_node(t_cmd *cmd)
{
	t_cmd	*node;

	node = cmd;
	if (!*(node->args) || !node->args[0][0])
		return (free_structs(cmd), 0);
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

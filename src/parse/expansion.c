#include "minishell.h"
#include "map.h"

char	**new_split(char **cmd_args)
{
	char	**new_args;
	char	**temp;
	int		i;
	int		j;

	new_args = ft_calloc(count_new_split(cmd_args) + 1, sizeof(char *));
	if (!new_args)
		return (free_split(cmd_args), NULL);
	i = 0;
	j = 0;
	while (cmd_args[i])
	{
		if (out_quotes(cmd_args[i]))
			split_words(cmd_args[i], new_args, &j);
		else if (cmd_args[i][0])
			new_args[j++] = ft_strdup(cmd_args[i]);
		i++;
	}
	return (free_split(cmd_args), new_args);
}


static int replace(char **str, int start, int end, t_map *env)
{
	char	*str_value = NULL;
	char	*replaced;
	char	*key;
	char	*temp_str;
	char	*value;

	key = ft_substr(*str, start, end - start);
	if (!key)
		return (start);
	if (env->get(env, key + 1))
		value = set_expansion(env->get(env, key + 1));
	else
		value = ft_strdup("\0");
	(*str)[start] = '\0';
	str_value = ft_strjoin(*str, value);
	replaced = ft_strjoin(str_value, &(*str)[end]);
	(free(str_value), free(key));
	temp_str = *str;
	if (!replaced)
		return (free(value), start);
	*str = replaced;
	start += ft_strlen(value) - 1;
	(free(value), free(temp_str));
	return (start);
}
// -1 por causa da iteracao do expanded.

char	*expanded(char *str, t_map *env, int *flag)
{
	int		i;
	char	f;
	int		start;
	int		end;

	i = -1;
	start = 0;
	f = 0;
	if (!str)
		return (NULL);
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == '"') && (!f || f == str[i]))
			f = str[i] * (f == 0);
		if (str[i] == '$' && (!f || f == '"') && ++(*flag))
		{
			start = i;
			end = start + 1;
			while (str[end] != 32 && ft_charalpha(str, end))
				end++;
			i = replace(&str, start, end, env);
		}
	}
	return (str);
}

int	expansion(t_cmd *cmd, t_map *env)
{
	t_cmd	*node;
	int 	i;
	int		flag;

	node = cmd;
	while (node)
	{
		i = -1;
		flag = 0;
		while (node->args[++i])
		{
			node->args[i] = expanded(node->args[i], env, &flag);
			if (!node->args[i])
				return (0);
		}
		if (flag)
			node->args = new_split(node->args);
		if (!node->args)
			return (0);
		node = node->next;
	}
	if (!remove_null_node(cmd))
		return (0);
	return (1);
}

#include "minishell.h"
#include "map.h"

static int replace(char **str, int start, int end, t_map *env)
{
	char	*str_value = NULL;
	char	*replaced;
	char	*key;
	char	*value;

	key = ft_substr(*str, start, end - start);
	if (env->get(env, key + 1))
		value = env->get(env, key + 1);
	else
		value = "\0";
	(*str)[start] = '\0';
	str_value = ft_strjoin(*str, value);
	replaced = ft_strjoin(str_value, &(*str)[end]);
	free(str_value);
	free(key);
	*str = replaced;
	return (start + ft_strlen(value));
}
char	*expanded(char *str, t_map *env)
{
	int		i;
	char	f;
	char	*expanded;
	int		start;
	int		end;

	i = -1;
	start = 0;
	f = 0;
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == '"') && (!f || f == str[i]))
			f = str[i] * (f == 0);
		if (str[i] == '$' && (!f || f == '"'))
		{
			start = i;
			end = start;
			while (str[end] != 32 && str[end] != '"' && str[end] != '\'' && str[end])
				end++;
			i = replace(&str, start, end, env);
		}
	}
	return (str);
}

int	expansion(t_cmd *cmd, t_map *env)
{
	t_cmd	*head;
	char	**new_args;
	int 	i;

	head = cmd;
	while (head)
	{
		i = -1;
		while (head->args[++i])
			head->args[i] = expanded(head->args[i], env);
		head = head->next;
	}
	return (1);
}
// " tes $PWD.TES e viado"
// char *key=PWD
// int		start=6
// int		end=9

// char *satrt = " tes "
// char *end= ".TES e viado"
// t = jo(star, value);
//  value = jo(t, end);
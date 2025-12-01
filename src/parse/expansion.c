#include "minishell.h"
#include "map.h"

int finding_arg(char **cmd_args, t_map *env)
{
	int		i;
	int		j;

	i = 0;
	while (cmd_args[i])
	{
		j = 0;
		while (cmd_args[i][j])
		{
			if (cmd_args[i][j] == '$' && cmd_args[i][j + 1]);
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}


int set_args(char **expand, char **new_args, int *j)
{
	int j_cpy;
	int i;

	j_cpy = *j;
	i = 0;
	while (expand[i])
	{
		new_args[j_cpy++] = ft_strdup(expand[i++]);
		if (!new_args[j_cpy - 1])
			return (0);
	}
	*j = j_cpy;
	return (1);
}

char	**expanded_args(char **cmd_args, t_map *env)
{
	char	**expand;
	char	**new_args;
	int		i;
	int		j;

	new_args = calloc(count_args(cmd_args, env), sizeof(char *));
	if (!new_args)
		return (NULL);
	i = 0;
	j = 0;
	while(cmd_args[i])
	{
		if (env->get(env, cmd_args[i] + 1))
		{
			expand = ft_split(env->get(env, cmd_args[i] + 1), ' ');
			if (!expand || !set_args(expand, new_args, &j))
				return (NULL);
			i++;
			continue ;
		}
		new_args[j++] = cmd_args[i++];
	}
	return (new_args);
}


int	expansion(t_cmd *cmd, t_map *env)
{
	t_cmd	*head;

	head = cmd;
	while (head)
	{
		if (finding_arg(head->args, env))
			head->args = expanded_args(head->args, env);
		head = head->next;
	}
	return (1);
}

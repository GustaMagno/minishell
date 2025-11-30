#include "minishell.h"
#include "map.h"

int	find_var(char *args)
{
	if (args[0] == '$')
		return (1);
	return (0);
}

int	count_args(char **cmd_args, t_map *env, int i_var)
{
	int i;
	int count;

	i = 0;
	while (cmd_args[i])
	{
		if (i == i_var)
			count += count_words(env->get(env, cmd_args[i++] + 1), ' ');
		else
			i++;
	}
	count += i;
	return (count);
}

int set_var_in_args(char **cmd_args, char **new_args, t_map *env, int i_var)
{
	char	**expand;
	int		i;

	expand = ft_split(env->get(env, cmd_args[i_var++] + 1), ' ');
	if (!expand)
		return (NULL);
}

// char	**expand_args(char **cmd_args, t_map *env)
// {
// 	char	**new_args;
// 	int		i;
// 	int 	j;

// 	i = 0;
// 	j = 0;
// 	new_args = calloc(count_args(cmd_args, env), sizeof(char *));
// 	if (!new_args)
// 		return (NULL);
// 	while (cmd_args[i])
// 	{
// 		if (find_var(cmd_args[i]))
// 		{
// 			if (!set_var_in_args(cmd_args, new_args, env))
// 				return (NULL);
// 		}
// 	}
// }


int	expansion(t_cmd *cmd, t_map *env)
{
	t_cmd	*head;

	head = cmd;
	while (head)
	{
		// cmd->args = expand_args(cmd->args, env);
		head = head->next;
	}
	return (1);
}

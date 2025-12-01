#include "minishell.h"

int	count_args(char **cmd_args, t_map *env)
{
	int i;
	int count;

	i = 0;
	while (cmd_args[i])
	{
		if (env->get(env, cmd_args[i] + 1))
			count += count_words(env->get(env, cmd_args[i] + 1), ' ');
		i++;
	}
	count += i;
	return (count);
}


int	ft_argslen(char **args)
{
	int i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
		i++;
	return (i);
}

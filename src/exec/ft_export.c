#include "minishell.h"

void	order_export(char **my_export)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (my_export[i])
	{
		j = i + 1;
		while (my_export[j])
		{
			if (ft_strcmp(my_export[i], my_export[j]) > 0)
			{
				temp = my_export[i];
				my_export[i] = my_export[j];
				my_export[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_export(t_map *env)
{
	char	**my_export;
	int		i;
	int		j;

	i = -1;
	my_export = env->to_str(env);
	order_export(my_export);
	while (my_export[++i])
	{
		j = 0;
		write(1, "declare -x ", 12);
		while (my_export[i][j] && my_export[i][j] != '=')
				write(1, &my_export[i][j++], 1);
		if (my_export[i][j + 1] == '\2' && write(1, "\n", 1))
			continue ;
		write(1, &my_export[i][j++], 1);
		write(1, "\"", 1);
		while (my_export[i][j] && my_export[i][j] != '=')
				write(1, &my_export[i][j++], 1);
		write(1, "\"", 1);
		write(1, "\n", 1);
	}
	free_split(my_export);
}

int	export_str(char *str, t_map *env)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	if (!str[i] && ft_stralpha(str) && !env->get(env, str))
		return (env->put(env, ft_strdup(str), ft_strdup("\2")), 1);
	key = ft_substr(str, 0, i);
	if (!key)
		return (0);
	if (!ft_stralpha(key) || str[0] == '=')
		return (write(2, "bash: export: not a valid identifier\n", 37), free(key), 1);
	value = ft_substr(str, i + 1, ft_strlen(str + i));
	if (!value)
		return (free(key), 0);
	if (str[i] != '=')
		return (free(key), free(value), 1);
	env->put(env, key, value);
	return (1);
}

void	ft_export(t_map *env, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->args[i])
	{
		if (!export_str(cmd->args[i++], env))
			return ;
	}
	if (i == 1)
		print_export(env);
}

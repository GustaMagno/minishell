#include "minishell.h"

void	print_export(t_map *env)
{
	char	**my_export;
	int		i;
	int		j;

	i = -1;
	my_export = env->to_str(env);
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
	if (!str[i])
		return (env->put(env, ft_strdup(str), ft_strdup("\2")), 1);
	key = ft_substr(str, 0, i);
	if (!key)
		return (0);
	value = ft_substr(str, i + 1, ft_strlen(str + i));
	if (!value)
		return (0);
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

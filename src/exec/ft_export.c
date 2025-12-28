#include "minishell.h"

void	print_export(t_map *env)
{
	char	**my_export;
	int		i;

	my_export = env->to_str(env);
	while (my_export[i])
	{
		printf("declare -x %s\n", my_export[i]);
		i++;
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
	if (!str[i] || !str[i + 1])
		return (1);
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

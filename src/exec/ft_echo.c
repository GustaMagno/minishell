#include "minishell.h"

int	is_flag(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (!(ft_strncmp(args[i], "-n", 2)))
	{
		j = 1;
		while (args[i][0] == '-' && args[i][j] == 'n')
			j++;
		if (args[i][j])
			break ;
		i++;
	}
	return (i);
}

void	ft_echo(t_cmd *cmd, t_map *env)
{
	int	i;

	if (!cmd->args[1])
		return ((void)printf("\n"));
	i = is_flag(cmd->args);
	if (!cmd->args[i])
		return ;
	while (cmd->args[i + 1])
	{
		printf("%s ", cmd->args[i]);
		i++;
	}
	printf("%s", cmd->args[i]);
	if (is_flag(cmd->args) == 1)
		printf("\n");
}

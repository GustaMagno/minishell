
#include "minishell.h"

int	is_flag(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i] && !(ft_strncmp(args[i], "-n", 2)))
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
		return ((void)write(1, "\n", 1));
	i = is_flag(cmd->args);
	if (!cmd->args[i])
		return ;
	// signal(SIGPIPE, SIG_IGN);
	while (cmd->args[i + 1])
	{
		write(1, cmd->args[i], ft_strlen(cmd->args[i]));
		write(1, " ", 1);
		i++;
	}
	write(1, cmd->args[i], ft_strlen(cmd->args[i]));
	if (is_flag(cmd->args) == 1)
		write(1, "\n", 1);
	ex_code(env, "0");
	// signal(SIGPIPE, SIG_DFL);
}

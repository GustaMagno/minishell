#include "minishell.h"

void	exec(t_cmd	*cmd, t_map *env)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ft_pwd(env);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		print_env(env);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		exec_cd(env, cmd);
	else
		ft_external(cmd, env);
}

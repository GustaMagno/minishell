#include "minishell.h"

void	status_and_end(t_map *env, t_cmd *cmd, long long exit_status, char *msg)
{
	env->put(env, ft_strdup("?"), ft_itoa(exit_status));
	env->destroy(env);
	free_structs(cmd);
	return (printf("exit\n%s", msg), exit(exit_status));
}

void	ft_exit(t_map *env, t_cmd *cmd)
{
	if (!cmd->args[1])
	{
		status_and_end(env, cmd, 0, "");
	}
	if (ft_strisnum(cmd->args[1]))
	{
		status_and_end(env, cmd, ft_atoi(cmd->args[1]), "");
	}
	else
	{
		status_and_end(env, cmd, 127, "bash: exit: numeric argument required\n");
	}
}

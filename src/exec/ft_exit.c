#include "minishell.h"


int		exceed_limits(char	*str)
{
	unsigned long long	nb;
	int					negative;

	negative = 0;
	if (str[0] == '-' && str++)
		negative++;
	nb = ft_atoull(str);
	if (negative && nb > 9223372036854775808)
		return (1);
	else if (!negative && nb > 9223372036854775807)
		return (1);
	return (0);
}

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
	if (!ft_strisnum(cmd->args[1]) || (ft_strisnum(cmd->args[1]) && exceed_limits(cmd->args[1])))
	{
		status_and_end(env, cmd, 127, "bash: exit: numeric argument required\n");
	}
	else if (cmd->args[2])
	{
		printf("exit\nbash: exit: too many argument\n");
		env->put(env, ft_strdup("?"), ft_strdup("1"));
	}
	else
		status_and_end(env, cmd, ft_atoll(cmd->args[1]), "");
}

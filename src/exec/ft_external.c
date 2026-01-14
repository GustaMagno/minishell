
#include "minishell.h"

void	exec_external(t_cmd *cmd, t_map *env, char *exec_path)
{
	char	**my_env;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		stat_check(exec_path);
		my_env = env->to_str(env);
		execve(exec_path, cmd->args, my_env);
		perror("execve");
		free_split(my_env);
		exit(127);
	}
	else
		wait(NULL);
}

void	ft_external(t_cmd *cmd, t_map *env)
{
	char	*exec_path;
	int		i;
	char	**abs_path;

	if (ft_strchr(cmd->args[0], '/'))
	{
		exec_external(cmd, env, cmd->args[0]);
		return ;
	}
	i = 0;
	abs_path = ft_split(env->get(env, "PATH"), ':');
	while (abs_path && abs_path[i])
	{
		exec_path = ft_pathjoin(abs_path[i], cmd->args[0]);
		if (access(exec_path, X_OK) == 0)
			break ;
		free(exec_path);
		exec_path == NULL;
		i++;
	}
	free_split(abs_path);
	access_check(cmd, env, exec_path);
}

void access_check(t_cmd *cmd, t_map *env, char *exec_path)
{
	if (access(exec_path, X_OK) != 0)
	{
		write(2, "minishell: command not found: ", 31);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, "\n", 1);
		return ;
	}
	// free(cmd->args[0]);
	cmd->args[0] = exec_path;
	exec_external(cmd, env, exec_path);
}

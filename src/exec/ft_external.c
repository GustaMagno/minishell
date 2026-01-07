
#include "minishell.h"

void	exec_external(t_cmd *cmd, t_map *env, char *exec_path)
{
	char	**my_env;
	pid_t	pid;

	pid = fork();
	my_env = env->to_str(env);
	if (pid == 0)
	{
		// if (is_directory(exec_path))
		// {
		// 	printf("minishell: %s: Is a directory\n", exec_path);
		// 	exit(127);
		// }
		execve(exec_path, cmd->args, my_env);
		perror("execve");
		exit(127);
	}
	else
		wait(NULL);
	free_split(my_env);
}

void	ft_external(t_cmd *cmd, t_map *env)
{
	char	*exec_path;
	int		i;
	char	**abs_path;

	i = 0;
	abs_path = ft_split(env->get(env, "PATH"), ':');
	while (abs_path[i])
	{
		if (access(cmd->args[0], X_OK) == 0)
		{
			exec_path = ft_strdup(cmd->args[0]);
			break ;
		}
		exec_path = ft_pathjoin(abs_path[i], cmd->args[0]);
		if (access(exec_path, X_OK) == 0)
			break ;
		free(exec_path);
		i++;
	}
	access_check(cmd, env, exec_path);
	free_split(abs_path);
}

void access_check(t_cmd *cmd, t_map *env, char *exec_path)
{
	if (access(exec_path, X_OK) != 0)
	{
		printf("minishell: command not found: %s\n", cmd->args[0]);
		return ;
	}
	else
	{
		free(cmd->args[0]);
		cmd->args[0] = exec_path;
		exec_external(cmd, env, exec_path);
	}
}

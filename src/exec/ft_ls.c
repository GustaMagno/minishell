
#include "minishell.h"

void	exec_ls(t_map *env, char *exec_path, t_cmd *cmd)
{
	char	**my_env;
	__pid_t	pid;

	pid = fork();
	my_env = env->to_str(env);
	if (pid == 0)
	{
		execve(exec_path, cmd->args, my_env);
		perror("execve");
		exit(1);
	}
	else
		wait(NULL);
}

void	ft_ls(t_cmd *cmd, t_map *env)
{
	char	*exec_path;
	t_path	*path;
	t_path	*tmp;

	path = NULL;
	fill_path(env, &path);
	tmp = path;
	while (tmp)
	{
		exec_path = ft_pathjoin(tmp->path, cmd->args[0]);
		if (access(exec_path, X_OK) == 0)
			break ;
		free(exec_path);
		tmp = tmp->next;
	}
	if (!exec_path)
	{
		printf("%s: command not found\n", cmd->args[0]);
		return ;
	}
	cmd->args[0] = exec_path;
	exec_ls(env, exec_path, cmd);
}

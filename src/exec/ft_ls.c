
#include "minishell.h"

void	exec_ls(t_all *all, char *exec_path)
{
	char	**my_env;
	__pid_t	pid;

	pid = fork();
	my_env = all->env->to_str(all->env);
	if (pid == 0)
	{
		execve(exec_path, all->cmd->args, my_env);
		perror("execve");
		exit(1);
	}
	else
		wait(NULL);
	free_split(my_env);
}

void	ft_ls(t_all *all)
{
	char	*exec_path;
	t_path	*path;
	t_path	*tmp;

	path = NULL;
	fill_path(all->env, &path);
	tmp = path;
	while (tmp)
	{
		exec_path = ft_pathjoin(tmp->path, all->cmd->args[0]);
		if (access(exec_path, X_OK) == 0)
			break ;
		free(exec_path);
		tmp = tmp->next;
	}
	if (!exec_path)
	{
		printf("%s: command not found\n", all->cmd->args[0]);
		all->env->destroy(all->env);
		free_all(NULL, &path, NULL);
	}
	all->cmd->args[0] = exec_path;
	exec_ls(all, exec_path);
	free(exec_path);
	free_path(&path);
}

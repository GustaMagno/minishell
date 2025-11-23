#include "minishell.h"


void	fill_path(t_map *env, t_path **path)
{
	char	**abs_path;
	t_path	*node;
	int		i;

	i = 0;
	node = NULL;
	abs_path = ft_split(env->get(env, "PATH"), ':');
	while (abs_path[i])
	{
		node = ft_lstnew(abs_path[i]);
		if (!node)
			exit (0);
		ft_lstadd_back(path, node);
		i++;
	}
}
void	exec(t_cmd	*cmd, t_map *env)
{
	char	*exec_path;
	char	**my_env;
	t_path	*path;
	t_path	*tmp;
	__pid_t	pid;

	pid = fork();
	path = NULL;
	fill_path(env, &path);
	tmp = path;
	my_env = env->to_str(env);
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
	if (pid == 0)
	{
		//function can be return -1, or -l
		execve(exec_path, cmd->args, my_env);
		perror("execve");
		exit(1);
	}
	else
	{
		wait(NULL);
	}
}


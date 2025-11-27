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
			free_all(abs_path, path, NULL);
		ft_lstadd_back(path, node);
		i++;
	}
	free_split(abs_path);
}

void	exec(t_cmd	*cmd, t_map *env)
{
	t_all	*all;

	all = malloc(sizeof(t_all));
	init_all(all, cmd, env);
	if (ft_strcmp(all->cmd->args[0], "ls") == 0)
		ft_ls(all);
	else if (ft_strcmp(all->cmd->args[0], "echo") == 0)
		ft_echo(all);
	else if (ft_strcmp(all->cmd->args[0], "pwd") == 0)
		ft_pwd(all);
	else if (ft_strcmp(all->cmd->args[0], "env") == 0)
		print_env(all);
	else if (ft_strcmp(all->cmd->args[0], "cd") == 0)
		exec_cd(all);
}

void	init_all(t_all *all, t_cmd *cmd, t_map *env)
{
	all->cmd = cmd;
	all->env = env;
	all->path = NULL;
}

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
	if (ft_strcmp(cmd->args[0], "ls") == 0)
		ft_ls(cmd, env);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd);
}


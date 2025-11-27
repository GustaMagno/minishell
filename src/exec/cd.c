
#include "minishell.h"

void	exec_cd(t_all *all)
{
	char	*cd;
	char	*tmp;

	tmp = ft_strdup(all->env->get(all->env, "PWD"));
	cd = cd_list(all);
	all->env->put(all->env, "OLDPWD", tmp);
	if (chdir(cd) != 0)
		perror("cd");
	all->env->put(all->env, "PWD", getcwd(NULL, 0));
	free (cd);
	
}

char	*cd_list(t_all *all)
{
	char	*cd;
	char	*home;

	home = all->env->get(all->env, "HOME");
	if (ft_argslen(all->cmd->args) == 1)
		cd = ft_strdup(home);
	else if (ft_strcmp(all->cmd->args[1], "--") == 0)
		cd = ft_strdup(all->env->get(all->env, "OLDPWD"));
	else
		cd = ft_strdup(all->cmd->args[1]);
	return (cd);
	
}
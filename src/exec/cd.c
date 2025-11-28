
#include "minishell.h"

void	exec_cd(t_map *env, t_cmd *cmd)
{
	char	*cd;
	char	*tmp;

	tmp = ft_strdup(env->get(env, "PWD"));
	cd = cd_list(env, cmd);
	env->put(env, "OLDPWD", tmp);
	if (chdir(cd) != 0)
		perror("cd");
	env->put(env, "PWD", getcwd(NULL, 0));
	free (cd);
	
}

char	*cd_list(t_map *env, t_cmd *cmd)
{
	char	*cd;
	char	*home;

	home = env->get(env, "HOME");
	if (ft_argslen(cmd->args) == 1)
		cd = ft_strdup(home);
	else if (ft_strcmp(cmd->args[1], "--") == 0)
		cd = ft_strdup(env->get(env, "OLDPWD"));
	else
		cd = ft_strdup(cmd->args[1]);
	return (cd);
	
}

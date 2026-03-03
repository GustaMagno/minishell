
#include "minishell.h"

void	exec_cd(t_map *env, t_cmd *cmd)
{
	char	*cd;
	char	*tmp;
	char	*pwd;

	tmp = ft_strdup(env->get(env, "PWD"));
	cd = cd_list(env, cmd);
	env->put(env, ft_strdup("OLDPWD"), tmp);
	if (!is_directory(cd))
	{
		write(2, "minishell: cd: ", 16);
		write(2, cd, ft_strlen(cd));
		write(2, ": Not a directory\n", 19);
		ex_code(env, "1");
		free(cd);
		return ;
	}
	if (chdir(cd) != 0)
		(perror("cd"), ex_code(env, "1"));
	else
		ex_code(env, "0");
	if ((pwd = getcwd(NULL, 0)))
		env->put(env, ft_strdup("PWD"), pwd);
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


#include "minishell.h"

void	ft_pwd(t_all *all)
{
	char	*pwd;

	pwd = all->env->get(all->env, "PWD");
	if (pwd)
		printf("%s\n", pwd);
	else
		perror("getcwd");
}

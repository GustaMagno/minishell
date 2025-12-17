
#include "minishell.h"

void	ft_pwd(t_map *env)
{
	char	*pwd;

	pwd = env->get(env, "PWD");
	if (pwd)
		printf("%s\n", pwd);
	else
		perror("getcwd");
}

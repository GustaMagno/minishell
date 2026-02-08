
#include "minishell.h"

void	ft_pwd(t_map *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = env->get(env, "PWD");
	if (pwd)
		printf("%s\n", pwd);
	else
		write(2, "pwd: error retrieving current directory: \
                getcwd: cannot access parent directories:", 99);
}

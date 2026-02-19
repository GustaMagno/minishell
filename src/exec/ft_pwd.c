
#include "minishell.h"

void	ft_pwd(t_map *env)
{
	char	*pwd;
	int		check;

	check = 1;
	pwd = getcwd(NULL, 0);
	if (!pwd && check--)
		pwd = env->get(env, "PWD");
	if (pwd)
		printf("%s\n", pwd);
	else
		write(2, "pwd: error retrieving current directory: \
                getcwd: cannot access parent directories:", 99);
	if (check)
		free(pwd);
}

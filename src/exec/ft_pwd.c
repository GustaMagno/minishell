
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
	{
		write(2, "pwd: error retrieving current directory: \
			getcwd: cannot access parent directories:", 100);
		env->put(env, ft_strdup("?"), ft_strdup("ERROR"));
	}
	if (ft_strcmp(env->get(env, "?"), "ERROR"))
		env->put(env, ft_strdup("?"), ft_strdup("1"));
	else
		env->put(env, ft_strdup("?"), ft_strdup("0"));
	free(pwd);
}

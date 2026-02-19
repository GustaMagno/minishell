#include "minishell.h"

void	ex_code(t_map *env, char *str)
{
	env->put(env, ft_strdup("?"), ft_strdup(str));
}

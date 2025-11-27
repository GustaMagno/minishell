#include "minishell.h"

static void run(t_map *env)
{
	char	*line;

	while (1)
	{
		line = readline("minishel: ");
		if (!line || !ft_strncmp(line, "exit", 5))
		{
			env->destroy(env);
			exit (1);
		}
		if (!syntax_error(line))
			continue ;
		parsing(line, env);
	}
}

int main(int argv, char **argc, char **envp)
{
	t_map	*env;

	(void) argc;
	(void) argv;
	env = new_map();
	create_env(env, envp);
	run(env);
}


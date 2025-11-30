#include "minishell.h"

static void run(t_map *env)
{
	char *line;
	t_cmd	*cmd;

	while (1)
	{
		line = readline("minishel: ");
		if (!line)
			break;
		cmd = parsing(line, env);
		if (!cmd) 
			continue;
		print_cmd(cmd);
		// exec(cmd, env);
		free_structs(cmd);
	}
	env->destroy(env);
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

#include "minishell.h"

int	g_signal = 0;

t_map	*adress_env(t_map *env)
{
	static t_map	*copy;

	if (env)
		copy = env;
	return (copy);
}


void	run(t_map *env)
{
	char *line;
	t_cmd	*cmd;

	while (1)
	{
		signal(SIGINT, handler_C);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell: ");
		if (!line)
			break;
		cmd = parsing(line, env);
		if (!cmd) 
			continue;
		print_cmd(cmd);
		exec(cmd, env);
		free_structs(cmd);
	}
}

int main(int argv, char **argc, char **envp)
{
	t_map	*env;

	(void) argc;
	(void) argv;
	env = new_map();
	if (!env)
		return (1);
	create_env(env, envp);
	adress_env(env);
	run(env);
	env->destroy(env);
}


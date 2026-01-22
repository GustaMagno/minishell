#include "minishell.h"

// t_map	*adress_env()
// {
// 	static t_map	*env;
// 	static int		i = 0;

// 	if (i == 0)
// 	{
// 		env = new_map();
// 		if (!env)
// 			return (NULL);
// 		i++;
// 	}
// }

void	handler_C(int signal)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	run(t_map *env)
{
	char *line;
	t_cmd	*cmd;

	signal(SIGINT, handler_C);
	while (1)
	{
		line = readline("minishell: ");
		if (!line)
			break;
		cmd = parsing(line, env);
		if (!cmd) 
			continue;
		// print_cmd(cmd);
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
	run(env);
	env->destroy(env);
}


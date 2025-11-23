#include "minishell.h"

static void run()
{
	char *line;

	while (1)
	{
		line = readline("minishel: ");
		if (!line)
			return ;
		if (!syntax_error(line))
			continue ;
		parsing(line);
	}
}

int main(int argv, char **argc, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;
	run();
}

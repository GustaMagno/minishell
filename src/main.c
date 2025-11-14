#include "minishell.h"

static void run()
{
	char *line;

	while (1)
	{
		line = readline("minishel: ");
		if (!line)
			return ;
		parsing(line);
	}
}

void	test_exec()
{
	t_cmd	*cmd;

	cmd = new_cmd(ft_split("ls", ' '));
	cmd->next = new_cmd(ft_split("cat", ' '));
	cmd->next->next = new_cmd(ft_split("wc", ' '));
	exec(cmd);
}

int main(int argv, char **argc, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;
	run();
	//test_exec();
}

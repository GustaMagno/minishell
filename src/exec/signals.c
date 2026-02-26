#include "minishell.h"


void	heredoc_handler(int signal)
{
	int	save_stdin;

	if (signal == SIGINT)
		close(STDIN_FILENO);
}

void	set_heredoc_sig(void)
{
	signal(SIGINT, heredoc_handler);
	signal(SIGQUIT, heredoc_handler);
}

void	set_child_sig(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	handler_C(int signal)
{
	write(1, "\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}
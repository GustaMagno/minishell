#include "minishell.h"

void	heredoc_handler(int signal)
{
	t_map	*env;

	env = adress_env(NULL);
	if (signal == SIGINT)
	{
		close(STDIN_FILENO);
		g_signal = SIGINT;
		env->put(env, ft_strdup("?"), ft_strdup("130"));
	}
	else if (signal == SIGQUIT)
		env->put(env, ft_strdup("?"), ft_strdup("131"));
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

void	set_ign_sig(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handler_C(int signal)
{
	t_map	*env;

	env = adress_env(NULL);
	ex_code(env, "130");
	write(1, "\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

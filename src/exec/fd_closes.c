#include "minishell.h"

void	close_pipes(int **fd_pipes, int t_pipes)
{
	int	i;

	i = 0;
	while (i < t_pipes)
	{
		close(fd_pipes[i][0]);
		close(fd_pipes[i][1]);
		i++;
	}
}

void	close_parent_pipes(int **fd_pipes, int i)
{
	if (i > 0)
	{
		close(fd_pipes[i - 1][0]);
		close(fd_pipes[i - 1][1]);
	}
}

void	close_heredoc_fds(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*redir;

	tmp = cmd;
	while (tmp)
	{
		redir = tmp->redir;
		while (redir)
		{
			if (ft_strcmp(redir->args[0], "<<") == 0 && redir->fd != -1)
			{
				close(redir->fd);
				redir->fd = -1;
			}
			redir = redir->next;
		}
		tmp = tmp->next;
	}
}

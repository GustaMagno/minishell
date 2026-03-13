/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:53:08 by matmagal          #+#    #+#             */
/*   Updated: 2026/03/13 18:14:06 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	stdin_1(char *input)
{
	int	fd;

	fd = open(input, O_RDONLY);
	if (fd == -1)
		return (write(2, "minishell: ", 11), perror(input), 0);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	stdout_1(char *output)
{
	int	fd;

	fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (write(2, "minishell: ", 11), perror(output), 0);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	stdout_2(char *output)
{
	int	fd;

	fd = open(output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (write(2, "minishell: ", 11), perror(output), 0);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

void	exec_heredoc(t_cmd *cmd, t_map *env)
{
	t_cmd	*tmp;
	t_redir	*redir;

	tmp = cmd;
	while (tmp)
	{
		redir = tmp->redir;
		while (redir)
		{
			g_signal = 0;
			if (ft_strcmp(redir->args[0], "<<") == 0 && redir->fd == -1)
			{
				redir->fd = heredoc(ft_strjoin(redir->args[1], "\n"), env);
				if (redir->fd == -1)
					return ;
			}
			redir = redir->next;
		}
		tmp = tmp->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:52:36 by matmagal          #+#    #+#             */
/*   Updated: 2026/03/13 15:52:37 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_tmp(char *path)
{
	int	fd;

	fd = open(path, O_CREAT | O_EXCL | O_RDWR, 0600);
	return (fd);
}

static char	*build_tmp_name(int counter)
{
	char	*pid;
	char	*cnt;
	char	*tmp;
	char	*tmp2;

	pid = ft_itoa(getpid());
	cnt = ft_itoa(counter);
	if (!pid || !cnt)
		return (free(pid), free(cnt), NULL);
	tmp = ft_strjoin("/tmp/minishell_heredoc_", pid);
	if (!tmp)
		return (free(pid), free(cnt), NULL);
	tmp2 = ft_strjoin(tmp, "_");
	free(tmp);
	if (!tmp2)
		return (free(pid), free(cnt), NULL);
	tmp = ft_strjoin(tmp2, cnt);
	return (free(tmp2), free(pid), free(cnt), tmp);
}

int	create_temp(char *tmp, size_t size)
{
	int		counter;
	int		fd;
	char	*tmp_name;

	counter = 0;
	while (counter < 1000)
	{
		tmp_name = build_tmp_name(counter);
		if (!tmp_name || ft_strlen(tmp_name) + 1 > size)
			return (free(tmp_name), -1);
		ft_strlcpy(tmp, tmp_name, size);
		free(tmp_name);
		fd = open_tmp(tmp);
		if (fd >= 0)
			return (fd);
		counter++;
	}
	return (-1);
}

int	exec_redir(t_redir *redir)
{
	char	*temp;

	if (!redir->args[0] || !redir->args[1])
		return (1);
	if (ft_strcmp(redir->args[0], "<<") == 0 && redir->fd != -1)
	{
		dup2(redir->fd, STDIN_FILENO);
		close(redir->fd);
		redir->fd = -1;
	}
	temp = redir->args[1];
	redir->args[1] = str_noquote(redir->args[1]);
	free(temp);
	if (ft_strcmp(redir->args[0], "<") == 0)
		return (stdin_1(redir->args[1]));
	else if (ft_strcmp(redir->args[0], ">") == 0)
		return (stdout_1(redir->args[1]));
	else if (ft_strcmp(redir->args[0], ">>") == 0)
		return (stdout_2(redir->args[1]));
	return (1);
}

int	loop_redir(t_cmd *cmd)
{
	t_redir	*temp;

	temp = cmd->redir;
	while (temp)
	{
		if (!exec_redir(temp))
			return (0);
		temp = temp->next;
	}
	return (1);
}

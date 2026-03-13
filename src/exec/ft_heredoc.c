/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:52:59 by matmagal          #+#    #+#             */
/*   Updated: 2026/03/13 15:52:59 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*heredoc_loop(char *end, t_map *env)
{
	char	*line;
	char	*buffer;
	char	*end_no_quotes;

	end_no_quotes = no_quote(end);
	line = NULL;
	while (write(1, "> ", 2))
	{
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer && g_signal == SIGINT)
		{
			free(line);
			line = NULL;
		}
		if ((!buffer && write(1, "\n", 1))
			|| ft_strcmp(buffer, end_no_quotes) == 0)
			break ;
		line = ft_strjoinfree(line, buffer, line, buffer);
	}
	if (ft_strcmp(buffer, end_no_quotes) == 0)
		free(buffer);
	if (end_no_quotes != end)
		free(end_no_quotes);
	return (expanded_heredoc(line, end, env));
}

int	heredoc(char *end, t_map *env)
{
	char	tmp[256];
	int		fd;
	char	*line;
	int		save_stdin;

	save_stdin = dup(STDIN_FILENO);
	fd = create_temp(tmp, sizeof(tmp));
	if (fd == -1)
		return (close(save_stdin), free(end), -1);
	set_heredoc_sig();
	line = heredoc_loop(end, env);
	if (!g_signal && write(fd, line, ft_strlen(line)))
		free(line);
	dup2(save_stdin, STDIN_FILENO);
	close(fd);
	fd = open(tmp, O_RDONLY);
	unlink(tmp);
	signal(SIGINT, handler_c);
	signal(SIGINT, SIG_IGN);
	return (free(end), close(save_stdin), fd);
}

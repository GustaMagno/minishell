
#include "minishell.h"

void	stdin_1(char *input)
{
	int	fd;

	fd = open(input, O_RDONLY);
	if (fd == -1)
		return ;
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	stdout_1(char *output)
{
	int	fd;

	fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

int	heredoc(char *end)
{
	int		here_pipes[2];
	char	*line;
	char	*buffer;
	int		save_stdin;
	int 	check;

	line = NULL;
	check = 0;
	save_stdin = dup(STDIN_FILENO);
	if (pipe(here_pipes) == -1)
		return (-1);
	set_heredoc_sig();
	while (write(1, "> ", 2))
	{
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer && ++check && write(1, "\n", 1))
			free(line);
		if (!buffer || ft_strcmp(buffer, end) == 0)
			break ;
		line = ft_strjoinfree(line, buffer, line, buffer);
	}
	if (!check && write(here_pipes[1], line, ft_strlen(line)))
		(free(line), free(buffer));
	dup2(save_stdin, STDIN_FILENO);
	return (free(end), close(save_stdin), close(here_pipes[1]), here_pipes[0]);
}

void	stdout_2(char *output)
{
		int	fd;

	fd = open(output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return ;
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	exec_redir(t_cmd *cmd, t_redir *redir)
{
	if (!redir->args[0] || !redir->args[1])
		return ;
	if (ft_strcmp(redir->args[0], "<") == 0)
		stdin_1(redir->args[1]);
	else if (ft_strcmp(redir->args[0], ">") == 0)
		stdout_1(redir->args[1]);
	else if (ft_strcmp(redir->args[0], ">>") == 0)
		stdout_2(redir->args[1]);
	else if (ft_strcmp(redir->args[0], "<<") == 0 && redir->fd != -1)
		dup2(redir->fd, STDIN_FILENO);
}

void	loop_redir(t_cmd *cmd)
{
	t_redir	*temp;

	temp = cmd->redir;
	while (temp)
	{
		exec_redir(cmd, temp);
		temp = temp->next;
	}
}
void	exec_heredoc(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*redir;

	tmp = cmd;
	while(tmp)
	{
		redir = tmp->redir;
		while (redir)
		{
		if (ft_strcmp(redir->args[0], "<<") == 0 && redir->fd == -1)
				redir->fd = heredoc(ft_strjoin(redir->args[1], "\n"));
			redir = redir->next;
		}
		tmp = tmp->next;
	}
}

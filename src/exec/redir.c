
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
	int	here_pipes[2];
	char	*line;

	if (pipe(here_pipes) == -1)
		return (-1);
	while (1)
	{
		write(here_pipes[1], "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (strcmp(line, end) == 0)
		{
			free(line);
			break ;
		}
		write(here_pipes[1], line, ft_strlen(line));
		write(here_pipes[1], '\n', 1);
		free(line);
	}
	close(here_pipes[1]);
	return (here_pipes[0]);
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
	else if (ft_strcmp(redir->args[0], "<<") == 0)
	{
		redir->fd = heredoc(redir->args[1]);
		if (redir->fd != -1)
			dup2(redir->fd, STDIN_FILENO);
	}
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

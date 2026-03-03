
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
	char	tmp[256];
	char	*line;
	int		fd;

	fd = create_temp(tmp, sizeof(tmp));
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, end) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	fd = open(tmp, O_RDONLY);
	unlink(tmp);
	return (fd);
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
	{
		dup2(redir->fd, STDIN_FILENO);
		close(redir->fd);
		redir->fd = -1;
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
				redir->fd = heredoc(redir->args[1]);
			redir = redir->next;
		}
		tmp = tmp->next;
	}
}

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

static int	create_temp(char *tmp, size_t size)
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

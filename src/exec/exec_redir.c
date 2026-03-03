
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
char	*no_quote(char *end)
{
	char	*ssub;
	char	*sjoin;


	if (end[0] != '\'' && end[0] != '"')
		return (end);
	ssub = ft_substr(end, 1, ft_strlen(end) - 3);
	sjoin = ft_strjoin(ssub, "\n");
	free(ssub);
	return (sjoin);
}

int	modify_line(char **str, int start, int end, t_map *env)
{
	char	*key;
	char	*temp_str;
	char	*value;
	char	*result1;
	char	*result2;

	result1 = NULL;
	key = ft_substr(*str, start, end - start);
	if (!key)
		return (start);
	if (env->get(env, key + 1))
		value = set_expansion(env->get(env, key + 1));
	else
		value = ft_strdup("\0");
	(*str)[start] = '\0';
	result1 = ft_strjoin(*str, value);
	result2 = ft_strjoin(result1, &(*str)[end]);
	(free(key), free(result1));
	temp_str = *str;
	if (!result2)
		return (free(value), start);
	*str = result2;
	start += ft_strlen(value) - 1;
	(free(value), free(temp_str));
	return (start);
}

char	*expanded_heredoc(char *line, char flag, t_map *env)
{
	int	i;
	int	start;
	int	end;

	if (!line)
		return (NULL);
	if (flag == '\'' || flag == '"')
		return (line);
	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			start = i;
			end = start + 1;
			while (ft_charalpha(line, end))
				end++;
			i = modify_line(&line, start, end, env);
		}
	}
	return (line);
}

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
		if ((!buffer && write(1, "\n", 1)) || ft_strcmp(buffer, end_no_quotes) == 0)
			break ;
		line = ft_strjoinfree(line, buffer, line, buffer);
	}
	if (ft_strcmp(buffer, end_no_quotes) == 0)
		free(buffer);
	if (end_no_quotes != end)
		free(end_no_quotes);
	return (expanded_heredoc(line, end[0], env));
}

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

int	heredoc(char *end, t_map *env)
{
	char	tmp[256];
	int		fd;
	char	*line;
	int		save_stdin;

	save_stdin = dup(STDIN_FILENO);
	fd = create_temp(tmp, sizeof(tmp));
	if (fd == -1)
		return (-1);
	set_heredoc_sig();
	line = heredoc_loop(end, env);
	if (!g_signal && write(fd, line, ft_strlen(line)))
		free(line);
	dup2(save_stdin, STDIN_FILENO);
	close(fd);
	fd = open(tmp, O_RDONLY);
	unlink(tmp);
	return (free(end), close(save_stdin), fd);
}
void	exec_heredoc(t_cmd *cmd, t_map *env)
{
	t_cmd	*tmp;
	t_redir	*redir;

	tmp = cmd;
	while(tmp)
	{
		redir = tmp->redir;
		while (redir)
		{
			g_signal = 0;
			if (ft_strcmp(redir->args[0], "<<") == 0 && redir->fd == -1)
				redir->fd = heredoc(ft_strjoin(redir->args[1], "\n"), env);
			redir = redir->next;
		}
		tmp = tmp->next;
	}
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
	char	*temp;

	if (!redir->args[0] || !redir->args[1])
		return ;
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
		stdin_1(redir->args[1]);
	else if (ft_strcmp(redir->args[0], ">") == 0)
		stdout_1(redir->args[1]);
	else if (ft_strcmp(redir->args[0], ">>") == 0)
		stdout_2(redir->args[1]);
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


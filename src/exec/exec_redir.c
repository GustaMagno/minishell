
#include "minishell.h"

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

int	heredoc(char *end, t_map *env)
{
	int		here_pipes[2];
	char	*line;
	int		save_stdin;

	save_stdin = dup(STDIN_FILENO);
	if (pipe(here_pipes) == -1)
		return (-1);
	set_heredoc_sig();
	line = heredoc_loop(end, env);
	if (!g_signal && write(here_pipes[1], line, ft_strlen(line)))
		free(line);
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

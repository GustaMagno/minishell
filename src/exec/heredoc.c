#include "minishell.h"

static int	eof_quote(char *end)
{
	int i;

	i = 0;
	while (end[i])
	{
		if (end[i] == '\'' || end[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

char	*no_quote(char *end)
{
	char	*ssub;
	char	*sjoin;

	if (!eof_quote(end))
		return (end);
	ssub = str_noquote(end);
	return (ssub);
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

char	*expanded_heredoc(char *line, char *eof, t_map *env)
{
	int	i;
	int	start;
	int	end;

	if (!line)
		return (NULL);
	if (eof_quote(eof))
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
		return (-1);
	set_heredoc_sig();
	line = heredoc_loop(end, env);
	if (!g_signal && write(fd, line, ft_strlen(line)))
		free(line);
	dup2(save_stdin, STDIN_FILENO);
	close(fd);
	fd = open(tmp, O_RDONLY);
	unlink(tmp);
	signal(SIGINT, handler_C);
	signal(SIGINT, SIG_IGN);
	return (free(end), close(save_stdin), fd);
}


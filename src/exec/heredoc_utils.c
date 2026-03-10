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

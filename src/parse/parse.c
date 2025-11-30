#include "minishell.h"

static int	put_redir(char *line, char *new_line, size_t *i, size_t *j)
{
	size_t i1;
	size_t j1;

	i1 = *i;
	j1 = *j;
	if (line[i1] == '>' || line[i1] == '<')
	{
		new_line[j1++] = '\2';
		new_line[j1++] = line[i1++];
		if (line[*i] == line[i1])
			new_line[j1++] = line[i1++];
		new_line[j1++] = '\2';
		*i = i1;
		*j = j1;
		return (1);	
	}
	return (0);
}

static char	*transformate_line(char *line, char *new_line)
{
	size_t	i;
	size_t	j;
	char	f;

	i = 0;
	j = 0;
	f = 0;
	while (line[i])
	{
		if (f == line[i] || (!f && (line[i] == '\'' || line[i] == '\"')))
			f = line[i] * (f == '\0');
		if (!f && line[i] == '|')
			line[i] = '\3';
		else if (!f && line[i] == ' ')
			line[i] = '\2';
		else if (put_redir(line, new_line, &i, &j))
			continue;
		new_line[j++] = line[i++];
	}
	return (free(line), new_line);
}

t_cmd	*parsing(char *line, t_map *env)
{
	t_cmd	*cmd;

	cmd = NULL;
	add_history(line);
	line = transformate_line(line, ft_calloc(ft_strlen(line) * 3, 1));
	cmd = parsing_cmd(line);
	if (syntax_error(cmd, line))
		return (write(1, "bash: syntax error near unexpected token\n", 41), NULL);
	if (!parsing_redir(cmd))
		return (NULL);
	return (cmd);
}

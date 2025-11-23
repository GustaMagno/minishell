#include "minishell.h"

int	redir_cases(char *line, int i)
{
	int	check;

	check = 0;
	if (line[i] == '>' && ++i)
	{
		if (line[i] == '<')
			return (0);
		if (line[i] == '>' && line[i + 1] == '>')
			return (0);
		while (line[i] == 32 && ++check)
			i++;
		if (line[i] == '\0' || ((line[i] == '>' || line[i] == '<') && check))
			return (0);
	}
	if (line[i] == '<' && ++i)
	{
		if (line[i] == '<' && line[i + 1] == '<' && (line[i + 2] == '<' || line[i + 2] == '>'))
			return (0);
		while (line[i] == 32 && ++check)
			i++;
		if (line[i] == '\0' || ((line[i] == '>' || line[i] == '<') && check))
			return (0);
	}
	return (1);
}

int	cases_syntax(char *line, int i)
{
	if (line[i] != '|' && line[i] != '<' && line[i] != '>')
		return (1);
	if (!redir_cases(line , i))
		return (0);
	if (line[i] == '|' && ++i)
	{
		while (line[i] == 32)
			i++;
		if (line[i] == '\0' || line[i] == '|')
			return (0);
	}
	return (1);
}

int	syntax_error(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!cases_syntax(line, i))
			return (printf("bash: syntax error near unexpected token\n"), 0);
		i++;
	}
	return (1);
}

#include "minishell.h"

void	print_args(char **args)
{
	int i = 0;

	while (args[i])
	{
		printf("%s\n", args[i++]);
	}
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*node;

	node = cmd;
	while (node)
	{
		printf("NODE :\n");
		print_args(node->args);
		node = node->next;
	}
}

char	verify_char(char c, int in_quotes)
{
	if (c == ' ' && !in_quotes)
		return ('\2');
	if (c == '|' && !in_quotes)
		return ('\3');
	return (c);
}

char	*transformate_line(char *line)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			in_quotes = (in_quotes == 0);
		line[i] = verify_char(line[i], in_quotes);
		i++;
	}
	return (line);
}

t_cmd	*parsing(char *line)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = parsing_cmd(transformate_line(line));
	if (!cmd)
		return (NULL);
	redir = parsing_redir(cmd);
	print_cmd(cmd);
	return (cmd);
}
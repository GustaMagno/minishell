#include "minishell.h"

void	print_args(char **args, int flag)
{
	int i = 0;

	while (args[i])
	{
		if (flag)
			printf("CMD ");
		else
			printf("REDIR ");
		printf("%s\n", args[i++]);
	}
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*node;
	t_redir	*rnode;

	node = cmd;
	while (node)
	{
		rnode = node->redir;
		printf("NODE :\n\n");
		print_args(node->args, 1);
		while (rnode)
		{
			print_args(rnode->args, 0);
			rnode = rnode->next;
		}
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

int	parsing(char *line, t_map *env)
{
	t_cmd	*cmd;

	cmd = parsing_cmd(transformate_line(line));
	if (!cmd || !parsing_redir(cmd))
		return (0);
	// print_cmd(cmd);
	exec(cmd, env);
	free_structs(cmd);
	return (1);
}

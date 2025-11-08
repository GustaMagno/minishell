#include "minishell.h"

void	print_args(char **args)
{
	int i = 0;

	while (args[i])
	{
		printf("%s\n", args[i++]);
	}
}

char	verify_char(char c, int flag)
{
	if (c == ' ' && !flag)
		return ('\2');
	if (c == '|' && !flag)
		return ('\3');
	return (c);
}

void	transformate_line(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		printf("char antes %c ", line[i]);
		if (line[i] == '"' || line[i] == '\'')
			flag = (flag == 0);
		line[i] = verify_char(line[i], flag);
		printf("char depois %c\n", line[i]);
		i++;
	}
}

t_cmd	*parsing(char *line)
{
	char	**args;

	transformate_line(line);
	// print_args(args);
	return (NULL);
}
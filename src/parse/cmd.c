#include "minishell.h"

t_cmd	*new_cmd(char **args)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = args;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*parsing_cmd(char *line)
{
	char	**args;
	t_cmd	*cmd_head;
	t_cmd	*node;
	int		i;

	i = 0;
	args = ft_split(line, '\3');
	if (!*line || !args)
		return (NULL);
	cmd_head = new_cmd(ft_split(args[i++], '\2'));
	if (!cmd_head)
		return (NULL);
	node = cmd_head;
	while (args[i])
	{
		node->next = new_cmd(ft_split(args[i++], '\2'));
		if (!node->next)
			return (NULL);
		node = node->next;
	}
	free_split(args);
	return (cmd_head);
}

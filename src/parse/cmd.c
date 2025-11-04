#include "minishell.h"

t_cmd	*new_cmd(char **args)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(cmd));
	if (!cmd)
		return (NULL);
	cmd->args = args;
	cmd->next = NULL;
	return (cmd);
}
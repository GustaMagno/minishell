#include "minishell.h"

void	free_split(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_structs(t_cmd *cmd)
{
	t_cmd	*node;
	t_redir	*r_node;
	t_redir	*temp_r;
	t_cmd	*temp_c;

	node = cmd;
	while (node)
	{
		free_split(node->args);
		r_node = node->redir;
		while (r_node)
		{
			free(r_node->args[0]);
			free(r_node->args[1]);
			temp_r = r_node->next;
			free(r_node);
			r_node = temp_r;
		}
		// free(node->redir);
		temp_c = node->next;
		free(node);
		node = temp_c;
	}
}

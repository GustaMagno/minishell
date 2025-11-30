#include "minishell.h"

void	print_args(char **args, int flag)
{
	int i = 0;

	while (args[i])
	{
		if (flag)
			printf("  CMD ");
		else
			printf("  REDIR ");
		printf("	%s\n", args[i++]);
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
		printf("NODE :\n");
		print_args(node->args, 1);
		while (rnode)
		{
			print_args(rnode->args, 0);
			rnode = rnode->next;
		}
		printf("\n");
		node = node->next;
	}
}
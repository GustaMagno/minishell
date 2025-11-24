
#include "minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		printf("%s ", cmd->args[i]);
		i++;
	}
	printf("\n");
}

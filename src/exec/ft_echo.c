
#include "minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 1 + !(ft_strcmp("-n", cmd->args[1]));
	while (cmd->args[i + 1])
	{
		printf("%s ", cmd->args[i]);
		i++;
	}
	printf("%s", cmd->args[i]);
	if (ft_strcmp("-n", cmd->args[1]))
		printf("\n");
}

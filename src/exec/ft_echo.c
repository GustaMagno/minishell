
#include "minishell.h"

void	ft_echo(t_all *all)
{
	int	i;

	i = 1;
	while (all->cmd->args[i])
	{
		printf("%s ", all->cmd->args[i]);
		i++;
	}
	printf("\n");
}

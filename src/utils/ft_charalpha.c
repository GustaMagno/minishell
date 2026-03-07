#include "minishell.h"

int	ft_charalpha(char *str, int i)
{
	if (i != 0 && str[i - 1] == '$' && str[i] == '?')
		return (1);
	if (i > 1 && str[i - 2] == '$' && str[i - 1] == '?')
		return (0);
	if (str[i] > 122 || str[i] < 65 && str[i] != '_' && !(str[i] >= '0' && str[i] <= '9'))
		return (0);
	if (str[i] > 90 && str[i] < 97 && str[i] != '_' && !(str[i] >= '0' && str[i] <= '9'))
		return (0);
	return (1);
}

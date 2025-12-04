#include "minishell.h"
#include "map.h"

char	*expanded(char *str, t_map *env)
{
	int i;
	char	f;

	i = 0;
	f = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && (!f || f == str[i]))
			f = str[i] * (f == 0);
		if (str[i] == '$')
		{
			
		}
	}
}

int	expansion(t_cmd *cmd, t_map *env)
{
	t_cmd	*head;
	char	**new_args;
	int 	i;

	head = cmd;
	while (head)
	{
		i = -1;
		while (head->args[++i])
			head->args[i] = expanded(head->args[i], env);
		head = head->next;
	}
	return (1);
}
// " tes $PWD.TES e viado"
// char *key=PWD
// int		start=6
// int		end=9

// char *satrt = " tes "
// char *end= ".TES e viado"
// t = jo(star, value);
//  value = jo(t, end);
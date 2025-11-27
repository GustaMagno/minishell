/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:57:42 by matmagal          #+#    #+#             */
/*   Updated: 2025/11/27 21:56:43 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_key(char *envp)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	j = 0;
	while (envp[i] != '=' && envp[i])
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	while (j < i)
	{
		key[j] = envp[j];
		j++;
	}
	key[j] = '\0';
	return (key);
}

char	*find_value(char *envp)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (envp[i] != '=' && envp[i])
		i++;
	i++;
	value = malloc(sizeof(char) * (ft_strlen(envp) - i + 1));
	while (envp[i])
	{
		value[j] = envp[i];
		i++;
		j++;
 	}
	value[j] = '\0';
	return (value);
}

void	create_env(t_map *env, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		env->put(env, find_key(envp[i]) ,find_value(envp[i]));
		i++;
	}
}

void	print_env(t_all *all)
{
	char	**my_env;
	int		i;

	my_env = all->env->to_str(all->env);
	while (my_env[i])
	{
		printf("%s\n", my_env[i]);
		i++;
	}
	free_split(my_env);
}
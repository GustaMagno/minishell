/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:57:42 by matmagal          #+#    #+#             */
/*   Updated: 2026/01/19 21:53:03 by marvin           ###   ########.fr       */
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
	if (!value)
		return (NULL);
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
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		key = find_key(envp[i]);
		value = find_value(envp[i]);
		env->put(env, ft_strdup(key), ft_strdup(value));
		free(key);
		free(value);
		i++;
	}
	env->put(env, ft_strdup("?"), ft_strdup("0"));
}

void	print_env(t_map *env)
{
	char	**my_env;
	int		i;
	int		last;

	i = 0;
	my_env = env->to_str(env);
	while (my_env[i])
	{
		last = ft_strlen(my_env[i]) - 1;
		if (my_env[i][last] == '\2' || my_env[i][0] == '?')
		{
			i++;
			continue ;
		}
		printf("%s\n", my_env[i]);
		i++;
	}
	free_split(my_env);
}

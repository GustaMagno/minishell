/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 17:43:22 by gustoliv          #+#    #+#             */
/*   Updated: 2026/03/12 17:43:22 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_map *env)
{
	char	*pwd;
	int		check;

	check = 1;
	pwd = getcwd(NULL, 0);
	if (!pwd && check--)
		pwd = env->get(env, "PWD");
	if (pwd)
		printf("%s\n", pwd);
	else
	{
		write(2, "pwd: error retrieving current directory: \
			getcwd: cannot access parent directories:", 86);
		ex_code(env, "ERROR");
	}
	if (!ft_strcmp(env->get(env, "?"), "ERROR"))
		ex_code(env, "1");
	else
		ex_code(env, "0");
	if (check)
		free(pwd);
}

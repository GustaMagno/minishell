/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 17:43:31 by gustoliv          #+#    #+#             */
/*   Updated: 2026/03/12 17:43:31 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_map *env, t_cmd *cmd)
{
	size_t	i;

	i = 1;
	while (cmd->args[i])
	{
		if (ft_strcmp(cmd->args[i], "?") != 0)
			env->remove(env, cmd->args[i]);
		i++;
	}
	ex_code(env, "0");
}

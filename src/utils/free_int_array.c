/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_int_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 17:18:52 by gustoliv          #+#    #+#             */
/*   Updated: 2026/03/12 17:19:14 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_int_array(int **args, int n)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (i < n)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

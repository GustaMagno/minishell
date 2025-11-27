/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:24:19 by matmagal          #+#    #+#             */
/*   Updated: 2025/11/27 20:45:33 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_path	*ft_lstnew(char *path)
{
	t_path	*new_node;

	new_node = (t_path *) malloc(sizeof(t_path));
	if (!new_node)
		return (NULL);
	new_node->path = ft_strdup(path);
	new_node->next = NULL;
	return (new_node);
}

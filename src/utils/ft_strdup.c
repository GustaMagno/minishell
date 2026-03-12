/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 17:15:23 by gustoliv          #+#    #+#             */
/*   Updated: 2026/03/12 17:15:24 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "minishell.h"

char	*ft_strdup(const char *s)
{
	char	*scpy;
	size_t	i;

	i = 0;
	scpy = (char *)malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!scpy)
		return (NULL);
	while (s[i])
	{
		scpy[i] = s[i];
		i++;
	}
	scpy[i] = '\0';
	return (scpy);
}

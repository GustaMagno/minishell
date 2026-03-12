/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 17:21:10 by gustoliv          #+#    #+#             */
/*   Updated: 2026/03/12 17:21:10 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin2(char *s1, char *s2, char *s1_temp)
{
	char	*str;
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2[j] != '\n' && s2[j])
		j++;
	str = malloc((i + j + 1 + (s2[j] == '\n')) * sizeof(char));
	if (!str)
		return (NULL);
	temp = str;
	while (s1 && *s1)
		*str++ = *s1++;
	while (*s2 && *s2 != '\n')
		*str++ = *s2++;
	if (*s2 == '\n')
		*str++ = '\n';
	free(s1_temp);
	*str = '\0';
	return (temp);
}

int	check_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

void	clean_buffer(char *buffer, int check)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (buffer[i])
	{
		if (!check && buffer[i] == '\n')
		{
			buffer[i++] = '\0';
			break ;
		}
		buffer[i++] = '\0';
	}
	while (buffer[i])
	{
		buffer[j++] = buffer[i];
		buffer[i++] = '\0';
	}
	buffer[j] = '\0';
}

char	*get_next_line(int fd)
{
	static char	s[BUFFER_SIZE + 1];
	char		*line;
	int			size;

	line = NULL;
	size = 1;
	if (fd < 0 || fd >= FOPEN_MAX)
		return (NULL);
	while (size)
	{
		if (*s == '\0')
			size = read(fd, s, BUFFER_SIZE);
		if (size < 0)
			return (clean_buffer(s, 1), free(line), NULL);
		if (size)
		{
			line = ft_strjoin2(line, s, line);
			if (!check_newline(s))
				return (clean_buffer(s, 0), line);
			clean_buffer(s, 0);
		}
	}
	return (line);
}

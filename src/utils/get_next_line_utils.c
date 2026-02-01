#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_check_nl(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newline;
	char	*ptr;
	char	*to_free;

	newline = malloc(ft_strlen(s2) + ft_strlen(s1) + 1);
	if (!newline)
	{
		free(s1);
		return (NULL);
	}
	ptr = newline;
	to_free = s1;
	while (s1 && *s1)
		*ptr++ = *s1++;
	while (*s2 && *s2 != '\n')
		*ptr++ = *s2++;
	if (*s2 == '\n')
		*ptr++ = '\n';
	free(to_free);
	*ptr = '\0';
	return (newline);
}

void	ft_clean(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < BUFFER_SIZE && buffer[i] && buffer[i] != '\n')
		i++;
	if (i < BUFFER_SIZE && buffer[i] == '\n')
		i++;
	while (i < BUFFER_SIZE + 1)
		buffer[j++] = buffer[i++];
	while (j < BUFFER_SIZE + 1)
		buffer[j++] = '\0';
}

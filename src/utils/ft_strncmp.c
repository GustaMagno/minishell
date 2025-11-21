#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	cont1;

	cont1 = 0;
	while (cont1 < n)
	{
		if (s1[cont1] != s2[cont1] || s1[cont1] == '\0' || s2[cont1] == '\0')
			return ((unsigned char)s1[cont1] - (unsigned char)s2[cont1]);
		cont1++;
	}
	return (0);
}
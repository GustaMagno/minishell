#include "minishell.h"

char	*ft_strjoinfree(char *s1, char *s2, char *s1_temp, char *s2_temp)
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
	return (free(s2_temp), temp);
}
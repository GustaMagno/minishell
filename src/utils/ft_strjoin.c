#include "map.h"
#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	char	*temp;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = malloc((i + j + 1) * sizeof(char));
	if (!str)
		return (NULL);
	temp = str;
	while (s1 && *s1)
		*str++ = *s1++;
	while (s2 && *s2)
		*str++ = *s2++;
	*str = '\0';
	return (temp);
}

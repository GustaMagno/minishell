#include "map.h"
#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	char	*temp;

	if (!s1 || !s2)
		return (NULL);
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

char	*ft_mapstrjoin(char *s1, char *s2)
{
	char	*str;
	int 	check;
	int		len_s1;
	int		len_s2;
	char	*temp_str;
	char	*temp_s1;

	if (!s1 || !s2)
		return (NULL);
	check = (*s2 == '=');
	temp_s1 = s1;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	temp_str = str;
	while (s1 && *s1)
		*str++ = *s1++;
	while (s2 && *s2)
		*str++ = *s2++;
	*str = '\0';
	if (!check)
		free(temp_s1);
	return (temp_str);
}

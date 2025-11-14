#include "minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char) c;
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (size != 0 && nmemb > ((size_t) - 1) / size)
		return (NULL);
	arr = (void *)malloc(nmemb * size);
	if (arr == NULL)
		return (NULL);
	ft_memset(arr, 0, nmemb * size);
	return (arr);
}

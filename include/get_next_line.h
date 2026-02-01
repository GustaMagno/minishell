#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line(int fd);
int		ft_check_nl(char *str);
char	*ft_strjoin(char *s1, char *s2);
void	ft_clean(char *buffer);
size_t	ft_strlen(char *str);

#endif

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0  || BUFFER_SIZE <= 0)
		return (buffer[0] = 0, NULL);
	line = NULL;
	bytes_read = 1;
	while (!ft_check_nl(line))
	{
		if (*buffer == '\0')
			bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(line), NULL);
		else if (bytes_read == 0)
			return (line);
		else
		{
			line = ft_strjoin(line, buffer);
			ft_clean(buffer);
		}
	}
	return (line);
}


# include "minishell.h"

int	is_directory(char *path)
{
	struct stat path_stat;

	if (!path || stat(path, &path_stat) == -1)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

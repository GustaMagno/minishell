
# include "minishell.h"

int	is_directory(char *path)
{
	struct stat path_stat;

	if (!path || stat(path, &path_stat) == -1)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

void	stat_check(char *path)
{
	struct stat path_stat;

	if (!path || stat(path, &path_stat) == -1)
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 29);
		exit(127);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": Is a directory\n", 17);
		exit(126);
	}
	if (!S_ISREG(path_stat.st_mode) || (access(path, X_OK) == -1))
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": Permission denied\n", 20);
		exit(126);
	}
}

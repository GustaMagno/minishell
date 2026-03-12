
#include "minishell.h"

void	free_and_exit(t_map *env, t_cmd *cmd, int exit_status)
{
	free_structs(cmd);
	env->destroy(env);
	exit(exit_status);
}

void	stat_check(char *path, t_cmd *cmd, t_map *env)
{
	struct stat	path_stat;

	if (!path || stat(path, &path_stat) == -1)
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 29);
		free_and_exit(env, cmd, 127);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": Is a directory\n", 17);
		free_and_exit(env, cmd, 126);
	}
	if (!S_ISREG(path_stat.st_mode) || (access(path, X_OK) == -1))
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": Permission denied\n", 20);
		free_and_exit(env, cmd, 126);
	}
}

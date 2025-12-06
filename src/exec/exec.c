#include "minishell.h"

void	exec(t_cmd	*cmd, t_map *env)
{
	if (ft_lstsize(cmd) > 1)
		pipeline(cmd, env);
	else if (ft_lstsize(cmd) == 1)
		exec_functions(cmd, env);
}

void	pipeline(t_cmd *cmd, t_map *env)
{
	int		**fd_pipes;
	int		cmd_len;
	t_cmd	*tmp;

	tmp = cmd;
	cmd_len = ft_lstsize(cmd);
	fd_pipes = alloc_pipe(cmd_len);
	while (tmp)
	{
		exec_pipe(tmp, env, fd_pipes, cmd_len);
		tmp = tmp->next;
	}
}

int	**alloc_pipe(int n_cmds)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (n_cmds - 1));
	while (i < n_cmds - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (pipes);
}

void	exec_pipe(t_cmd *cmd, t_map *env, int **fd_pipes, int args)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < args)
	{
		if (i == 0)
		{
			pipe(fd_pipes[i]);
			pid = fork();
			if (pid == 0)
			{
				dup2(fd_pipes[i][1], STDOUT_FILENO);
				close_pipes(fd_pipes, args - 1, i);
				exec_functions(cmd, env);
				exit(127);
			}
			else
			{
				close_pipes(fd_pipes, args - 1, i);
				// wait(NULL);
			}
		}
		else if (i < args - 2)
		{
			pipe(fd_pipes[i]);
			pid = fork();
			if (pid == 0)
			{
				dup2(fd_pipes[i - 1][0], STDIN_FILENO);
				dup2(fd_pipes[i][1], STDOUT_FILENO);
				close_pipes(fd_pipes, args - 1, i);
				exec_functions(cmd, env);
				exit(127);
			}
			else
			{
				close_pipes(fd_pipes, args - 1, i);
				// wait(NULL);
			}
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				dup2(fd_pipes[i - 1][0], STDIN_FILENO);
				close_pipes(fd_pipes, args - 1, i);
				exec_functions(cmd, env);
				exit(127);
			}
			else
			{
				close_pipes(fd_pipes, args - 1, i);
				// wait(NULL);
			}
		}
		i++;
	}
}

void	close_pipes(int	**fd_pipes, int	t_pipes, int c_pipe)
{
	int	i;

	i = 0;
	while (i < t_pipes)
	{
		if (i != c_pipe - 1)
			close(fd_pipes[i][0]);
		if (i != c_pipe)
			close(fd_pipes[i][1]);
		i++;
	}
}

void	exec_functions(t_cmd *cmd, t_map *env)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ft_pwd(env);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		print_env(env);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		exec_cd(env, cmd);
	else
		ft_external(cmd, env);
}

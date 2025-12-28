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
	int		i;
	pid_t	pid;
	t_cmd	*tmp;

	tmp = cmd;
	i = 0;
	cmd_len = ft_lstsize(cmd);
	fd_pipes = alloc_pipe(cmd_len);
	while (i < cmd_len)
	{
		if (i < cmd_len - 1)
			pipe(fd_pipes[i]);
		pid = fork();
		if (pid == 0)
		{
			if (i > 0)
				dup2(fd_pipes[i - 1][0], STDIN_FILENO);
			if (i < cmd_len - 1)
				dup2(fd_pipes[i][1], STDOUT_FILENO);
			
			close_pipes(fd_pipes, cmd_len - 1);
			exec_functions(tmp, env);
			exit(127);
		}
		if (i > 0)
		{
			close(fd_pipes[i - 1][0]);
			close(fd_pipes[i - 1][1]);
		}
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while (i < cmd_len)
	{
		wait(NULL);
		i++;
	}
}

int	**alloc_pipe(int n_cmds)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (n_cmds - 1));
	i = 0;
	if (!pipes)
		return (NULL);
	while (i < n_cmds - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (NULL);
		i++;
	}
	return (pipes);
}


void	close_pipes(int	**fd_pipes, int	t_pipes)
{
	int	i;

	i = 0;
	while (i < t_pipes)
	{
		close(fd_pipes[i][0]);
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
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		ft_unset(env, cmd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		ft_export(env, cmd);
	else
		ft_external(cmd, env);
}

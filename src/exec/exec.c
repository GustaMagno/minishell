#include "minishell.h"

void	exec(t_cmd	*cmd, t_map *env)
{
	pid_t	pid;
	if (ft_lstsize(cmd) > 1)
		pipeline(cmd, env);
	
	else if (ft_lstsize(cmd) == 1)
	{
		if (exec_functions(cmd, env))
			return ;
		pid = fork();
		if (pid == 0)
		{
			if (cmd->redir)
				loop_redir(cmd);
			ft_external(cmd, env);
			free_and_exit(env, cmd, 127);
		}
		else
			wait(NULL);
	}
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
			exec_child_process(tmp, fd_pipes, i, cmd_len, env);
		close_parent_pipes(fd_pipes, i);
		tmp = tmp->next;
		i++;
	}
	i = -1;
	while (++i < cmd_len)
		wait(NULL);
}

void	exec_child_process(t_cmd *tmp, int **fd_pipes, int i, int cmd_len, t_map *env)
{
	if (i > 0)
		dup2(fd_pipes[i - 1][0], STDIN_FILENO);
	if (i < cmd_len - 1)
		dup2(fd_pipes[i][1], STDOUT_FILENO);
	if (tmp->redir)
		loop_redir(tmp);
	close_pipes(fd_pipes, cmd_len - 1);
	exec_functions(tmp, env);
	exit(127);
}

void	close_parent_pipes(int **fd_pipes, int i)
{
	if (i > 0)
	{
		close(fd_pipes[i - 1][0]);
		close(fd_pipes[i - 1][1]);
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

int	exec_functions(t_cmd *cmd, t_map *env)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return(ft_echo(cmd), 1);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return(ft_pwd(env), 1);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return(print_env(env), 1);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return(ft_exit(env, cmd), 1);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return(ft_export(env, cmd), 1);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return(ft_unset(env, cmd), 1);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return(exec_cd(env, cmd), 1);
	return (0);
}

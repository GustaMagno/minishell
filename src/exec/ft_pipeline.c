#include "minishell.h"

void	pipeline(t_cmd *cmd, t_map *env)
{
	int		i;
	pid_t	pid;
	pid_t	last_pid;
	t_cmd	*tmp;
	t_ctx	ctx;

	tmp = cmd;
	i = 0;
	last_pid = -1;
	init_ctx(&ctx, env, cmd);
	init_pipes(ctx.fd_pipes, ctx.cmd_len);
	while (i < ctx.cmd_len)
	{
		pid = fork();
		if (pid == 0)
			exec_child_process(tmp, ctx, i);
		if (i == ctx.cmd_len - 1)
			last_pid = pid;
		close_parent_pipes(ctx.fd_pipes, i);
		tmp = tmp->next;
		i++;
	}
	wait_pipeline(ctx.cmd_len, last_pid);
	free_pipes(ctx.fd_pipes, ctx.cmd_len - 1);
	close_heredoc_fds(ctx.cmd);
}

void	exec_child_process(t_cmd *tmp, t_ctx ctx, int i)
{
	if (i > 0)
		dup2(ctx.fd_pipes[i - 1][0], STDIN_FILENO);
	if (i < ctx.cmd_len - 1)
		dup2(ctx.fd_pipes[i][1], STDOUT_FILENO);
	if (tmp->redir && !loop_redir(tmp))
		free_and_exit(ctx.env, ctx.cmd, 1);
	close_heredoc_fds(ctx.cmd);
	close_pipes(ctx.fd_pipes, ctx.cmd_len - 1);
	free_pipes(ctx.fd_pipes, ctx.cmd_len - 1);
	if (exec_functions(tmp, ctx.env, 1))
		free_and_exit(ctx.env, ctx.cmd, 0);
	else
	{
		if (!tmp->args || !tmp->args[0])
			free_and_exit(ctx.env, ctx.cmd, 0);
		ft_external(tmp, ctx.env);
		free_and_exit(ctx.env, ctx.cmd, 127);
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

void	free_pipes(int **pipes, int len)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (i < len)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	wait_pipeline(int cmd_len, pid_t last_pid)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < cmd_len)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == last_pid)
			set_end_status(status);
		i++;
	}
}

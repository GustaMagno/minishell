#include "minishell.h"

int	set_end_status(int signal)
{
	t_map	*env;

	env = adress_env(NULL);
	if (signal == SIGINT)
		env->put(env, ft_strdup("?"), ft_strdup("130"));
	else if (signal == SIGQUIT)
		env->put(env, ft_strdup("?"), ft_strdup("131"));
}

void	exec(t_cmd	*cmd, t_map *env)
{
	pid_t	pid;
	int		status;

	ex_code(env, "0");
	exec_heredoc(cmd, env);
	if (ft_lstsize(cmd) > 1)
		pipeline(cmd, env);
	else if (ft_lstsize(cmd) == 1)
	{
		if (!redir_input(cmd, env))
			return ;
		exec_2(cmd, env);
	}
}

void	exec_2(t_cmd *cmd, t_map *env)
{
	pid_t	pid;
	int		status;

	if (exec_functions(cmd, env, 0))
			return ;
	set_ign_sig();
	pid = fork();
	if (pid == 0)
	{
		set_child_sig();
		if (cmd->redir)
			loop_redir(cmd);
		if (!cmd->args || !cmd->args[0])
			free_and_exit(env, cmd, 0);
		ft_external(cmd, env);
		free_and_exit(env, cmd, 127);
	}
	else if (pid > 0 && waitpid(pid, &status, 0) && set_end_status(status))
	{
		(WTERMSIG(status) == SIGINT) && (write(1, "\n", 1));
		if (status != -1 && !ft_strcmp(env->get(env, "?"), 0))
			ex_code(env, ft_itoa(status >> 8));
	}
	close_heredoc_fds(cmd);
}

int	redir_input(t_cmd *cmd, t_map *env)
{
	t_redir	*redir;

	if (cmd->redir)
	{
		redir = cmd->redir;
		while(redir)
		{
			if (ft_strcmp(redir->args[0], "<") == 0)
			{
				if(!check_input(redir->args[1], cmd, env))
					return (0);
			}
			redir = redir->next;		
		}
	}
	return (1);
}

int	check_input(char *path, t_cmd *cmd, t_map *env)
{
	if (!path || access(path, R_OK) == -1)
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 29);
		ex_code(env, "1");
		return (0);
	}
	return (1);
}

void	pipeline(t_cmd *cmd, t_map *env)
{
	int		i;
	pid_t	pid;
	t_cmd	*tmp;
	t_ctx	ctx;

	tmp = cmd;
	i = 0;
	init_ctx(&ctx, env, cmd);
	init_pipes(ctx.fd_pipes, ctx.cmd_len);
	while (i < ctx.cmd_len)
	{
		pid = fork();
		if (pid == 0)
			exec_child_process(tmp, ctx, i);
		close_parent_pipes(ctx.fd_pipes, i);
		tmp = tmp->next;
		i++;
	}
	i = -1;
	while (++i < ctx.cmd_len)
		wait(NULL);
	free_pipes(ctx.fd_pipes, ctx.cmd_len - 1);
	close_heredoc_fds(ctx.cmd);
}

void	exec_child_process(t_cmd *tmp, t_ctx ctx, int i)
{
	if (i > 0)
		dup2(ctx.fd_pipes[i - 1][0], STDIN_FILENO);
	if (i < ctx.cmd_len - 1)
		dup2(ctx.fd_pipes[i][1], STDOUT_FILENO);
	if (tmp->redir)
		loop_redir(tmp);
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

int	exec_functions(t_cmd *cmd, t_map *env, int child)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return(ft_echo(cmd, env), 1);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return(ft_pwd(env), 1);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return(print_env(env), 1);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return(ft_exit(env, cmd, child), 1);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return(ft_export(env, cmd), 1);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return(ft_unset(env, cmd), 1);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return(exec_cd(env, cmd), 1);
	return (0);
}

void	free_pipes(int **pipes, int	len)
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

void	init_pipes(int **fd_pipes, int cmd_len)
{
	int	i;

	i = 0;
	while (i < cmd_len - 1)
	{
		pipe(fd_pipes[i]);
		i++;
	}
}

void	init_ctx(t_ctx *ctx, t_map *env, t_cmd *cmd)
{
	ctx->cmd = cmd;
	ctx->cmd_len = ft_lstsize(cmd);
	ctx->env = env;
	ctx->fd_pipes = alloc_pipe(ctx->cmd_len);
}

void	close_heredoc_fds(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*redir;

	tmp = cmd;
	while (tmp)
	{
		redir = tmp->redir;
		while (redir)
		{
			if (ft_strcmp(redir->args[0], "<<") == 0 && redir->fd != -1)
			{
				close(redir->fd);
				redir->fd = -1;
			}
			redir = redir->next;
		}
		tmp = tmp->next;
	}
}

/* mkdir a
cd a
mkdir aa
cd a */
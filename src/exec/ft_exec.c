#include "minishell.h"

int	set_end_status(int status)
{
	t_map	*env;
	char	*str_status;

	str_status = NULL;
	env = adress_env(NULL);
	if (status == SIGINT)
		env->put(env, ft_strdup("?"), ft_strdup("130"));
	else if (status == SIGQUIT)
		env->put(env, ft_strdup("?"), ft_strdup("131"));
	if (status != -1 && !ft_strcmp(env->get(env, "?"), "0"))
	{
		str_status = ft_itoa(status >> 8);
		ex_code(env, str_status);
		free(str_status);
	}
	return (1);
}

void	exec(t_cmd *cmd, t_map *env)
{
	ex_code(env, "0");
	exec_heredoc(cmd, env);
	if (ft_lstsize(cmd) > 1)
		pipeline(cmd, env);
	else if (ft_lstsize(cmd) == 1)
		exec_2(cmd, env);
}

static int	is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (2);
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
        return (1);
	return (0);
}

void	exec_builtin_parent(t_cmd *cmd, t_map *env)
{
	int	save_in;
	int	save_out;

	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	if (save_in < 0 || save_out < 0)
		return ;
	if (cmd->redir && !loop_redir(cmd))
		ex_code(env, "1");
	else
		exec_functions(cmd, env, 0);
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	close(save_in);
	close(save_out);
	close_heredoc_fds(cmd);
}

void	exec_2(t_cmd *cmd, t_map *env)
{
	pid_t	pid;
	int		status;

	if (is_builtin(cmd) == 1)
		return (exec_builtin_parent(cmd, env));
	else if (is_builtin(cmd) == 2 && (!cmd->redir || loop_redir(cmd)))
		return (ft_exit(env, cmd, 0), close_heredoc_fds(cmd), (void)0);
	else if (is_builtin(cmd) == 2)
		return (ex_code(env, "1"), close_heredoc_fds(cmd), (void)0);
	set_ign_sig();
	pid = fork();
	if (pid == 0)
	{
		set_child_sig();
		if (cmd->redir && !loop_redir(cmd))
			free_and_exit(env, cmd, 1);
		if (!cmd->args || !cmd->args[0])
			free_and_exit(env, cmd, 0);
		ft_external(cmd, env);
		free_and_exit(env, cmd, 127);
	}
	else if (pid > 0 && waitpid(pid, &status, 0) && set_end_status(status))
		(WTERMSIG(status) == SIGINT) && (write(1, "\n", 1));
		close_heredoc_fds(cmd);
}


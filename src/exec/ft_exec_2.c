/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:52:33 by matmagal          #+#    #+#             */
/*   Updated: 2026/03/13 15:52:34 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	exec_functions(t_cmd *cmd, t_map *env, int child)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd, env), 1);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd(env), 1);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (print_env(env, cmd), 1);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(env, cmd, child), 1);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(env, cmd), 1);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(env, cmd), 1);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (exec_cd(env, cmd), 1);
	return (0);
}

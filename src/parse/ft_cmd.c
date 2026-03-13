/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:56:10 by gustoliv          #+#    #+#             */
/*   Updated: 2026/03/13 15:56:10 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(char **args)
{
	t_cmd	*cmd;

	if (!args)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = args;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*parsing_cmd(char *line)
{
	char	**args;
	t_cmd	*cmd_head;
	t_cmd	*node;
	int		i;

	cmd_head = NULL;
	i = 0;
	if (!line)
		return (NULL);
	args = ft_split(line, '\3');
	if (!args)
		return (NULL);
	cmd_head = new_cmd(ft_split(args[i++], '\2'));
	if (!cmd_head)
		return (free_split(args), NULL);
	node = cmd_head;
	while (args[i])
	{
		node->next = new_cmd(ft_split(args[i++], '\2'));
		if (!node->next)
			return (free_structs(cmd_head), free_split(args), NULL);
		node = node->next;
	}
	free_split(args);
	return (cmd_head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:56:18 by gustoliv          #+#    #+#             */
/*   Updated: 2026/03/13 15:56:18 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	put_redir(char *line, char *new_line, size_t *i, size_t *j)
{
	size_t	i1;
	size_t	j1;

	i1 = *i;
	j1 = *j;
	if (line[i1] == '>' || line[i1] == '<')
	{
		new_line[j1++] = '\2';
		new_line[j1++] = line[i1++];
		if (line[*i] == line[i1])
			new_line[j1++] = line[i1++];
		new_line[j1++] = '\2';
		*i = i1;
		*j = j1;
		return (1);
	}
	return (0);
}

static char	*transformate_line(char *line, char *new_line)
{
	size_t	i;
	size_t	j;
	char	f;

	if (!new_line)
		return (NULL);
	i = 0;
	j = 0;
	f = 0;
	while (line[i])
	{
		if (f == line[i] || (!f && (line[i] == '\'' || line[i] == '\"')))
			f = line[i] * (f == '\0');
		if (!f && line[i] == '|')
			line[i] = '\3';
		else if (!f && line[i] == ' ')
			line[i] = '\2';
		else if (!f && put_redir(line, new_line, &i, &j))
			continue ;
		new_line[j++] = line[i++];
	}
	return (free(line), new_line);
}

t_cmd	*parsing(char *line, t_map *env)
{
	t_cmd	*cmd;

	if (is_space(line))
		return (free(line), NULL);
	cmd = NULL;
	add_history(line);
	line = transformate_line(line, ft_calloc((ft_strlen(line) * 3) + 1, 1));
	if (!line)
		return (free(line), NULL);
	if (error_in_pipe(line))
		return (free(line), write(2, S_ERRO, 41), ex_code(env, "2"), NULL);
	cmd = parsing_cmd(line);
	if (!cmd)
		return (free(line), NULL);
	if (syntax_error(cmd, line) && write(2, S_ERRO, 41))
		return (ex_code(env, "2"), free_structs(cmd), NULL);
	if (!parsing_redir(cmd) || !expansion(cmd, env) || !remove_quotes(cmd))
		return (free_structs(cmd), NULL);
	return (cmd);
}

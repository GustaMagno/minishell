/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:52:11 by matmagal          #+#    #+#             */
/*   Updated: 2026/03/13 15:52:12 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	too_many_arguments(t_map *env, char *cd)
{
	write(2, "minishell: cd: too many arguments\n", 35);
	ex_code(env, "1");
	free(cd);
	return ;
}

void	is_not_directory(t_map *env, char *cd)
{
	write(2, "minishell: cd: ", 15);
	write(2, cd, ft_strlen(cd));
	write(2, ": Not a directory\n", 18);
	ex_code(env, "1");
	free(cd);
	return ;
}

void	path_dont_exist(t_map *env, char *cd)
{
	write(2, "minishell: cd: ", 15);
	perror(cd);
	ex_code(env, "1");
	free(cd);
	return ;
}

static char	*last_pwd_folder(char *oldpwd)
{
	int	i;

	if (!oldpwd || !oldpwd[0])
		return (ft_strdup("/"));
	i = ft_strlen(oldpwd) - 1;
	while (i > 0 && oldpwd[i] == '/')
		i--;
	while (i > 0 && oldpwd[i] != '/')
		i--;
	if (i == 0)
		return (ft_strdup("/"));
	return (ft_substr(oldpwd, 0, i));
}

char	*create_new_pwd(char *oldpwd, char *cd)
{
	char	*tmp;
	char	*newpwd;

	write(2, "cd: error retrieving current directory: ", 40);
	write(2, "getcwd: cannot access parent directories: ", 43);
	write(2, "No such file or directory\n", 26);
	if (!cd)
		return (NULL);
	if (cd[0] == '/')
		return (ft_strdup(cd));
	if (!oldpwd)
		oldpwd = "/";
	if (ft_strcmp(cd, ".") == 0)
		return (ft_strdup(oldpwd));
	if (ft_strcmp(cd, "..") == 0)
		return (last_pwd_folder(oldpwd));
	if (ft_strcmp(oldpwd, "/") == 0)
		return (ft_strjoin(ft_strdup("/"), cd));
	tmp = ft_strjoin(ft_strdup(oldpwd), "/");
	if (!tmp)
		return (NULL);
	newpwd = ft_strjoin(tmp, cd);
	free(tmp);
	return (newpwd);
}

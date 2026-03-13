/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:52:17 by matmagal          #+#    #+#             */
/*   Updated: 2026/03/13 15:52:18 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_error(t_map *env, char *tmp, char *cd)
{
	write(2, "minishell: cd: ", 15);
	perror(cd);
	ex_code(env, "1");
	free(tmp);
	free(cd);
}

void	exec_cd(t_map *env, t_cmd *cmd)
{
	char	*cd;
	char	*tmp;
	char	*pwd;

	tmp = NULL;
	if (env->get(env, "PWD"))
		tmp = ft_strdup(env->get(env, "PWD"));
	cd = cd_list(env, cmd);
	if (conditions_check(env, cmd, cd) == 1)
		return (free(tmp), (void)0);
	if (chdir(cd) != 0)
		return (cd_error(env, tmp, cd));
	ex_code(env, "0");
	if (tmp)
		env->put(env, ft_strdup("OLDPWD"), tmp);
	pwd = getcwd(NULL, 0);
	if (pwd)
		env->put(env, ft_strdup("PWD"), pwd);
	else
	{
		pwd = create_new_pwd(env->get(env, "PWD"), cd);
		if (pwd)
			env->put(env, ft_strdup("PWD"), pwd);
	}
	free (cd);
}

char	*cd_list(t_map *env, t_cmd *cmd)
{
	char	*cd;
	char	*home;

	home = env->get(env, "HOME");
	if (ft_argslen(cmd->args) == 1)
	{
		if (!home)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (NULL);
		}
		cd = ft_strdup(home);
	}
	else if (ft_strcmp(cmd->args[1], "--") == 0)
	{
		if (!env->get(env, "OLDPWD"))
			return (write(2, "minishell: cd: OLDPWD not set\n", 30), NULL);
		cd = ft_strdup(env->get(env, "OLDPWD"));
	}
	else
		cd = ft_strdup(cmd->args[1]);
	return (cd);
}

int	conditions_check(t_map *env, t_cmd *cmd, char *cd)
{
	int			i;
	struct stat	st;

	i = 0;
	if (!cd)
	{
		ex_code(env, "1");
		return (1);
	}
	if (ft_argslen(cmd->args) > 2)
	{
		too_many_arguments(env, cd);
		i = 1;
	}
	else if (stat(cd, &st) == -1)
	{
		path_dont_exist(env, cd);
		i = 1;
	}
	else if (!S_ISDIR(st.st_mode))
	{
		is_not_directory(env, cd);
		i = 1;
	}
	return (i);
}

#include "minishell.h"

// static void run()
// {
// 	char *line;

// 	while (1)
// 	{
// 		line = readline("minishell: ");
// 		if (!line)
// 			return ;
// 		parsing(line);
// 	}
// }


// int main(int argv, char **argc, char **env)
// {
// 	(void) argc;
// 	(void) argv;
// 	(void) env;
// 	run();
// 	//test_exec();
// }

char	*find_key(char *envp)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	j = 0;
	while (envp[i] != '=' && envp[i])
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	while (j < i)
	{
		key[j] = envp[j];
		j++;
	}
	key[j] = '\0';
	return (key);
}

char	*find_value(char *envp)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (envp[i] != '=' && envp[i])
		i++;
	i++;
	value = malloc(sizeof(char) * (ft_strlen(envp) - i + 1));
	while (envp[i])
	{
		value[j] = envp[i];
		i++;
		j++;
 	}
	value[j] = '\0';
	return (value);
}

void	create_env(t_map *env, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		env->put(env, find_key(envp[i]) ,find_value(envp[i]));
		i++;
	}
}

void	fill_path(t_map *env, t_path **path)
{
	char	**abs_path;
	t_path	*node;
	int		i;

	i = 0;
	node = NULL;
	abs_path = ft_split(env->get(env, "PATH"), ':');
	while (abs_path[i])
	{
		node = ft_lstnew(abs_path[i]);
		if (!node)
			exit (0);
		ft_lstadd_back(path, node);
		i++;
	}
}

int	main (int ac, char **av, char **envp)
{
	int		i;
	t_map	*env;
	t_path	*path;

	env = new_map();
	path = NULL;
	i = 0;
	create_env(env, envp);
	fill_path(env, &path);
	return (0);
}

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

int	main (int ac, char **av, char **envp)
{
	int		i;
	t_map	*env;
	t_map	*path;
	char	**result;

	env = new_map();
	path = new_map();
	i = 0;
	create_env(env, envp);
	result = path->to_str(path);
	while (result[i])
	{
		printf("%s\n", result[i]);
		i++;
	}
	return (0);
}
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include "map.h"

typedef struct s_redir
{
	char			*args[3];
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	struct s_cmd	*next;
	t_redir			*redir;
}	t_cmd;

typedef struct s_path
{
	char			*path;
	struct s_path	*next;
}	t_path;


char		**ft_split(char const *s, char c);
void		exec(t_cmd *cmd, t_map *env);
int			parsing(char *line, t_map *env);
t_cmd		*new_cmd(char **args);
size_t		ft_strlen(const char *str);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *str);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup(const char *s);
t_cmd		*parsing_cmd(char *line);
char		**final_split(char *line);
int			parsing_redir(t_cmd *cmd);
int			ft_argslen(char **args);
void		free_structs(t_cmd *cmd);
void		free_split(char **args);
int			redir_in_cmd(char *cmd_arg);
int			len_line(char *line);
int			syntax_error(char *line);
t_path		*ft_lstnew(char *path);
void		ft_lstadd_back(t_path **lst, t_path *new);
t_path		*ft_lstlast(t_path *lst);
char		*ft_pathjoin(char *s1, char *s2);
void		create_env(t_map *env, char **envp);
char		*find_value(char *envp);
char		*find_key(char *envp);
void		fill_path(t_map *env, t_path **path);

#endif

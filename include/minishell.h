#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "map.h"

# define SYNTAX_ERROR "bash: syntax error near unexpected token\n"

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

char				**ft_split(char const *s, char c);
size_t				count_words(char const *s, char c);
void				*ft_calloc(size_t nmemb, size_t size);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlen(const char *str);
t_cmd				*parsing(char *line, t_map *env);
t_cmd				*new_cmd(char **args);
void				exec(t_cmd *cmd, t_map *env);
size_t				ft_strlen(const char *str);
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_mapstrjoin(char *s1, char *s2);
char				*ft_strdup(const char *s);
t_cmd				*parsing_cmd(char *line);
char				**final_split(char *line);
int					parsing_redir(t_cmd *cmd);
int					ft_argslen(char **args);
void				free_structs(t_cmd *cmd);
int					free_node_content(t_cmd *node);
void				remove_node(t_cmd **list, t_cmd *node);
void				free_split(char **args);
int					redir_in_cmd(char *cmd_arg);
int					len_line(char *line);
int					syntax_error(t_cmd *cmd, char *line);
int					error_in_pipe(char *line);
t_path				*ft_lstnew(char *path);
void				ft_lstadd_back(t_path **lst, t_path *new);
t_path				*ft_lstlast(t_path *lst);
char				*ft_pathjoin(char *s1, char *s2);
void				create_env(t_map *env, char **envp);
char				*find_value(char *envp);
char				*find_key(char *envp);
char				*cd_list(t_map *env, t_cmd *cmd);
void				exec_cd(t_map *env, t_cmd *cmd);
void				free_all(char **str, t_path **path, t_path *node);
void				ft_external(t_cmd *cmd, t_map *env);
void				exec_external(t_cmd *cmd, t_map *env, char *exec_path);
char				*find_value(char *envp);
char				*find_key(char *envp);
void				create_env(t_map *env, char **envp);
void				print_env(t_map *env);
void				free_path(t_path **path);
int					is_space(char *line);
int					ft_charalpha(char *str, int i);
int					ft_strisnum(char *str);
int					ft_stralpha(char *str);
void				print_cmd(t_cmd *cmd);
int					count_args(char **cmd_args, t_map *env);
char				*ft_substr(char const *s, unsigned int start, size_t len);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
int 				remove_null_node(t_cmd *cmd);
int					count_new_split(char **cmd_args);
int					out_quotes(char *arg);
void 				access_check(t_cmd *cmd, t_map *env, char *exec_path);
int					ft_lstsize(t_cmd *lst);
int					expansion(t_cmd *cmd, t_map *env);
void				pipeline(t_cmd *cmd, t_map *env);
int					**alloc_pipe(int n_cmds);
void				close_pipes(int	**fd_pipes, int	t_pipes);
void				exec_functions(t_cmd *cmd, t_map *env);
int					remove_quotes(t_cmd *cmd);
char				*set_expansion(char *str);
void				split_words(char *arg, char **new_args, int *j);
void				ft_unset(t_map *env, t_cmd *cmd);
void				ft_export(t_map *env, t_cmd *cmd);
void				ft_exit(t_map *env, t_cmd *cmd);
void				ft_echo(t_cmd *cmd, t_map *env);
void				ft_pwd(t_map *env);
int					is_directory(char *path);
int					expansion(t_cmd *cmd, t_map *env);
void				stat_check(char *path, t_cmd *cmd, t_map *env);
char				*ft_strchr(const char *s, int c);
void				free_and_exit(t_map *env, t_cmd *cmd, int exit_status);
long long			ft_atoll(const char *str);
void				free_int_array(int **args, int n);
unsigned long long	ft_atoull(const char *str);
void				ex_code(t_map *env, char *str);
void				run(t_map *env);

#endif


NAME = minishell
CC = cc

CFLAGS = -g -Iinclude -Wall -Wextra -Werror # -fsanitize=address -fno-omit-frame-pointer 

LDFLAGS = -lreadline

SRC = src/main.c \
	src/map/map_utils.c \
	src/map/map.c \
	src/utils/ft_itoa.c \
	src/utils/ft_strcmp.c \
	src/utils/ft_strncmp.c \
	src/utils/ft_substr.c \
	src/utils/free_struct_cmd.c \
	src/utils/ft_calloc.c \
	src/utils/ft_strlcpy.c \
	src/utils/ft_lstadd_back.c \
	src/utils/ft_lstlast.c \
	src/utils/ft_pathjoin.c \
	src/utils/ft_charalpha.c \
	src/utils/ft_stralpha.c \
	src/utils/ft_utils_parse.c \
	src/utils/ft_atoi.c \
	src/utils/ft_atoll.c \
	src/utils/ft_strchr.c \
	src/utils/ft_atoull.c \
	src/utils/ft_strisnum.c \
	src/utils/ft_strjoin.c \
	src/utils/get_next_line.c \
	src/utils/ft_put_exitcode.c \
	src/utils/ft_strjoinfree.c \
	src/utils/ft_split.c \
	src/utils/ft_is_space.c \
	src/utils/ft_print_debug.c \
	src/utils/ft_strdup.c \
	src/utils/free_int_array.c \
	src/utils/ft_lstnew.c \
	src/utils/ft_lstsize.c \
	src/exec/ft_pwd.c \
	src/exec/ft_unset.c \
	src/exec/fd_closes.c \
	src/exec/ft_cd.c \
	src/exec/ft_cd_utils.c \
	src/exec/ft_dir_check.c \
	src/exec/ft_exec.c \
	src/exec/ft_exec_2.c \
	src/exec/ft_exec_redir.c \
	src/exec/ft_external.c \
	src/exec/ft_heredoc.c \
	src/exec/ft_heredoc_utils.c \
	src/exec/ft_pipeline.c \
	src/exec/ft_redirections.c \
	src/exec/ft_echo.c \
	src/exec/ft_env.c \
	src/exec/ft_exit.c \
	src/exec/ft_export.c \
	src/exec/ft_signals.c \
	src/parse/ft_cmd.c \
	src/parse/ft_expansion.c \
	src/parse/ft_expansion_utils.c \
	src/parse/ft_parse.c \
	src/parse/ft_redir.c \
	src/parse/ft_remove_quotes.c \
	src/parse/ft_syntax_error.c
OBJ = $(SRC:src/%.c=obj/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "Makefile successfully compiled"

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf obj

fclean: clean
	@rm -f $(NAME)
	@echo "All files have been deleted."

re: fclean all

reclear:
	make re && clear

r: reclear
	@./$(NAME)

v: reclear
	 valgrind --suppressions=readline.supp ./$(NAME)

vl: reclear
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./$(NAME)

vc: reclear
	valgrind --track-origins=yes --suppressions=readline.supp ./$(NAME)

vall: reclear
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp ./$(NAME)

.PHONY: all clean fclean re r

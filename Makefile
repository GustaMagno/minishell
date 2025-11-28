
NAME = minishell
CC = cc

CFLAGS = -g -Iinclude -fsanitize=address -fno-omit-frame-pointer #-Wall -Wextra -Werror

LDFLAGS = -lreadline

SRC := $(shell find src/ -name '*.c')

OBJ := $(patsubst src/%.c,obj/%.o,$(SRC))

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

asan:
	@echo "Compiling minishell with ASan (x86_64 via Rosetta)..."
	@$(MAKE) fclean
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME) $(LDFLAGS)
	@echo "Done! Run ./$(NAME) to test with AddressSanitizer."

re: fclean all

r:
	make re && clear && ./$(NAME)

v:
	make re && clear &&  valgrind --suppressions=readline.supp ./$(NAME)

vl:
	make re && clear && valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./$(NAME)

vc:
	make re && clear && valgrind --track-origins=yes --suppressions=readline.supp ./$(NAME)

vall:
	make re && clear && valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp ./$(NAME)

.PHONY: all clean fclean re r

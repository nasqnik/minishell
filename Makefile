NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LIBFT = libft/libft.a

RLFLAGS		=	-lreadline -lhistory
RLDIR		=	-L/opt/vagrant/embedded/lib
RLINC		=	-I/opt/vagrant/embedded/include/readline/readline.h


SRC = minishell.c parsing.c \
	tokens/token_types.c tokens/token_utils.c tokens/token_types02.c tokens/token_list.c \
	tokens/join_tokens.c tokens/remove_spaces.c \
	expansions/expansions_dquotes.c expansions/env_list.c expansions/expansions.c \
	verify_logic.c \
	utils/print_error.c utils/utils.c wildcard/wildcard_last.c wildcard/utils.c\
	ast_tree/create_tree.c
 
OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS)  $(OBJ) $(LIBFT) $(RLDIR) $(RLINC) $(RLFLAGS) -o $(NAME)

$(LIBFT):
	make all -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(RLINC) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

valgrind: $(NAME)
	sh ak.sh

.PHONY: all clean fclean re
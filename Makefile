NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LIBFT = libft/libft.a
SRC = minishell.c tokens.c token_types.c token_utils.c\
	linked_list.c print.c 
 
OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	make all -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

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
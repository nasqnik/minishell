valgrind --trace-children=yes -s --suppressions=_notes/ignore_readline_leaks.txt  --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell

valgrind --trace-children=yes -s --suppressions=_notes/ignore_readline_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell 2> out

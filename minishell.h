// echo *.c > "file1.txt $USER"hi'lol $PWD' | grep "*.c" >> ls $? &&  awk $_ << $USER 

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:13:28 by meid              #+#    #+#             */
/*   Updated: 2024/12/12 12:02:01 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h> 
#include <dirent.h>
#include <fcntl.h>
# include <sys/types.h> //waitpid flags
# include <sys/wait.h>  //wait, waitpid

// int rl_replace_line(const char *text, int clear_undo);

// extern int sig;

typedef enum e_token_type
{
    WORD,
    REDIRECT_IN,     // <
    REDIRECT_OUT,    // >
    REDIRECT_APPEND, // >>
    HEREDOC,         // <<
    PIPE,            // |
    LOGIC_AND,       // &&  
    LOGIC_OR,        // ||
    BRACKET,         // () //maybe we'll need left and right
    COMMAND,         // echo ls
    ARGUMENT,        // after command or flag and it dose not have space at the en ir a flag
    FILENAME,        // after  < > >>
    DELIMITER        // after << heredoc
} t_token_type;
;

typedef struct s_tokens
{
    char *data;
    int type;
    struct s_tokens *next;    
}           t_tokens;

typedef struct s_env
{
    // char *env;
    char *key;
    char *value;
    struct s_env *next;
}       t_env;

// typedef struct s_tmp
// {
//     char *data;
//     struct s_tmp *next;
// }       t_w_tmp;

typedef struct s_tree
{
    int type;
    char *file;
    char **args;
    struct s_tree *left;
    struct s_tree *right;
    //int *level;
}           t_tree;

typedef struct s_info
{
    char		*buffer;
    t_tokens 	*token_list;
    t_tree      *ast_tree;
    char		**envp_array;
    t_env		*envp_list;
    int     i;
    int stdout;
    int stdin;

    // int			error_flag;
    // t_w_tmp       *tmp;
    // int			env_size;
    // int         exit_status;
    // char        *last_arg;
    // // int     error_signal;
    // char        *temporary;
}           t_info;

void	free_array(char **array);
// env_list.c
void	env_to_list(t_info *info);
void	ft_clear_list(t_env **lst);
t_env	*env_lstnew(char *env_var);
void	env_lstadd_back(t_env **lst, t_env *new);

//utils
int ft_is(int c, char *str);

// // token_types.c
t_tokens *operators_token(char *str, t_info *info , int len);
t_tokens *bracket_token(char *str, t_info *info , int len);
t_tokens	*word_token(char *str, t_info *info, int len);


// token_list.c
t_tokens *ft_lstlast_token(t_tokens *lst);
t_tokens *ft_create_token(t_info *info, int len, int type, char *str);
void	add_back_token(t_tokens **lst, t_tokens *new);
void	ft_clear_tokens(t_tokens **lst);

// parsing.c
void parsing(t_info *info);
void lexer(t_info *info, char *str);

// token_utils.c
// int check_brackets(char *str, t_info *info);
int check_operator_type(int flag, char cur);

// print.c
void handle_error(t_info *info, char *msg, int flag);
const char *token_type_to_string(t_token_type type);
void	print_list(t_tokens	*list);
void	print_the_error(char *args, int flag, int fd);

// void	print_after_expansions(t_info *info);
// void open_the_shell(t_info *info);
// void handle_calc(t_info *info);
// void check_parenthesis(t_info *info);
// void handle_the_input(t_info *info);



// rename_tokens.c
void rename_tokens(t_info *info);
t_tokens	*tokens_after_redirect(t_info *info, t_tokens *cursor, int i);

// create_tree
t_tree *create_ast_tree(t_tokens **token);
t_tree *create_ast_and(t_tokens **tokens);
t_tree *create_ast_or(t_tokens **tokens);
t_tree *create_ast_pipe(t_tokens **tokens);
t_tree *create_ast_redirections(t_tokens **tokens);
t_tree *create_ast_command(t_tokens **tokens);
void print_ast(t_tree *node, int depth, char *flag);

// clear_tree
void ft_clear_tree(t_tree *node);

// // execution
// char	*find_path(char *command, t_first *f);
void execute_binary(t_info *info, char *command, char **args, int fd);
void execute_command(t_info *info, t_tree *tree);
int	strcmp_builtin(t_info *info, char *command, char **args);
void	execute_binary(t_info *info, char *command, char **args, int fd);

// builtins
int ft_echo(char **args, int i);
int ft_cd(t_info *info, char **args, int i);
int ft_export(t_info *info, char **args, int i);
int ft_unset(t_info *info, char **args, int i);
int ft_env(t_info *info, char **args, int i);
int ft_exit(t_info *info, char **args, int i, int j);
int ft_pwd(char **args, int i);
int ft_meow(char **args, int i, int j);

char	*search_in_env(t_info *info, char *key);
void	change_pwd_in_env(t_info *f);
int	invalid_identifier(char *str, int flag);

// execution_logic
void execution(t_info *info, t_tree *tree);
void execution_pipe(t_info *info, t_tree *tree);
pid_t   handle_left_pipe(t_info *info, t_tree *tree, int pipefd[2]);
pid_t   handle_right_pipe(t_info *info, t_tree *tree, int pipefd[2]);
void execution_redirection(t_info *info, t_tree *tree);
void handle_redirect_in(t_info *info, t_tree *tree);
void handle_redirect_out(t_info *info, t_tree *tree);
void handle_redirect_append(t_info *info, t_tree *tree);
void	get_file(t_info *info);

// // env_list.c
// void env_to_list(t_info *info);
// char *search_in_env(t_info *info, char *key);
// void print_env(t_info *info, int flag);
// void ft_clear_list(t_list **lst);



// /*RIP*/

// int do_op(char *str, t_info *info);


// void expand_variables(t_info *info);
// void expand_envp(t_tokens *token, t_info *info);
// void expand_d_quotes(t_tokens *token, t_info *info);

// // expansions_dquotes.c
// char *handle_variable(char *data, int *i, char *result, t_list *envp_list);
// char *append_remaining_data(char *data, int start, int end, char *result);
// char *get_var(char *data, int *i, t_list *envp_list);
// char *get_var_value(char *var_name, t_list *envp_list);

// // wildcard
// void	ft_clear_tmp(t_w_tmp **lst);
// void	free_array(char **array);

// int ft_there_wildcard(char *str);
// int who_many_wildcard(char *str);
// char *clean_wildcard(char *data);
// void prossing_files(t_first *f, struct dirent *entry);

// void wildcard_str(t_first *f);

// t_w_tmp	*ft_data_lstnew(char *con);

// // remove_spaces
// void	remove_spaces(t_first *f);

// // verify_logic
// int verify_logic(t_first *f);





// int invalid_identifier(char *str, int flag);

// void print_the_error(char *args, int flag, int fd);
// void change_pwd_in_env(t_first *f);
// void execution(t_first *f, t_tree *tree);
// int execute_redirections(t_first *f, int tree_type);
// int	handle_here_doc(t_first *f);
// int	open_file(char *filepath, char mode, t_first *f);
// void	handle_dup2(int input_fd, int output_fd);

// int str_cmp_builtin(t_first *f, char *command, char **args);
// void	get_file(t_first *f);


#endif
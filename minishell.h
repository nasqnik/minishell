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


// typedef struct s_export
// {
//     char *data;
//     struct s_tmp *next;
// }       t_export;

typedef struct s_tree
{
    int type;
    char *file;
    char **args;
    struct s_tree *left;
    struct s_tree *right;
    //int *level;
}           t_tree;
typedef struct s_env
{
    char *env;
    char *key;
    char *value;
    struct s_env *next;
}       t_env;

typedef struct s_info
{
    t_env		*envp_list;
    t_env       *export_tmp;
    char		*buffer;
    t_tokens 	*token_list;
    t_tree      *ast_tree;
    char		**envp_array;
    int     i;
    int stdout;
    int stdin;
    char        *temporary;
    int         exit_status; // add that

    // int			error_flag;
    // t_w_tmp       *tmp;
    // int			env_size;
    // char        *last_arg;
    // // int     error_signal;
}           t_info;

void	free_array(char **array);
// env_list.c
void	env_to_list(t_info *info);
void	ft_lstadd_front(t_env **lst, t_env *new);
void	ft_clear_list(t_env **lst);
t_env	*env_lstnew(char *env_var);
void	env_lstadd_back(t_env **lst, t_env *new);

void update_envp_array(t_info *info);

//utils
int ft_is(int c, char *str);
int our_static(t_info *info, char *str, int set);

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
int parsing(t_info *info);
int lexer(t_info *info, char *str);

// token_utils.c
// int check_brackets(char *str, t_info *info);
int check_operator_type(int flag, char cur);

// print.c
void	handle_error(t_info *info, char *msg, int what_am_i, int flag);
const char *token_type_to_string(t_token_type type);
void	print_list(t_tokens	*list);
void	print_the_error(t_info *info ,char *args, int flag, int fd);

// void	print_after_expansions(t_info *info);
// void open_the_shell(t_info *info);
// void handle_calc(t_info *info);
// void check_parenthesis(t_info *info);
// void handle_the_input(t_info *info);



// rename_tokens.c
int rename_tokens(t_info *info);
t_tokens	*tokens_after_redirect(t_info *info, t_tokens *cursor, int i);

// create_tree
t_tree *create_ast_tree(t_tokens **token);
t_tree *create_ast_and(t_tokens **tokens);
t_tree *create_ast_or(t_tokens **tokens);
t_tree *create_ast_pipe(t_tokens **tokens);
t_tree *create_ast_redirections(t_tokens **tokens);
t_tree *create_ast_command(t_tokens **tokens);
t_tree *create_ast_heredoc(t_tokens **tokens);
void print_ast(t_tree *node, int depth, char *flag);

// clear_tree
void ft_clear_tree(t_tree *node);

// // execution
// char	*find_path(char *command, t_first *f);
int execute_binary(t_info *info, char *command, char **args, int fd);
void execute_command(t_info *info, t_tree *tree);
int	strcmp_builtin(t_info *info, char *command, char **args);
// void	execute_binary(t_info *info, char *command, char **args, int fd);

// builtins
int ft_echo(char **args, int i);
int ft_cd(t_info *info, char **args, int i);
int ft_export(t_info *info, char **args, int i);
int ft_unset(t_info *info, char **args, int i);
int ft_env(t_info *info, char **args, int i);
int ft_exit(t_info *info, char **args, int i, int j);
int ft_pwd();
int ft_meow(t_info *info, char **args, int i, int j);

char	*search_in_env(t_info *info, char *key);
void	change_pwd_in_env(t_info *f);
int	invalid_identifier(char *str, int flag);
void env_sort(t_info *info, t_env *envp_list);

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

// wildcard
int wildcard(t_info *info, char **exp_res);
//wildcard/utils
int	ft_there_wildcard(char *str);
int	who_many_wildcard(char *str);
char	*clean_wildcard(char *data);
void	prossing_files(t_info *info, struct dirent *entry);
int	ft_matchy(char *file, char *wildcard);
// // env_list.c
// void env_to_list(t_info *info);
// char *search_in_env(t_info *info, char *key);
// void print_env(t_info *info, int flag);
// void ft_clear_list(t_list **lst);



// /*RIP*/

// int do_op(char *str, t_info *info);

void expand_command(t_info *info, t_tree *tree);
char *process_expansion(char *arg, t_info *info);
char *expand_d_quotes(char *str, int *pos, t_info *info);
char *expand_s_quotes(char *str, int *pos);
char *expand_variables(char *str, int *pos, t_info *info);

// expansions_dquotes.c
char	*handle_variable(char *data, int pov[2], char *result, t_info *info);
char    *handle_var_value(char *data, int pov[2], t_info *info);
char    *handle_exit_status(char *data, int pov[2], t_info *info);
char	*append_remaining_data(char *data, int pov[2], char *result);
char    *clean_quotes(char *result);


// expansions_utils.c

char	*get_var(char *data, int *i, t_env *envp_list);
char	*get_var_value(char *var_name, t_env *envp_list);
void count_without_quotes(char *result, int *count);
char *substring_without_quotes(char *result, int count);

void free_and_set_null(t_info *info, int flag);


// whildcard


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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:13:28 by meid              #+#    #+#             */
/*   Updated: 2025/01/15 16:23:40 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h> 
# include <dirent.h>
# include <fcntl.h>
# include <sys/types.h> //waitpid flags
# include <sys/wait.h>  //wait, waitpid
# include <termios.h>
# include <sys/stat.h> 

int rl_replace_line(const char *text, int clear_undo);

// extern int sig;

#define TRUE 1
#define FALSE 0

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
    int fd;
    struct s_tree *left;
    struct s_tree *right;
    //int *level;
}           t_tree;
typedef struct s_env
{
    char *env;
    char *key;
    char *value;
    int     flag; // 1 there is = // 0 not there is not
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
    char        *pwd;

    // int			error_flag;
    // t_w_tmp       *tmp;
    // int			env_size;
    // char        *last_arg;
    // // int     error_signal;
}           t_info;

//--------------------------------------main_functions-----------------------------------------//

//-----------minishell.c-----------//
void	minishell(t_info *info);

//-----------initialize.c-----------//
void	initialize(t_info *info, char **env);
char	**ft_allocate_env(char **env);
char	**create_non_existing_env(void);
void	env_to_list(t_info *info, int flag);

//-----------env_utils.c-----------//
t_env *env_lstnew(char *env_var, int flag);
void env_lstadd_back(t_env **lst, t_env *new);
void	ft_clear_list(t_env **lst);

//-----------update_envp_array.c-----------//
void update_envp_array(t_info *info);

//-----------print_error.c-----------//
void	handle_error(t_info *info, char *msg, int what_am_i, int flag);
void	print_the_error(t_info *info ,char *args, int flag, int fd);
const char	*token_type_to_string(t_token_type type); //----------------------- to delete
void	print_list(t_tokens	*list); //----------------------------------------- to delete
void print_ast(t_tree *node, int depth, char *flag); //------------------------ to delete

//-----------signals.c-----------//
void	castom_signals(void);
void	handle_sig(int sig);
void	disable_echoctl(void);

//-----------utils.c-----------//
void free_and_set_null(t_info *info, int flag);
int	ft_is(int c, char *str);
int our_static(char *str, int set);


//--------------------------------------parsing-----------------------------------------//

//-----------parsing.c-----------//

int parsing(t_info *info);
int lexer(t_info *info, char *str);

//----------rename_tokens.c-----------//
int rename_tokens(t_info *info);
t_tokens	*tokens_after_redirect(t_info *info, t_tokens *cursor, int *j);

//-----------token_list.c-----------//
t_tokens	*ft_lstlast_token(t_tokens *lst);
t_tokens	*ft_create_token(t_info *info, int len, int type, char *str);
void	add_back_token(t_tokens **lst, t_tokens *new);
void	ft_clear_tokens(t_tokens **token_list);

//-----------token_types.c-----------//
t_tokens	*operators_token(char *str, t_info *info, int len);
t_tokens	*bracket_token(char *str, t_info *info, int len);
t_tokens	*word_token(char *str, t_info *info, int len);

//-----------verify_logic.c-----------//
int print_error_from_return_value(t_info *info, int to_return, t_tokens *cursor);
int verify_logic(t_info *info);

//-----------verify_logic02.c-----------//
int control_operators(t_tokens *cursor, int index);
int redirection_operators(t_tokens *cursor);
int subshell_rules(t_tokens *cursor, int flag);

//--------------------------------------execution-----------------------------------------//

//-----------exec_logic.c-----------//
void  execution(t_info *info, t_tree *tree);

//-----------exec_pipe.c-----------//
void execution_pipe(t_info *info, t_tree *tree);
pid_t   handle_left_pipe(t_info *info, t_tree *tree, int pipefd[2]);
pid_t   handle_right_pipe(t_info *info, t_tree *tree, int pipefd[2]);

//-----------exec_command.c-----------//
void execute_command(t_info *info, t_tree *tree);

//-----------exec_binary_command.c-----------//
void	binary(t_info *info, t_tree *tree);
int	execute_binary(t_info *info, char *command, char **args, int fd);

//-----------exec_redirection.c-----------//
void execution_redirection(t_info *info, t_tree *tree);
void handle_redirect_in(t_info *info, t_tree *tree);
void handle_redirect_out(t_info *info, t_tree *tree);
void handle_redirect_append(t_info *info, t_tree *tree);
int	get_file(int read_from, t_tree *tree, t_info *info);

//-----------here_doc.c-----------//
void read_and_expand(t_info *info, int read_from, int fd);
int	here_docs_ahead(t_tree *tree);
int	ft_hdoc(t_info *info, char *limiter, t_tree *tree);
int	find_docs(t_info *info, t_tree *tree);

//-----------subshell.c-----------//
void subshell(t_info *info, t_tree *tree);

//--------------------------------------wildcard-----------------------------------------//

//-----------wildcard.c-----------//
int	is_matching_quote(char *wildcard, char *file, int *wc, int i);
int	wildcard(t_info *info, char **exp_res);

//-----------matchy.c-----------//
int	ft_matchy(char *file, char *wildcard, char *tmp_file);
int	ft_end_with(char *str, char *end);
int	ft_strat_with(char *str, char *start);
int ft_mid_with(char *file, char *wildcard, int wc);

//-----------mid_part.c-----------//
int ft_mid_with(char *file, char *wildcard, int wc);
//-----------end_part.c-----------//
char *end_sub(char *wildcard, int *i, int *j);
//-----------start_part.c-----------//
char *start_sub(char *wildcard, int *i, int *j);

//-----------utils.c-----------//
int     who_many_wildcard(char *str);
void	prossing_files(t_info *info, struct dirent *entry);
char	*clean_wildcard(const char *data);
int     ft_there_wildcard(char *str);

//--------------------------------------wildcard-----------------------------------------//


void	free_array(char **array);
// env_list.c
void	env_to_list(t_info *info, int flag);
void	ft_lstadd_front(t_env **lst, t_env *new);
void	ft_clear_list(t_env **lst);
t_env	*env_lstnew(char *env_var, int flag);
void	env_lstadd_back(t_env **lst, t_env *new);

void update_envp_array(t_info *info);

//utils
int ft_is(int c, char *str);
int our_static(char *str, int set);

// // token_types.c
t_tokens *operators_token(char *str, t_info *info , int len);
t_tokens *bracket_token(char *str, t_info *info , int len);
t_tokens	*word_token(char *str, t_info *info, int len);


// token_list.c
t_tokens *ft_lstlast_token(t_tokens *lst);
t_tokens *ft_create_token(t_info *info, int len, int type, char *str);
void	add_back_token(t_tokens **lst, t_tokens *new);
void	ft_clear_tokens(t_tokens **lst);

// create_tree
t_tree *create_ast_tree(t_tokens **token);
t_tree *create_ast_and(t_tokens **tokens);
t_tree *create_ast_or(t_tokens **tokens);
t_tree *create_ast_pipe(t_tokens **tokens);
t_tree *create_ast_redirections(t_tokens **tokens);
t_tree *create_ast_command(t_tokens **tokens);
// t_tree *create_ast_heredoc(t_tokens **tokens);
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
void	change_pwd_in_env(t_info *f, char *oldpwd);
int	invalid_identifier(char *str, int flag);
void env_sort(t_info *info, t_env *envp_list);

// void	get_file(t_info *info);
int	get_file(int read_from, t_tree *tree, t_info *info);


void expand_command(t_info *info, t_tree *tree);
char *process_expansion(char *arg, t_info *info);
char *expand_d_quotes(char *str, int *pos, t_info *info);
char *expand_s_quotes(char *str, int *pos);
char *expand_variables(char *str, int *pos, t_info *info);
int expand_redirection(t_info *info, t_tree *tree);

// expansions_dquotes.c
char	*handle_variable(char *data, int pov[2], char *result, t_info *info);
char    *handle_var_value(char *data, int pov[2], t_info *info);
char    *handle_exit_status(char *data, int pov[2], t_info *info);
char	*append_remaining_data(char *data, int pov[2], char *result);
char    *clean_quotes(char *result);

char *process_expansion_heredoc(char *arg, t_info *info);
char *expand_quotes_heredoc(char *str, int *pos, t_info *info);
char	*handle_variable_heredoc(char *data, int pov[2], char *result, t_info *info);
char *expand_variables_heredoc(char *str, int *pos, t_info *info);

// expansions_utils.c

char	*get_var(char *data, int *i, t_env *envp_list);
char	*get_var_value(char *var_name, t_env *envp_list);
void count_without_quotes(char *result, int *count);
char *substring_without_quotes(char *result, int count);

void free_and_set_null(t_info *info, int flag);

void	new_env(t_info *info, char *search_for, char *value, int flagoooo);
char *tilda_string(t_info *info, char *str, int pov[2], char *result);

#include "assert.h"
// anas was explaining from this is was great

// max 100
// 1.92×10 
// 196
 
// is 42
// 2.02×10 
// 82
 
#endif
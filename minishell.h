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

extern int sig;

typedef enum e_token_type
{
    D_QUOTES,       // " " (we will need to expand the variables)
    S_QUOTES,          // ' ' (no need to expand)
    WORD,            // Command or argument (can be expanded)
    ENV_VAR,         // $VARIABLE
    WSPACE,           // Whitespace
    REDIRECT_IN,     // <
    REDIRECT_OUT,    // >
    REDIRECT_APPEND, // >>
    HEREDOC,         // <<
    PIPE,            // |
    LOGIC_AND,       // &&  
    LOGIC_OR,        // ||
    BRACKET,         // () //maybe we'll need left and right
    COMMAND,         // echo ls
    FLAG,            //  -l
    ARGUMENT,        // after command or flag and it dose not have space at the en ir a flag
    FILENAME,        // after  < > >>
    DELIMITER        // agter << heredoc
} t_token_type;
;

// union s_data {
//     int fd;
//     char *word;
//     char pipe;
//     char *file_name;
// } t_data;

typedef struct s_tokens
{
    void *data;
    int type;
    int len;
    char data_type;
    struct s_tokens *next;    
}           t_tokens;

typedef struct s_list
{
    char *key;
    char *value;
    struct s_list *next;
}       t_list;

typedef struct s_tmp
{
    char *data;
    struct s_tmp *next;
}       t_w_tmp;

typedef struct s_tree
{
    // void *data; // why you did close this one
    int type;
    //int *level;
    char *file;
    char **args;
    struct s_tree *left;
    struct s_tree *right;
}           t_tree;

typedef struct s_first
{
    char		*buffer;
    t_w_tmp       *tmp;
    t_tokens 	*token_list;
    t_tree      *ast_tree;
    char		**envp_array;
    t_list		*envp_list;
    int			env_size;
    int			error_flag;
    int         exit_status;
    char        *last_arg;
    // int     error_signal;
    char        *temporary;
    int     i;
}           t_first;

// int rl_replace_line(const char *text, int clear_undo);


void open_the_shell(t_first *f);
void handle_calc(t_first *f);
void check_parenthesis(t_first *f);
void handle_the_input(t_first *f);

// tokens.c
void parsing(t_first *f);
void lexer(t_first *f, char *str);
void here_doc_env_check(t_first *f);

// token_types.c
t_tokens *operators_token(char *str, t_first *f , int len);
t_tokens *variable_token(char *str, t_first *f , int len);
t_tokens *quote_token(char *str, t_first *f , int len);
t_tokens *bracket_token(char *str, t_first *f , int len);
t_tokens *word_token(char *str, t_first *f , int len);
t_tokens *space_token(char *str, t_first *f);

// join_tokens.c
void rename_tokens(t_first *f);
t_tokens *make_argument(t_tokens *cursor);

// linked_list.c
t_tokens *ft_lstlast_token(t_tokens *lst);
t_tokens *ft_create_token(t_first *f, int len, int type, char *str);
void	add_back_token(t_tokens **lst, t_tokens *new);
void	ft_clear_tokens(t_tokens **lst);

// env_list.c
void env_to_list(t_first *f);
char *search_in_env(t_first *f, char *key);
void print_env(t_first *f, int flag);
void ft_clear_list(t_list **lst);

// token_utils.c
int check_brackets(char *str, t_first *f);
int check_operator_type(int flag, char cur);

// print.c
void handle_error(t_first *f, char *msg, int flag);
const char *token_type_to_string(t_token_type type);
void	print_after_expansions(t_first *f);
void	print_list(t_tokens	*list);

//utils
int ft_is(int c, char *str);

/*RIP*/

int do_op(char *str, t_first *f);


void expand_variables(t_first *f);
void expand_envp(t_tokens *token, t_first *f);
void expand_d_quotes(t_tokens *token, t_first *f);

// expansions_dquotes.c
char *handle_variable(char *data, int *i, char *result, t_list *envp_list);
char *append_remaining_data(char *data, int start, int end, char *result);
char *get_var(char *data, int *i, t_list *envp_list);
char *get_var_value(char *var_name, t_list *envp_list);

// wildcard
void	ft_clear_tmp(t_w_tmp **lst);

int ft_there_wildcard(char *str);
int who_many_wildcard(char *str);
char *clean_wildcard(char *data);
void prossing_files(t_first *f, struct dirent *entry);

void wildcard_str(t_first *f);

t_w_tmp	*ft_data_lstnew(char *con);

// remove_spaces
void	remove_spaces(t_first *f);

// verify_logic
int verify_logic(t_first *f);

// create_tree
t_tree *create_ast_tree(t_tokens **tokens);
t_tree *create_ast_logic(t_tokens **tokens);
t_tree *create_ast_pipe(t_tokens **tokens);
t_tree *create_ast_redirections(t_tokens **tokens);
t_tree *create_ast_command(t_tokens **tokens);
void print_ast(t_tree *node, int depth, char *flag);


#endif
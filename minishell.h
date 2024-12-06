/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:13:28 by meid              #+#    #+#             */
/*   Updated: 2024/12/06 15:30:46 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h> 

// enum
// {
//     COMMAND,
//     OP,
//     FLAG,
//     ARG,
//     WORD,
//     DEL,
// };

typedef enum e_token_type
{
    WORD,            // Command or argument (can be expanded)
    PIPE,            // |
    REDIRECT_IN,     // <
    REDIRECT_OUT,    // >
    REDIRECT_APPEND, // >>
    HEREDOC,         // <<
    ENV_VAR,         // $VARIABLE
    SPACE,           // Whitespace
    D_QUOTES,       // " " (we will need to expand the variables)
    S_QUOTES,          // ' ' (no need to expand)
    LOGIC_AND,       // &&  
    LOGIC_OR,        // ||
    BRACKET,         // () //maybe we'll need left and right
    EQUATION,        // $(())  
    SUBSHELL         // $()
} t_token_type;
;

typedef struct s_tokens
{
    char *data;
    int len;
    // int flag;
    int type;
    struct s_tokens *next;    
}           t_tokens;

typedef struct s_first
{
    
    char    *buffer;
    char    **input;
    t_tokens *token_list;
    int     i;
    int     j;
    char    flag;
}           t_first;

void open_the_shell(t_first *f);
void handle_calc(t_first *f);
void check_parenthesis(t_first *f);
void handle_the_input(t_first *f);

// tokens.c
void parsing(t_first *f);
void lexer(t_first *f, char *str);

// token_types.c
t_tokens *operators_token(char *str, t_first *f , int len);
t_tokens *variable_token(char *str, t_first *f , int len);
t_tokens *quote_and_bracket_token(char *str, t_first *f , int len);
t_tokens *word_token(char *str, t_first *f , int len);
t_tokens *space_token(char *str, t_first *f);

// linked_list.c
t_tokens *ft_lstlast_token(t_tokens *lst);
t_tokens *ft_create_token(t_first *f, int len, int type, char *str);
void	add_back_token(t_tokens **lst, t_tokens *new);

// token_utils.c
int check_brackets(char *str, t_first *f);
int check_operator_type(int flag, char cur);

// print.c
void handle_error(t_first *f, char *msg, int flag);
const char *token_type_to_string(t_token_type type);

/*RIP*/

int do_op(char *str, t_first *f);

#endif
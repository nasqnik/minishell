/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:13:28 by meid              #+#    #+#             */
/*   Updated: 2024/12/05 20:12:38 by meid             ###   ########.fr       */
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

enum
{
    COMMAND,
    OP,
    FLAG,
    ARG,
    WORD,
    DEL,
};


typedef struct s_tokens
{
    char *data;
    int len;
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
void parsing(t_first *f);
void handle_the_input(t_first *f);
void tokens(t_first *f, char *str);
void handle_error(t_first *f, char *msg, int flag);





/*RIP*/

int do_op(char *str, t_first *f);

#endif
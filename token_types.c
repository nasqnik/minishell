/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:35:25 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/06 18:42:40 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_tokens *operators_token(char *str, t_first *f , int len)  // handel ||   |   &&   >> << > <
{
    char flag = 'o';
    int type;
    char cur = str[f->i];
    
    f->i++;
    if (str[f->i] == cur)
    {
        f->i++;
        flag = 'O';
    }
    if (cur == '&' && flag != 'O')
        handle_error(f, "you cant use one &", 1);
    type = check_operator_type(flag, cur);
    len = f->i - len;
    return (ft_create_token(f, len, type, str));
}

t_tokens *variable_token(char *str, t_first *f , int len)
{
    int type;
    int brackets_num = 0;
    
    f->i++;
    type = ENV_VAR; 
    if (str[f->i] == ' ' || str[f->i] == '\0')
        return (ft_create_token(f, f->i - len, WORD, str));
    brackets_num = check_brackets(str, f);
    if (brackets_num == 1)
        type = SUBSHELL; 
    if (brackets_num > 1)
        type = EQUATION;
    else
    {
        while (str[f->i] && !ft_isspace(str[f->i]))
            f->i++;
    }
    len = f->i - len;
    return (ft_create_token(f, len, type, str));
}    

t_tokens *quote_token(char *str, t_first *f , int len)
{
    int type;
    type = S_QUOTES;
    if (str[f->i] == '\"')
        type = D_QUOTES;
    char close = str[f->i];
    f->i++;
    while (str[f->i] && str[f->i] != close)
        f->i++;
    if (str[f->i] && str[f->i] == close)
        f->i++;
    else
        handle_error(f, "you did not close like this "" | '' | ()", 1);
    len = f->i - len;
    return (ft_create_token(f, len, type, str)); 
}

t_tokens *bracket_token(char *str, t_first *f , int len)
{
    int type = BRACKET;
    int open_B = 0;
    int close_B = 0;
    while (str[f->i])
    {
        while (str[f->i] && str[f->i] != ')')
        {
            if (str[f->i] == '(')
                open_B++;
            f->i++;
        }
        while (str[f->i] && str[f->i] != '(')
        {
            if (str[f->i] == ')')
                close_B++;
            f->i++;
        }
    }
    if (open_B != close_B)
    {
        handle_error(f, "hey, the brackets are not matching", 1);
    }
    len = f->i - len;
    return (ft_create_token(f, len, type, str)); 
}

t_tokens *word_token(char *str, t_first *f , int len)
{
    while (str[f->i] && ft_isspace(str[f->i]) == 0  
        && ft_isoperator(str[f->i]) == 0 && str[f->i] != '$')
        f->i++;
    len = f->i - len;
    return (ft_create_token(f, len, WORD, str)); 
}

t_tokens *space_token(char *str, t_first *f)
{
    while (str[f->i] && ft_isspace(str[f->i]) == 1)
        f->i++;
    return (ft_create_token(f, 1, WSPACE, str));
}




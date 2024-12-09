/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:35:25 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/09 18:58:43 by meid             ###   ########.fr       */
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
        return (handle_error(f, "you cant use one &", 1), NULL);
    type = check_operator_type(flag, cur);
    len = f->i - len;
    return (ft_create_token(f, len, type, str));
}

t_tokens *variable_token(char *str, t_first *f , int len)
{
    int type;

    f->i++;
    type = ENV_VAR; 
    if (str[f->i] == ' ' || str[f->i] == '\0')
        return (ft_create_token(f, f->i - len, WORD, str));
    else
    {
        while (str[f->i] && str[f->i] == '$')
            f->i++;
        while (str[f->i] && (ft_isalnum(str[f->i]) || ft_isbrackets(str[f->i])))
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
        return(handle_error(f, "you did not close like this "" | '' | ()", 1), NULL);
    len = f->i - len;
    return (ft_create_token(f, len, type, str)); 
}

t_tokens *bracket_token(char *str, t_first *f , int len)
{
    int type = BRACKET;
    int stack = 0;
    int start = -1;
    int end = -1;
    // int i = 0; 

    while (str[f->i])
    {
        if (str[f->i] == '(') 
        {
            if (stack == 0)
                start = f->i;
            stack++;
        }
        else if (str[f->i] == ')')
        {
            stack--;
            if (stack == 0)
            {
                end = f->i;
                f->i++;
                break;
            }
        }
        f->i++;
    }
    if (start == -1 || end == -1)
        return (handle_error(f, "hey, the brackets are not matching", 1), NULL);
    len = f->i - len;
    printf("ft_substr, f->i-len: %d, len: %d\n", f->i - len, len);
    return (ft_create_token(f, len, type, str)); 
}

t_tokens *word_token(char *str, t_first *f , int len)
{
    while (str[f->i] && ft_isspace(str[f->i]) == 0  
        && ft_isoperator(str[f->i]) == 0 && str[f->i] != '$'  && str[f->i] != ')' 
        && str[f->i] != '(' &&  ft_isquote(str[f->i]) == 0)
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




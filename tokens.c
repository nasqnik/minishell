/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:33:53 by meid              #+#    #+#             */
/*   Updated: 2024/12/09 18:10:32 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parsing(t_first *f)
{
    lexer(f, f->buffer);
}


void lexer(t_first *f, char *str)
{
    int len;
    t_tokens *current_token;
    f->i = 0;
    f->token_list = NULL;
    
    while (str[f->i] && ft_isspace(str[f->i]) == 1)
        f->i++;
    while (str[f->i])
    {   
        len = f->i;
        if (str[f->i] == '$')                              
            current_token = variable_token(str, f, len);
        else if (ft_isquote(str[f->i]) == 1)
            current_token = quote_token(str, f, len);
        else if (str[f->i] == '(' || str[f->i] == ')')
            current_token = bracket_token(str, f, len);
        else if (ft_isoperator(str[f->i]) == 1)
            current_token = operators_token(str, f, len);
        else if (ft_isspace(str[f->i]) == 1)
            current_token = space_token(str, f);
        else
            current_token = word_token(str, f, len);
        if (!current_token)
            return ;
        printf("string :   #%s#  ", current_token->data);
        printf("      type: %s\n", token_type_to_string(current_token->type));
        add_back_token(&f->token_list, current_token);
    }
    printf("the list\n");
    t_tokens *tmp = f->token_list;
    while(tmp)
    {
        printf("s: %s\n", tmp->data);
        tmp = tmp->next;
    }
} // echo $_ handel this later

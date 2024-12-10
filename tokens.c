/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:33:53 by meid              #+#    #+#             */
/*   Updated: 2024/12/10 16:00:24 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parsing(t_first *f)
{
    lexer(f, f->buffer);
    // add delimiter for here_doc before expansion to not expand $ in the delimeter
    expand_variables(f);
    t_tokens *tmp = f->token_list;
    printf("\nAFTER EXPANSIONS\n");
    while(tmp)
    {
        printf("string :   #%s#  ", tmp->data);
        printf("      type: %s\n", token_type_to_string(tmp->type));
        tmp = tmp->next;
    }
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
        else if (ft_is(str[f->i], "quote"))
            current_token = quote_token(str, f, len);
        else if (ft_is(str[f->i], "brackets"))
            current_token = bracket_token(str, f, len);
        else if (ft_is(str[f->i], "operator"))
            current_token = operators_token(str, f, len);
        else if (ft_is(str[f->i], "space"))
            current_token = space_token(str, f);
        else
            current_token = word_token(str, f, len);
        if (!current_token)
            return ;
        else if (ft_strcmp(current_token->data, "env") == 0) // just for fun "will remove leter"
        {
            print_env(f, 0);
            continue;
        }
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


void expand_variables(t_first *f)
{
    t_tokens *cursor;
    
    cursor = f->token_list;
    
    while (cursor != NULL)
    {
        if (cursor->type == ENV_VAR)
            expand_envp(cursor, f);
        else if (cursor->type == D_QUOTES)
            expand_d_quotes(cursor, f);
        cursor = cursor->next;
    }
}


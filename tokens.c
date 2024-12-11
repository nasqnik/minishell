/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:33:53 by meid              #+#    #+#             */
/*   Updated: 2024/12/11 19:34:51 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parsing(t_first *f)
{
    lexer(f, f->buffer);
    // add delimiter for here_doc before expansion to not expand $ in the delimeter
    // expand_variables(f);
    wildcard(f);
    t_tokens *tmp = f->token_list;
    printf("\nAFTER EXPANSIONS\n");
    while(tmp)
    {
        if (tmp->data_type == 's')
            printf("string :   #%s#  \n", (char *)tmp->data);
        if (tmp->data_type == 'l')
        {
            if (tmp->data != NULL)
            {
                t_w_tmp *tmp_data = (t_w_tmp *)tmp->data;
                printf("list\n");
                while (tmp_data)
                {
                    printf("list :   #%s#  ", tmp_data->data);
                    tmp_data = tmp_data->next;
                }
            }

        }
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
        printf("string :   #%s#  ", (char *)current_token->data);
        printf("      type: %s\n", token_type_to_string(current_token->type));
        add_back_token(&f->token_list, current_token);
    }
    printf("the list\n");
    t_tokens *tmp = f->token_list;
    while(tmp)
    {
        printf("s: %s\n", (char *)tmp->data);
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


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:28:33 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/12 18:52:11 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void rename_tokens(t_first *f)
{
    t_tokens *cursor;
    cursor = f->token_list;
    int i = 0;
        
    while (cursor)
    {
        i = 0;
        printf("hi\n");
        if (!(cursor->type >= PIPE && cursor->type <= LOGIC_OR))
        {
            sleep(1);
            printf("hiiii\n");
            if (cursor->type == WORD && i == 0)
            {
                printf("0\n");
                cursor->type = COMMAND;
            }
            else if ((cursor->type >= D_QUOTES && cursor->type <= WORD) 
                && ((char *)(cursor->data))[0] == '-' && i != 0) // could be a d_quotes
            {
                printf("1\n");
                cursor->type = FLAG;
            }
            else if ((cursor->type >= REDIRECT_IN && cursor->type <= REDIRECT_APPEND) 
                && cursor->next)
            {
                printf("2\n");
                if (cursor->next->type == WSPACE && cursor->next->next)
                {
                    printf("3\n");
                    cursor = cursor->next;
                }
                cursor = cursor->next;
                if (cursor->type == WORD)
                {
                    printf("4\n");
                    cursor->type = FILENAME;
                }
            }
            else if (cursor->type >= D_QUOTES && cursor->type <= ENV_VAR)
                cursor = make_argument(cursor);
            i++;
        }
        if (cursor->type >= PIPE && cursor->type <= LOGIC_OR)
            i = 0;
        cursor = cursor->next;
    }
}
// could be a d_quotes

t_tokens *make_argument(t_tokens *cursor)
{
    t_tokens *tmp_token;
    char *tmp;
    int i = 0;
    
    tmp_token = cursor;
    tmp_token->type = ARGUMENT;
    tmp_token->data_type = 's';
    tmp = tmp_token->data;
    
    if (cursor->next)
        cursor = cursor->next;
    while (cursor && (cursor->type >= D_QUOTES && cursor->type <= WSPACE))
    {
        tmp_token->data = ft_strjoin(tmp, cursor->data);
        free(tmp);
        if (cursor->next)
            tmp = cursor->next->data;
        cursor = cursor->next;
        i++;
    }
    //clear_extra_tokens(tmp_token);
    return (cursor);
}

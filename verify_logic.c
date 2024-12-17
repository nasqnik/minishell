/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:51:42 by meid              #+#    #+#             */
/*   Updated: 2024/12/17 13:44:23 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int Control_Operators(t_tokens *cursor, int index)
{
    if (!cursor->next || (cursor->next
    && (cursor->next->type >= PIPE && cursor->next->type <= LOGIC_OR))
    || (index == 0))
        return(1);
    return (0);
}

int Redirection_Operators(t_tokens *cursor)
{
    if (!cursor->next
        || (cursor->next && ((cursor->type == HEREDOC && cursor->next->type != DELIMITER)
        || (cursor->next->type != FILENAME))))
        return (1);
    // if (cursor->next->next && index == 0)
    //     cursor->next->next->type = COMMAND; 
    return (0);
}

int verify_logic(t_first *f)
{
    t_tokens *cursor;
    int to_return  = 0;
    int i = 0;
    // int part = 0;
    
    cursor = f->token_list;
    while (cursor)
    {
        if (cursor->type >= PIPE && cursor->type <= LOGIC_OR)
            to_return = Control_Operators(cursor, i);
        if (cursor->type >= REDIRECT_IN && cursor->type <= REDIRECT_APPEND)
            to_return = Redirection_Operators(cursor);
        if (to_return != 0)
            return(handle_error(f, "logic_error", 1), to_return);
        cursor = cursor->next;
        i++;
    }
    return (to_return);
}
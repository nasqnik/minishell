/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:51:42 by meid              #+#    #+#             */
/*   Updated: 2025/01/07 18:40:15 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int control_operators(t_tokens *cursor, int index)
{
    if (!cursor->next || (cursor->next
    && (cursor->next->type >= PIPE && cursor->next->type <= LOGIC_OR))
    || (index == 0))
        return(1);
    return (0);
}

int redirection_operators(t_tokens *cursor)
{
    if (!cursor->next
        || (cursor->next && ((cursor->type == HEREDOC && cursor->next->type != DELIMITER)
        || (cursor->next->type != FILENAME))))
        return (5);
    return (0);
}

int subshell_rules(t_tokens *cursor, int flag)
{
    if (flag == 1)
    {
        if (!(cursor->next))
            return (0);
        if (cursor->next->type == BRACKET)
            return (2);
        if (!(cursor->next->type >= REDIRECT_IN && cursor->next->type <= LOGIC_OR))
            return (3);
    }
    if (flag == 0)
    {
        if (cursor->type == COMMAND)
            return (4);
        if (!(cursor->type >= REDIRECT_IN && cursor->type <= LOGIC_OR))
            return (2);
    } 
    return (0);
}

char *first_word(char *str)
{
    char *first;
    int i = 0;
    int start;
    while (str[i] == ' ')
        i++;
    if (str[i] == '(')
        i++;
    start = i;
    while (str[i] != ' ' && str[i] != ')')
        i++;
    first = ft_substr(str, start, i - start);
    return (first);
}
int verify_logic(t_info *info)
{
    t_tokens *cursor;
    int to_return  = 0;
    int i = 0;
    // int part = 0;
    
    cursor = info->token_list;
    while (cursor)
    {
        if (cursor->type >= PIPE && cursor->type <= LOGIC_OR)
            to_return = control_operators(cursor, i);
        if (cursor->type >= REDIRECT_IN && cursor->type <= REDIRECT_APPEND)
            to_return = redirection_operators(cursor);
        if (cursor->type == BRACKET)
            to_return = subshell_rules(cursor, 1);
        if (cursor->next && cursor->next->type == BRACKET)
            to_return = subshell_rules(cursor, 0);
        // to_return_function(to_return, cursor);
        if (to_return == 1)
        {
            if (cursor->next)
                return(handle_error(info, cursor->next->data, 2, '\0'), to_return);
            return(handle_error(info, cursor->data, 2, '\0'), to_return);
        }
        if (to_return == 5)
        {
            if (cursor->next && cursor->next->type == PIPE)
                return(handle_error(info, "(Forced Redirection)", 2, '\0'), 1);
            return(handle_error(info, cursor->next->data, 2, '\0'), 1);
        }
        if (to_return == 2)
            return(handle_error(info, "(", 2, '\0'), 1);
        if (to_return == 3)
            return(handle_error(info, cursor->next->data, 2, '\0'), 1);
        if (to_return == 4)
        {
            char *first = first_word(cursor->next->data);
            if (first[0] == '(')
                handle_error(info, "(", 2, '\0');
            else
                handle_error(info, first, 2, '\0');
            free(first);
            return (1);
        }
        cursor = cursor->next;
        i++;
    }
    return (to_return);
}
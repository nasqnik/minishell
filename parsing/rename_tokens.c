/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rename_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:37:22 by anikitin          #+#    #+#             */
/*   Updated: 2025/01/04 16:39:29 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int rename_tokens(t_info *info)
{
    t_tokens	*cursor;
	int			i;

	cursor = info->token_list;
	i = 0;
	while (cursor)
    {
        if (cursor && cursor->type == WORD && i == 0)
                cursor->type = COMMAND;
        else if (cursor && (cursor->type >= REDIRECT_IN
			&& cursor->type <= HEREDOC))
            cursor = tokens_after_redirect(info, cursor, i);
        else if (cursor && cursor->type == WORD)
            cursor->type = ARGUMENT;
        i++;
        if (cursor && ((cursor->type == PIPE 
            || cursor->type == LOGIC_AND 
            || cursor->type == LOGIC_OR)))
			i = 0;
        if (!cursor)
            return (1);
        cursor = cursor->next;
    }
    return (0);
}

t_tokens	*tokens_after_redirect(t_info *info, t_tokens *cursor, int i)
{
	int	flag;

	flag = 0;
	if (i == 0)
		flag++;
    
    int type = cursor->type;
    
    if (!(cursor->next))
        return (handle_error(info, "newline", 2, '\0'), NULL);
    cursor = cursor->next;
	if (cursor && (cursor->type == WORD))
	{
        cursor->type = FILENAME;
        if (type == HEREDOC)
            cursor->type = DELIMITER;
		flag++;
	}
	if (cursor && (cursor->type == WORD) && flag == 2)
		cursor->type = COMMAND;
	return (cursor);
}
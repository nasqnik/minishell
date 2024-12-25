/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rename_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:37:22 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/25 18:32:41 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void rename_tokens(t_info *info)
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
			&& cursor->type <= HEREDOC) && cursor->next)
            cursor = tokens_after_redirect(info, cursor, i);
        else if (cursor && cursor->type == WORD)
            cursor->type = ARGUMENT;
        i++;
        if (cursor && ((cursor->type == PIPE 
            || cursor->type == LOGIC_AND 
            || cursor->type == LOGIC_OR)))
			i = 0;
        cursor = cursor->next;
    }
}

t_tokens	*tokens_after_redirect(t_info *info, t_tokens *cursor, int i)
{
	int	flag;

	flag = 0;
	if (i == 0)
		flag++;
    
    int type = cursor->type;
    
    if (!cursor->next)
        handle_error(info, "nothing after the operator", 1);
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
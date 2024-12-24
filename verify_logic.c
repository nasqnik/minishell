/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:51:42 by meid              #+#    #+#             */
/*   Updated: 2024/12/24 13:00:44 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	control_operators(t_tokens *cursor, int index)
{
	if (!cursor->next || (cursor->next && (cursor->next->type >= PIPE
				&& cursor->next->type <= LOGIC_OR)) || (index == 0))
		return (1);
	return (0);
}

int	redirection_operators(t_tokens *cursor)
{
	if (!cursor->next || (cursor->next && ((cursor->type == HEREDOC
					&& cursor->next->type != DELIMITER)
				&& (cursor->next->type != FILENAME))))
		return (1);
	return (0);
}

int	verify_logic(t_first *f)
{
	t_tokens	*cursor;
	int			i;
	int			to_return;

	to_return = 0;
	i = 0;
	cursor = f->token_list;
	while (cursor)
	{
		if (cursor->type >= PIPE && cursor->type <= LOGIC_OR)
			to_return = control_operators(cursor, i);
		if (cursor->type >= REDIRECT_IN && cursor->type <= REDIRECT_APPEND)
		{
			
			to_return = redirection_operators(cursor);
		}
		if (to_return != 0)
			return (handle_error(f, "logic_error", 1), to_return);
		cursor = cursor->next;
		i++;
	}
	return (to_return);
}

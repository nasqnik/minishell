/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_logic02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:51:42 by meid              #+#    #+#             */
/*   Updated: 2025/02/04 17:05:18 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	control_operators(t_tokens *cursor, int index)
{
	if (!cursor->next || (cursor->next && ((cursor->next->type >= PIPE
					&& cursor->next->type <= LOGIC_OR))))
		return (1);
	if (index == 0)
		return (6);
	return (0);
}

int	redirection_operators(t_tokens *cursor)
{
	if (!cursor->next || (cursor->next
			&& ((cursor->type == HEREDOC && cursor->next->type != DELIMITER)
				|| (cursor->type != HEREDOC
					&& cursor->next->type != FILENAME))))
		return (5);
	return (0);
}

int	subshell_rules(t_tokens *cursor, int flag)
{
	if (flag == 1)
	{
		if (!(cursor->next))
			return (0);
		if (cursor->next->type == BRACKET)
			return (2);
		if (cursor->next->type == COMMAND
			|| cursor->next->type == ARGUMENT)
			return (3);
	}
	return (0);
}

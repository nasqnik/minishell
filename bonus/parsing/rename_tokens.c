/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rename_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:37:22 by anikitin          #+#    #+#             */
/*   Updated: 2025/01/14 17:16:52 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	loopp(t_info *info, t_tokens	**cursor, int *i, int *j)
{
	if ((*cursor) && (*cursor)->type == WORD && (*i) == 0)
	{
		(*cursor)->type = COMMAND;
		(*j) = 1;
	}
	else if ((*cursor) && ((*cursor)->type >= REDIRECT_IN
			&& (*cursor)->type <= HEREDOC))
		(*cursor) = tokens_after_redirect(info, (*cursor), j);
	else if ((*cursor) && (*cursor)->type == WORD)
		(*cursor)->type = ARGUMENT;
	(*i)++;
	if ((*cursor) && (((*cursor)->type == PIPE || (*cursor)->type == LOGIC_AND
				|| (*cursor)->type == LOGIC_OR)))
	{
		(*i) = 0;
		(*j) = 0;
	}
}

int	rename_tokens(t_info *info)
{
	t_tokens	*cursor;
	int			i;
	int			j;

	cursor = info->token_list;
	i = 0;
	j = 0;
	while (cursor)
	{
		loopp(info, &cursor, &i, &j);
		if (!cursor)
			return (1);
		cursor = cursor->next;
	}
	return (0);
}

t_tokens	*tokens_after_redirect(t_info *info, t_tokens *cursor, int *j)
{
	int	type;

	type = cursor->type;
	if (!(cursor->next))
		return (handle_error(info, "newline", 2, '\0'), NULL);
	if ((cursor->next) && (cursor->next->type >= REDIRECT_IN
			&& cursor->next->type <= HEREDOC))
		return (handle_error(info, cursor->next->data, 2, '\0'), NULL);
	cursor = cursor->next;
	if (cursor && (cursor->type == WORD))
	{
		cursor->type = FILENAME;
		if (type == HEREDOC)
			cursor->type = DELIMITER;
	}
	if (cursor->next && (cursor->next->type == WORD) && (*j) == 0)
	{
		cursor->next->type = COMMAND;
		cursor = cursor->next;
		(*j) = 1;
	}
	return (cursor);
}

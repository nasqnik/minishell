/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:28:33 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/13 19:02:58 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//  in -k mo -k error

t_tokens	*rename_one_part(t_tokens *cursor, int i)
{
	if (cursor && cursor->type == WORD && i == 0)
		cursor->type = COMMAND;
	else if (cursor && (cursor->type >= D_QUOTES && cursor->type <= WORD)
		&& ((char *)(cursor->data))[0] == '-' && i != 0)
		cursor->type = FLAG;
	else if (cursor && (cursor->type >= REDIRECT_IN
			&& cursor->type <= REDIRECT_APPEND) && cursor->next)
	{
		cursor = cursor->next;
		if (cursor && cursor->type == WSPACE && cursor->next)
			cursor = cursor->next;
		if (cursor && cursor->type == WORD)
			cursor->type = FILENAME;
	}
	else if (cursor && cursor->type >= D_QUOTES && cursor->type <= ENV_VAR)
		cursor = make_argument(cursor);
	return (cursor);
}

void	rename_tokens(t_first *f)
{
	t_tokens	*cursor;
	int			i;

	cursor = f->token_list;
	i = 0;
	while (cursor)
	{
		if (cursor->next && cursor->type == WSPACE)
			cursor = cursor->next;
		if (!(cursor->type >= PIPE && cursor->type <= LOGIC_OR))
		{
			cursor = rename_one_part(cursor, i);
			i++;
		}
		if (cursor && cursor->type >= PIPE && cursor->type <= LOGIC_OR)
			i = 0;
		if (cursor && !((cursor->type >= D_QUOTES && cursor->type <= WORD)))
			cursor = cursor->next;
	}
}

void	clear_extra_tokens(t_tokens *start, t_tokens *end)
{
	t_tokens	*cursor;
	t_tokens	*tmp;

	cursor = start->next;
	if (!start)
		return ;
	while (cursor && cursor != end)
	{
		tmp = cursor;
		cursor = cursor->next;
		if (tmp->data)
			free(tmp->data);
		free(tmp);
	}
	if (cursor)
		start->next = cursor;
	else
		start->next = NULL;
}

int	quick_checkup(t_tokens *cursor)
{
	if (cursor->next && cursor->type == WSPACE
		&& ((!(cursor->next->type >= D_QUOTES && cursor->next->type <= ENV_VAR))
			|| ((cursor->next->type >= D_QUOTES && cursor->next->type <= WORD)
				&& ((char *)(cursor->next->data))[0] == '-')))
		return (1);
	if (cursor && (cursor->type >= D_QUOTES && cursor->type <= WORD)
		&& ((char *)(cursor->data))[0] == '-')
		return (1);
	return (0);
}

t_tokens	*make_argument(t_tokens *cursor)
{
	t_tokens	*tmp_token;
	char		*tmp;
	int			i;

	i = 0;
	tmp_token = cursor;
	tmp_token->type = ARGUMENT;
	tmp = tmp_token->data;
	if (!cursor->next)
		return (tmp_token);
	cursor = cursor->next;
	while (cursor && (cursor->type >= D_QUOTES && cursor->type <= WSPACE))
	{
		if (quick_checkup(cursor) == 1)
			break ;
		tmp_token->data = ft_strjoin(tmp, cursor->data);
		free(tmp);
		if (cursor->next)
			tmp = tmp_token->data;
		cursor = cursor->next;
		i++;
	}
	clear_extra_tokens(tmp_token, cursor);
	return (tmp_token);
}

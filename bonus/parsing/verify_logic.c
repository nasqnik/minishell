/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:51:42 by meid              #+#    #+#             */
/*   Updated: 2025/02/04 17:05:26 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static char	*first_word(char *str)
{
	char	*first;
	int		i;
	int		start;

	i = 0;
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

static int	return_four(t_info *info, t_tokens *cursor)
{
	char	*first;

	first = NULL;
	first = first_word(cursor->next->data);
	if (first[0] == '(')
		handle_error(info, "(", 2, '\0');
	else
		handle_error(info, first, 2, '\0');
	return (free(first), 1);
}

int	print_error_from_return_value(t_info *info, int to_return, t_tokens *cursor)
{
	if (to_return == 1 || to_return == 6)
	{
		if (cursor->next && to_return != 6)
			return (handle_error(info, cursor->next->data, 2, '\0'), to_return);
		return (handle_error(info, cursor->data, 2, '\0'), 1);
	}
	if (to_return == 5)
	{
		if (cursor->next && cursor->next->type == PIPE)
			return (handle_error(info, "(Forced Redirection)", 2, '\0'), 1);
		return (handle_error(info, cursor->next->data, 2, '\0'), 1);
	}
	if (to_return == 2)
		return (handle_error(info, "(", 2, '\0'), 1);
	if (to_return == 3)
		return (handle_error(info, cursor->next->data, 2, '\0'), 1);
	if (to_return == 4)
		return (return_four(info, cursor), 1);
	return (0);
}

int	verify_logic(t_info *info)
{
	t_tokens	*cursor;
	int			i;
	int			to_return;

	i = 0;
	to_return = 0;
	cursor = info->token_list;
	while (cursor)
	{
		if (cursor->type >= PIPE && cursor->type <= LOGIC_OR)
			to_return = control_operators(cursor, i);
		if (cursor->type >= REDIRECT_IN && cursor->type <= HEREDOC)
			to_return = redirection_operators(cursor);
		if (cursor->type == BRACKET)
			to_return = subshell_rules(cursor, 1);
		if (print_error_from_return_value(info, to_return, cursor))
			return (1);
		cursor = cursor->next;
		i++;
	}
	return (to_return);
}

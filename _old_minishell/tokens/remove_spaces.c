/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:41:57 by meid              #+#    #+#             */
/*   Updated: 2024/12/24 16:46:56 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_spaces(t_first *f)
{
	t_tokens	*tmp;
	t_tokens	*to_delete;

	to_delete = NULL;
	tmp = f->token_list;
	if (!f || !f->token_list)
		return ;
	while (tmp)
	{
		if ((tmp->next && tmp->next->type == WSPACE))
		{
			if (tmp->type == ARGUMENT
				&& (tmp->next->next && tmp->next->next->type == ARGUMENT))
			{
				tmp->next->type = ARGUMENT;
				tmp = tmp->next;
			}
			else
			{
				to_delete = tmp->next;
				if (tmp->next->next)
					tmp->next = tmp->next->next;
				else
					tmp->next = NULL;
				free(to_delete->data);
				free(to_delete);
			}
			
		}
		else
			tmp = tmp->next;
	}
	// while (tmp)
	// {
	// 	if ((tmp->type == ARGUMENT || tmp->type == FLAG) && (tmp->next
	// 		&& tmp->next->type == WSPACE) && (!tmp->next->next
	// 		||  (tmp->next->next && tmp->next->next->type != ARGUMENT && tmp->next->next->type != FLAG)))
	// 	{
	// 		to_delete = tmp->next;
	// 		if (tmp->next->next)
	// 			tmp->next = tmp->next->next;
	// 		else
	// 			tmp->next = NULL;
	// 		free(to_delete->data);
	// 		free(to_delete);
	// 	}
	// 	else if ((tmp->type == ARGUMENT || tmp->type == FLAG) && (tmp->next
	// 		&& tmp->next->type == WSPACE) && (tmp->next->next && (tmp->next->next->type == ARGUMENT || tmp->next->next->type == FLAG)))
	// 	{
	// 		tmp->next->type = ARGUMENT;
	// 		tmp = tmp->next;
	// 	}
	// 	else
	// 		tmp = tmp->next;
	// }
}

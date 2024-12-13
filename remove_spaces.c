/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:41:57 by meid              #+#    #+#             */
/*   Updated: 2024/12/13 18:44:19 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_spaces(t_first *f)
{
	t_tokens	*tmp;
	t_tokens	*to_delete;

	to_delete = NULL;
	tmp = f->token_list;
	if (!f || !f->token_list)
        return;
	while (tmp)
	{
		if (tmp->next && tmp->next->type == WSPACE)
		{
			to_delete = tmp->next;
			if (tmp->next->next)
				tmp->next = tmp->next->next;
			else
				tmp->next = NULL;
			free(to_delete->data);
			free(to_delete);
		}
		else
			tmp = tmp->next;
	}
}
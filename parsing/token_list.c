/* ************************************************************************** */
/*				                                                             */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:31:13 by meid              #+#    #+#             */
/*   Updated: 2024/12/13 18:00:53 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	*ft_lstlast_token(t_tokens *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_tokens	*ft_create_token(t_info *info, int len, int type, char *str)
{
	t_tokens	*new;
	int			token_len;

	token_len = len;
	new = malloc(sizeof(t_tokens));
	if (new)
	{
		new->data = ft_substr(str, info->i - len, token_len);
		new->type = type;
		new->next = NULL;
		new->fd = -1;
	}
	return (new);
}

void	add_back_token(t_tokens **lst, t_tokens *neww)
{
	t_tokens	*last;

	if (*lst == NULL)
	{
		*lst = neww;
		return ;
	}
	last = ft_lstlast_token(*lst);
	last->next = neww;
}

void	ft_clear_tokens(t_tokens **token_list)
{
	t_tokens	*current;
	t_tokens	*next;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	while (current)
	{
		if (current->next)
			next = current->next;
		else
			next = NULL;
		if (current->data)
			free(current->data);
		current->data = NULL;
		free(current);
		current = next;
	}
	*token_list = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:31:03 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/09 09:51:07 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens *ft_lstlast_token(t_tokens *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_tokens *ft_create_token(t_first *f, int len, int type, char *str)
{
    t_tokens *new;
    
    new = malloc(sizeof(t_tokens));
    if (new)
    {
        new->data = ft_substr(str, f->i - len, len);
        new->len = len;
        new->type = type;
        new->next = NULL;
    }
    return (new);
}

void	add_back_token(t_tokens **lst, t_tokens *new)
{
    static int i = 1;
	t_tokens	*last;

    if (*lst == NULL)
    {
        *lst = new;
        return ;
    }
	last = ft_lstlast_token(*lst);
    i++;
	last->next = new;
}

void ft_clear_tokens(t_tokens **token_list)
{
    t_tokens *current = *token_list;
    t_tokens *next;

    while (current)
	{
        next = current->next;
        if (current->data) {
            free(current->data);
            current->data = NULL;
        }
        free(current);
        current = next;
    }
    *token_list = NULL;
}

/* ************************************************************************** */
/*			                                                                */
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

t_tokens	*ft_create_token(t_first *f, int len, int type, char *str)
{
	t_tokens	*new;
	int			token_len;

	token_len = len;
	new = malloc(sizeof(t_tokens));
	if (new)
	{
		if (type == D_QUOTES || type == S_QUOTES || type == BRACKET)
		{
			token_len = len - 2;
			new->data = ft_substr(str, f->i - len + 1, token_len);
		}
		else if (type == ENV_VAR)
		{
			token_len = len - 1;
			new->data = ft_substr(str, f->i - len + 1, token_len);
		}
		else
			new->data = ft_substr(str, f->i - len, token_len);
		new->data_type = 's';
		new->len = token_len;
		new->type = type;
		new->next = NULL;
	}
	return (new);
}

void	add_back_token(t_tokens **lst, t_tokens *new)
{
	t_tokens	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast_token(*lst);
	last->next = new;
}

void	ft_clear_tmp(t_w_tmp **lst)
{
	t_w_tmp	*current;
	t_w_tmp	*tmp;

	if (!lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
            free (tmp->data);
            tmp->data = NULL;   
		free(tmp);
        tmp = NULL;
	}
	*lst = NULL;
}

void	ft_clear_node(t_tokens *node)
{
	t_w_tmp	*tmp_data;

	tmp_data = NULL;
	if (!node)
		return ;
	if (node->data)
	{
		if (node->data_type == 'l')
		{
			tmp_data = (t_w_tmp *)node->data;
			ft_clear_tmp(&tmp_data);
		}
		else if (node->data_type == 's')
		{
			free(node->data);
			node->data = NULL;
		}
	}
	free(node);
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
		next = current->next;
		ft_clear_node(current);
		current = next;
	}
	*token_list = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:46:02 by meid              #+#    #+#             */
/*   Updated: 2024/12/13 18:59:43 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list	*ft_lstnew(char *env_var)
{
	t_list	*new;
	int		i;

	new = malloc((sizeof(t_list)));
	if (new)
	{
		i = 0;
		while (env_var[i] != '=')
			i++;
		new->key = ft_substr(env_var, 0, i);
		new->value = ft_substr(env_var, i + 1, ft_strlen(env_var) - i - 1);
		new->next = NULL;
	}
	return (new);
}

static t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

static void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

void	env_to_list(t_first *f)
{
	t_list	*new_node;
	int		k;

	f->i = 0;
	f->env_size = 0;
	new_node = NULL;
	while (f->envp_array[f->env_size])
		f->env_size++;
	f->envp_list = ft_lstnew(f->envp_array[0]);
	k = 1;
	while (k < f->env_size)
	{
		new_node = ft_lstnew(f->envp_array[k]);
		if (!new_node)
			return ;
		ft_lstadd_back(&f->envp_list, new_node);
		k++;
	}
}

void	ft_clear_list(t_list **lst)
{
	t_list	*current;
	t_list	*tmp;

	if (!lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	*lst = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:46:02 by meid              #+#    #+#             */
/*   Updated: 2024/12/10 17:25:17 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*ft_lstnew(char *env_var)
{
	t_list	*new;
 
	new = malloc((sizeof(t_list)));
	if (new)
	{
        int i = 0;
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

void env_to_list(t_first *f)
{
    f->i = 0;
    f->env_size = 0;
    while (f->envp_array[f->env_size])
        f->env_size++;
    f->envp_list = ft_lstnew(f->envp_array[0]);
    int k = 1;
    while (k < f->env_size)
    {
        t_list *new_node = ft_lstnew(f->envp_array[k]);
        if (!new_node)
            return ;
        ft_lstadd_back(&f->envp_list, new_node);
        k++;       
    }
}

void print_env(t_first *f, int flag)
{
    t_list *tmp = f->envp_list;
    int i = 0;
    while (tmp)
    {
        if (flag == 0)
            printf("%s\n", f->envp_array[i]);
        else
        {
            printf("key: %s\n", tmp->key);
            printf("value: %s\n", tmp->value);
        }
        tmp = tmp->next;
        i++;
    } 
}
char *search_in_env(t_first *f, char *key)
{
    t_list *tmp = f->envp_list;
    while(tmp)
    {
        if (ft_strcmp(tmp->key, key) == 0)
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
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
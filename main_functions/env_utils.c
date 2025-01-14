/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:46:02 by meid              #+#    #+#             */
/*   Updated: 2025/01/14 12:05:32 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_function(void **one, void **two, void **three, void **four)
{
	if (one && *one)
	{
		free(*one);
		*one = NULL;
	}
	if (two && *two)
	{
		free(*two);
		*two = NULL;
	}
	if (three && *three)
	{
		free(*three);
		*three = NULL;
	}
	if (four && *four)
	{
		free(*four);
		*four = NULL;
	}
}

int	set_value_and_flag(char *env_var, int flag, t_env **new, int *i)
{
	while (env_var[(*i)] && env_var[(*i)] != '=')
		(*i)++;
	(*new)->key = ft_substr(env_var, 0, (*i));
	if (!(*new)->key)
	{
		free_function((void **)&((*new)->env), (void **)&(*new), NULL, NULL);
		return (1);
	}
	if (env_var[(*i)])
		(*i)++;
	if (env_var[(*i)])
	{
		(*new)->value = ft_substr(env_var, (*i), ft_strlen(env_var) - (*i));
		if (!(*new)->value)
		{
			free_function((void **)&((*new)->key), (void **)&((*new)->env),
				(void **)&(*new), NULL);
			return (1);
		}
	}
	else
		(*new)->value = NULL;
	(*new)->flag = flag;
	(*new)->next = NULL;
	return (0);
}

t_env	*env_lstnew(char *env_var, int flag)
{
	t_env	*new;
	int		i;

	if (!env_var)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->env = NULL;
	new->key = NULL;
	new->value = NULL;
	i = 0;
	new->env = ft_strdup(env_var);
	if (!new->env)
	{
		free(new);
		return (NULL);
	}
	if (set_value_and_flag(env_var, flag, &new, &i))
		return (NULL);
	return (new);
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	ft_clear_list(t_env **lst)
{
	t_env	*current;
	t_env	*tmp;

	if (!lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp->env);
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	*lst = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:46:02 by meid              #+#    #+#             */
/*   Updated: 2025/01/12 13:55:27 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *env_lstnew(char *env_var, int flag) {
    t_env *new;
    int i;

    if (!env_var)
        return NULL;
    new = malloc(sizeof(t_env));
    if (!new)
	{
		printf("the allocation of new is not happning\n");
        return NULL;
	}
    i = 0;
    new->env = ft_strdup(env_var);
    if (!new->env) {
        free(new);
        return NULL;
    }
    while (env_var[i] && env_var[i] != '=')
        i++;
    new->key = ft_substr(env_var, 0, i);
    if (!new->key) {
        free(new->env);
        free(new);
        return NULL;
    }
    if (env_var[i])
        i++;
    if (env_var[i]) {
        new->value = ft_substr(env_var, i, ft_strlen(env_var) - i);
        if (!new->value) {
            free(new->key);
            free(new->env);
            free(new);
            return NULL;
        }
    } else {
        new->value = NULL;
    }
    new->flag = flag;
    new->next = NULL;
    return new;
}

// t_env	*env_lstnew(char *env_var, int flag)
// {
// 	t_env	*new;
// 	int		i;

// 	if (!env_var)
// 		return NULL;
// 	new = malloc((sizeof(t_env)));
// 	if (!new)
// 		return NULL;
// 	if (new)
// 	{
// 		i = 0;
// 		new->env = ft_strdup(env_var);
// 		while (env_var[i] && env_var[i] != '=')
// 			i++;
// 		new->key = ft_substr(env_var, 0, i);
// 		if (env_var[i])
// 			i++;
// 		if (env_var[i])
// 			new->value = ft_substr(env_var, i , ft_strlen(env_var) - i);
// 		else 
// 			new->value = NULL;
// 		new->flag = flag;
// 		new->next = NULL;
// 	}
// 	return (new);
// }

void	ft_lstadd_front(t_env **lst, t_env *new)
{
	new->next = *lst;
	*lst = new;
}

t_env	*env_lstlast(t_env *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// void	env_lstadd_back(t_env **lst, t_env *new)
// {
// 	t_env	*last;

// 	if (lst == NULL)
// 		return ;
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	last = env_lstlast(*lst);
// 	last->next = new;
// }

void env_lstadd_back(t_env **lst, t_env *new) {
    t_env *last;

    if (lst == NULL)
        return;

    if (*lst == NULL) {
        *lst = new;
        return;
    }

    last = *lst;
    while (last->next)
        last = last->next;
    last->next = new;
}

void env_to_list(t_info *info, int flag) {
    t_env *new_node;
    int k;
    int env_size;

    env_size = 0;
    new_node = NULL;
    if (!(info->envp_array) || !(*(info->envp_array))) {
        printf("you did not create me\n");
        return;
    }
    while (info->envp_array[env_size])
        env_size++;
    info->envp_list = env_lstnew(info->envp_array[0], 1);
    if (!info->envp_list)
        return;
    k = 1;
    while (k < env_size) {
        if (flag == 0 && k == 2)
            new_node = env_lstnew(info->envp_array[k], 0);
        else
            new_node = env_lstnew(info->envp_array[k], 1);
        if (!new_node)
            return;
        env_lstadd_back(&info->envp_list, new_node);
        k++;
    }
}

// void	env_to_list(t_info *info, int flag)
// {
// 	t_env	*new_node;
// 	int		k;
// 	int env_size;

// 	env_size = 0;
// 	new_node = NULL;
// 	if (!(info->envp_array) || !(*(info->envp_array)))
// 	{
// 		printf("you did not creat me\n");
// 		return ;
// 	}
// 	while (info->envp_array[env_size])
// 		env_size++;
// 	info->envp_list = env_lstnew(info->envp_array[0], 1);
// 	k = 1;
// 	while (k < env_size)
// 	{
// 		if (flag == 0 && k == 2)
// 			new_node = env_lstnew(info->envp_array[k], 0);
// 		else
// 			new_node = env_lstnew(info->envp_array[k], 1);
// 		if (!new_node)
// 			return ;
// 		env_lstadd_back(&info->envp_list, new_node);
// 		k++;
// 	}
// }

void	ft_clear_list(t_env **lst)
{
	t_env	*current;
	t_env	*tmp;

	if (!lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		printf("clear\n");
		tmp = current;
		current = current->next;
		free(tmp->env);
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	*lst = NULL;
}

int	ft_lstsize(t_env *lst)
{
	int	counter;

	counter = 0;
	while (lst)
	{
		++counter;
		lst = lst->next;
	}
	return (counter);
}

void update_envp_array(t_info *info)
{
	t_env *env_cur = info->envp_list;

	int counter;
	counter = ft_lstsize(env_cur);
	env_cur = info->envp_list;

	char **new_env_array = malloc((counter + 1) * sizeof(char *));
	new_env_array[counter] = NULL;

	int	j, x;
	int i = 0;

	int c_key;
	int c_val;
	c_key = 0;
	c_val = 0;

	while (i < counter)
	{
		j = 0;
		x = 0;
		c_key = ft_strlen(env_cur->key);
		c_val = ft_strlen(env_cur->value);

		new_env_array[i] = malloc((c_key + c_val + 2) * sizeof(char));
		while (x < c_key)
			new_env_array[i][j++] = env_cur->key[x++];
		new_env_array[i][j++] = '=';
		x = 0;
		while (x < c_val)
			new_env_array[i][j++] = env_cur->value[x++];
		new_env_array[i][j] = '\0';

		// printf("string: %s\n", new_env_array[i]);

		env_cur = env_cur->next;
		i++;
	}
	new_env_array[i] = NULL;
	if (info->envp_array)
		free_array(info->envp_array);
	info->envp_array = new_env_array;
}
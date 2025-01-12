/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:30:05 by meid              #+#    #+#             */
/*   Updated: 2025/01/12 14:05:40 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_export_error(t_info *info, char *str)
{
	if (invalid_identifier(str, 1))
	{
		print_the_error(info, str, 3, 1);
		our_static("exit status", 1);
		return (1);
	}
	return (0);
}

void	new_env(t_info *info, char *search_for, char *value, int flagoooo)
{
	char	*the_str;
	char	*tmpo;

	the_str = NULL;
	tmpo = NULL;
	if (flagoooo == 1)	
		tmpo = ft_strjoin(search_for, "=");
	else
		tmpo = ft_strdup(search_for);
	free(search_for);
	if (flagoooo == 1)
	{
		if (value)
			the_str = ft_strjoin(tmpo, value);
		else
			the_str = ft_strdup(tmpo);
	}
	else
		the_str = ft_strdup(tmpo);
	if (value)
		free(value);
	free(tmpo);
	if (flagoooo == 1)
		env_lstadd_back(&info->envp_list, env_lstnew(the_str, 1));
	else
		env_lstadd_back(&info->envp_list, env_lstnew(the_str, 0));
	free(the_str);
}
int	check_env_there(t_info *info, char *search_for, char *value, char flago, int flagoooo)
{
	(void)flago;
	t_env	*tmp;
	char *tmp_joined = NULL;
	char *tmpo = NULL;

	tmp = info->envp_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, search_for) == 0 && (flagoooo == 0 || (value == NULL && flago == 'y' && flagoooo == 1)))
			return (1);
		else if  (ft_strcmp(tmp->key, search_for) == 0 && flagoooo != 0)
		{
			if (flago == 'n')
			{
				free(tmp->env);
				tmpo = ft_strjoin(search_for, "=");
				if (value)
					tmp->env = ft_strjoin(tmpo, value);
				else
					tmp->env = ft_strdup(tmpo);
				free(tmp->value);
				free(tmpo);
				tmp->value = value;
			}
			else
			{
				
				tmp_joined = ft_strjoin(tmp->value, value);
				free(tmp->value);
				if (value)
					free(value);
				tmp->value = tmp_joined;
				free(tmp->env);
				tmpo = ft_strjoin(search_for, "=");
				tmp->env = ft_strjoin(tmpo, tmp_joined);
				printf("%s\n", tmp->env);
				free(tmpo);
			}
			free(search_for);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_export(t_info *info, char **args, int i)
{
	char	*value;
	int		j;
	int		flag;
	char	*search_for;
	char flago;
	int flagoooo = 0; 
	int return_value = 0;

	value = NULL;
	j = 0;
	flag = 0;
	search_for = NULL;
	flago = 'n';
	if (!args[i])
	{
		env_sort(info, info->envp_list);
		return (0);
	}
	while (args[i])
	{
		if (handle_export_error(info, args[i]))
		{
			i++;
			return_value = 1;
			continue;
		}
		else if (ft_strcmp(args[i], " ") != 0)
		{
			j = 0;
			while (args[i][j] && args[i][j] != '=')
				j++;
			if (args[i][j - 1] && args[i][j - 1] == '+')
			{
				flago = 'y';
				search_for = ft_substr(args[i], 0, j - 1);
			}
			else
				search_for = ft_substr(args[i], 0, j);
			if (args[i][j] && args[i][j] == '=')
			{
				flagoooo = 1;
				j++;
			}
			if (args[i][j])
				value = ft_substr(args[i], j, ft_strlen(args[i]) - j);
			else
				value = NULL;
			if (check_env_there(info, search_for, value, flago, flagoooo))
				flag = 1;
			if (flag == 0)
				new_env(info, search_for, value, flagoooo);
		}
		i++;
	}
	printf("return_value %d\n", return_value);
	return (return_value);
}

// void	search_to_unset(t_env *tmp, char *str)
// {
// 	t_env	*tmp1;

// 	tmp1 = NULL;
// 	while (tmp)
// 	{
// 		if (tmp->next && ft_strcmp(tmp->next->key, str) == 0)
// 		{
// 			if (tmp->next->next)
// 				tmp1 = tmp->next->next;
// 			free(tmp->next->env);
// 			free(tmp->next->value);
// 			free(tmp->next->key);
// 			free(tmp->next);
// 			tmp->next = tmp1;
// 		}
// 		tmp = tmp->next;
// 	}
// }

// void	search_to_unset(t_env **begin_list, char *str)
// {
// 	t_env	*cur;

// 	if (begin_list == NULL || *begin_list == NULL)
// 		return;

// 	cur = *begin_list;

// 	if (ft_strcmp(cur->key, str) == 0)
// 	{
// 		*begin_list = cur->next;
// 		free(cur->env);
// 		cur->env = NULL;
// 		free(cur->value);
// 		cur->value = NULL;
// 		free(cur->key);
// 		cur->key = NULL;
// 		free(cur);
// 		cur = NULL;
// 		search_to_unset(begin_list, str);
// 	}
// 	else
// 	{
// 		search_to_unset(&cur->next, str);
// 	}
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void	search_to_unset(t_env **head, char *str)
// {
// 	t_env	*current;
// 	t_env	*prev;

// 	if (!head || !*head) // Handle empty list
// 		return;

// 	current = *head;
// 	prev = NULL;

// 	// Iterate through the list
// 	while (current)
// 	{
// 		if (ft_strcmp(current->key, str) == 0) // Match found
// 		{
// 			if (prev == NULL)
// 				*head = current->next;
// 			else
// 				prev->next = current->next; // Bypass the current node
// 			if (current->env)
// 			{
// 				free(current->env);
// 				current->env = NULL;
// 			}
// 			if (current->value)
// 			{
// 				free(current->value);
// 				current->value = NULL;
// 			}
// 			if (current->key)
// 			{
// 				free(current->key);
// 				current->key = NULL;
// 			}
// 			free(current);
// 			current = NULL;

// 			break; // Exit after deleting one node
// 		}
// 		prev = current;
// 		current = current->next; // Move to the next node
// 	}
	
// 	t_env *tmp = *head;
// 	while (tmp)
// 	{
// 		printf("env: %s. %s=%s\n", tmp->env, tmp->key, tmp->value);
// 		tmp = tmp->next;
// 	}
// }
// void *env1;
// void *env2;

void search_to_unset(t_env **env_list, char *arg)
{
    t_env *current = *env_list;
    t_env *previous = NULL;

    while (current != NULL)
    {
        if (ft_strcmp(current->key, arg) == 0)
        {
            if (previous == NULL)
			{
                *env_list = current->next;
			}
            else
                previous->next = current->next;
			if (current->env)
			{
				if (current->value)
					free(current->value);
				current->value = NULL;
				if (current->key)
					free(current->key);
				current->key = NULL;
				if (current->env)
					free(current->env);
				current->env = NULL;
				if (current)
					free(current);
				current = NULL;
			}
            return;
        }
        previous = current;
        current = current->next;
    }
}

#include "assert.h"
int	ft_unset(t_info *info, char **args, int i)
{
	t_env **tmp;
	int fd;
	int return_value = 0;

	tmp = NULL;
	fd = 1;
	while (args[i])
	{
		if (invalid_identifier(args[i], 2))
		{
			print_the_error(info, args[i], 3, fd);
			printf("our_static: %d\n", our_static("exit status", 1));
			return_value = 1;
			i++;
			continue ;
		}
		else if (ft_strcmp(args[i], " ") != 0)
		{
			tmp = &info->envp_list;
			search_to_unset(tmp, args[i]);
		}
		i++;
	}
	return (return_value);
}
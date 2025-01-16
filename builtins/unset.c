/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:01:59 by meid              #+#    #+#             */
/*   Updated: 2025/01/16 18:05:09 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	delete_env_node(t_env **env_list, t_env *current, t_env *previous)
{
	if (previous == NULL)
		*env_list = current->next;
	else
		previous->next = current->next;
	if (current->value)
		free(current->value);
	if (current->key)
		free(current->key);
	if (current->env)
		free(current->env);
	free(current);
	current = NULL;
}

void	search_to_unset(t_env **env_list, char *arg)
{
	t_env	*current;
	t_env	*previous;

	current = *env_list;
	previous = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, arg) == 0)
		{
			delete_env_node(env_list, current, previous);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

int	ft_unset(t_info *info, char **args, int i)
{
	t_env	**tmp;
	int		fd;
	int		return_value;

	return_value = 0;
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

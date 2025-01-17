/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:10:31 by meid              #+#    #+#             */
/*   Updated: 2025/01/17 14:46:44 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	env_lstadd_back(&info->envp_list, env_lstnew(the_str, flagoooo));
	free(the_str);
}

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

void	print_export(t_info *info)
{
	t_env	*tmp1;

	tmp1 = info->envp_list;
	while (tmp1)
	{
		printf("declare -x ");
		printf("%s", tmp1->key);
		if (tmp1->flag == 1 && tmp1->value)
			printf("=%s", tmp1->value);
		if (tmp1->flag == 1 && !(tmp1->value))
			printf("=\"\"");
		printf("\n");
		tmp1 = tmp1->next;
	}
}

void	env_sort(t_info *info, t_env *envp_list)
{
	t_env	*tmp;
	t_env	*new_node;
	t_env	**current;

	tmp = envp_list;
	while (tmp && tmp->env)
	{
		new_node = env_lstnew(tmp->env, tmp->flag);
		if (!new_node)
			return ;
		current = &info->export_tmp;
		while (*current && ft_strcmp((*current)->env, new_node->env) < 0)
		{
			current = &((*current)->next);
		}
		new_node->next = *current;
		*current = new_node;
		tmp = tmp->next;
	}
	print_export(info);
	ft_clear_list(&info->export_tmp);
	info->export_tmp = NULL;
}

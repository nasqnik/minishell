/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:30:21 by meid              #+#    #+#             */
/*   Updated: 2025/02/03 10:24:49 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// add free for all of the errors

void	add_to_the_value(char *search_for, char *value, t_env **tmp, char *tmpo)
{
	char	*tmp_joined;
	char	*without_quotes;

	tmp_joined = NULL;
	without_quotes = NULL;
	(*tmp)->flag = 1;
	if ((*tmp)->value)
	{
		without_quotes = ft_strtrim_sides((*tmp)->value);
		tmp_joined = ft_strjoin(without_quotes, value);
		free(without_quotes);
		free((*tmp)->value);
	}
	else
		tmp_joined = ft_strdup(value);
	if (value)
		free(value);
	(*tmp)->value = add_quotes(tmp_joined);
	if (!((*tmp)->value))
		return ;
	free((*tmp)->env);
	tmpo = ft_strjoin(search_for, "=");
	(*tmp)->env = ft_strjoin(tmpo, tmp_joined);
	free(tmp_joined);
	free(tmpo);
}

void	set_new_value(char *search_for, char *value, t_env **tmp)
{
	char	*tmpo;

	tmpo = NULL;
	(*tmp)->flag = 1;
	free((*tmp)->env);
	tmpo = ft_strjoin(search_for, "=");
	if (value)
		(*tmp)->env = ft_strjoin(tmpo, value);
	else
		(*tmp)->env = ft_strdup(tmpo);
	free((*tmp)->value);
	free(tmpo);
	(*tmp)->value = value;
}

int	check_env_there(t_info *info, char *search_for, char *value, int flag[2])
{
	t_env	*tmp;

	tmp = info->envp_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, search_for) == 0 && (flag[1] == 0
				|| (value == NULL && flag[0] == 1 && flag[1] == 1)))
			return (1);
		else if (ft_strcmp(tmp->key, search_for) == 0 && flag[1] != 0)
		{
			if (flag[0] == 0)
				set_new_value(search_for, value, &tmp);
			else
				add_to_the_value(search_for, value, &tmp, NULL);
			free(search_for);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	handle_export_str(t_info *info, char *args, int flag[2], int j)
{
	char	*search_for;
	char	*value;

	search_for = NULL;
	value = NULL;
	while (args[j] && args[j] != '=')
		j++;
	if (args[j - 1] && args[j - 1] == '+')
	{
		flag[0] = 1;
		search_for = ft_substr(args, 0, j - 1);
	}
	else
		search_for = ft_substr(args, 0, j);
	if (args[j] && args[j] == '=')
	{
		flag[1] = 1;
		j++;
	}
	if (args[j])
		value = ft_substr(args, j, ft_strlen(args) - j);
	else
		value = NULL;
	if (check_env_there(info, search_for, value, flag) == 0)
		new_env(info, search_for, value, flag[1]);
}

int	ft_export(t_info *info, char **args, int i)
{
	int	flag[2];
	int	return_value;

	flag[0] = 0;
	flag[1] = 0;
	return_value = 0;
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
			continue ;
		}
		else if (ft_strcmp(args[i], " ") != 0)
			handle_export_str(info, args[i], flag, 0);
		i++;
	}
	return (return_value);
}

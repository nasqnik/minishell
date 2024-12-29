/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_dquotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:36:49 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/29 15:36:06 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_variable(char *data, int pov[2], char *result, t_info *info) 
{
	char	*before_var;
	char	*var_value;
	char	*tmp;

	before_var = ft_substr(data, pov[1], pov[0] - pov[1]);
	var_value = handle_var_value(data, pov, info);
	
	tmp = ft_strjoin(result, before_var);
	free(result);
	result = ft_strjoin(tmp, var_value);
	free(tmp);
	// if (data[pov[0]] == '\"')
	// {
	// 	tmp = ft_strjoin(result, "\"");
	// 	free(result);
	// 	result = tmp;
	// }
	free(before_var);
	free(var_value);
	return (result);
}

char *handle_var_value(char *data, int pov[2], t_info *info)
{	
	if (data[pov[0] + 1])
		(pov[0])++;
	if (ft_is(data[pov[0]], "alnum") || data[pov[0]] == '_')
		return (get_var(data, &pov[0], info->envp_list));
	else if (data[pov[0]] == '?')
		return(handle_exit_status(data, pov, info));
	return (ft_strdup("$"));
}

char *handle_exit_status(char *data, int pov[2], t_info *info)
{
	char *tmp;

	tmp = ft_itoa(info->exit_status);
	pov[0]++;
	pov[1] = pov[0];

	while (data[pov[0]] && data[pov[0]] != ' ')
		pov[0]++;
	tmp = append_remaining_data(data, pov, tmp);
	return (tmp);
}

char	*append_remaining_data(char *data, int pov[2], char *result)
{
	char	*remaining_part;
	char	*new_result;

	remaining_part = ft_substr(data, pov[1], pov[0] - pov[1] + 1);
	new_result = ft_strjoin(result, remaining_part);
	free(result);
	free(remaining_part);
	return (new_result);
}

char	*get_var(char *data, int *i, t_env *envp_list)
{
	char	*var_name;
	char	*var_value;
	int		start;

	start = *i;
	var_name = NULL;
	while (data[*i] && (ft_is(data[*i], "alnum") || data[*i] == '_'))
		(*i)++;
	if (*i > start)
	{
		var_name = ft_substr(data, start, *i - start);
		var_value = get_var_value(var_name, envp_list);
		free(var_name);
	}
	else
		var_value = ft_strdup("$");
	return (var_value);
}

char	*get_var_value(char *var_name, t_env *envp_list)
{
	t_env	*cursor;

	cursor = envp_list;
	while (cursor)
	{
		if (!ft_strncmp(var_name, cursor->key, ft_strlen(var_name))
			&& ft_strlen(var_name) == ft_strlen(cursor->key))
			return (ft_strdup(cursor->value));
		cursor = cursor->next;
	}
	return (ft_strdup(""));
}

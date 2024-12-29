/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_dquotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:36:49 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/29 15:50:25 by anikitin         ###   ########.fr       */
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

char *clean_quotes(char *result)
{
	char *end_result;
	int count;
	
	count = 0;
	count_without_quotes(result, &count);	
	end_result = substring_without_quotes(result, count);
	free(result);
	return (end_result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_dquotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:36:49 by anikitin          #+#    #+#             */
/*   Updated: 2025/01/17 14:34:32 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_variable(char *data, int pov[2], char *result, t_info *info) 
{
	char	*before_var;
	char	*var_value;
	char	*tmp;
	// char	*new_result;

	before_var = NULL;
	tmp = NULL;
	var_value = NULL;
	before_var = ft_substr(data, pov[1], pov[0] - pov[1]);
	if (!before_var)
		before_var = ft_strdup("");
	var_value = handle_var_value(data, pov, info);
	tmp = ft_strjoin(result, before_var);
	// if (!tmp)
    // {
    //     free(before_var);
    //     free(var_value);
    //     return NULL; // error
    // }
	if (result)
		free(result);
	result = ft_strjoin(tmp, var_value);
	free(tmp);
	free(before_var);
	free(var_value);
	return (result);
}

char *handle_var_value(char *data, int pov[2], t_info *info)
{	
	if (data[pov[0] + 1])
		(pov[0])++;
	else
	{
		pov[0]++;
		return(ft_strdup("$"));
	}
	if (ft_is(data[pov[0]], "alnum") || data[pov[0]] == '_' || data[pov[0]] == '$')
		return (get_var(data, &pov[0], info->envp_list));
	else if (data[pov[0]] == '?')
		return(handle_exit_status(data, pov, info));
	return (ft_strdup(""));
}


char *handle_exit_status(char *data, int pov[2], t_info *info)
{
	(void)info;
	char *tmp;

	tmp = ft_itoa(our_static("exit status", -1));
	pov[0]++;
	pov[1] = pov[0];

	while (data[pov[0]] && data[pov[0]] != ' ')
		pov[0]++;
	tmp = append_remaining_data(data, pov, tmp, 0); // +1?
	return (tmp);
}

char	*append_remaining_data(char *data, int pov[2], char *result, int flag)
{
	char	*remaining_part;
	char	*new_result;

	remaining_part = ft_substr(data, pov[1], pov[0] - pov[1] + flag);
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
	printf("end_result: %s\n", end_result);
	free(result);
	return (end_result);
}

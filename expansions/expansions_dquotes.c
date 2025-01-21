/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_dquotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:36:49 by anikitin          #+#    #+#             */
/*   Updated: 2025/01/21 12:24:38 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_d_var_value(char *data, int pov[2], t_info *info)
{
	pov[0]++;
	if (data[pov[0]] == '$')
	{
		pov[0]++;
		return (ft_strdup(""));
	}
	if (ft_is(data[pov[0]], "alnum")
		|| data[pov[0]] == '_')
		return (get_var(data, &pov[0], info->envp_list));
	else if (data[pov[0]] == '?')
		return (handle_exit_status(data, pov));
	return (ft_strdup("$"));
}

char	*handle_d_variable(char *data, int pov[2], char *result, t_info *info)
{
	char	*before_var;
	char	*var_value;
	char	*tmp;

	before_var = NULL;
	tmp = NULL;
	var_value = NULL;
	before_var = ft_substr(data, pov[1], pov[0] - pov[1]);
	if (!before_var)
		before_var = ft_strdup("");
	var_value = handle_d_var_value(data, pov, info);
	tmp = ft_strjoin(result, before_var);
	if (result)
		free(result);
	result = ft_strjoin(tmp, var_value);
	free(tmp);
	free(before_var);
	free(var_value);
	return (result);
}
// if (!tmp)
// {
//     free(before_var);
//     free(var_value);
//     return NULL; // error
// } // they was in the function up

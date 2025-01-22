/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:35:08 by meid              #+#    #+#             */
/*   Updated: 2025/01/22 13:47:34 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_hd_var_value(char *data, int pov[2], t_info *info)
{
	char	*res;
	char	*clean_res;

	pov[0]++;
	if (data[pov[0]] == '$')
	{
		pov[0]++;
		return (ft_strdup(""));
	}
	if (ft_is(data[pov[0]], "alnum")
		|| data[pov[0]] == '_')
	{
		res = get_var(data, &pov[0], info->envp_list);
		clean_res = ft_substr(res, 1, ft_strlen(res) - 2);
		free(res);
		return (clean_res);
	}
	else if (data[pov[0]] == '?')
		return (handle_exit_status(data, pov));
	return (ft_strdup("$"));
}

char	*handle_hd_variable(char *data, int pov[2], char *result, t_info *info)
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
	var_value = handle_hd_var_value(data, pov, info);
	tmp = ft_strjoin(result, before_var);
	if (result)
		free(result);
	result = ft_strjoin(tmp, var_value);
	free(tmp);
	free(before_var);
	free(var_value);
	return (result);
}

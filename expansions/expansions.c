/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:16:00 by anikitin          #+#    #+#             */
/*   Updated: 2025/02/05 18:27:07 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*process_var_char(char *str, int pov[2], char *result, t_info *info)
{
	if (str[pov[0]] == '~')
	{
		result = tilda_string(info, str, pov, result);
		pov[1] = pov[0];
	}
	else if (str[pov[0]] == '$')
	{
		result = handle_variable(str, pov, result, info);
		pov[1] = pov[0];
	}
	else
		pov[0]++;
	return (result);
}

char	*expand_variables(char *str, int *pos, t_info *info)
{
	char	*result;
	int		pov[2];

	pov[0] = *pos;
	pov[1] = *pos;
	result = ft_strdup("");
	while (str[pov[0]] && str[pov[0]] != '\'' && str[pov[0]] != '\"')
		result = process_var_char(str, pov, result, info);
	if (pov[1] < pov[0])
		result = append_remaining_data(str, pov, result, 0);
	*pos = pov[0];
	return (result);
}

static char	*expand_d_quotes(char *str, int *pos, t_info *info)
{
	char	*result;
	int		pov[2];

	pov[0] = *pos + 1;
	pov[1] = *pos;
	result = ft_strdup("");
	while (str[pov[0]] && str[pov[0]] != '\"')
	{
		if (str[pov[0]] == '$')
		{
			result = handle_d_variable(str, pov, result, info);
			pov[1] = pov[0];
		}
		else
			pov[0]++;
	}
	if (pov[1] < pov[0] || str[pov[0]] == '\"')
		result = append_remaining_data(str, pov, result, 1);
	*pos = pov[0] + 1;
	return (result);
}

static char	*expand_s_quotes(char *str, int *pos)
{
	char	*result;
	int		i;

	i = *pos + 1;
	while (str[i] && str[i] != '\'')
		i++;
	result = ft_substr(str, *pos, i - *pos + 1);
	*pos = i + 1;
	return (result);
}

char	*process_expansion(char *arg, t_info *info)
{
	int		j;
	char	*result;
	char	*tmp;
	char	*tmp1;

	j = 0;
	result = ft_strdup("");
	tmp = NULL;
	tmp1 = NULL;
	while (arg[j])
	{
		if (arg[j] == '\"')
			tmp = expand_d_quotes(arg, &j, info);
		else if (arg[j] == '\'')
			tmp = expand_s_quotes(arg, &j);
		else
			tmp = expand_variables(arg, &j, info);
		tmp1 = result;
		result = ft_strjoin(tmp1, tmp);
		free(tmp1);
		free(tmp);
	}
	return (result);
}

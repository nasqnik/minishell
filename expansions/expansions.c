/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:16:00 by anikitin          #+#    #+#             */
/*   Updated: 2025/01/13 19:18:34 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *process_expansion(char *arg, t_info *info)
{
	int j;
	char *result;
	char *tmp;
	char *tmp1;
	
	j = 0;
	result = ft_strdup("");
	if (!result)
		return NULL;
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
	printf("result: %s\n", result);
	return (result);
}

char *expand_variables(char *str, int *pos, t_info *info)
{
	char *result;
	char *tmp;
	char *tmp2;
	int pov[2];

	pov[0] = *pos;
	pov[1] = *pos;
	result = ft_strdup("");
	while (str[pov[0]] && str[pov[0]] != '\'' && str[pov[0]] != '\"')
	{
		printf("Im here too\n");
		if (str[pov[0]] == '\'' || str[pov[0]] == '\"')
			break ;
		if (str[pov[0]] == '~')
		{
			result = tilda_string(info, str, pov);
			pov[1] = pov[0];
		}
		if (str[pov[0]] == '$')
		{
			result = handle_variable(str, pov, result, info);
			pov[1] = pov[0];
		}
		else
			pov[0]++;
	}
	if (pov[1] < pov[0])
	{
		printf("I'm here\n");
		tmp = ft_substr(str, pov[1], pov[0] - pov[1]);
		tmp2 = ft_strjoin(result, tmp);
		free(result);
		free(tmp);
		result = tmp2;
	}
	// if (*result == '\0') // fix it
	// {
	// 	free(result);
	// 	result = ft_substr(str, pov[1], pov[0] - pov[1]);
	// }
	*pos = pov[0];
	return (result);
}

char *expand_d_quotes(char *str, int *pos, t_info *info)
{
	char *result;
	int pov[2];

	pov[0] = *pos + 1; 
	pov[1] = *pos;
	result = ft_strdup("");
	while (str[pov[0]] && str[pov[0]] != '\"')
	{
		if (str[pov[0]] == '$')
		{
			result = handle_variable(str, pov, result, info); 
			pov[1] = pov[0];
		}
		else
			pov[0]++;
	}
	if (pov[1] < pov[0] || str[pov[0]] == '\"')
		result = append_remaining_data(str, pov, result);
	*pos = pov[0] + 1;
	return (result);
}

char *expand_s_quotes(char *str, int *pos)
{
	char *result;
	int i;
	
	i = *pos + 1;
	
	while (str[i] && str[i] != '\'')
		i++;
	result = ft_substr(str, *pos, i - *pos + 1);
	*pos = i + 1;

	return (result);
}


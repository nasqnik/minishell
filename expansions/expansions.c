/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:16:00 by anikitin          #+#    #+#             */
/*   Updated: 2025/01/01 11:16:59 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// $USER'$LANG'facaskdfsd'$SHLVL'jff"$PWD"
// echo *".""c"
// echo *".c"
// echo *"as"
// echo *

void expand_command(t_info *info, t_tree *tree)
{
	int i;
	char *result;

	i = 0;
	while (tree->args[i])
	{
		result = process_expansion(tree->args[i], info);
		wildcard(info, &result);
		result = clean_quotes(result);
		free(tree->args[i]);
		tree->args[i] = ft_strdup(result);
		free(result);
		if (!tree->args[i])
			return;
		i++;
	}
}

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
	return (result);
}

char *expand_variables(char *str, int *pos, t_info *info)
{
	char *result;
	int pov[2];

	pov[0] = *pos;
	pov[1] = *pos;
	result = ft_strdup("");
	while (str[pov[0]] && str[pov[0]] != '\'' && str[pov[0]] != '\"')
	{
		if (str[pov[0]] == '\'' || str[pov[0]] == '\"')
			break ;
		if (str[pov[0]] == '$')
		{
			result = handle_variable(str, pov, result, info);
			pov[1] = pov[0];
		}
		else
			pov[0]++;
	}
	if (*result == '\0')
	{
		free(result);
		result = ft_substr(str, pov[1], pov[0] - pov[1]);
	}
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
	if (pov[1] < pov[0])
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


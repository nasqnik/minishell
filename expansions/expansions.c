/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:16:00 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/29 12:51:53 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// $USER'$LANG'facaskdfsd'$SHLVL'jff"$PWD"
// echo *".""c"
// echo *".c"
// echo *"as"
// echo *
// $?a 

void expand_command(t_info *info, t_tree *tree)
{
	int i;
	int j;
	char *tmp;
	char *tmp1;
	char *result;

	i = 0;
	j = 0;
	tmp = NULL;
	tmp1 = NULL;
	while (tree->args[i])
	{
		j = 0;
		result = ft_strdup("");
		if (!result)
			return;
		while (tree->args[i][j])
		{
			if (tree->args[i][j] == '\"')	
				tmp = expand_d_quotes(tree->args[i], &j, info);
			else if (tree->args[i][j] == '\'')
			 	tmp = expand_s_quotes(tree->args[i], &j);
			else
				tmp = expand_variables(tree->args[i], &j, info);
			if (!tmp) 
			{
				free(result);
				return; 
			}
			tmp1 = result;
			result = ft_strjoin(tmp1, tmp);
			free(tmp1);
			free(tmp);
			if (!result)
				return;
		}
		wildcard(info, &result);
		free(tree->args[i]);
		tree->args[i] = ft_strdup(result);
		free(result);
		if (!tree->args[i])
			return;
		i++;
	}
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
	char *tmp;
	int pov[2];

	pov[0] = *pos + 1;
	pov[1] = *pos ;
	result = ft_strdup("");
	while (str[pov[0]] && str[pov[0]] != '\"')
	{
		if (str[pov[0]] == '$')
		{
			result = handle_variable(str, pov, result, info); // add $_ and $?
			if (str[pov[0]] == '\"')
			{
				tmp = ft_strjoin(result, "\"");
				free(result);
				result = tmp;
			}
			pov[1] = pov[0];
		}
		else
			pov[0]++;
	}
	if (pov[1] < pov[0])
		result = append_remaining_data(str, pov, result);
	printf("result: %s\n", result);
	*pos = pov[0] + 1;
	return (result);
}

char *expand_s_quotes(char *str, int *pos)
{
	char *result;
	int i;
	
	i = *pos + 1;
	
	while (str[i] && str[i] != '\'') // check for empty
		i++;
	result = ft_substr(str, *pos, i - *pos + 1); // (str, *pos + 1, i - *pos - 1)
	*pos = i + 1;

	return (result);
}

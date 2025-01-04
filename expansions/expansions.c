/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:16:00 by anikitin          #+#    #+#             */
/*   Updated: 2025/01/03 15:23:54 by meid             ###   ########.fr       */
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
	int wildcard_flag;
	char *result;


	char **wildcard_array;
	char **new_array;

	i = 0;
	wildcard_flag = 0;
	wildcard_array = NULL;
	while (tree->args[i])
	{
		result = process_expansion(tree->args[i], info);
		wildcard_flag = wildcard(info, &result);
		printf("result: %s\n", result);
		if (wildcard_flag == 0)
		{
			result = clean_quotes(result);
			free(tree->args[i]);
			tree->args[i] = ft_strdup(result);
		}
		else
		{
			int wildcard_count;
			int arg_count;
			int new_array_size = 0;

			wildcard_array = ft_split(result, ' ');
			wildcard_count = 0;

			while (wildcard_array[wildcard_count])
				wildcard_count++;

			arg_count = 0;
			while(tree->args[arg_count])
				arg_count++;

			new_array_size = arg_count + wildcard_count;
			new_array = malloc(sizeof(char *) * (new_array_size));
			new_array[new_array_size] = NULL;

			int point;
			point = 0;
			while (point < i)
			{
				new_array[point] = ft_strdup(tree->args[point]);
				point++;
			}
			int j = 0;

			while (wildcard_array[j])
				new_array[point++] = ft_strdup(wildcard_array[j++]);

			j = i + 1;
			while (tree->args[j])
				new_array[point++] = ft_strdup(tree->args[j++]);
			new_array[point] = NULL; 
			free_array(tree->args);
			tree->args = new_array;
			free_array(wildcard_array);
			i += wildcard_count;
		}
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


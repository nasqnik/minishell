/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:09:21 by anikitin          #+#    #+#             */
/*   Updated: 2025/01/17 12:39:10 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int expand_redirection(t_info *info, t_tree *tree)
{
    char *result;
	char *tmp;
	char **wildcard_array;

	tmp = ft_strdup(tree->file);
	wildcard_array = NULL;
    wildcard(info, &tmp);
    if (ft_strcmp(tmp, tree->file) == 0)
	{
		free(tmp);
        result = process_expansion(tree->file, info);
        if (*result == '\0')
            handle_error(info, tree->file, 0, 2);
		result = clean_quotes(result);
		free(tree->file);
		tree->file = ft_strdup(result);
	}
    else
	{
		wildcard_array = ft_split(tmp, ' ');
		free(tmp);
		int i = 0;
		while (wildcard_array[i])
			i++;
		if (i == 1)
		{
			result = ft_strdup(wildcard_array[0]);
			free_array(wildcard_array);
			free(tree->file);
			tree->file = ft_strdup(result);
		}
		else
		{
			free_array(wildcard_array);
			handle_error(info, tree->file, 0, 2);
			return (1);
		}
	}
    free(result);
	return (0);
}


char *process_expansion_heredoc(char *arg, t_info *info)
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
		if (arg[j] == '\"' || arg[j] == '\'')	
			tmp = expand_quotes_heredoc(arg, &j, info);
		else
			tmp = expand_variables_heredoc(arg, &j, info);
		tmp1 = result;
		result = ft_strjoin(tmp1, tmp);
		free(tmp1);
		free(tmp);
	}
	return (result);
}

char *expand_quotes_heredoc(char *str, int *pos, t_info *info)
{
	char *result;
	int pov[2];
    char close;

	pov[0] = *pos + 1;
	pov[1] = *pos;
    close = str[pov[1]];
	result = ft_strdup("");
	while (str[pov[0]] && str[pov[0]] != close)
	{
		if (str[pov[0]] == '$')
		{
			result = handle_variable_heredoc(str, pov, result, info); 
			pov[1] = pov[0];
		}
		else
			pov[0]++;
	}
	if (pov[1] < pov[0])
		result = append_remaining_data(str, pov, result, 1);
	*pos = pov[0] + 1;
	return (result);
}

char	*handle_variable_heredoc(char *data, int pov[2], char *result, t_info *info) 
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
    if (data[pov[0]] == '\"' || data[pov[0]] == '\'')
	{
        if (data[pov[0]] == '\"')
		    tmp = ft_strjoin(result, "\"");
        else
            tmp = ft_strjoin(result, "\'");
		free(result);
		result = tmp;
	}
	free(before_var);
	free(var_value);
	return (result);
}

char *expand_variables_heredoc(char *str, int *pos, t_info *info)
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
	if (pov[1] < pov[0]) 
    {
        char *remaining_part = ft_substr(str, pov[1], pov[0] - pov[1]);
        char *tmp = ft_strjoin(result, remaining_part);
        free(result);
        result = tmp;
        free(remaining_part);
    }
	*pos = pov[0];
	return (result);
}
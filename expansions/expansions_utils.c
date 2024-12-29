/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:46:25 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/29 16:00:11 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void count_without_quotes(char *result, int *count)
{
	int i;
	char close;
	
	i = 0;
	while (result[i])
	{
		if (result[i] == '\"' || result[i] == '\'')
		{
			close = result[i++];
			while (result[i] && result[i] != close)
			{
				(*count)++;
				i++;
			}
			if (result[i] == close)
				i++;
		}
		else
		{
			(*count)++;
			i++;
		}
	}
}

char *substring_without_quotes(char *result, int count)
{
	char *end_result;
	int i;
	char close;
	
	end_result = malloc(count + 1);
	if (!end_result)
		return (NULL);
	i = 0;
	count = 0;
	while (result[i])
	{
		if (result[i] == '\"' || result[i] == '\'')
		{
			close = result[i++];
			while (result[i] && result[i] != close)
				end_result[count++] = result[i++];
			if (result[i] == close) 
				i++;
		}
		else
			end_result[count++] = result[i++];
	}
	end_result[count] = '\0';
	return (end_result);
}

char	*get_var(char *data, int *i, t_env *envp_list)
{
	char	*var_name;
	char	*var_value;
	int		start;

	start = *i;
	var_name = NULL;
	while (data[*i] && (ft_is(data[*i], "alnum") || data[*i] == '_'))
		(*i)++;
	if (*i > start)
	{
		var_name = ft_substr(data, start, *i - start);
		var_value = get_var_value(var_name, envp_list);
		free(var_name);
	}
	else
		var_value = ft_strdup("$");
	return (var_value);
}

char	*get_var_value(char *var_name, t_env *envp_list)
{
	t_env	*cursor;

	cursor = envp_list;
	while (cursor)
	{
		if (!ft_strncmp(var_name, cursor->key, ft_strlen(var_name))
			&& ft_strlen(var_name) == ft_strlen(cursor->key))
			return (ft_strdup(cursor->value));
		cursor = cursor->next;
	}
	return (ft_strdup(""));
}
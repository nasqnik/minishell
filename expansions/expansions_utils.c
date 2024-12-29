/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:46:25 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/29 14:52:13 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *clean_quotes(char *result)
{
	char *end_result;
	int count;
	
	count = 0;
	count_without_quotes(result, &count);	
	end_result = substring_without_quotes(result, count);
	free(result);
	return (end_result);
}

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
			if (result[i])
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
			if (result[i]) 
				i++;
		}
		else
			end_result[count++] = result[i++];
	}
	end_result[count] = '\0';
	return (end_result);
}

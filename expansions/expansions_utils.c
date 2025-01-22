/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:46:25 by anikitin          #+#    #+#             */
/*   Updated: 2025/01/22 09:59:50 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	count_without_quotes(char *result, int *count)
{
	int		i;
	char	close;

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

static char	*substring_without_quotes(char *result, int count)
{
	char	*end_result;
	int		i;
	char	close;

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

char	*append_remaining_data(char *data, int pov[2], char *result, int flag)
{
	char	*remaining_part;
	char	*new_result;

	remaining_part = ft_substr(data, pov[1], pov[0] - pov[1] + flag);
	if (!remaining_part)
		remaining_part = ft_strdup("");
	new_result = ft_strjoin(result, remaining_part);
	free(result);
	free(remaining_part);
	return (new_result);
}

char	*clean_quotes(char *result)
{
	char	*end_result;
	int		count;

	count = 0;
	count_without_quotes(result, &count);
	end_result = substring_without_quotes(result, count);
	free(result);
	return (end_result);
}

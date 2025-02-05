/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:16:30 by meid              #+#    #+#             */
/*   Updated: 2025/01/15 15:24:30 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static int	count_start_sub(char *wildcard, int *i)
{
	int		count;
	char	close;

	count = 0;
	while (wildcard[*i] && wildcard[*i] != '*')
	{
		if (wildcard[*i] == '\'' || wildcard[*i] == '\"')
		{
			close = wildcard[(*i)++];
			while (wildcard[*i] && wildcard[*i] != close)
			{
				count++;
				(*i)++;
			}
			(*i)++;
		}
		else
		{
			count++;
			(*i)++;
		}
	}
	return (count);
}

static void	fill_start_sub(char *wildcard, char *str, int *i, int *j)
{
	char	close;

	*i = 0;
	while (wildcard[*i] && wildcard[*i] != '*')
	{
		if (wildcard[*i] == '\'' || wildcard[*i] == '\"')
		{
			close = wildcard[(*i)++];
			while (wildcard[*i] && wildcard[*i] != close)
				str[(*j)++] = wildcard[(*i)++];
			(*i)++;
		}
		else
		{
			str[(*j)++] = wildcard[(*i)++];
		}
	}
}

char	*start_sub(char *wildcard, int *i, int *j)
{
	char	*str;
	int		count;

	*i = 0;
	*j = 0;
	count = count_start_sub(wildcard, i);
	str = malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	*i = 0;
	fill_start_sub(wildcard, str, i, j);
	str[*j] = '\0';
	return (str);
}

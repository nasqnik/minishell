/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_part.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:11:54 by meid              #+#    #+#             */
/*   Updated: 2025/01/15 15:22:28 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_end_sub(char *wildcard, int *i)
{
	int		count;
	char	open;

	count = 0;
	while (*i >= 0 && wildcard[*i] != '*')
	{
		if (wildcard[*i] == '\'' || wildcard[*i] == '\"')
		{
			open = wildcard[(*i)--];
			while (*i >= 0 && wildcard[*i] != open)
			{
				count++;
				(*i)--;
			}
			(*i)--;
		}
		else
		{
			count++;
			(*i)--;
		}
	}
	return (count);
}

static void	fill_end_sub(char *wildcard, char *str, int *i, int *j)
{
	char	open;

	*i = ft_strlen(wildcard) - 1;
	while (*i >= 0 && wildcard[*i] != '*')
	{
		if (wildcard[*i] == '\'' || wildcard[*i] == '\"')
		{
			open = wildcard[(*i)--];
			while (*i >= 0 && wildcard[*i] != open)
				str[(*j)--] = wildcard[(*i)--];
			(*i)--;
		}
		else
		{
			str[(*j)--] = wildcard[(*i)--];
		}
	}
}

char	*end_sub(char *wildcard, int *i, int *j)
{
	char	*str;
	int		count;

	*i = ft_strlen(wildcard) - 1;
	count = count_end_sub(wildcard, i);
	*j = count - 1;
	str = malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	fill_end_sub(wildcard, str, i, j);
	str[count] = '\0';
	return (str);
}

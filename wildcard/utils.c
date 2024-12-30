/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:27:46 by meid              #+#    #+#             */
/*   Updated: 2024/12/30 11:57:13 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_there_wildcard(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (i);
		i++;
	}
	return (-1);
}

int	who_many_wildcard(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '*')
			count++;
		i++;
	}
	return (count);
}

char	*clean_wildcard(char *data)
{
	char	*result;
	int		i;
	int		j;
	int		wildcard_found;

	result = malloc(ft_strlen(data) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	wildcard_found = 0;
	while (data[i])
	{
		if (data[i] == '*')
		{
			if (!wildcard_found)
			{
				result[j++] = '*';
				wildcard_found = 1;
			}
		}
		else
		{
			result[j++] = data[i];
			wildcard_found = 0;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

void	prossing_files(t_info *info, struct dirent *entry)
{
	char	*tmp;

	tmp = NULL;
	if (info->temporary == NULL)
	{
		info->temporary = ft_strdup(entry->d_name);
		if (!info->temporary)
			return ;
	}
	else
	{
		tmp = ft_strjoin(info->temporary, " ");
		if (!tmp)
			return ;
		free(info->temporary);
		info->temporary = ft_strjoin(tmp, entry->d_name);
		if (!info->temporary)
			return ;
		free(tmp);
	}
}
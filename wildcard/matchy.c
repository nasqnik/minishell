/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matchy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:11:54 by meid              #+#    #+#             */
/*   Updated: 2025/01/15 15:56:02 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	process_mid(char **sub_str, char **tmp_file)
{
	if ((*tmp_file) && who_many_wildcard(*sub_str) >= 2)
	{
		if (*sub_str && ft_mid_with(*tmp_file, *sub_str, 0) == 0)
			return (0);
	}
	free(*sub_str);
	free(*tmp_file);
	return (1);
}

static int	process_start(char *file, char *wildcard, int *start, int *start_f)
{
	int		i;
	int		j;
	char	*sub_str;

	i = 0;
	j = 0;
	sub_str = start_sub(wildcard, &i, &j);
	if (ft_strncmp(file, sub_str, ft_strlen(sub_str)) != 0)
	{
		free(sub_str);
		return (0);
	}
	*start = i;
	*start_f = j;
	free(sub_str);
	return (1);
}

static int	process_end(char *file, char *wildcard, int *end, int *end_f)
{
	int		i;
	int		j;
	char	*sub_str;

	i = 0;
	j = 0;
	sub_str = end_sub(wildcard, &i, &j);
	*end = i;
	*end_f = ft_strlen(file) - j - 1;
	if (ft_strcmp_end(file, sub_str) != 1)
	{
		free(sub_str);
		return (0);
	}
	free(sub_str);
	return (1);
}

int	ft_matchy(char *file, char *wildcard, char *tmp_file)
{
	char	*sub_str;
	int		start;
	int		start_f;
	int		end;
	int		end_f;

	tmp_file = NULL;
	sub_str = NULL;
	if (!file || !wildcard)
		return (0);
	if (!process_start(file, wildcard, &start, &start_f))
		return (0);
	if (!process_end(file, wildcard, &end, &end_f))
		return (0);
	sub_str = ft_substr(wildcard, start, end - start + 1);
	tmp_file = ft_substr(file, start_f, end_f - start_f + 1);
	if (!process_mid(&sub_str, &tmp_file))
		return (0);
	return (1);
}

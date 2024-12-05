/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 08:04:50 by meid              #+#    #+#             */
/*   Updated: 2024/07/15 05:57:28 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_first_non_matching(const char *s1, const char *s2)
{
	int	i;
	int	j;
	int	is_match;

	i = 0;
	while (s1[i])
	{
		j = 0;
		is_match = 0;
		while (s2[j])
		{
			if (s1[i] == s2[j])
			{
				is_match = 1;
				break ;
			}
			j++;
		}
		if (is_match == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	find_last_non_matching(const char *s1, const char *s2)
{
	int	i;
	int	j;
	int	is_match;

	if (ft_strlen(s1) == 0)
		return (-1);
	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		j = 0;
		is_match = 0;
		while (s2[j])
		{
			if (s1[i] == s2[j])
			{
				is_match = 1;
				break ;
			}
			j++;
		}
		if (is_match == 0)
			return (i);
		i--;
	}
	return (-1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		start;
	int		end;
	int		len;

	if (!s1 || !set)
		return (0);
	start = find_first_non_matching(s1, set);
	end = find_last_non_matching(s1, set);
	len = end - start + 1;
	result = ft_substr((char *)s1, start, len);
	return (result);
}

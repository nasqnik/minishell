/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:06:14 by meid              #+#    #+#             */
/*   Updated: 2024/12/11 18:11:08 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strcmp_end(char *s1, char *s2)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	
	while (j >= 0)
	{
		if (i < 0 || s1[i] != s2[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}

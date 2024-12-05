/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 06:51:14 by meid              #+#    #+#             */
/*   Updated: 2024/07/15 05:57:20 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	unsigned char	c2;

	c2 = (unsigned char)c;
	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == c2)
			return ((char *)s + i);
		i--;
	}
	if (s[i] == c2)
		return ((char *)s + i);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:05:24 by meid              #+#    #+#             */
/*   Updated: 2024/07/15 05:54:25 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*src1;
	unsigned char	*dest;

	i = 0;
	src1 = (unsigned char *)src;
	dest = (unsigned char *)dst;
	if (!dest && !src1)
		return (0);
	while (i < n)
	{
		dest[i] = src1[i];
		i++;
	}
	return (dst);
}

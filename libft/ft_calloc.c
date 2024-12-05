/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:26:50 by meid              #+#    #+#             */
/*   Updated: 2024/07/17 19:03:53 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;
	size_t	max_size;

	max_size = count * size;
	if (size && max_size / size != count)
		return (NULL);
	arr = (void *)malloc(max_size);
	if (!(arr))
		return (NULL);
	ft_bzero(arr, (max_size));
	return (arr);
}

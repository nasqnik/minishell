/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:12:18 by meid              #+#    #+#             */
/*   Updated: 2024/07/15 05:55:22 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;
	char	t_char;

	str = (char *)s;
	t_char = (char)c;
	i = 0;
	while (str[i] != t_char)
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (str + i);
}

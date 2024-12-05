/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 07:25:29 by meid              #+#    #+#             */
/*   Updated: 2024/07/15 05:52:42 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numlen(long num)
{
	int	i;

	i = 1;
	if (num < 0)
	{
		num *= -1;
		i++;
	}
	while (num > 9)
	{
		num /= 10;
		i++;
	}
	return (i);
}

void	ft_putnum(long num, char *str, int *i)
{
	if (num > 9)
	{
		ft_putnum(num / 10, str, i);
		ft_putnum(num % 10, str, i);
	}
	else
		str[(*i)++] = num + '0';
}

char	*ft_itoa(int n)
{
	int			i;
	int long	num;
	char		*str;

	i = 0;
	num = n;
	str = malloc((sizeof(char)) * (ft_numlen(num) + 1));
	if (!str)
	{
		return (0);
	}
	if (num < 0)
	{
		str[i] = '-';
		num *= -1;
		i++;
	}
	ft_putnum(num, str, &i);
	return (str[i] = '\0', str);
}

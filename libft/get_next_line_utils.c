/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:08:23 by anikitin          #+#    #+#             */
/*   Updated: 2024/07/29 16:22:50 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*gnl_ft_strchr(const char *str, int c)
{
	char	*s;

	s = (char *)str;
	if (!str)
		return (NULL);
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

char	*gnl_ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	str = malloc(sizeof(char) * (gnl_ft_strlen(s1) + gnl_ft_strlen(s2) + 1));
	if (!str)
		return (gnl_ft_free(&s1));
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*copy_current(char *s, int c)
{
	char	*str;
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
	{
		if (c != '\0')
			str = malloc(sizeof(char) * (i + 2));
		else
			str = malloc(sizeof(char) * (i + 1));
		if (!str)
			return (NULL);
		if (c != '\0')
			str[i + 1] = '\0';
		while (i >= 0)
		{
			str[i] = s[i];
			i--;
		}
		return (str);
	}
	return (0);
}

char	*copy_next(char *s, int c)
{
	char	*str;
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (i < gnl_ft_strlen(s) && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
	{
		str = malloc(sizeof(char) * (gnl_ft_strlen(s) - i) + 1);
		if (!str)
			return (NULL);
		i++;
		while (i < gnl_ft_strlen(s))
		{
			str[j] = s[i];
			j++;
			i++;
		}
		str[j] = '\0';
		return (str);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 08:17:33 by meid              #+#    #+#             */
/*   Updated: 2024/07/15 05:55:16 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

static void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static int	ft_partnum(const char *str, char c)
{
	int		num;
	int		i;

	i = 0;
	num = 0;
	while (str[i])
	{
		if (str[i] != c && (i == 0 || str[i - 1] == c))
		{
			num++;
		}
		i++;
	}
	return (num);
}

static char	*get_word(const char **s, char c)
{
	size_t	word_len;
	char	*word;

	while (**s == c && **s)
		(*s)++;
	if (!**s)
		return (NULL);
	if (!ft_strchr(*s, c))
		word_len = ft_strlen(*s);
	else
		word_len = ft_strchr(*s, c) - *s;
	word = ft_substr(*s, 0, word_len);
	*s += word_len;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	char	*word;
	int		i;
	int		parts;

	if (!s)
		return (NULL);
	parts = ft_partnum(s, c);
	arr = (char **)malloc((parts + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	word = get_word(&s, c);
	while (word != NULL)
	{
		arr[i] = word;
		if (!arr[i])
		{
			free_array(arr);
			return (NULL);
		}
		i++;
		word = get_word(&s, c);
	}
	return (arr[i] = NULL, arr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:07:12 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/21 19:31:48 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_ft_free(char **tmp)
{
	if (tmp && *tmp)
	{
		free(*tmp);
		*tmp = NULL;
	}
	return (NULL);
}

char	*reader(int fd, char *line)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (gnl_ft_free(&line));
	buffer[0] = '\0';
	bytes = 1;
	while (bytes > 0 && !gnl_ft_strchr(buffer, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes > 0)
		{
			buffer[bytes] = '\0';
			line = gnl_ft_strjoin(line, buffer);
		}
	}
	free(buffer);
	if (bytes < 0)
		return (gnl_ft_free(&line));
	return (line);
}

char	*current(char *line)
{
	char	*l;

	if (!gnl_ft_strchr(line, '\n'))
		l = copy_current(line, '\0');
	else
		l = copy_current(line, '\n');
	if (!l)
		return (NULL);
	return (l);
}

char	*next(char *line)
{
	char	*n;
	char	*l;
	int		len;

	n = gnl_ft_strchr(line, '\n');
	if (!n)
	{
		l = NULL;
		return (gnl_ft_free(&line));
	}
	else
		len = n - line + 1;
	if (!line[len])
		return (gnl_ft_free(&line));
	l = copy_next(line, '\n');
	gnl_ft_free(&line);
	if (l == NULL)
		return (NULL);
	return (l);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*l;

	if (fd < 0 || BUFFER_SIZE >= INT_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = reader(fd, line);
	if (!line)
		return (NULL);
	l = current(line);
	if (!l)
		return (gnl_ft_free(&line));
	line = next(line);
	return (l);
}

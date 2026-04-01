/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc04.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 08:41:30 by meid              #+#    #+#             */
/*   Updated: 2025/02/03 09:08:02 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_and_expand(t_info *info, int read_from, int fd, t_tree *tree)
{
	char	*buffer;
	char	*tmp;
	int		flag;

	flag = 0;
	if (tree->file[0] == '\'' || tree->file[0] == '\"')
		flag = 1;
	buffer = get_next_line(read_from);
	while (buffer)
	{
		if (flag == 0)
		{
			tmp = buffer;
			buffer = process_expansion_heredoc(buffer, info, &tmp);
		}
		if (*buffer == '\0')
		{
			tmp = ft_strdup("\n");
			free(buffer);
			buffer = tmp;
		}
		ft_putstr_fd(buffer, fd);
		free(buffer);
		buffer = get_next_line(read_from);
	}
}

int	here_docs_ahead(t_tokens *list)
{
	while (list)
	{
		if (list->type == LOGIC_AND || list->type == LOGIC_OR)
			return (0);
		if (list->type == HEREDOC)
			return (1);
		list = list->next;
	}
	return (0);
}

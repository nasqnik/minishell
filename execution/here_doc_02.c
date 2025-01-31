/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:11:22 by maakhan           #+#    #+#             */
/*   Updated: 2025/01/31 21:11:47 by meid             ###   ########.fr       */
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

int	here_docs_ahead(t_tree *tree)
{
	if (!tree)
		return (FALSE);
	// print_ast(&tree, 5, "head");
	if (tree->type == HEREDOC)
		return (TRUE);
	return (here_docs_ahead(tree->left) || here_docs_ahead(tree->right));
}


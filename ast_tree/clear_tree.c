/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:28:56 by meid              #+#    #+#             */
/*   Updated: 2025/01/14 12:50:38 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clear_tree(t_tree *node)
{
	int	i;

	if (!node)
		return ;
	if (node->left)
		ft_clear_tree(node->left);
	if (node->right)
		ft_clear_tree(node->right);
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			free(node->args[i]);
			i++;
		}
		free(node->args);
	}
	if (node->file)
		free(node->file);
	if (node->fd != -1)
		close(node->fd);
	free(node);
}

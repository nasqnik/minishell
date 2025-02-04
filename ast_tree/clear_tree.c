/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:28:56 by meid              #+#    #+#             */
/*   Updated: 2025/02/04 19:09:15 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clear_node(t_tree *node)
{
	if (!node)
		return ;
	if (node->file)
	{
		free(node->file);
		node->file = NULL;
	}
	if (node->fd >= 0)
	{
		close(node->fd);
		node->fd = -1;
	}
	free(node);
}

void	ft_clear_tree(t_tree *node)
{
	int	i;

	if (!node)
		return ;
	ft_clear_tree(node->left);
	ft_clear_tree(node->right);
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			free(node->args[i]);
			node->args[i] = NULL;
			i++;
		}
		free(node->args);
		node->args = NULL;
	}
	ft_clear_node(node);
}

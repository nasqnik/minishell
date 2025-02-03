/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:28:56 by meid              #+#    #+#             */
/*   Updated: 2025/02/03 19:20:01 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clear_tre(t_tree *node)
{
	if (node->file)
	{
		free(node->file);
		node->file = NULL;
	}
	if (node->fd != -1)
	{
		close(node->fd);
		node->fd = -1;
	}
	if (node)
	{
		free(node);
		node = NULL;
	}
}

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
			node->args[i] = NULL;
			i++;
		}
		free(node->args);
		node->args = NULL;
	}
	ft_clear_tre(node);
}

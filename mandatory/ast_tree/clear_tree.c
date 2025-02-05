/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:28:56 by meid              #+#    #+#             */
/*   Updated: 2025/02/04 20:10:16 by meid             ###   ########.fr       */
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

void	ft_clear_subtrees(t_subtree **subtree_list)
{
	t_subtree	*current;
	t_subtree	*next;

	if (!subtree_list || !*subtree_list)
		return ;
	current = *subtree_list;
	while (current)
	{
		next = current->next;
		ft_clear_tree(current->tree);
		free(current);
		current = next;
	}
	*subtree_list = NULL;
}

void	add_subtree(t_info *info, t_tree *subtree)
{
	t_subtree	*new_node;
	t_subtree	*current;

	if (!info || !subtree)
		return ;
	new_node = malloc(sizeof(t_subtree));
	if (!new_node)
		return ;
	new_node->tree = subtree;
	new_node->next = NULL;
	if (!info->subtree_lest)
	{
		info->subtree_lest = new_node;
		return ;
	}
	current = info->subtree_lest;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

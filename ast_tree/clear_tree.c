/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:28:56 by meid              #+#    #+#             */
/*   Updated: 2024/12/18 15:11:10 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_clear_tree(t_tree *node)
{
    printf("before\n");
    if (!node)
        return;
    printf("before2\n");

    if (node->left)
        ft_clear_tree(node->left);
    if (node->right)
        ft_clear_tree(node->right);
    printf("lol\n");
    if (node->args)
    {
        int i = 0;
        while (node->args[i])
        {
            free(node->args[i]);
            i++;
        }
        free(node->args);
    }

    if (node->file)
        free(node->file);

    free(node);
}

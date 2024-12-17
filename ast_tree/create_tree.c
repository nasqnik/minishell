/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:06:15 by meid              #+#    #+#             */
/*   Updated: 2024/12/16 15:17:50 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int 

void	create_tree(t_tokens *token)
{
    t_tree *ast_node;
    t_tokens *start = token;

    while (token != NULL)
    {
        if (token->type == LOGIC_AND || token->type == LOGIC_OR)
        {
            ast_node = malloc(t_tree);
            ast_node->data = token->data;
            ast_node->left = 
            if (token->next)
                ast_node->right = token->next;
        }

    }
}
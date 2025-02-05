/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:06:15 by meid              #+#    #+#             */
/*   Updated: 2025/01/14 13:11:30 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

t_tree	*create_ast_tree(t_tokens **token)
{
	return (create_ast_and(token));
}

t_tree	*create_ast_and(t_tokens **tokens)
{
	t_tree	*node;
	t_tree	*left;

	left = create_ast_or(tokens);
	if (!(*tokens) || (*tokens)->type != LOGIC_AND)
		return (left);
	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->type = LOGIC_AND;
	node->file = NULL;
	node->args = NULL;
	node->left = left;
	node->fd = -1;
	*tokens = (*tokens)->next;
	node->right = create_ast_and(tokens);
	return (node);
}

t_tree	*create_ast_or(t_tokens **tokens)
{
	t_tree	*node;
	t_tree	*left;

	left = create_ast_pipe(tokens);
	if (!(*tokens) || (*tokens)->type != LOGIC_OR)
		return (left);
	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->type = LOGIC_OR;
	node->file = NULL;
	node->args = NULL;
	node->left = left;
	node->fd = -1;
	*tokens = (*tokens)->next;
	node->right = create_ast_or(tokens);
	return (node);
}

t_tree	*create_ast_pipe(t_tokens **tokens)
{
	t_tree	*node;
	t_tree	*left;

	left = create_ast_redirections(tokens);
	if (!(*tokens) || (*tokens)->type != PIPE)
		return (left);
	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->type = PIPE;
	node->file = NULL;
	node->args = NULL;
	node->left = left;
	node->fd = -1;
	*tokens = (*tokens)->next;
	node->right = create_ast_pipe(tokens);
	return (node);
}

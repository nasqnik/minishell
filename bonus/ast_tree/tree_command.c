/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:58:12 by meid              #+#    #+#             */
/*   Updated: 2025/01/14 13:31:04 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	count_to_allocate(t_tokens *tokens)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	tmp = tokens;
	while (tmp && ((tmp->type == COMMAND || tmp->type == ARGUMENT
				|| tmp->type == FILENAME || tmp->type == DELIMITER)
			|| (tmp->type >= REDIRECT_IN && tmp->type <= HEREDOC)))
	{
		if (tmp->type == COMMAND || tmp->type == ARGUMENT)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	skip_tokens(t_tree *node, t_tokens **tokens)
{
	while ((*tokens) && ((*tokens)->type == COMMAND
			|| (*tokens)->type == ARGUMENT))
		(*tokens) = (*tokens)->next;
	node->file = NULL;
	node->fd = -1;
	node->left = NULL;
	node->right = NULL;
}

void	fill_in_args(t_tree *node, t_tokens **tokens, int i)
{
	t_tokens	*tmp;

	node->type = COMMAND;
	i = count_to_allocate(*tokens);
	if (i != 0)
	{
		node->args = malloc(sizeof(char *) * (i + 1));
		if (!node->args)
			return ;
		i = 0;
		tmp = (*tokens);
		while (tmp && ((tmp->type == COMMAND || tmp->type == ARGUMENT
					|| tmp->type == FILENAME || tmp->type == DELIMITER)
				|| (tmp->type >= REDIRECT_IN && tmp->type <= HEREDOC)))
		{
			if (tmp->type == COMMAND || tmp->type == ARGUMENT)
			{
				node->args[i] = ft_strdup(tmp->data);
				i++;
			}
			tmp = tmp->next;
		}
		node->args[i] = NULL;
	}
	skip_tokens(node, tokens);
}

t_tree	*create_ast_command(t_tokens **tokens)
{
	t_tree	*node;

	if (!tokens || !(*tokens))
		return (NULL);
	if ((*tokens)->type == BRACKET || (*tokens)->type == COMMAND)
	{
		node = malloc(sizeof(t_tree));
		if (!node)
			return (NULL);
		if ((*tokens)->type == BRACKET)
		{
			node->type = BRACKET;
			node->file = ft_strdup((*tokens)->data);
			node->args = NULL;
			(*tokens) = (*tokens)->next;
			node->fd = -1;
			node->left = NULL;
			node->right = NULL;
		}
		else if ((*tokens)->type == COMMAND)
			fill_in_args(node, tokens, 0);
		return (node);
	}
	return (NULL);
}

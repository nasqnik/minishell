/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:59:07 by meid              #+#    #+#             */
/*   Updated: 2025/01/14 15:32:50 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*create_ast_redirections(t_tokens **tokens)
{
	t_tree	*cmd;
	t_tree	*node;
	t_tree	*tmp;
	t_tree	*first;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	tmp = NULL;
	first = NULL;
	cmd = create_ast_command(tokens);
	while (*tokens && ((*tokens)->type >= REDIRECT_IN
			&& (*tokens)->type <= HEREDOC))
	{
		flag = 1;
		node = malloc(sizeof(t_tree));
		if (!node)
			return (NULL);
		node->type = (*tokens)->type;
		node->args = NULL;
		*tokens = (*tokens)->next;
		if (*tokens && ((*tokens)->type == FILENAME
				|| (*tokens)->type == DELIMITER))
			node->file = ft_strdup((*tokens)->data);
		if (tmp)
			tmp->left = node;
		else
		{
			first = node;
			node->left = NULL;
		}
		tmp = node;
		if (*tokens && ((*tokens)->type == FILENAME
				|| (*tokens)->type == DELIMITER))
		{
			*tokens = (*tokens)->next;
		}
		while ((*tokens) && ((*tokens)->type == COMMAND
				|| (*tokens)->type == ARGUMENT))
		{
			if ((*tokens)->type == COMMAND && !cmd)
			{
				cmd = create_ast_command(tokens);
				continue ;
			}
			*tokens = (*tokens)->next;
		}
		node->right = NULL;
		node->fd = -1;
		i++;
	}
	if (flag == 1)
		node->left = cmd;
	if (i == 0)
		return (cmd);
	else
		return (first);
}

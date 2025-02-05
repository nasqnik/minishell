/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:59:07 by meid              #+#    #+#             */
/*   Updated: 2025/02/03 09:12:25 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_node_redir(t_tree **node, t_tokens **tokens, int *flag)
{
	(*flag) = 1;
	(*node) = malloc(sizeof(t_tree));
	if (!(*node))
		return ;
	(*node)->type = (*tokens)->type;
	(*node)->args = NULL;
	(*node)->fd = (*tokens)->fd;
	*tokens = (*tokens)->next;
	if (*tokens && ((*tokens)->type == FILENAME
			|| (*tokens)->type == DELIMITER))
		(*node)->file = ft_strdup((*tokens)->data);
}

void	skip_cmd_arg(t_tree **cmd, t_tokens **tokens, t_tree **node)
{
	if (*tokens && ((*tokens)->type == FILENAME
			|| (*tokens)->type == DELIMITER))
	{
		*tokens = (*tokens)->next;
	}
	while ((*tokens) && ((*tokens)->type == COMMAND
			|| (*tokens)->type == ARGUMENT))
	{
		if ((*tokens)->type == COMMAND && !(*cmd))
		{
			(*cmd) = create_ast_command(tokens);
			continue ;
		}
		*tokens = (*tokens)->next;
	}
	(*node)->right = NULL;
}

void	check_and_set_tmp(t_tree **tmp, t_tree **node, t_tree **first)
{
	if ((*tmp))
		(*tmp)->left = (*node);
	else
	{
		(*first) = (*node);
		(*node)->left = NULL;
	}
	(*tmp) = (*node);
}

t_tree	*create_ast_redirections(t_tokens **tokens)
{
	t_tree	*cmd;
	t_tree	*node;
	t_tree	*tmp;
	t_tree	*first;
	int		flag[2];

	flag[0] = 0;
	flag[1] = 0;
	tmp = NULL;
	first = NULL;
	cmd = create_ast_command(tokens);
	while (*tokens && ((*tokens)->type >= REDIRECT_IN
			&& (*tokens)->type <= HEREDOC))
	{
		create_node_redir(&node, tokens, &flag[1]);
		check_and_set_tmp(&tmp, &node, &first);
		skip_cmd_arg(&cmd, tokens, &node);
		flag[0]++;
	}
	if (flag[1] == 1)
		node->left = cmd;
	if (flag[0] == 0)
		return (cmd);
	else
		return (first);
}

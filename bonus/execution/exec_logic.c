/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 20:04:03 by meid              #+#    #+#             */
/*   Updated: 2025/02/04 20:23:25 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	execution(t_info *info, t_tree *tree)
{
	if (!info->ast_tree || !tree)
		return ;
	if (tree->type == LOGIC_AND)
	{
		execution(info, tree->left);
		if (our_static("exit status", -1) == 0)
			execution(info, tree->right);
	}
	else if (tree->type == LOGIC_OR)
	{
		execution(info, tree->left);
		if (our_static("exit status", -1) != 0)
			execution(info, tree->right);
	}
	else if (tree->type == PIPE)
		execution_pipe(info, tree);
	else if (tree->type >= REDIRECT_IN && tree->type <= HEREDOC)
		execution_redirection(info, tree);
	else if (tree->type == COMMAND)
		execute_command(info, tree);
	else if (tree->type == BRACKET)
		subshell(info, tree);
}

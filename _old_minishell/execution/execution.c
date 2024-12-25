/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:58:32 by meid              #+#    #+#             */
/*   Updated: 2024/12/24 16:59:31 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	execution(t_first *f)
// {
// 	int		exit_value;
// 	t_tree	*tree;

// 	if (!f->ast_tree)
// 		return ;
// 	tree = f->ast_tree;
// 	if (tree->type >= REDIRECT_IN && tree->type <= HEREDOC)
// 		exit_value = execute_redirections(f, tree->type);
// 	else if (tree->type == COMMAND)
// 		execute_command(f, tree);
// 	// else if (tree->type == PIPE)
// 	// 	execution_pipe(f, tree);
// 	(void)exit_value;
// }

void	execute_command(t_first *f, t_tree *tree)
{
	// str_cmp_builtin(f, tree->args[0], tree->args);
	int	pid = 0;

	if (!(str_cmp_builtin(f, tree->args[0], tree->args)))
	{
		pid = fork();
		if (pid == -1)
			return ;
		else if (pid == 0)
		{
			execute_binary(f, tree->args[0], tree->args, 1);
		}
		wait(NULL);
	}
	dup2(f->stdout, STDOUT_FILENO);
	dup2(f->stdin, STDIN_FILENO);
}

// ◦ echo with option -n
// ◦ cd with only a relative or absolute path ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options
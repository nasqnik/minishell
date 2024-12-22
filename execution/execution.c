/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:58:32 by meid              #+#    #+#             */
/*   Updated: 2024/12/22 10:23:42 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execution(t_first *f)
{
    int exit_value;
    if (!f->ast_tree)
        return ;
    t_tree *tree = f->ast_tree;
    
    if (tree->type >= REDIRECT_IN && tree->type <= HEREDOC)
        exit_value = execute_redirections(f, tree->type);
    else if (tree->type == COMMAND) // the command works
        execute_command(f, tree);
    (void)exit_value;
}

void execute_command(t_first *f, t_tree *tree)
{
    int	pid;

    if (!(str_cmp_builtin(f, tree->args[0], tree->args)))
    {
        pid = fork();
	    if (pid == -1)
            return ;
        else if (pid == 0)
            execute_binary(f, tree->args[0], tree->args, 1);
        wait(NULL);
    }
}


// ◦ echo with option -n
// ◦ cd with only a relative or absolute path ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options
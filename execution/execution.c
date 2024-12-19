/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:58:32 by meid              #+#    #+#             */
/*   Updated: 2024/12/19 14:54:08 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void str_cmp_builtin(t_first *f, char *command, char **args)
{
    
    int i = 1;
    if (ft_strcmp(command, "echo") == 0) // done
        ft_echo(args, i);
    if (ft_strcmp(command, "cd") == 0)
        ft_cd(f, args, i);
    if (ft_strcmp(command, "pwd") == 0) // done
        ft_pwd(args, i);
    if (ft_strcmp(command, "export") == 0) // connect with the real env list
        ft_export(f, args, i);
    if (ft_strcmp(command, "unset") == 0) // connect with the real env list
        ft_unset(f, args, i);
    if (ft_strcmp(command, "env") == 0) // connect with the real env list
        ft_env(f, args, i);
    if (ft_strcmp(command, "exit") == 0)
        ft_exit(f, args, i);
    if (ft_strcmp(command, "meow") == 0)
        ft_meow(args, i);
}
void execute_command(t_first *f, t_tree *tree)
{
   str_cmp_builtin(f, tree->args[0], tree->args);
}

// ◦ echo with option -n
// ◦ cd with only a relative or absolute path ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

void execution(t_first *f)
{
    if (!f->ast_tree)
        return ;
    t_tree *tree = f->ast_tree;
    
    if (tree->type == COMMAND)
        execute_command(f, tree);
    else
    {
        printf("now only commmands\n");
        return ;
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:58:32 by meid              #+#    #+#             */
/*   Updated: 2024/12/18 16:34:57 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *str_cmp_builtin(char *command, char **args)
{
    char *str;
    
    int i = 1;
    str = NULL;
    if (ft_strcmp(command, "echo"))
        str = ft_echo(args, i);
    if (ft_strcmp(command, "cd"))
        str = ft_cd(args, i);
    if (ft_strcmp(command, "export"))
        str = ft_export(args, i);
    if (ft_strcmp(command, "unset"))
        str = ft_unset(args, i);
    if (ft_strcmp(command, "env"))
        str = ft_env(args, i);
    if (ft_strcmp(command, "exit"))
        str = ft_exit(args, i);
    return (str);
}

char *execute_command(t_tree *tree)
{
    (void)tree;
    char *str;
    str = str_cmp_builtin(tree->args[0], tree->args);
    if (str != NULL)
        return (str);
    else
        str = "it is not a builtin";
    return (str);
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
    char *the_str;
    
    if (tree->type == COMMAND)
        the_str = execute_command(tree);
    else
    {
        printf("now only commmands\n");
        return ;
    }
    if (the_str)
        printf("\033[38m%s\033[0m", the_str);
    else
        printf("\033[38mNULL\033[0m");
}
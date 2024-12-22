/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 09:27:47 by meid              #+#    #+#             */
/*   Updated: 2024/12/22 09:36:06 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int str_cmp_builtin(t_first *f, char *command, char **args)
{
    
    int i = 1;
    
    if (ft_strcmp(command, "echo") == 0) // done
        return(ft_echo(args, i));
    if (ft_strcmp(command, "cd") == 0)
        return(ft_cd(f, args, i));
    if (ft_strcmp(command, "pwd") == 0) // done
        return(ft_pwd(args, i));
    if (ft_strcmp(command, "export") == 0) // connect with the real env list
        return(ft_export(f, args, i));
    if (ft_strcmp(command, "unset") == 0) // connect with the real env list
        return(ft_unset(f, args, i));
    if (ft_strcmp(command, "env") == 0) // connect with the real env list
        return(ft_env(f, args, i));
    if (ft_strcmp(command, "exit") == 0)
        return(ft_exit(f, args, i, 0));
    if (ft_strcmp(command, "meow") == 0)
        return(ft_meow(args, i, 0));
    return 0;
}
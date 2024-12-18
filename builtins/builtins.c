/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:48:36 by meid              #+#    #+#             */
/*   Updated: 2024/12/18 17:23:16 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_echo(char **args, int i)
{
    int line_flag = 0;
    int fd = 1;
    if (args[i] && ft_strcmp(args[i], "-n") == 0)
    {
        line_flag = 1;
        i++;
        if (args[i] && ft_strcmp(args[i], " ") == 0)
            i++;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], fd);
        i++;
    }
        
   
    if (line_flag == 0)
        ft_putstr_fd("\n", fd);
    return ("printed successfully\n");
}

char *ft_cd(char **args, int i)
{
    (void)args;
    (void)i;
    return (NULL);
}

char *ft_export(char **args, int i)
{
    (void)args;
    (void)i;
    return (NULL);
}

char *ft_unset(char **args, int i)
{
    (void)args;
    (void)i;
    return (NULL);
}

char *ft_env(char **args, int i)
{
    (void)args;
    (void)i;
    return (NULL);
}

char *ft_exit(char **args, int i)
{
    (void)args;
    (void)i;
    return (NULL);
}
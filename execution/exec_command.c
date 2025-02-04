/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:29:48 by meid              #+#    #+#             */
/*   Updated: 2025/02/04 20:22:24 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	strcmp_builtin(t_info *info, char *command, char **args)
{
	int	i;

	i = 1;
	if (ft_str_cmd_cmp(command, "echo") == 0)
		return (ft_echo(args, i));
	if (ft_str_cmd_cmp(command, "cd") == 0)
		return (ft_cd(info, args));
	if (ft_str_cmd_cmp(command, "pwd") == 0)
		return (ft_pwd());
	if (ft_str_cmd_cmp(command, "export") == 0)
		return (ft_export(info, args, i));
	if (ft_str_cmd_cmp(command, "unset") == 0)
		return (ft_unset(info, args, i));
	if (ft_str_cmd_cmp(command, "env") == 0)
		return (ft_env(info, args, i));
	if (ft_str_cmd_cmp(command, "exit") == 0)
		return (ft_exit(info, args, i, 0));
	if (ft_str_cmd_cmp(command, "meow") == 0)
		return (ft_meow(info, args, i, 0));
	return (2);
}

void	execute_command(t_info *info, t_tree *tree)
{
	int	return_builtin;

	if (!info || !tree)
		return ;
	expand_command(info, tree);
	return_builtin = strcmp_builtin(info, tree->args[0], tree->args);
	if (return_builtin == 0)
		our_static("exit status", 0);
	if (return_builtin == 2)
	{
		binary(info, tree);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:58:32 by meid              #+#    #+#             */
/*   Updated: 2024/12/26 09:32:58 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_command(t_info *info, t_tree *tree)
{
	if (!info || !tree)
		return ;
	// strcmp_builtin(info, tree->args[0], tree->args);
	int	pid = 0;
	//  expansions
	// clear quotes
	if (!(strcmp_builtin(info, tree->args[0], tree->args)))
	{
		pid = fork();
		if (pid == -1)
			return ;
		else if (pid == 0)
		{
			execute_binary(info, tree->args[0], tree->args, 1);
		}
		wait(NULL);
	}
	dup2(info->stdout, STDOUT_FILENO);
	dup2(info->stdin, STDIN_FILENO);
}

int	strcmp_builtin(t_info *info, char *command, char **args)
{
	int	i;

	i = 1;
	if (ft_strcmp(command, "echo") == 0)
		return (ft_echo(args, i));
	if (ft_strcmp(command, "cd") == 0)
		return (ft_cd(info, args, i));
	if (ft_strcmp(command, "pwd") == 0)
		return (ft_pwd(args, i));
	if (ft_strcmp(command, "export") == 0)
		return (ft_export(info, args, i));
	if (ft_strcmp(command, "unset") == 0)
		return (ft_unset(info, args, i));
	if (ft_strcmp(command, "env") == 0)
		return (ft_env(info, args, i));
	if (ft_strcmp(command, "exit") == 0)
		return (ft_exit(info, args, i, 0));
	if (ft_strcmp(command, "meow") == 0)
		return (ft_meow(args, i, 0));
	return (0);
}

// ◦ echo with option -n
// ◦ cd with only a relative or absolute path ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options
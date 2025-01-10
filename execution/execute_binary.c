/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 09:26:45 by meid              #+#    #+#             */
/*   Updated: 2025/01/10 17:08:40 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(char *command, t_info *info);

int	execute_binary(t_info *info, char *command, char **args, int fd)
{
	struct stat	directory;
	char	*command_path;

	if (command[0] != '/' && command[0] != '.')
		command_path = find_path(args[0], info);
	else
		command_path = args[0];
	if (!command_path || access(command_path, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", fd);
		ft_putstr_fd("\033[31mcommand not found: \033[00m", fd);
		ft_putstr_fd(args[0], fd);
		ft_putchar_fd('\n', fd);
		return 127;
	}
	update_envp_array(info);
	execve(command_path, args, info->envp_array);
	if (!stat(command_path, &directory))
	{
		handle_error(info, command_path, 0, 6);
		return 126;
	}
	return (1);
}

char	*find_path(char *command, t_info *info)
{
	char	**all_paths;
	char	*command_path;
	char	*tmp;
	int		i;

	all_paths = ft_split(search_in_env(info, "PATH"), ':');
	if (!all_paths)
		return (NULL);
	i = 0;
	while (all_paths[i])
	{
		tmp = ft_strjoin(all_paths[i], "/");
		command_path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(command_path, F_OK | X_OK) == 0)
		{
			free_array(all_paths);
			return (command_path);
		}
		free(command_path);
		i++;
	}
	free_array(all_paths);
	return (NULL);
}

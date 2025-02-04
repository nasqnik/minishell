/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:11:47 by meid              #+#    #+#             */
/*   Updated: 2025/02/04 20:22:14 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_path(char *command, t_info *info, int *flag)
{
	char	**all_paths;
	char	*command_path;
	char	*tmp;
	int		i;

	if (*command == '\0')
		return (NULL);
	all_paths = ft_split(search_in_env(info, "PATH"), ':');
	if (!all_paths)
		return ((*flag) = 1, NULL);
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
	return (free_array(all_paths), NULL);
}

static char	*find_command_path(t_info *info, char first_c, char *arg, int *flag)
{
	if (first_c != '/' && first_c != '.')
		return (find_path(arg, info, flag));
	else
		return (arg);
}

int	execute_binary(t_info *info, char *command, char **args)
{
	struct stat	directory;
	char		*command_path;
	int			flag;

	flag = 0;
	ft_str_tolower(&args[0]);
	command_path = find_command_path(info, command[0], args[0], &flag);
	if (!command_path || access(command_path, X_OK) == -1)
	{
		if (flag == 0 && (command[0] == '/' || (command[0] == '.'
					&& command[1] == '/')))
			handle_error(info, args[0], 0, 12);
		else
			handle_error(info, args[0], 0, 14);
		return (127);
	}
	update_envp_array(info, info->envp_list, ft_lstsize(info->envp_list));
	execve(command_path, args, info->envp_array);
	if (command[0] == '.' && command[1] == '\0')
		return (handle_error(info, args[0], 0, 17), 2);
	if (!stat(command_path, &directory))
		return (handle_error(info, command_path, 0, 6), 126);
	return (1);
}

void	child_pro(t_info *info, t_tree *tree)
{
	int		exit_status;

	if (info->stdout != -1)
	{
		close(info->stdout);
		info->stdout = -1;
	}
	if (info->stdin != -1)
	{
		close(info->stdin);
		info->stdin = -1;
	}
	castom_dfl();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	exit_status = execute_binary(info, tree->args[0], tree->args);
	free_and_set_null(info, 2);
	if (exit_status != 0)
		exit(exit_status);
}

void	binary(t_info *info, t_tree *tree)
{
	int		status;
	pid_t	pid;

	castom_ing();
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		free_and_set_null(info, 2);
		return ;
	}
	else if (pid == 0)
	{
		child_pro(info, tree);
	}
	waitpid(pid, &status, 0);
	castom_signals();
	signals_exit_statue(status);
}

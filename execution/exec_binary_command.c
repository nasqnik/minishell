/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:11:47 by meid              #+#    #+#             */
/*   Updated: 2025/01/15 16:24:33 by meid             ###   ########.fr       */
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

int	execute_binary(t_info *info, char *command, char **args, int fd)
{
	struct stat	directory;
	char		*command_path;
	int			flag;

	flag = 0;
	command_path = find_command_path(info, command[0], args[0], &flag);
	if (!command_path || access(command_path, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", fd);
		ft_putstr_fd(args[0], fd);
		if (flag == 1)
			ft_putstr_fd("\033[31m: No such file or directory\033[00m", fd);
		else
			ft_putstr_fd("\033[31m: command not found\033[00m", fd);
		ft_putchar_fd('\n', fd);
		return (127);
	}
	update_envp_array(info);
	execve(command_path, args, info->envp_array);
	if (!stat(command_path, &directory))
	{
		handle_error(info, command_path, 0, 6);
		return (126);
	}
	return (1);
}

static void	signals_exit_statue(int status)
{
	char	*massage;

	if (WIFEXITED(status))
		our_static("exit status", WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT || WTERMSIG(status) == SIGSEGV)
		{
			if (WTERMSIG(status) == SIGQUIT)
				write(2, "Quit: ", 7);
			else
			{
				write(2, "Segmentation fault: ", 20);
				massage = ft_itoa(WTERMSIG(status));
				write(2, massage, ft_strlen(massage));
				write(2, "\n", 1);
			}
			our_static("exit status", WTERMSIG(status) + 128);
		}
	}
}

void	binary(t_info *info, t_tree *tree)
{
	int		status;
	pid_t	pid;
	int		exit_status;

	close(info->stdin);
	close(info->stdout);
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return ;
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exit_status = execute_binary(info, tree->args[0], tree->args, 1);
		free_and_set_null(info, 2);
		if (exit_status != 0)
			exit(exit_status);
	}
	waitpid(pid, &status, 0);
	signals_exit_statue(status);
}

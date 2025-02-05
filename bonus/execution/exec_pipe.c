/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:29:07 by meid              #+#    #+#             */
/*   Updated: 2025/02/05 08:22:48 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	execution_pipe(t_info *info, t_tree *tree)
{
	int		pipefd[2];
	pid_t	pipe_left;
	pid_t	pipe_right;
	int		status_left;
	int		status_right;

	our_static("exit status", 0);
	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		free_and_set_null(info, 2);
		return ;
	}
	pipe_left = handle_left_pipe(info, tree, pipefd);
	pipe_right = handle_right_pipe(info, tree, pipefd);
	close(pipefd[1]);
	close(pipefd[0]);
	waitpid(pipe_left, &status_left, 0);
	waitpid(pipe_right, &status_right, 0);
	castom_signals();
	if (WIFEXITED(status_left) && WEXITSTATUS(status_left) != 0)
		our_static("exit status", WEXITSTATUS(status_left));
	else if (WIFEXITED(status_right) && WEXITSTATUS(status_right) != 0)
		our_static("exit status", WEXITSTATUS(status_right));
}

pid_t	handle_left_pipe(t_info *info, t_tree *tree, int pipefd[2])
{
	pid_t	pid;
	int		exit_code;

	castom_ing();
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		free_and_set_null(info, 2);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		castom_dfl();
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execution(info, tree->left);
		exit_code = our_static("exit status", -1);
		free_and_set_null(info, 2);
		exit(exit_code);
	}
	return (pid);
}

pid_t	handle_right_pipe(t_info *info, t_tree *tree, int pipefd[2])
{
	pid_t	pid;
	int		exit_code;

	castom_ing();
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		free_and_set_null(info, 2);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		castom_dfl();
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		execution(info, tree->right);
		exit_code = our_static("exit status", -1);
		free_and_set_null(info, 2);
		exit(exit_code);
	}
	return (pid);
}

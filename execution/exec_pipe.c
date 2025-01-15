/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:29:07 by meid              #+#    #+#             */
/*   Updated: 2025/01/15 16:06:42 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution_pipe(t_info *info, t_tree *tree)
{
	int		pipefd[2];
	pid_t	pipe_left;
	pid_t	pipe_right;
	int		status_left;
	int		status_right;

	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		return ;
	}
	pipe_left = handle_left_pipe(info, tree, pipefd);
	pipe_right = handle_right_pipe(info, tree, pipefd);
	close(pipefd[1]);
	close(pipefd[0]);
	waitpid(pipe_left, &status_left, 0);
	waitpid(pipe_right, &status_right, 0);
	if (WIFEXITED(status_left) && WEXITSTATUS(status_left) != 0)
		our_static("exit status", WEXITSTATUS(status_left));
	else if (WIFEXITED(status_right) && WEXITSTATUS(status_right) != 0)
		our_static("exit status", WEXITSTATUS(status_right));
}

pid_t	handle_left_pipe(t_info *info, t_tree *tree, int pipefd[2])
{
	pid_t	pid;

	(void)info;
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execution(info, tree->left);
		free_and_set_null(info, 2);
		exit(EXIT_SUCCESS);
	}
	return (pid);
}

pid_t	handle_right_pipe(t_info *info, t_tree *tree, int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		execution(info, tree->right);
		free_and_set_null(info, 2);
		exit(EXIT_SUCCESS);
	}
	return (pid);
}

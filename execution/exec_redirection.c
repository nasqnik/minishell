/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:25:25 by meid              #+#    #+#             */
/*   Updated: 2025/01/16 20:25:22 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution_redirection(t_info *info, t_tree *tree)
{
	if (tree->type != HEREDOC)
	{
		if (expand_redirection(info, tree))
		{
			our_static("exit status", 1);
			return ;
		}
	}
	if (tree->type == HEREDOC)
		get_file(tree->fd, tree, info);
	else if (tree->type == REDIRECT_IN)
		handle_redirect_in(info, tree);
	else if (tree->type == REDIRECT_OUT)
		handle_redirect_out(info, tree);
	else if (tree->type == REDIRECT_APPEND)
		handle_redirect_append(info, tree);
	if (tree->left)
		execution(info, tree->left);
	else
	{
		if (dup2(info->stdout, STDOUT_FILENO) == -1
            || dup2(info->stdin, STDIN_FILENO) == -1)
		{
			perror("dup2 failed during cleanup");
		}
	}
}

void	handle_redirect_in(t_info *info, t_tree *tree)
{
	int	file;

	(void)info;
	file = open(tree->file, O_RDONLY, 0); //have to check permissions
	if (file == -1)
	{
		perror("Error opening file for input redirection");
		return ;
	}
	if (dup2(file, STDIN_FILENO) == -1)
	{
		perror("Error duplicating file descriptor");
	}
	close(file);
}

void	handle_redirect_out(t_info *info, t_tree *tree)
{
	int	file;

	(void)info;
	file = open(tree->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		//have to check permissions
	if (file == -1)
		return ;
	dup2(file, STDOUT_FILENO);
	close(file);
	// printf("I'm here\n");
}

void	handle_redirect_append(t_info *info, t_tree *tree)
{
	int	file;

	(void)info;
	file = open(tree->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		//have to check permissions
	if (file == -1)
		return ;
	dup2(file, STDOUT_FILENO);
	close(file);
}

int	get_file(int read_from, t_tree *tree, t_info *info)
{
	int	fd;

	if (read_from != -1)
	{
		fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		read_and_expand(info, read_from, fd);
		close(fd);
		close(read_from);
		fd = open(".tmp", O_RDONLY, 0777);
		dup2(fd, 0);
		close(fd);
		unlink(".tmp");
		fd = -1;
		tree->fd = -1;
	}
	return (0);
}

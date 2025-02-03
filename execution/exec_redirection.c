/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:25:25 by meid              #+#    #+#             */
/*   Updated: 2025/02/03 19:25:49 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution_redirection(t_info *info, t_tree *tree)
{
	int	flag;

	flag = 0;
	if (tree->type != HEREDOC)
	{
		if (expand_redirection(info, tree))
		{
			our_static("exit status", 1);
			return ;
		}
	}
	if (tree->type == HEREDOC)
		flag = get_file(tree->fd, tree, info);
	else if (tree->type == REDIRECT_IN)
		flag = handle_redirect_in(info, tree);
	else if (tree->type == REDIRECT_OUT)
		flag = handle_redirect_out(info, tree);
	else if (tree->type == REDIRECT_APPEND)
		flag = handle_redirect_append(info, tree);
	if (tree->left && flag == 0)
		execution(info, tree->left);
}

int	handle_redirect_in(t_info *info, t_tree *tree)
{
	int	file;

	(void)info;
	file = 0;
	if (access(tree->file, F_OK) == -1)
	{
		handle_error(info, tree->file, 0, 12);
		return (1);
	}
	file = open(tree->file, O_RDONLY);
	if (file == -1)
	{
		if (access(tree->file, R_OK) == -1)
			return (handle_error(info, tree->file, 0, 13), 1);
		handle_error(info, tree->file, 0, 12);
		return (1);
	}
	if (dup2(file, STDIN_FILENO) == -1)
	{
		perror("Error duplicating file descriptor");
		return (1);
	}
	close(file);
	return (0);
}

int	handle_redirect_out(t_info *info, t_tree *tree)
{
	int	file;

	(void)info;
	file = open(tree->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
	{
		if (access(tree->file, W_OK) == -1)
		{
			handle_error(info, tree->file, 0, 13);
			return (1);
		}
		handle_error(info, tree->file, 0, 12);
		return (1);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	return (0);
}

int	handle_redirect_append(t_info *info, t_tree *tree)
{
	int	file;

	(void)info;
	file = open(tree->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file == -1)
	{
		if (access(tree->file, W_OK) == -1)
		{
			handle_error(info, tree->file, 0, 13);
			return (1);
		}
		handle_error(info, tree->file, 0, 12);
		return (1);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	return (0);
}

int	get_file(int read_from, t_tree *tree, t_info *info)
{
	int	fd;

	if (read_from != -1)
	{
		fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		read_and_expand(info, read_from, fd, tree);
		close(fd);
		close(read_from);
		fd = open(".tmp", O_RDONLY, 0777);
		dup2(fd, 0);
		close(fd);
		unlink(".tmp");
		fd = -1;
		tree->fd = -1;
		return (0);
	}
	return (2);
}

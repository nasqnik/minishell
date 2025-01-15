/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:11:22 by maakhan           #+#    #+#             */
/*   Updated: 2025/01/15 16:05:25 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_and_expand(t_info *info, int read_from, int fd)
{
	char	*buffer;
	char	*tmp;

	while (1)
	{
		buffer = get_next_line(read_from);
		if (!buffer)
			break ;
		tmp = buffer;
		buffer = process_expansion_heredoc(buffer, info);
		free(tmp);
		if (*buffer == '\0')
		{
			tmp = ft_strdup("\n");
			free(buffer);
			buffer = tmp;
		}
		ft_putstr_fd(buffer, fd);
		free(buffer);
	}
}

int	here_docs_ahead(t_tree *tree)
{
	int	result;

	result = FALSE;
	if (tree->type == HEREDOC)
		result = TRUE;
	if (tree->left != NULL)
		result = here_docs_ahead(tree->left);
	if (!result)
		if (tree->right != NULL)
			result = here_docs_ahead(tree->right);
	return (result);
}

static void	read_write(char *limiter, int write_to)
{
	char	*new_line;
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (line)
		{
			if (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
			{
				free(line);
				line = NULL;
				break ;
			}
			new_line = ft_strjoin(line, "\n");
			write(write_to, new_line, ft_strlen(new_line));
			free(new_line);
			new_line = NULL;
			free(line);
			line = NULL;
		}
	}
	close(write_to);
}

static void	handle_heredoc_sig(int sig)
{
	if (sig == SIGINT)
	{
		our_static("exit status", 1);
		close(STDIN_FILENO);
	}
}

int	ft_hdoc(t_info *info, char *limiter, t_tree *tree)
{
	pid_t	pid;
	int		status;
	int		doc_pipe[2];

	if (pipe(doc_pipe) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		close(doc_pipe[1]);
		close(doc_pipe[0]);
		return (1);
	}
	if (pid == 0)
	{
		signal(SIGINT, handle_heredoc_sig);
		signal(SIGQUIT, SIG_IGN);
		read_write(limiter, doc_pipe[1]);
		close(doc_pipe[0]);
		free_and_set_null(info, 2);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 1)
		{
			our_static("exit status", 1);
			return (close(tree->fd), FALSE);
		}
	}
	close(doc_pipe[1]);
	return (doc_pipe[0]);
}

int	find_docs(t_info *info, t_tree *tree)
{
	int	result;

	result = 1;
	if (!tree)
		return (0);
	if (tree && tree->type == HEREDOC)
	{
		tree->fd = ft_hdoc(info, tree->file, tree);
		if (tree->left != NULL)
			if (here_docs_ahead(tree->left) == TRUE)
			{
				close(tree->fd);
				tree->fd = -1;
			}
	}
	if (tree->left)
		result = find_docs(info, tree->left);
	if (tree->right)
		result = find_docs(info, tree->right);
	return (result);
}

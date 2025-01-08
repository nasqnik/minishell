/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:11:22 by maakhan           #+#    #+#             */
/*   Updated: 2025/01/08 16:57:28 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			// new_line = env_expansion(new_line, env, shl); // ana, do expansions
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
		// g_signal_caught = SIGINT;
		close(STDIN_FILENO);
	}
}

int	ft_hdoc(t_info *info, char *limiter, t_tree *tree)
{
	pid_t	pid;
	int status;
	int	doc_pipe[2];

	// printf("limiter: %s", limiter);
	if (pipe(doc_pipe) == -1)
		return (1); //error pipe
	pid = fork();
	if (pid == -1)
	{
		close(doc_pipe[1]);
		close(doc_pipe[0]);
		return (1);
	}
		// (free_array(shl->env), nuke(shl, TNT), print_exit(ERR_FORK));
	if (pid == 0)
	{
		signal(SIGINT, handle_heredoc_sig);
		signal(SIGQUIT, SIG_IGN);
		read_write(limiter, doc_pipe[1]);
		close(doc_pipe[0]);
		free_and_set_null(info, 2);
		exit (0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 1)
		{
			our_static("exit status", 1);
			printf("\nheloooooooooooooOOOOOOO\n");
			return (close(tree->fd), FALSE);
		}
	}
	close(doc_pipe[1]);
	// free(limiter); // fixed
	// printf("fd doc_pipe: %d\n", doc_pipe[0]);
	return (doc_pipe[0]);
}

int	find_docs(t_info *info, t_tree *tree)
{
	int		result;

	result = 1;
	
	if (!tree)
		return (0); 
	if (tree && tree->type == HEREDOC)
	{
		tree->fd = ft_hdoc(info, tree->file, tree);
		// printf("fd in find_docs: %d\n", tree->fd);
		if (tree->left != NULL)
			if (here_docs_ahead(tree->left) == TRUE)
			{
				// printf("\nthats true\n");
				// printf("\ntree fd:%d", tree->fd);
				close(tree->fd);
				tree->fd = -1;
				// printf("\ntree fd:%d", tree->fd);

			}
	}
	if (tree->left)
		result = find_docs(info, tree->left);
	if (tree->right)
		result = find_docs(info, tree->right);
	return (result);
}

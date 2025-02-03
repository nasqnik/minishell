/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 08:25:36 by meid              #+#    #+#             */
/*   Updated: 2025/02/03 09:50:47 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	read_loop(char *line, char *stop, int write_to, char *limiter)
{
	char	*new_line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (line)
		{
			if (!ft_strncmp(line, stop, ft_strlen(limiter) + 1))
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
}

static void	read_write(char *limiter, int write_to)
{
	char	*line;
	char	*new_limiter;
	int		len;
	char	*stop;

	line = NULL;
	new_limiter = NULL;
	len = ft_strlen(limiter);
	if (limiter[0] == '\'' || limiter[0] == '\"')
	{
		new_limiter = ft_substr(limiter, 1, len - 2);
		if (!new_limiter)
			new_limiter = ft_strdup("");
	}
	stop = limiter;
	if (new_limiter)
		stop = new_limiter;
	read_loop(line, stop, write_to, limiter);
	close(write_to);
}

static int	fork_here_doc(t_info *info, pid_t *pid, int doc_pipe[2],
		char *limiter)
{
	(*pid) = fork();
	if ((*pid) == -1)
	{
		close(doc_pipe[1]);
		close(doc_pipe[0]);
		return (1);
	}
	if ((*pid) == 0)
	{
		signal(SIGINT, handle_heredoc_sig);
		signal(SIGQUIT, SIG_IGN);
		read_write(limiter, doc_pipe[1]);
		close(doc_pipe[0]);
		free_and_set_null(info, 2);
		exit(0);
	}
	return (0);
}

static int	handle_one_heredoc(t_info *info, char *limiter, t_tokens *list)
{
	pid_t	pid;
	int		status;
	int		doc_pipe[2];

	if (pipe(doc_pipe) == -1)
		return (1);
	castom_ing();
	if (fork_here_doc(info, &pid, doc_pipe, limiter))
		return (1);
	waitpid(pid, &status, 0);
	castom_signals();
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 1)
		{
			our_static("exit status", 1);
			return (close(list->fd), FALSE);
		}
	}
	close(doc_pipe[1]);
	return (doc_pipe[0]);
}

void	here_doc(t_info *info, t_tokens *list)
{
	t_tokens	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp && tmp->next && tmp->type == HEREDOC
			&& tmp->next->type == DELIMITER)
		{
			tmp->fd = handle_one_heredoc(info, tmp->next->data, tmp);
			if (tmp->next->next && here_docs_ahead(tmp->next->next))
			{
				printf("close\n");
				close(tmp->fd);
				tmp->fd = -1;
			}
		}
		tmp = tmp->next;
	}
}

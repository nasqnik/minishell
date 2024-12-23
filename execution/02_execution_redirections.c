/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_execution_redirections.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:49:44 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/24 13:55:26 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_file(t_first *f)
{
	char	*buffer;
	char	*limiter;
	int		file;

	buffer = NULL;
	limiter = ft_strjoin(f->ast_tree->file, "\n");
	file = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1 || limiter == NULL)
	{
		perror("Error opening file or allocating limiter");
		free(limiter);
		return ;
	}
	while (1)
	{
		write(1, "heredoc> ", 9);
		buffer = get_next_line(0);
		if (ft_strncmp(limiter, buffer, ft_strlen(limiter)) == 0)
			break ;
		ft_putstr_fd(buffer, file);
		free(buffer);
	}
	free(buffer);
	free(limiter);
	close(file);
	file = open("here_doc", O_RDONLY, 0777);
	dup2(file, STDIN_FILENO);
	unlink("here_doc");
}

void send_info_to_fd(t_first *f, int fd[2], int tree_type)
{
	char	*str;
	int		file;
	char	buffer[1024];
	ssize_t	bytes_read;

	if (tree_type == HEREDOC)
		str = "here_doc";
	else
		str = f->ast_tree->file;
	file = open(str, O_RDONLY);
	if (file == -1)
		exit(1);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	while ((bytes_read = read(file, buffer, sizeof(buffer))) > 0)
		write(STDOUT_FILENO, buffer, bytes_read);
	close(file);
	ft_clear_tokens(&(f->token_list));
	ft_clear_tree(f->ast_tree);
	ft_clear_list(&(f->envp_list));
	exit(0);
}

void execute_from_fd(t_first *f, int fd[2], int tree_type)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	execute_command(f, f->ast_tree->left);
	if (tree_type == HEREDOC)
		unlink("here_doc");
	ft_clear_tokens(&(f->token_list));
	ft_clear_tree(f->ast_tree);
	ft_clear_list(&(f->envp_list));
	exit(0);
}

int	Redirects_stdin(t_first *f, int tree_type)
{
	int		fd[2];
	int		status;
	int		id1;
	int		id2;

	status = 0;
	if (tree_type == HEREDOC)
		get_file(f);
	if (pipe(fd) == -1)
		return (1);
	id1 = fork();
	if (id1 == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	if (id1 == 0)
		send_info_to_fd(f, fd, tree_type);
	id2 = fork();
	if (id2 == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	if (id2 == 0)
		execute_from_fd(f, fd, tree_type);
	close (fd[0]);
	close (fd[1]);
	waitpid(id1, NULL, 0);
	waitpid(id2, &status, 0);
	return (WEXITSTATUS(status));
}

void	receive_the_input(t_first *f, int fd[2], int tree_type)
{
	char	*str;
	int		file;
	char	buffer[1024];
	ssize_t	bytes_read;

	str = f->ast_tree->file;
	if (tree_type == REDIRECT_APPEND)
		file = open(str, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		file = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		exit(1);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
		write(file, buffer, bytes_read);
	close(file);
	ft_clear_tokens(&(f->token_list));
	ft_clear_tree(f->ast_tree);
	ft_clear_list(&(f->envp_list));
	exit(0);
}

void	execute_to_fd(t_first *f, int fd[2])
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execute_command(f, f->ast_tree->left);
	ft_clear_tokens(&(f->token_list));
	ft_clear_tree(f->ast_tree);
	ft_clear_list(&(f->envp_list));
	exit(0);
}

int	Redirects_stdout(t_first *f, int tree_type)
{
	int		fd[2];
	int		status;
	int		id1;
	int		id2;

	status = 0;
	if (pipe(fd) == -1)
		return (1);
	id1 = fork();
	if (id1 == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	if (id1 == 0)
		execute_to_fd(f, fd);
	id2 = fork();
	if (id2 == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	if (id2 == 0)
		receive_the_input(f, fd, tree_type);
	close (fd[0]);
	close (fd[1]);
	waitpid(id1, NULL, 0);
	waitpid(id2, &status, 0);
	return (WEXITSTATUS(status));
}

int	execute_redirections(t_first *f, int tree_type)
{
	int	return_value;

	return_value = 0;
	if (tree_type == HEREDOC || tree_type == REDIRECT_IN)
		return_value = Redirects_stdin(f, tree_type);
	else if (tree_type == REDIRECT_OUT || tree_type == REDIRECT_APPEND)
		return_value = Redirects_stdout(f, tree_type);
	else
		printf("wrong in put");
	return (return_value);
}

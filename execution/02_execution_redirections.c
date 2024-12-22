/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_execution_redirections.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:49:44 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/22 10:44:11 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_file(t_first *f)
{
	char	*buffer;
    char	*limiter;
	int		file;

	file = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	limiter = ft_strjoin(f->ast_tree->file, "\n");
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
}

void send_info_to_fd(t_first *f, int fd[2])
{
	(void)f;
    int file = open("here_doc", O_RDONLY);
    if (file == -1)
        exit(1);

    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);

    char buffer[1024];
    ssize_t bytes_read;
    while ((bytes_read = read(file, buffer, sizeof(buffer))) > 0)
        write(STDOUT_FILENO, buffer, bytes_read);
    close(file);
    exit(0);
}

void execute_from_fd(t_first *f, int fd[2])
{
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);

    execute_command(f, f->ast_tree->left);
    exit(0);
}


int execute_redirections(t_first *f, int tree_type)
{
	// int return_value;
	// if (tree_type == HEREDOC || tree_type == REDIRECT_IN)
	// 	return_value = Redirects_stdin(f, tree_type)
	// if (tree_type == REDIRECT_OUT || tree_type == REDIRECT_APPEND)
	// 	return_value = Redirects_stdout(f, tree_type);
		
		get_file(f);
	(void)tree_type;
	int		fd[2];
	int		status;
	int		id1;
	int		id2;

	if (pipe(fd) == -1)
		return (1);
	id1 = fork();
	if (id1 == -1)
		return (1);
	if (id1 == 0)
		send_info_to_fd(f, fd); // write into fd[1]
	id2 = fork();
	if (id2 == 0)
		execute_from_fd(f, fd);
	// free_here(h);
	close (fd[0]);
	close (fd[1]);
	waitpid(id1, NULL, 0);
	waitpid(id2, &status, 0);
	return (WEXITSTATUS(status));
}
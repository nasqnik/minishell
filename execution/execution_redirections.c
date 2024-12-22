/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:49:44 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/22 08:03:21 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_the_command(t_first *f, int fd)
{
	int pid;
	printf("pov");
	char **args = f->ast_tree->left->args;
	    int i = 0;
    while (args[i])
    {
        printf("string: %s\n", args[i]);
        i++;
    }

    pid = fork();
	if (pid == -1)
        return ;
		
    else if (pid == 0)
        execute_binary(f, f->ast_tree->left->args[0], f->ast_tree->left->args, fd);
    wait(NULL);
}

void execute_redirections(t_first *f, int tree_type)
{
	(void)tree_type;
        int fd = handle_here_doc(f);
		execute_the_command(f, fd);
			unlink(".heredoc_tmp");
} 

int	handle_here_doc(t_first *f)
{
	char	*buffer;
    char	*limiter;
	int		file;

	file = open_file("heredoc_tmp", 'W', f);
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
	file = open_file("heredoc_tmp", 'R', f);
	return (file);
	// handle_dup2(file, -1);
	// unlink(".heredoc_tmp");
}

int	open_file(char *filepath, char mode, t_first *f)
{
	int	fd;

	fd = 0;
	if (mode == 'R' && access(filepath, R_OK) == -1)
    {
        ft_putstr_fd("minishell: ", fd);
        ft_putstr_fd(f->ast_tree->file, fd);
        ft_putstr_fd("\033[31m: Permission denied\033[00m", fd);
		return 0;
    }
	if (mode == 'R')
		fd = open(filepath, O_RDONLY);
	else if (mode == 'W')
		fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (mode == 'A')
		fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
        ft_putstr_fd("minishell: ", fd);
        ft_putstr_fd(f->ast_tree->file, fd);
        ft_putstr_fd("\033[31m: No such file or directory\033[00m", fd);
		return 0;
    }
	return (fd);
}

void	handle_dup2(int input_fd, int output_fd)
{
	if (input_fd != -1)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			return ;
		close(input_fd);
	}
	if (output_fd != -1)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
			return ;
		close(output_fd);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:49:44 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/19 19:21:04 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_redirections(t_first *f, int tree_type)
{
    int pid;
    int fd;

    pid = fork();
    fd = 0;
    if (pid == -1)
        return ;
    if (tree_type == HEREDOC)
        handle_here_doc(f);
    else
        handle_files();
    
    
  // execute_command(f, tree->left);  
} 

void	handle_here_doc(t_first *f)
{
	char	*buffer;
    char	*limiter;
	int		file;

	file = open_file(".heredoc_tmp", 'W', f);
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
	file = open_file(".heredoc_tmp", 'R', f);
	handle_dup2(file, -1);
	unlink(".heredoc_tmp");
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
		return ;
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
		return ;
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 20:04:03 by meid              #+#    #+#             */
/*   Updated: 2025/01/05 16:46:12 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void  execution(t_info *info, t_tree *tree)
{
    if (!info->ast_tree || !tree)
		return ;
    // printf("token_type:%s\n", token_type_to_string(tree->type));
    if (tree->type == LOGIC_AND)
    {
        execution(info, tree->left);
        if (our_static("exit status", -1) == 0)
            execution(info, tree->right);
    }
    else if (tree->type == LOGIC_OR)
    {
        execution(info, tree->left);
        if (our_static("exit status", -1) != 0)
            execution(info, tree->right);
    }
    else if (tree->type == PIPE)
        execution_pipe(info, tree);
    else if (tree->type >= REDIRECT_IN && tree->type <= HEREDOC)
        execution_redirection(info, tree);
    else if (tree->type == COMMAND)
        execute_command(info, tree);
}

void execution_pipe(t_info *info, t_tree *tree)
{
    int pipefd[2];
    pid_t   pipe_left;
    pid_t   pipe_right;
    int status_left, status_right;

    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return ;
    }
    pipe_left = handle_left_pipe(info, tree, pipefd);
    pipe_right = handle_right_pipe(info, tree, pipefd);
    close(pipefd[1]);
    close(pipefd[0]);

    // waitpid(pipe_left, NULL, 0);
    // waitpid(pipe_right, NULL, 0);
    waitpid(pipe_left, &status_left, 0);
    waitpid(pipe_right, &status_right, 0);
    if (WIFEXITED(status_left) && WEXITSTATUS(status_left) != 0)
        our_static("exit status",  WEXITSTATUS(status_left));
    else if (WIFEXITED(status_right) && WEXITSTATUS(status_right) != 0)
        our_static("exit status",  WEXITSTATUS(status_right));
}

pid_t   handle_left_pipe(t_info *info, t_tree *tree, int pipefd[2])
{
    (void)info;
    pid_t pid;

    pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }// add error
    if (pid == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execution(info, tree->left);
        free_and_set_null(info, 2);
        exit(EXIT_SUCCESS);
    }
    
    return(pid);
}

pid_t   handle_right_pipe(t_info *info, t_tree *tree, int pipefd[2])
{
    pid_t pid;

    pid = fork(); 
    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }// add error
    if (pid == 0)
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        execution(info, tree->right);
        free_and_set_null(info, 2);
        exit(EXIT_SUCCESS);
    }
    return(pid);
}

void execution_redirection(t_info *info, t_tree *tree)
{
    
    if (tree->type == HEREDOC)
        get_file(info);
    else if (tree->type == REDIRECT_IN)
        handle_redirect_in(info, tree);
    else if (tree->type == REDIRECT_OUT)
        handle_redirect_out(info, tree);
    else if (tree->type == REDIRECT_APPEND)
        handle_redirect_append(info, tree);
    execution(info, tree->left);
}

void handle_redirect_in(t_info *info, t_tree *tree)
{
    (void)info;
    int file;

    file = open(tree->file, O_RDONLY, 0); //have to check permissions
    if (file == -1)
    {
        perror("Error opening file for input redirection");
        return;
    }
    if (dup2(file, STDIN_FILENO) == -1)
    {
        perror("Error duplicating file descriptor");
    }
    close(file);
}

void handle_redirect_out(t_info *info, t_tree *tree)
{
    (void)info;
    int file;

    file = open(tree->file, O_WRONLY | O_CREAT | O_TRUNC, 0644); //have to check permissions
    if (file == -1)
        return ;
    dup2(file, STDOUT_FILENO);
    close(file);
}

void handle_redirect_append(t_info *info, t_tree *tree)
{
        (void)info;
    int file;

    file = open(tree->file, O_WRONLY | O_CREAT | O_APPEND, 0644); //have to check permissions
    if (file == -1)
        return ;
    dup2(file, STDOUT_FILENO);
    close(file);
}

void	get_file(t_info *info)
{
	char	*buffer;
	char	*limiter;
	int		file;

	buffer = NULL;
	limiter = ft_strjoin(info->ast_tree->file, "\n");
	file = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0600);
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
        if (!buffer)
        {
            perror("Error reading from stdin");
            break;
        }
		if (ft_strncmp(limiter, buffer, ft_strlen(limiter)) == 0)
        {
            free(buffer);
            break;
        }
		ft_putstr_fd(buffer, file);
		free(buffer);
	}
	free(buffer);
	free(limiter);
	close(file);
	file = open("here_doc", O_RDONLY);
	dup2(file, STDIN_FILENO);
    if (unlink("here_doc") == -1)
        perror("Error unlinking here_doc");
}

// start with heredoc 
// if the command is not right it should stop exe
// 
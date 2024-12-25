/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 20:04:03 by meid              #+#    #+#             */
/*   Updated: 2024/12/24 16:53:19 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execution(t_first *f, t_tree *tree)
{
    if (!f->ast_tree || !tree)
		return ;
    if (tree->type == PIPE)
        execution_pipe(f, tree);
    else if (tree->type >= REDIRECT_IN && tree->type <= HEREDOC)
        execution_redirection(f, tree);
    else if (tree->type == COMMAND)
        execute_command(f, tree);
}

void execution_pipe(t_first *f, t_tree *tree)
{
    int pipefd[2];
    pid_t   pipe_left;
    pid_t   pipe_right;
    int left;
    int right;

    pipe(pipefd);
    // if (pipefd == -1)
    //     return ;
    pipe_left = handle_left_pipe(f, tree, pipefd);
    pipe_right = handle_right_pipe(f, tree, pipefd);
    waitpid(pipe_left, &left, 0);
    waitpid(pipe_right, &right, 0); 
}

pid_t   handle_left_pipe(t_first *f, t_tree *tree, int pipefd[2])
{
    (void)f;
    pid_t pid;

    pid = fork();
    // if (pid = -1)
    //     error
    if (pid == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execution(f, tree->left);
    }
    
    return(pid);
}

pid_t   handle_right_pipe(t_first *f, t_tree *tree, int pipefd[2])
{
    pid_t pid;

    pid = fork(); 
    // if (pid = -1)
    //     error
    if (pid == 0)
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        execution(f, tree->right);
    }
    return(pid);
}

void execution_redirection(t_first *f, t_tree *tree)
{
    
    if (tree->type == HEREDOC)
        get_file(f);
    else if (tree->type == REDIRECT_IN)
        handle_redirect_in(f, tree);
    else if (tree->type == REDIRECT_OUT)
        handle_redirect_out(f, tree);
    else if (tree->type == REDIRECT_APPEND)
        handle_redirect_append(f, tree);
    execution(f, tree->left);
}

void handle_redirect_in(t_first *f, t_tree *tree)
{
        (void)f;
    int file;

    file = open(tree->file, O_RDONLY, 0777); //have to check permissions
    dup2(file, STDIN_FILENO);
    close(file);
}

void handle_redirect_out(t_first *f, t_tree *tree)
{
        (void)f;
    int file;

    file = open(tree->file, O_WRONLY | O_CREAT | O_TRUNC, 0777); //have to check permissions
    if (file == -1)
        return ;
    dup2(file, STDOUT_FILENO);
    close(file);
}

void handle_redirect_append(t_first *f, t_tree *tree)
{
        (void)f;
    int file;

    file = open(tree->file, O_WRONLY | O_CREAT | O_APPEND, 0777); //have to check permissions
    if (file == -1)
        return ;
    dup2(file, STDOUT_FILENO);
    close(file);
}
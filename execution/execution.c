/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:58:32 by meid              #+#    #+#             */
/*   Updated: 2025/01/09 14:40:36 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_command(t_info *info, t_tree *tree)
{
    int return_builtin;
    int status;

    
    if (!info || !tree)
        return;
        
    expand_command(info, tree);
    return_builtin = strcmp_builtin(info, tree->args[0], tree->args);
    if (return_builtin == 0)
    {
        our_static("exit status", 0);
                // Consider moving this to a cleanup function
        if (info->stdout && info->stdin)
        {
            if (dup2(info->stdout, STDOUT_FILENO) == -1 ||
                dup2(info->stdin, STDIN_FILENO) == -1)
            {
                perror("dup2 failed during cleanup");
            }
        }    
    }
    if (return_builtin == 2)
    {
        close(info->stdin);
        close(info->stdout);
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork failed");
            return;
        }
        else if (pid == 0)
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            // printf("execute_binary\n");
            int exit_status = execute_binary(info, tree->args[0], tree->args, 1);
            // Clean up and exit
			free_and_set_null(info, 2);
            if (exit_status != 0)
                exit (exit_status);
        }
        waitpid(pid, &status, 0);
        // ft_putstr_fd("helllooooooooooo\n", 1);
        // printf("WIFEXITED(status): %d\n", WIFEXITED(status));
        // printf("WEXITSTATUS(status): %d\n", WEXITSTATUS(status));
        if (WIFEXITED(status))
            our_static("exit status",   WEXITSTATUS(status));
        if (WIFSIGNALED(status))
        {
            if (WTERMSIG(status) == SIGQUIT || WTERMSIG(status) == SIGSEGV)
            {
                if (WTERMSIG(status) == SIGQUIT)
		            write(2, "Quit: ", 7);
                else
		            write(2, "Segmentation fault: ", 20);;
                char *mas = ft_itoa(WTERMSIG(status));
                write(2, mas, ft_strlen(mas)); 
                write(2, "\n", 1);  
            }
            our_static("exit status",   WTERMSIG(status) + 128);
        }
    }
}

int	strcmp_builtin(t_info *info, char *command, char **args)
{
	int	i;

	i = 1;
	if (ft_strcmp(command, "echo") == 0)
		return (ft_echo(args, i)); // return 1 when there is an error
	if (ft_strcmp(command, "cd") == 0)
		return (ft_cd(info, args, i)); // return 0 
	if (ft_strcmp(command, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(command, "export") == 0)
		return (ft_export(info, args, i));
	if (ft_strcmp(command, "unset") == 0)
		return (ft_unset(info, args, i));
	if (ft_strcmp(command, "env") == 0)
		return (ft_env(info, args, i));
	if (ft_strcmp(command, "exit") == 0)
		return (ft_exit(info, args, i, 0));
	if (ft_strcmp(command, "meow") == 0)
		return (ft_meow(info, args, i, 0));
	return (2);
}

// ◦ echo with option -n
// ◦ cd with only a relative or absolute path ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options
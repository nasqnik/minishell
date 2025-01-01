/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:58:32 by meid              #+#    #+#             */
/*   Updated: 2025/01/01 10:43:31 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_command(t_info *info, t_tree *tree)
{
    int status;
    
    if (!info || !tree)
        return;
        
    expand_command(info, tree);
    
    if (!strcmp_builtin(info, tree->args[0], tree->args))
    {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork failed");
            return;
        }
        else if (pid == 0)
        {
            execute_binary(info, tree->args[0], tree->args, 1);
            // Clean up and exit
			close(info->stdout);
	    	close(info->stdin);
            ft_clear_tree(info->ast_tree);
            ft_clear_list(&(info->envp_list));
        	free(info->buffer);
        	info->buffer = NULL;
            exit(1);
        }
        waitpid(pid, &status, 0);
        info->last_status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
    }
    
    // Consider moving this to a cleanup function
    if (dup2(info->stdout, STDOUT_FILENO) == -1 ||
        dup2(info->stdin, STDIN_FILENO) == -1)
    {
        perror("dup2 failed during cleanup");
    }
}

int	strcmp_builtin(t_info *info, char *command, char **args)
{
	int	i;

	i = 1;
	if (ft_strcmp(command, "echo") == 0)
		return (ft_echo(args, i));
	if (ft_strcmp(command, "cd") == 0)
		return (ft_cd(info, args, i));
	if (ft_strcmp(command, "pwd") == 0)
		return (ft_pwd(args, i));
	if (ft_strcmp(command, "export") == 0)
		return (ft_export(info, args, i));
	if (ft_strcmp(command, "unset") == 0)
		return (ft_unset(info, args, i));
	if (ft_strcmp(command, "env") == 0)
		return (ft_env(info, args, i));
	if (ft_strcmp(command, "exit") == 0)
		return (ft_exit(info, args, i, 0));
	if (ft_strcmp(command, "meow") == 0)
		return (ft_meow(args, i, 0));
	return (0);
}

// ◦ echo with option -n
// ◦ cd with only a relative or absolute path ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options
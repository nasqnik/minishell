/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:58:32 by meid              #+#    #+#             */
/*   Updated: 2024/12/19 18:49:59 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int str_cmp_builtin(t_first *f, char *command, char **args)
{
    
    int i = 1;
    
    if (ft_strcmp(command, "echo") == 0) // done
        return(ft_echo(args, i));
    if (ft_strcmp(command, "cd") == 0)
        return(ft_cd(f, args, i));
    if (ft_strcmp(command, "pwd") == 0) // done
        return(ft_pwd(args, i));
    if (ft_strcmp(command, "export") == 0) // connect with the real env list
        return(ft_export(f, args, i));
    if (ft_strcmp(command, "unset") == 0) // connect with the real env list
        return(ft_unset(f, args, i));
    if (ft_strcmp(command, "env") == 0) // connect with the real env list
        return(ft_env(f, args, i));
    if (ft_strcmp(command, "exit") == 0)
        return(ft_exit(f, args, i));
    if (ft_strcmp(command, "meow") == 0)
        return(ft_meow(args, i));
    return 0;
}
void execute_command(t_first *f, t_tree *tree)
{
    int	pid;

    if (!(str_cmp_builtin(f, tree->args[0], tree->args)))
    {
        // update the envp_array;
        pid = fork();
	    if (pid == -1)
            return ;
        else if (pid == 0)
            execute_binary(f, tree->args[0], tree->args);
        wait(NULL);
    }
}

char	*find_path(char *command, t_first *f)
{
	char	**all_paths;
	char	*command_path;
	char	*tmp;
	int		i;

	all_paths = ft_split(search_in_env(f, "PATH"), ':');
	if (!all_paths)
		return (NULL);
	i = 0;
	while (all_paths[i])
	{
		tmp = ft_strjoin(all_paths[i], "/");
		command_path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(command_path, F_OK | X_OK) == 0)
		{
			free_array(all_paths);
			return (command_path);
		}
		free(command_path);
		i++;
	}
	free_array(all_paths);
	return (NULL);
}

void execute_binary(t_first *f, char *command, char **args)
{
    
    int fd = 1;
    
	char	*command_path;

	if (command[0] != '/')
        command_path = find_path(args[0], f);
    else
        command_path = args[0];
    if (!command_path || access(command_path, X_OK) == -1)
    {
        ft_putstr_fd("minishell: ", fd);
        ft_putstr_fd("\033[31mcommand not found: \033[00m", fd);
        ft_putstr_fd(args[0], fd);
        ft_putchar_fd('\n', fd);
        return ;
    }
    if (execve(command_path, args, f->envp_array) == -1)
    {
        ft_putstr_fd("minishell: ", fd);
        ft_putstr_fd("\033[31merror executing command: \033[00m", fd);
        ft_putstr_fd(args[0], fd);
        ft_putchar_fd('\n', fd);
        return ;
    }
}

// ◦ echo with option -n
// ◦ cd with only a relative or absolute path ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options




void execution(t_first *f)
{
    if (!f->ast_tree)
        return ;
    t_tree *tree = f->ast_tree;
    
    if (tree->type >= REDIRECT_IN && tree->type <= HEREDOC)
    {
        execute_redirections(f, tree->type);
       
    }
    // else if (tree->type == COMMAND)
    //     execute_command(f, tree);
    else
    {
        printf("now only commmands\n");
        return ;
    }
}
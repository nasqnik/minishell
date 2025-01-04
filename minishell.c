/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:02:22 by anikitin          #+#    #+#             */
/*   Updated: 2025/01/03 15:37:18 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_and_set_null(t_info *info, int flag)
{
	if (info->token_list)
		ft_clear_tokens(&(info->token_list));
	if (info->ast_tree)
        ft_clear_tree(info->ast_tree);
	if (info->stdout)
		close(info->stdout);
	if (info->stdin)
	    close(info->stdin);
	if (flag == 1) // between the calls
	{
		info->stdout = dup(STDOUT_FILENO);
		info->stdin = dup(STDIN_FILENO);
	}
	else // at the end or exit
	{
		if (info->envp_array)
			free_array(info->envp_array);
		if (info->envp_list)
			ft_clear_list(&(info->envp_list));
	}
	info->token_list = NULL;
	info->ast_tree = NULL;
}

char **ft_allocate_env(char **env)
{
	int i = 0;
	char **env_array;

	while (env[i])
		i++;
	env_array = malloc(sizeof(char *) * (i + 1));
	if (!env_array)
		return NULL;
	i = 0;
	while (env[i])
	{
		env_array[i] = ft_strdup(env[i]);
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

static void	initialize(t_info *info, char **env)
{
	info->buffer = NULL;
	info->token_list = NULL;
	info->ast_tree = NULL;
	info->envp_array = ft_allocate_env(env);
	info->envp_list = NULL;
	info->i = 0;
	info->exit_status = 0;
	info->stdout = dup(STDOUT_FILENO);
	info->stdin = dup(STDIN_FILENO);
	if (info->stdout == -1 || info->stdin == -1) {
    	perror("dup failed");
    	exit(EXIT_FAILURE);
	}
	info->exit_status = 0;
    
	// f->last_arg = "empty";
	// signal(SIGINT, handle_signal);
	// signal(SIGQUIT, SIG_IGN);
	env_to_list(info);
}



int main(int argc, char **argv, char **env)
{
    t_info info;
    
    (void)argv;
    
    if (argc != 1)
	{
		printf("Dont add another paratmer just ./minishell\n"); // perror? exit_code?
		return (1); // or exit?
	}
    initialize(&info, env);
	if (!(info.envp_list))
		return (0);
    while (1)
	{
        // signals(info);
        info.buffer = readline("mini_cat😺$ ");
		free_and_set_null(&info, 1);
        if (info.buffer)
        {
            add_history(info.buffer);
            if (parsing(&info))
				continue;
            free(info.buffer);
            info.buffer = NULL;
			execution(&info, info.ast_tree); // should we s if there is an error in the parsing sould we execiute a part
        }
    }
	free_and_set_null(&info, 2);
	printf("out of the looop\n");
	printf("info.stdout: %d, info.stdin: %d\n", info.stdout, info.stdin);
	if (close(info.stdout) != -1)
		printf("%d, is closed\n", info.stdout);
	else
		printf("i am not closed, Regards, stdout\n");
	if (close(info.stdin) != -1)
		printf("%d, is closed\n", info.stdin);
	else
		printf("i am not closed, Regards, stdin\n");
	// ft_clear_list(&(info.envp_list));
}
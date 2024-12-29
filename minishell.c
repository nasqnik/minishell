/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:02:22 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/27 13:45:33 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialize(t_info *info, char **env)
{
	info->buffer = NULL;
	info->token_list = NULL;
	info->ast_tree = NULL;
	info->envp_array = env;
	info->envp_list = NULL;
	info->i = 0;
	info->stdout = dup(STDOUT_FILENO);
	info->stdin = dup(STDOUT_FILENO);
    
	// f->exit_status = 0;
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
    while (1)
	{
        // signals(info);
        
        info.buffer = readline("\033[92mmini_cat😺$ \033[00m");
        if (info.buffer)
        {
            add_history(info.buffer);
            parsing(&info);
			execution(&info, info.ast_tree); // should we s if there is an error in the parsing sould we execiute a part
			print_ast(info.ast_tree, 5, "head");
            free(info.buffer);
            info.buffer = NULL;
        }
		if (info.token_list)
			ft_clear_tokens(&info.token_list);
		if (info.ast_tree)
			ft_clear_tree(info.ast_tree);
    }
	ft_clear_list(&(info.envp_list));
    
}
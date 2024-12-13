/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:25:43 by meid              #+#    #+#             */
/*   Updated: 2024/12/12 12:54:35 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signalnumber;

void handle_signal(int sig) 
{
    (void)sig;
    g_signalnumber = SIGINT;
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay(); 
}

void initialize(t_first *f, char **env)
{
    f->buffer = NULL;
    f->token_list = NULL;
    f->envp_list = NULL;
    f->i = 0;
    f->envp_array = env;
    f->envp_list = NULL;
    f->i = 0;
    f->exit_status = 0;
    f->last_arg = "empty"; //change later
    signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

int main(int ac, char **av, char **env) {
    t_first f;

    (void)av;
    if (ac != 1)
    {
        printf("Dont add another paratmer just ./minishell\n");
        return(1);
    }
    initialize(&f, env);
    
    // for (int i = 0; i < 5; i++)
    //     printf("[%d]  %s\n", i, f.envp_list[i]);
    
    // print_env(&f , 1);
    // printf("----  %s  ----\n", search_in_env(&f, "HOME"));   // <------ there is a function to search in env
    while (1) 
    {
        if (g_signalnumber != SIGINT)
            f.buffer = readline("\033[92mminishell$ \033[00m");
        else
            f.buffer = readline(NULL);
        if (!f.buffer) {
            printf("\nExiting...\n");
            break;
        }
        if (*f.buffer != '\0')
        {
            parsing(&f);
            add_history(f.buffer);
            free(f.buffer);
            f.buffer = NULL;
        }
        ft_clear_tokens(&(f.token_list));
        ft_clear_list(&(f.envp_list));
    }
    return 0;
}
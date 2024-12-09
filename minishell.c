/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:25:43 by meid              #+#    #+#             */
/*   Updated: 2024/12/09 13:34:30 by meid             ###   ########.fr       */
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

void initialize(t_first *f)
{
    f->buffer = NULL;
    f->token_list = NULL;
    f->envp_list = NULL;
    f->i = 0;
}

int main(int ac, char **av) {
    t_first f;

    (void)av;
    if (ac != 1)
    {
        printf("Dont add another paratmer just ./minishell\n");
        return(1);
    }
    initialize(&f);
        signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
    while (1) 
    {
        // if (f.error_flag) // Skip processing if an error occurred
        // {
        //     f.error_flag = 0; // Reset the error flag
        //     continue;
        // }
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
            // check_parenthesis(&f);
            parsing(&f);
            // handle_the_input(&f);
            add_history(f.buffer);
        }
        free(f.buffer);
        ft_clear_tokens(&(f.token_list));
    }
    return 0;
}

// void check_parenthesis(t_first *f)
// {
//     (void)f;
//     f->i = 0;
//     int i = 0;
//     int open = 0;
//     int flag = 0;
//     while (f->buffer[f->i])
//     {
//         open = ft_is_open_parenthesis(f->buffer[f->i]);
//         if (open == 34 || open == 39 || open == 40)
//         {
//             flag = 0;
//             i = ++f->i;
//             while (f->buffer[i])
//             {
//                 if(ft_is_close_parenthesis(open, f->buffer[i]) == 1)
//                 {
//                     flag = 1;
//                     break ;
//                 }
//                 i++;
//             }
//         }
//         f->i++;
//     }
//     if (flag == 1)
//         printf("fine    \n");
//     if (flag == 0)
//         printf("not fine     \n");
// }
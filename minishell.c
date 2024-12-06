/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:25:43 by meid              #+#    #+#             */
/*   Updated: 2024/12/05 22:02:44 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void handle_signal(int signal) {
//     if (signal == SIGINT) {
//         write(1, "\n", 1); // Print newline
//         exit(0);           // Exit gracefully
//     }
// }

int main(int ac, char **av) {
    t_first f;
    f.i = 0;

    (void)av;
    if (ac != 1)
    {
        printf("Dont add another paratmer just ./minishell");
        return(1);
    }

    // signal(SIGINT, handle_signal);
    while (1) {
        f.buffer = readline("\033[92mminishell$ \033[00m");
        if (!f.buffer) {
            printf("\nExiting...\n");
            break;
        }
        if (*f.buffer != '\0')
        {
            // check_parenthesis(&f);
            tokens(&f, f.buffer);
            // parsing(&f);
            // handle_the_input(&f);
            add_history(f.buffer);
        }
        free(f.buffer);
    }
    return 0;
}

void check_parenthesis(t_first *f)
{
    (void)f;
    f->i = 0;
    int i = 0;
    int open = 0;
    int flag = 0;
    while (f->buffer[f->i])
    {
        open = ft_is_open_parenthesis(f->buffer[f->i]);
        if (open == 34 || open == 39 || open == 40)
        {
            flag = 0;
            i = ++f->i;
            while (f->buffer[i])
            {
                if(ft_is_close_parenthesis(open, f->buffer[i]) == 1)
                {
                    flag = 1;
                    break ;
                }
                i++;
            }
        }
        f->i++;
    }
    if (flag == 1)
        printf("fine    \n");
    if (flag == 0)
        printf("not fine     \n");
}

void parsing(t_first *f)
{
    (void)f;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:13:22 by meid              #+#    #+#             */
/*   Updated: 2024/12/05 16:24:05 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void handle_calc(t_first *f)
// {
//     (void)f;
//     char c_num1[10];
//     char *c_num2;
//     char op;
//     int num1;
//     int num2;
//     (void)c_num1;
//     (void)c_num2;
//     (void)op;
//     (void)num1;
//     (void)num2;
//     int i = 0;
//     f->j = 0;
//     while (f->input[f->i])
//     {
//         printf("1\n");
//         while (f->input[f->i][f->j])
//         {
//             printf("2\n");
//             if (f->input[f->i][f->j] == ')')
//             {
//                 if (f->input[f->i][++f->j] != ')')
//                     printf(">\n");
//                 f->flag = 10;
//                 break;
//             }
//             printf("3\n");
//             while (ft_isdigit(f->input[f->i][f->j]) == 1)
//             {
//                 printf("4\n");
//                 c_num1[i] = f->input[f->i][f->j];
//                 i++;
//                 f->j++;
//             }
//             printf("5\n");
            
//             printf("d: %c", c_num1[0]);
//             f->j++;
//         }
//         if (f->flag == 10)
//             break ;
//         f->i++;
//     }
//     printf("calc");
// }


// void handle_calc(t_first *f)
// {
    
// }

void handle_echo(t_first *f)
{
    f->i = 1;
    if (f->input[f->i] && ft_strcmp(f->input[f->i], "-n") != 0)
        f->flag = 'y';
    else if (f->input[f->i])
        f->i++;
    while (f->input[f->i])
    {
        if (ft_strncmp(f->input[f->i], "$((", 3) == 0)
            printf("l");
            // handle_calc(f);
        else
            printf("%s", f->input[f->i]);
        f->i++;
    }
    if (f->flag == 'y')
        printf("\n");
}

void handle_the_input(t_first *f)
{
    (void)f;
    f->input = ft_split(f->buffer, 32);
    while(f->input[f->i])
    {
        printf("string [%d]: %s\n", f->i, f->input[f->i]);
        f->i++;
    }
    if (ft_strcmp(f->input[0], "echo") == 0)
        handle_echo(f);
    else
        printf("buffer: %s\n", f->buffer);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:11:03 by meid              #+#    #+#             */
/*   Updated: 2024/12/05 20:52:03 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_error(t_first *f, char *msg, int flag)
{
    (void)f;
    printf("\033[31m %s\033[00m\n", msg);
    if (flag == 1)
        printf("\033[31mfree list\033[00m\n");
    // i think we should use a signal here
    return ;
}
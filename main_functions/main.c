/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:28:10 by meid              #+#    #+#             */
/*   Updated: 2025/01/09 15:29:19 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int ac, char **av, char **env)
{
    t_info info;
    
    (void)av;
    
    if (ac != 1)
	{
		printf("\033[31mminicat: %s:no such file or directory\033[00m\n", av[1]);
		exit (127);
	}
    initialize(&info, env);
	if (!(info.envp_list))
		return (0);
	minishell(&info);
	free_and_set_null(&info, 2);
	
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
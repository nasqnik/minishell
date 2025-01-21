/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:28:10 by meid              #+#    #+#             */
/*   Updated: 2025/01/21 11:02:48 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	t_info	info;

	(void)av;
	if (ac != 1)
	{
		printf("\033[31mminicat: %s:no such file or directory\033[00m\n",
			av[1]);
		exit(127);
	}
	initialize(&info, env);
	minishell(&info);
	free_and_set_null(&info, 2);
	ft_clear_list(&(info.envp_list));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:27:53 by meid              #+#    #+#             */
/*   Updated: 2025/01/14 13:06:49 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minishell(t_info *info)
{
	while (1)
	{
		disable_echoctl();
		castom_signals();
		free_and_set_null(info, 1);
		info->buffer = readline("mini_cat😺$ ");
		if (!info->buffer)
		// there is condtion that i did not understand (isatty(0))
		{
			write(2, "exit\n", 5);
			free_and_set_null(info, 2);
			exit(1);
		}
		if (info->buffer)
		{
			add_history(info->buffer);
			if (parsing(info))
				continue ;
			free(info->buffer);
			info->buffer = NULL;
			find_docs(info, info->ast_tree);
			execution(info, info->ast_tree);
		}
	}
}

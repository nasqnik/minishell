/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 09:22:31 by meid              #+#    #+#             */
/*   Updated: 2025/02/05 15:20:53 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signals_exit_statue(int status)
{
	char	*massage;

	if (WIFEXITED(status))
		our_static("exit status", WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT || WTERMSIG(status) == SIGSEGV)
		{
			if (WTERMSIG(status) == SIGQUIT)
				write(2, "Quit: ", 7);
			else
			{
				write(2, "Segmentation fault: ", 20);
				massage = ft_itoa(WTERMSIG(status));
				write(2, massage, ft_strlen(massage));
				free(massage);
				write(2, "\n", 1);
			}
			our_static("exit status", WTERMSIG(status) + 128);
		}
	}
}

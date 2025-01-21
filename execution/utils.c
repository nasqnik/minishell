/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 09:22:31 by meid              #+#    #+#             */
/*   Updated: 2025/01/21 12:23:11 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_permissions(const char *file, int mode)
{
	struct stat	file_stat;

	if (stat(file, &file_stat) == -1)
	{
		perror("stat error");
		return (-1);
	}
	if (mode == R_OK && !(file_stat.st_mode & S_IRUSR))
		return (-1);
	if (mode == W_OK && !(file_stat.st_mode & S_IWUSR))
		return (-1);
	return (0);
}

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
				write(2, "\n", 1);
			}
			our_static("exit status", WTERMSIG(status) + 128);
		}
	}
}
// int check_file_path(t_info *info, char *str)
// {
//     char		buf[1024];

// 	if (getcwd(buf, sizeof(buf)) == NULL)
// 		return (1);

// }
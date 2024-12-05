/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:13:34 by meid              #+#    #+#             */
/*   Updated: 2024/12/04 09:20:00 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void first(int fd[2])
{
    close(fd[0]);
	write(1, "minishell$ ", 11);
    write(fd[1], "8", 1);
}

void second(t_first *f, int fd[2])
{
    // int     read_bytes;
    char j;
    // int from_input;

    read(fd[0], &j, 1);
    if (j == '8')
    {
	    f->buffer = readline("minishell$ ");
        // from_input = 
        handle_the_input(f);
    }
}

void open_the_shell(t_first *f)
{
	int		fd[2];
	int		status;
	int		id1;
	int		id2;

	if (pipe(fd) == -1)
		return ;
	id1 = fork();
	if (id1 == -1)
		return ;
	if (id1 == 0)
        first(fd);
	id2 = fork();
	if (id2 == 0)
        second(f, fd);
	close (fd[0]);
	close (fd[1]);
	waitpid(id1, NULL, 0);
	waitpid(id2, &status, 0);
}

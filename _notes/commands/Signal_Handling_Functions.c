/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signal_Handling_Functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:45:08 by meid              #+#    #+#             */
/*   Updated: 2025/01/17 15:45:16 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ## Signal Handling Functions:
// [signal]* - <signal.h>
// [sigaction] - <signal.h>
// [sigemptyset] - <signal.h>
// [sigaddset] - <signal.h>
// [kill] - <signal.h>

// signal : Sets a signal handler for a specific signal.
//void (*signal(int signum, void (*handler)(int)))(int);

// sigaction : : Provides a more advanced way to set
// signal handlers, offering better control than signal.
// int sigaction(int signum, const struct sigaction *act,
		// struct sigaction *oldact);

// The sigemptyset function is used to initialize a signal set 
// to exclude all signals.
// It clears all bits in the signal set,
	// effectively creating an empty signal set.
// int sigemptyset(sigset_t *set);

//sigaddset :: Adds a specific signal to a signal set.
// int sigaddset(sigset_t *set, int signum);

// kill :: Sends a signal to a specific process or group of processes.
// int kill(pid_t pid, int sig);

// #include "libft/libft.h"
// #include <signal.h>

// void	handle_sigusr(int sig)
// {
// 	static char	c;
// 	static int	i;

// 	if (sig == SIGUSR1)
// 		c = (c << 1) + 1;
// 	else if (sig == SIGUSR2)
// 		c = (c << 1) + 0;
// 	i++;
// 	if (i == 8)
// 	{
// 		ft_printf("%c", c);
// 		i = 0;
// 		c = 0;
// 	}
// }

// int	main(void)
// {
// 	struct sigaction	sa;

// 	ft_printf("%d\n", getpid());
// 	sa.sa_handler = &handle_sigusr;
// 	while (1)
// 	{
// 		sigaction(SIGUSR1, &sa, NULL);
// 		sigaction(SIGUSR2, &sa, NULL);
// 	}
// }

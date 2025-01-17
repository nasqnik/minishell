/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_a_problem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:45:37 by meid              #+#    #+#             */
/*   Updated: 2025/01/17 18:08:14 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// Segmentation fault: 11
int	main(void)
{
	printf("smaklfnahbs\n");
	int	*ptr;

	ptr = NULL;
	*ptr = 42;
	return (0);
}

// #include <signal.h>

// // Quit : 4
// int main(void)
// {
//     raise(SIGQUIT); // Send SIGQUIT to the process itself
//     return (0);
// }

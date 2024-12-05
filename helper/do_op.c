/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:43:28 by meid              #+#    #+#             */
/*   Updated: 2024/12/03 20:05:38 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int do_op(char *str, t_first *f)
// {
// 	int i = 1;
// 	f->i = 0;

// 	int result = 0;
// 	while (1)
// 	{
		
// 	}
// 	printf("\n");
// 	printf("result %d \n", result);
// 	return (result);
// 	1
// }

// int do_op(char *str, t_first *f)
// {
// 	int i = 1;
// 	f->i = 0;
// 	char **op = ft_split(str, ' ');
// 	int result = 0;
// 	while (1)
// 	{
// 		printf("lo\n");
// 		while(op[f->i])
//     	{
//         	printf("op [%d]: %s\n", f->i, op[f->i]);
//         	f->i++;
//     	}
// 		printf ("op: %s ", op[1]);
// 		if ((char)op[i] != '+' || (char)op[i] != '-' || (char)op[i] != '*' || (char)op[i] != '/' || (char)op[i] != '%')
// 			break ;
// 		if ((char)op[i]== '+')
// 			result += atoi(op[i - 1]) + atoi(op[i + 1]);
// 		if ((char)op[i] == '-')
// 			result += atoi(op[i - 1]) - atoi(op[i + 1]);
// 		if ((char)op[i] == '*')
// 			result += atoi(op[i - 1]) * atoi(op[i + 1]);
// 		if ((char)op[i] == '/')
// 			result += atoi(op[i - 1]) / atoi(op[i + 1]);
// 		if ((char)op[i] == '%')
// 			result += atoi(op[i - 1]) % atoi(op[i + 1]);
// 		i += 2;
// 	}
// 	printf("\n");
// 	printf("result %d \n", result);
// 	return (result);
// }
// echo $(( 4 + 3 )) 
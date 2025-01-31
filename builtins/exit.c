/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:08:37 by meid              #+#    #+#             */
/*   Updated: 2025/01/31 18:40:56 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_and_set_sign(char **str, int *i, int *sign)
{
	while (((*str)[(*i)] && (*str)[(*i)] == 32)
		|| ((*str)[(*i)] >= 9 && (*str)[(*i)] <= 13))
		i++;
	if ((*str)[(*i)] == '-' || (*str)[(*i)] == '+')
	{
		if ((*str)[(*i)] == '-')
			(*sign) = -1;
		(*i)++;
	}
}

static int	ft_ascii_to_exitcode(t_info *info, char *str)
{
	int					i;
	int					sign;
	long long			res;

	i = 0;
	sign = 1;
	res = 0;
	skip_and_set_sign(&str, &i, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		if ((sign == 1 && res > 9223372036854775807)
			|| (sign != -1 && res > 9223372036854775807))
		{
			handle_error(info, str, 0, 5);
			return (255);
		}
		i++;
	}
	res *= sign;
	while ((int)res < 0)
		res += 256;
	if (res > 255)
		res = res % 255;
	return ((int)res);
}

int	ft_exit(t_info *info, char **args, int i, int j)
{
	int	exit_code;

	exit_code = 0;
	ft_putstr_fd("exit\n", 1);
	while (args[i])
	{
		if (i > 1)
			return (print_the_error(info, NULL, 4, 2), 0);
		while (args[i][j])
		{
			if (!((args[i][j] >= '0' && args[i][j] <= '9')
			|| (args[i][0] == '-')))
			{
				handle_error(info, args[i], 0, 5);
				free_and_set_null(info, 2);
				exit(255);
			}
			j++;
		}
		exit_code = ft_ascii_to_exitcode(info, args[i]);
		i++;
	}
	free_and_set_null(info, 2);
	exit(exit_code);
}

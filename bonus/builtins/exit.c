/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:08:37 by meid              #+#    #+#             */
/*   Updated: 2025/02/03 19:53:47 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	skip_and_set_sign(char **str, int *i, int *sign)
{
	if (!((*str)))
		return (1);
	while (((*str)[(*i)] && (*str)[(*i)] == 32) || ((*str)[(*i)] >= 9
			&& (*str)[(*i)] <= 13))
		i++;
	if ((*str)[(*i)] && ((*str)[(*i)] == '-' || (*str)[(*i)] == '+'))
	{
		if ((*str)[(*i)] == '-')
			(*sign) = -1;
		(*i)++;
	}
	return (0);
}

static int	ft_ascii_to_exitcode(t_info *info, char *str)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	if (skip_and_set_sign(&str, &i, &sign))
		return (1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		if ((sign == 1 && res > 9223372036854775807) || (sign != -1
				&& res > 9223372036854775807))
			return (handle_error(info, str, 0, 5), 255);
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
	ft_putstr_fd("exit\n", 2);
	if (ft_arraylen(args) > 2)
		return (handle_error(info, NULL, 0, 4), 1);
	if (args[1] && args[1][0] == '\0')
	{
		handle_error(info, args[i], 0, 5);
		free_and_set_null(info, 2);
		exit(255);
	}
	while (args[1] && args[1][j])
	{
		if (!((args[1][j] >= '0' && args[1][j] <= '9') || (args[1][0] == '-')))
		{
			handle_error(info, args[1], 0, 5);
			free_and_set_null(info, 2);
			exit(255);
		}
		j++;
	}
	exit_code = ft_ascii_to_exitcode(info, args[1]);
	free_and_set_null(info, 2);
	exit(exit_code);
}

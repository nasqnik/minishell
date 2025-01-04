/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:48:46 by meid              #+#    #+#             */
/*   Updated: 2025/01/04 08:18:35 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is(int c, char *str)
{
	if (ft_strcmp(str, "alnum") == 0)
	{
		return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A'
				&& c <= 'Z'));
	}
	else if (ft_strcmp(str, "space") == 0)
		return (c == 32 || (c >= 9 && c <= 13));
	else if (ft_strcmp(str, "quote") == 0)
		return (c == 39 || c == 34);
	else if (ft_strcmp(str, "op") == 0)
		return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
	else if (ft_strcmp(str, "operator") == 0)
		return (c == '|' || c == '>' || c == '<' || c == '&');
	else if (ft_strcmp(str, "brackets") == 0)
		return (c == '(' || c == ')');
	return (0);
}


int our_static(char *str, int set)
{
	static int exit_status = 0;

	if (ft_strcmp(str, "exit status") == 0)
	{
		if (set != -1)
		{
			exit_status = set;
		}
		return (exit_status);
	}
	return (0);
}



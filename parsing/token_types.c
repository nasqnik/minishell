/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:35:25 by anikitin          #+#    #+#             */
/*   Updated: 2025/01/02 12:28:42 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	*operators_token(char *str, t_info *info, int len)
{
	char	flag;
	int		type;
	char	cur;

	flag = 'o';
	cur = str[info->i];
	info->i++;
	if (str[info->i] == cur)
	{
		info->i++;
		flag = 'O';
	}
	if (cur == '&' && flag != 'O')
		return (handle_error(info, "&", 2, '\0'), NULL);
	type = check_operator_type(flag, cur);
	len = info->i - len;
	return (ft_create_token(info, len, type, str));
}

static int	find_bracket_positions(char *str, t_info *info, int *start, int *end)
{
	int	stack;

	stack = 0;
	*start = -1;
	*end = -1;
	while (str[info->i])
	{
		if (str[info->i] == '(')
		{
			if (stack++ == 0)
				*start = info->i;
		}
		else if (str[info->i] == ')')
		{
			if (--stack == 0)
			{
				*end = info->i;
				info->i++;
				return (1);
			}
		}
		info->i++;
	}
	return (0);
}

t_tokens	*bracket_token(char *str, t_info *info, int len)
{
	int	type;
	int	start;
	int	end;

	type = BRACKET;
	if (!find_bracket_positions(str, info, &start, &end))
	{
		handle_error(info, "newline", 2, '\0');
		return (NULL);
	}
	len = info->i - len;
	return (ft_create_token(info, len, type, str));
}

t_tokens	*word_token(char *str, t_info *info, int len)
{
	char close;

	while (str[info->i])
	{
		while (str[info->i] && ft_isspace(str[info->i]) == 0 && str[info->i] != '\'' && str[info->i] != '\"'
			&& ft_isoperator(str[info->i]) == 0 && str[info->i] != ')' && str[info->i] != '(')
			info->i++;
		if ((str[info->i] && (ft_isoperator(str[info->i]) == 1 || str[info->i] == ')'
			|| str[info->i] == '(' || ft_isspace(str[info->i]) == 1)) || str[info->i] == '\0')
			break ;
		close = str[info->i];
		info->i++;
		while (str[info->i] && str[info->i] != close)
			info->i++;
		if (str[info->i] && str[info->i] == close)
			info->i++;
		else
			return (handle_error(info, "newline", 2, '\0'), NULL);
	} 
	len = info->i - len;
    if (len == 0) // Ensure non-empty token
	{
		printf("there is somthing weird\n");
		// return (handle_error(info, "Empty token detected", 2, '\0'), NULL);
	}  
	return (ft_create_token(info, len, WORD, str));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:35:25 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/13 18:56:55 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	*operators_token(char *str, t_first *f, int len)
{
	char	flag;
	int		type;
	char	cur;

	flag = 'o';
	cur = str[f->i];
	f->i++;
	if (str[f->i] == cur)
	{
		f->i++;
		flag = 'O';
	}
	if (cur == '&' && flag != 'O')
		return (handle_error(f, "you cant use one &", 1), NULL);
	type = check_operator_type(flag, cur);
	len = f->i - len;
	return (ft_create_token(f, len, type, str));
}

t_tokens	*variable_token(char *str, t_first *f, int len)
{
	int	type;

	f->i++;
	type = ENV_VAR;
	if (str[f->i] == ' ' || str[f->i] == '\0')
		return (ft_create_token(f, f->i - len, WORD, str));
	else
	{
		while (str[f->i] && str[f->i] == '$')
			f->i++;
		while (str[f->i] && (ft_is(str[f->i], "alnum") || ft_is(str[f->i],
					"brackets") || str[f->i] == '_' || str[f->i] == '?'))
			f->i++;
	}
	len = f->i - len;
	return (ft_create_token(f, len, type, str));
}

t_tokens	*quote_token(char *str, t_first *f, int len)
{
	int		type;
	char	close;

	type = S_QUOTES;
	if (str[f->i] == '\"')
		type = D_QUOTES;
	close = str[f->i];
	f->i++;
	while (str[f->i] && str[f->i] != close)
		f->i++;
	if (str[f->i] && str[f->i] == close)
		f->i++;
	else
		return (handle_error(f, "you did not close "" | '' | ()", 1), NULL);
	len = f->i - len;
	return (ft_create_token(f, len, type, str));
}

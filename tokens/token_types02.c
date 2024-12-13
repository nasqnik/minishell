/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:28:31 by meid              #+#    #+#             */
/*   Updated: 2024/12/13 18:57:01 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	find_bracket_positions(char *str, t_first *f, int *start, int *end)
{
	int	stack;

	stack = 0;
	*start = -1;
	*end = -1;
	while (str[f->i])
	{
		if (str[f->i] == '(')
		{
			if (stack++ == 0)
				*start = f->i;
		}
		else if (str[f->i] == ')')
		{
			if (--stack == 0)
			{
				*end = f->i;
				f->i++;
				return (1);
			}
		}
		f->i++;
	}
	return (0);
}

t_tokens	*bracket_token(char *str, t_first *f, int len)
{
	int	type;
	int	start;
	int	end;

	type = BRACKET;
	if (!find_bracket_positions(str, f, &start, &end))
	{
		handle_error(f, "hey, the brackets are not matching", 1);
		return (NULL);
	}
	len = f->i - len;
	return (ft_create_token(f, len, type, str));
}

t_tokens	*word_token(char *str, t_first *f, int len)
{
	while (str[f->i] && ft_isspace(str[f->i]) == 0
		&& ft_isoperator(str[f->i]) == 0 && str[f->i] != '$' && str[f->i] != ')'
		&& str[f->i] != '(' && ft_isquote(str[f->i]) == 0)
		f->i++;
	len = f->i - len;
	return (ft_create_token(f, len, WORD, str));
}

t_tokens	*space_token(char *str, t_first *f)
{
	while (str[f->i] && ft_is(str[f->i], "space") == 1)
		f->i++;
	return (ft_create_token(f, 1, WSPACE, str));
}

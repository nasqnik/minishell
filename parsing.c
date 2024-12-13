/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:33:53 by meid              #+#    #+#             */
/*   Updated: 2024/12/13 20:11:18 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_first *f)
{
	env_to_list(f);
	f->i = 0;
	lexer(f, f->buffer);
	here_doc_env_check(f);
	expand_variables(f);
	rename_tokens(f);
	remove_spaces(f);
	verify_logic(f);
	wildcard_str(f);
	print_after_expansions(f);
}
	//wildcard(f); - put the check for ls

void	lexer(t_first *f, char *str)
{
	int			len;
	t_tokens	*current_token;

	f->token_list = NULL;
	while (str[f->i] && ft_isspace(str[f->i]) == 1)
		f->i++;
	while (str[f->i])
	{
		len = f->i;
		if (str[f->i] == '$')
			current_token = variable_token(str, f, len);
		else if (ft_is(str[f->i], "quote"))
			current_token = quote_token(str, f, len);
		else if (ft_is(str[f->i], "brackets"))
			current_token = bracket_token(str, f, len);
		else if (ft_is(str[f->i], "operator"))
			current_token = operators_token(str, f, len);
		else if (ft_is(str[f->i], "space"))
			current_token = space_token(str, f);
		else
			current_token = word_token(str, f, len);
		if (!current_token)
			return ;
		add_back_token(&f->token_list, current_token);
	}
}

void	expand_variables(t_first *f)
{
	t_tokens	*cursor;

	cursor = f->token_list;
	while (cursor != NULL)
	{
		if (cursor->type == ENV_VAR)
			expand_envp(cursor, f);
		else if (cursor->type == D_QUOTES)
			expand_d_quotes(cursor, f);
		cursor = cursor->next;
	}
}

void	here_doc_env_check(t_first *f)
{
	t_tokens	*tmp;
	char		*tmpo;

	tmp = f->token_list;
	while (tmp != NULL)
	{
		if (tmp->type == HEREDOC)
		{
			tmp = tmp->next;
			if (tmp && tmp->type == WSPACE)
				tmp = tmp->next;
			if (tmp && tmp->type == ENV_VAR)
			{
				tmpo = ft_strjoin("$", tmp->data);
				free(tmp->data);
				tmp->data = tmpo;
			}
			tmp->type = DELIMITER;
		}
		tmp = tmp->next;
	}
}

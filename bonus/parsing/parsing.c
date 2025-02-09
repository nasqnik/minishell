/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:38:28 by anikitin          #+#    #+#             */
/*   Updated: 2025/02/03 16:47:12 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	parsing(t_info *info)
{
	t_tokens	*tokens;

	info->i = 0;
	if (lexer(info, info->buffer) || !info->token_list)
	{
		free(info->buffer);
		info->buffer = NULL;
		return (1);
	}
	free(info->buffer);
	info->buffer = NULL;
	if (rename_tokens(info))
		return (1);
	if (verify_logic(info))
		return (1);
	tokens = info->token_list;
	here_doc(info, tokens);
	info->ast_tree = create_ast_tree(&tokens);
	if (info->ast_tree == NULL)
		return (handle_error(info, "creat_tree", 2, '\0'), 1);
	ft_clear_tokens(&info->token_list);
	return (0);
}

int	lexer(t_info *info, char *str)
{
	int			len;
	t_tokens	*current_token;

	if (!str || !str[info->i])
		return (1);
	while (str[info->i])
	{
		len = info->i;
		if (ft_is(str[info->i], "space") == 1)
		{
			while (str[info->i] && ft_is(str[info->i], "space") == 1)
				info->i++;
			continue ;
		}
		else if (str[info->i] && ft_is(str[info->i], "operator"))
			current_token = operators_token(str, info, len);
		else if (str[info->i] && ft_is(str[info->i], "brackets"))
			current_token = bracket_token(str, info, len);
		else
			current_token = word_token(str, info, len);
		if (!current_token)
			return (1);
		add_back_token(&info->token_list, current_token);
	}
	return (0);
}

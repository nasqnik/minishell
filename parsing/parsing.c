/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:38:28 by anikitin          #+#    #+#             */
/*   Updated: 2025/01/14 13:30:29 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// echo <<HEREDOC 1<2<3 "hi"'howareyou'$USER | ejrhgb e;rojg ||erbg && en

#include "../minishell.h"

int	parsing(t_info *info)
{
	t_tokens	*tokens;

	info->i = 0;
	if (lexer(info, info->buffer))
		return (1);
	if (!info->token_list)
		return (1);
	free(info->buffer);
	info->buffer = NULL;
	// printf("1\n");
	// print_list(info->token_list);
	if (rename_tokens(info))
		return (1);
	// printf("2\n");
	// print_list(info->token_list);
	if (verify_logic(info))
		return (1);
	// printf("3\n");
	print_list(info->token_list);
	tokens = info->token_list;
	info->ast_tree = create_ast_tree(&tokens);
	if (info->ast_tree == NULL)
		return (handle_error(info, "creat_tree", 2, '\0'), 1);
		// meybe we dont need that
	ft_clear_tokens(&info->token_list);
	print_ast(info->ast_tree, 5, "head");
	return (0);
}

int	lexer(t_info *info, char *str)
{
	int			len;
	t_tokens	*current_token;

	if (!str[info->i])
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

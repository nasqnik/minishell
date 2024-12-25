/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:38:28 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/25 19:16:14 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// echo <<HEREDOC 1<2<3 "hi"'howareyou'$USER | ejrhgb e;rojg ||erbg && en

#include "../minishell.h"

void parsing(t_info *info)
{
    lexer(info, info->buffer);
	rename_tokens(info);
	print_list(info->token_list);
	info->ast_tree = create_ast_tree(&info->token_list);
	print_ast(info->ast_tree, 5, "head");
}					

void lexer(t_info *info, char *str)
{
    int			len;
	t_tokens	*current_token;

    info->i = 0;
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
			return ;
		add_back_token(&info->token_list, current_token);
	}
}


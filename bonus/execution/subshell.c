/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:20:32 by meid              #+#    #+#             */
/*   Updated: 2025/02/04 20:21:35 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

char	*ft_strtrim_sides(char *str)
{
	char	*stro;

	if (ft_strlen(str) == 2)
	{
		return (ft_strdup(""));
	}
	stro = ft_substr(str, 1, ft_strlen(str) - 2);
	return (stro);
}

void	parsing_subshell(t_info *info, t_tree **subtree)
{
	char		*new_buffer;
	t_tokens	*tokens;

	new_buffer = ft_strtrim_sides(info->buffer);
	if (new_buffer[0] == '\0')
		return (free(info->buffer), free(new_buffer));
	free(info->buffer);
	info->buffer = NULL;
	info->i = 0;
	if (lexer(info, new_buffer))
		return ;
	free(new_buffer);
	new_buffer = NULL;
	if (rename_tokens(info))
		return ;
	if (verify_logic(info))
		return ;
	tokens = info->token_list;
	here_doc(info, tokens);
	(*subtree) = create_ast_tree(&tokens);
	if (info->ast_tree == NULL)
		return (handle_error(info, "creat_tree", 2, '\0'));
	ft_clear_tokens(&info->token_list);
}

void	subshell(t_info *info, t_tree *tree)
{
	t_tree	*subtree;

	subtree = NULL;
	if (!tree || tree->type != BRACKET || !tree->file)
		return ;
	info->buffer = ft_strdup(tree->file);
	parsing_subshell(info, &subtree);
	if (!subtree)
		return ;
	add_subtree(info, subtree);
	execution(info, subtree);
}

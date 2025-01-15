/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:20:32 by meid              #+#    #+#             */
/*   Updated: 2025/01/15 16:24:59 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strtrim_sides(char *str)
{
	char	*stro;

	stro = ft_substr(str, 1, ft_strlen(str) - 2);
	return (stro);
}

t_tree	*parsing_subshell(t_info *info)
{
	char		*new_buffer;
	t_tokens	*tokens;
	t_tree		*subshell;

	// printf("parsing_subshell\n");
	new_buffer = ft_strtrim_sides(info->buffer);
	free(info->buffer), info->buffer = NULL;
	// printf("hii");
	// printf("%s\n", new_buffer);
	if (lexer(info, new_buffer))
		return (NULL);
	free(new_buffer), new_buffer = NULL;
	if (rename_tokens(info))
		return (NULL);
	if (verify_logic(info))
	{
		printf("the error inside the subshell");
		return (NULL);
	}
	tokens = info->token_list;
	subshell = create_ast_tree(&tokens);
	// print_list(info->token_list);
	if (info->ast_tree == NULL)
		return (handle_error(info, "creat_tree", 2, '\0'), NULL);
		// meybe we dont need that
	ft_clear_tokens(&info->token_list);
	// print_ast(subshell, 5, "head");
	return (subshell);
}

void	subshell(t_info *info, t_tree *tree)
{
	if (!tree || tree->type != BRACKET || !tree->file)
		return ;
	info->buffer = ft_strdup(tree->file);
	t_tree *subtree = parsing_subshell(info);
	if (!subtree)
		return ;
	(void)subtree;
	execution(info, subtree);
	ft_clear_tree(subtree);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:09:21 by anikitin          #+#    #+#             */
/*   Updated: 2025/01/08 18:24:33 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void expand_redirection(t_info *info, t_tree *tree)
{
    char *result;
    int wildcard_flag;

    wildcard_flag = wildcard(info, &result);
    if (wildcard_flag == 0)
	{
        result = process_expansion(tree->file, info);
        if (*result == '\0')
            handle_error(info, tree->file, 0, 2);
		result = clean_quotes(result);
		free(tree->file);
		tree->file = ft_strdup(result);
	}
    else
        handle_error(info, tree->file, 0, 2);
    free(result);
}
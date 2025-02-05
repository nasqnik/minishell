/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:09:21 by anikitin          #+#    #+#             */
/*   Updated: 2025/01/17 19:23:01 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static int	handle_wildcard_expansion(t_info *info, char *tmp, t_tree *tree)
{
	char	**wildcard_array;
	char	*result;
	int		i;

	wildcard_array = ft_split(tmp, ' ');
	free(tmp);
	i = 0;
	while (wildcard_array[i])
		i++;
	if (i == 1)
	{
		result = ft_strdup(wildcard_array[0]);
		free_array(wildcard_array);
		free(tree->file);
		tree->file = ft_strdup(result);
	}
	else
	{
		free_array(wildcard_array);
		handle_error(info, tree->file, 0, 2);
		return (1);
	}
	return (0);
}

static void	process_regular_expansion(t_info *info, t_tree *tree)
{
	char	*result;

	result = process_expansion(tree->file, info);
	if (*result == '\0')
		handle_error(info, tree->file, 0, 2);
	result = clean_quotes(result);
	free(tree->file);
	tree->file = ft_strdup(result);
	free(result);
}

int	expand_redirection(t_info *info, t_tree *tree)
{
	int		result_code;
	char	*tmp;

	tmp = ft_strdup(tree->file);
	wildcard(info, &tmp);
	if (ft_strcmp(tmp, tree->file) == 0)
	{
		free(tmp);
		process_regular_expansion(info, tree);
	}
	else
	{
		result_code = handle_wildcard_expansion(info, tmp, tree);
		if (result_code != 0)
			return (result_code);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:09:56 by anikitin          #+#    #+#             */
/*   Updated: 2025/02/05 18:25:20 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	merge_expanded_arrays(char **orig, char **wildcard,
		char **new_array, int i)
{
	int	point;
	int	j;

	point = 0;
	while (point < i)
	{
		new_array[point] = ft_strdup(orig[point]);
		point++;
	}
	j = 0;
	while (wildcard && wildcard[j])
		new_array[point++] = ft_strdup(wildcard[j++]);
	j = i + 1;
	while (orig[j])
		new_array[point++] = ft_strdup(orig[j++]);
	new_array[point] = NULL;
}

static void	handle_wildcard(char ***args, char *result, int *i)
{
	int		new_array_size;
	char	**wildcard_array;
	char	**new_array;
	int		wildcard_count;

	wildcard_array = ft_split(result, ' ');
	wildcard_count = ft_arraylen(wildcard_array);
	new_array_size = wildcard_count + ft_arraylen(*args);
	new_array = malloc(sizeof(char *) * (new_array_size + 1));
	merge_expanded_arrays(*args, wildcard_array, new_array, *i);
	free_array(*args);
	*args = new_array;
	free_array(wildcard_array);
	*i += wildcard_count;
}

void	expand_command(t_info *info, t_tree *tree)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	while (tree->args[i])
	{
		result = process_expansion(tree->args[i], info);
		if (wildcard(info, &result) == 0)
		{
			result = clean_quotes(result);
			free(tree->args[i]);
			tree->args[i] = ft_strdup(result);
		}
		else
			handle_wildcard(&tree->args, result, &i);
		if (result)
		{
			free(result);
			result = NULL;
		}
		if (!tree->args[i])
			return ;
		i++;
	}
}

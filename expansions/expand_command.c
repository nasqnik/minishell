/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:09:56 by anikitin          #+#    #+#             */
/*   Updated: 2025/01/08 17:10:12 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void expand_command(t_info *info, t_tree *tree)
{
	int i;
	int wildcard_flag;
	char *result;


	char **wildcard_array;
	char **new_array;

	i = 0;
	wildcard_flag = 0;
	wildcard_array = NULL;
	while (tree->args[i])
	{
		result = process_expansion(tree->args[i], info);
		wildcard_flag = wildcard(info, &result);
		// printf("result: %s\n", result);
		if (wildcard_flag == 0)
		{
			result = clean_quotes(result);
			free(tree->args[i]);
			tree->args[i] = ft_strdup(result);
		}
		else
		{
			int wildcard_count;
			int arg_count;
			int new_array_size = 0;

			wildcard_array = ft_split(result, ' ');
			wildcard_count = 0;

			while (wildcard_array[wildcard_count])
				wildcard_count++;

			arg_count = 0;
			while(tree->args[arg_count])
				arg_count++;

			new_array_size = arg_count + wildcard_count;
			new_array = malloc(sizeof(char *) * (new_array_size));
			new_array[new_array_size - 1] = NULL;

			int point;
			point = 0;
			while (point < i)
			{
				new_array[point] = ft_strdup(tree->args[point]);
				point++;
			}
			int j = 0;

			while (wildcard_array[j])
				new_array[point++] = ft_strdup(wildcard_array[j++]);

			j = i + 1;
			while (tree->args[j])
				new_array[point++] = ft_strdup(tree->args[j++]);
			new_array[point] = NULL; 
			free_array(tree->args);
			tree->args = new_array;
			free_array(wildcard_array);
			i += wildcard_count;
		}
		free(result);
		if (!tree->args[i])
			return;
		i++;
	}
}
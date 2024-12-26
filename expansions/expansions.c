/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:16:00 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/26 15:39:05 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void expand_command(t_info *info, t_tree *tree)
{
	int i;
	int j;
	char *tmp;
	// char *result;
	// char *temp_result;

	i = 0;
	j = 0;
	tmp = ft_strdup("");
	while (tree->args[i])
	{
		while (tree->args[i][j])
		{
			if (tree->args[i][j] == '\"')
			{
				tmp = expand_d_quotes(tree->args[i], &j, info->envp_list);
				printf("tmp: |%s|\n", tmp);
			}
			// else if (tree->args[i][j] == '\'')
			// 	tmp = exands_quotes(tree->args[i], &j);
			
			// else if (tree->args[i][j] == '$')
			// temp_result = (ft_strjoin (, tmp));
			// free(tmp);
			j++;
		}
		i++;
	}
		
}


char *expand_d_quotes(char *str, int *pos, t_env *envp_list) // add
{
	// int i;
	// int	start;
	char *result;
	int pov[2];

	pov[0] = *pos + 1;
	pov[1] = *pos + 1;
	result = ft_strdup("");
	
	while (str[pov[0]] && str[pov[0]] != '\"')
	{
		if (str[pov[0]] == '$')
		{
			result = handle_variable(str, pov, result, envp_list);
			pov[1] = pov[0];
		}
		else
			pov[0]++;
	}
	if (pov[1] < pov[0])
		result = append_remaining_data(str, pov, result);
	*pos = pov[0];
	return result;
// 	free(token->data);
// 	token->data = result;
}
// char	*search_in_env(t_first *f, char *key)
// {
// 	t_list	*tmp;

// 	tmp = f->envp_list;
// 	while (tmp)
// 	{
// 		if (ft_strcmp(tmp->key, key) == 0)
// 			return (tmp->value);
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

// void	expand_envp(t_tokens *token, t_first *f)
// {
// 	char	*env_value;
// 	char	*new_token_data;

// 	env_value = NULL;
// 	new_token_data = NULL;
// 	if (ft_strlen(token->data) == 1)
// 	{
// 		if (((char *)(token->data))[0] == '?')
// 			new_token_data = ft_itoa(f->exit_status);
// 		else if (((char *)(token->data))[0] == '_')
// 			new_token_data = ft_strdup(f->last_arg);
// 	}
// 	else
// 	{
// 		env_value = search_in_env(f, token->data);
// 		if (env_value)
// 			new_token_data = ft_strdup(env_value);
// 	}
// 	if (new_token_data)
// 	{
// 		free(token->data);
// 		token->data = new_token_data;
// 	}
// }

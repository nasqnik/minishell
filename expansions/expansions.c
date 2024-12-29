/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:16:00 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/27 14:21:08 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// $USER'$LANG'facaskdfsd'$SHLVL'jff"$PWD"
// echo *".""c"
// echo *".c"
// echo *"as"
// echo *

void expand_command(t_info *info, t_tree *tree)
{
	int i;
	int j;
	char *tmp;
	char *tmp1;
	char *result;

	i = 0;
	j = 0;
	tmp = NULL;
	tmp1 = NULL;
	while (tree->args[i])
	{
		j = 0;
		result = ft_strdup("");
		while (tree->args[i][j])
		{
			if (tree->args[i][j] == '\"')	
				tmp = expand_d_quotes(tree->args[i], &j, info->envp_list);
			else if (tree->args[i][j] == '\'')
			 	tmp = expand_s_quotes(tree->args[i], &j);
			else
				tmp = expand_variables(tree->args[i], &j, info->envp_list);
			tmp1 = result;
			result = ft_strjoin(tmp1, tmp);
			free(tmp1);
			free(tmp);
		}
		wildcard(info, &result);
		free(tree->args[i]);
		tree->args[i] = ft_strdup(result);
		free(result);
		i++;
	}
}

char *expand_variables(char *str, int *pos, t_env *envp_list)
{
	char *result;
	int pov[2];

	pov[0] = *pos;
	pov[1] = *pos;
	result = ft_strdup("");
	
	while (str[pov[0]] && str[pov[0]] != '\'' && str[pov[0]] != '\"')
	{
		if (str[pov[0]] == '\'' || str[pov[0]] == '\"')
			break ;
		if (str[pov[0]] == '$')
		{
			result = handle_variable(str, pov, result, envp_list);
			pov[1] = pov[0];
		}
		else
			pov[0]++;
	}
	if (*result == '\0')
		result = ft_substr(str, pov[1], pov[0] - pov[1]);
	*pos = pov[0];
	return (result);
}

char *expand_d_quotes(char *str, int *pos, t_env *envp_list)
{
	char *result;
	int pov[2];

	pov[0] = *pos + 1;
	pov[1] = *pos ;
	result = ft_strdup("");
	
	while (str[pov[0]] && str[pov[0]] != '\"')
	{
		
		if (str[pov[0]] == '$')
		{
			result = handle_variable(str, pov, result, envp_list); // add $_ and $?
			pov[1] = pov[0];
		}
		else
			pov[0]++;
	}
	if (pov[1] < pov[0])
		result = append_remaining_data(str, pov, result);
	printf("result: %s\n", result);
	*pos = pov[0] + 1;
	return (result);
}

char *expand_s_quotes(char *str, int *pos)
{
	char *result;
	int i;
	
	i = *pos + 1;
	
	while (str[i] && str[i] != '\'') // check for empty
		i++;
	result = ft_substr(str, *pos, i - *pos + 1); // (str, *pos + 1, i - *pos - 1)
	*pos = i + 1;

	return (result);
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

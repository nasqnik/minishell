/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_dquotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:36:49 by anikitin          #+#    #+#             */
/*   Updated: 2025/01/14 13:42:32 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_variable(char *data, int pov[2], char *result, t_info *info) 
{
	char	*before_var;
	char	*var_value;
	char	*tmp;

	before_var = NULL;
	tmp = NULL;
	var_value = NULL;
	before_var = ft_substr(data, pov[1], pov[0] - pov[1]);
	printf("before_var: %s\n", before_var);
	var_value = handle_var_value(data, pov, info);
	printf("var_value: %s\n", var_value);
	if (before_var == NULL)
		before_var = ft_strdup("");
	tmp = ft_strjoin(result, before_var);
	free(result);
	result = ft_strjoin(tmp, var_value);
	printf("handle_var result: %s\n", result);
	free(tmp);
	free(before_var);
	free(var_value);
	return (result);
}

char *tilda_string(t_info *info, char *str, int pov[2], char *result)
{
	char *home = NULL;
	char *sub = NULL;
	int i;
	
	printf("bonjour\n");
	i = 1;
	if (str[0] == '~' && (ft_strlen(str) == 1
		|| (str[1] && (str[1] == '/' || str[1] == '+' || str[1] == '-'))))
	{
		if (str[1] == '+')
		{
			i++;
			home = search_in_env(info, "PWD");
		}
		else if (str[1] == '-')
		{
			i++;
			home = search_in_env(info, "OLDPWD");
		}
		else
			home = search_in_env(info, "HOME");
		if (home)
		{
			printf("home: %s\n", home);
			printf("lalala\n");
			// pov[0] = i;
			while (str[pov[0]] && str[pov[0]] != '\'' && str[pov[0]] != '\"' && str[pov[0]] != '$')
				pov[0]++;
			sub = ft_substr(str, i, pov[0] - i);
			if (sub == NULL)
				sub = ft_strdup("");
			free(result);
			result = ft_strjoin(home, sub);
			if (sub)
				free(sub);
			printf("result1: %s\n", result);
			return (result);
		}
	}
	pov[0]++;
	if (pov[1] < pov[0])
	{
		home = ft_substr(str, pov[1], pov[0] - pov[1]);
		sub = ft_strjoin(result, home);
		printf("sub: %s\n", sub);
		free(result);
		free(home);
		return (sub);
	}
	free(result);
	return (ft_strdup("~"));
}
char *handle_var_value(char *data, int pov[2], t_info *info)
{	

	if (data[pov[0] + 1])
		(pov[0])++;
	else
	{
		pov[0]++;
		return(ft_strdup("$"));
	}
	if (ft_is(data[pov[0]], "alnum") || data[pov[0]] == '_' || data[pov[0]] == '$')
		return (get_var(data, &pov[0], info->envp_list));
	else if (data[pov[0]] == '?')
		return(handle_exit_status(data, pov, info));
	return (ft_strdup(""));
}


char *handle_exit_status(char *data, int pov[2], t_info *info)
{
	(void)info;
	char *tmp;

	tmp = ft_itoa(our_static("exit status", -1));
	// printf("tmp: %s\n", tmp);
	pov[0]++;
	pov[1] = pov[0];

	while (data[pov[0]] && data[pov[0]] != ' ')
		pov[0]++;
	tmp = append_remaining_data(data, pov, tmp);
	return (tmp);
}

char	*append_remaining_data(char *data, int pov[2], char *result)
{
	char	*remaining_part;
	char	*new_result;

	remaining_part = ft_substr(data, pov[1], pov[0] - pov[1] + 1);
	new_result = ft_strjoin(result, remaining_part);
	free(result);
	free(remaining_part);
	return (new_result);
}

char *clean_quotes(char *result)
{
	char *end_result;
	int count;
	
	count = 0;
	count_without_quotes(result, &count);	
	end_result = substring_without_quotes(result, count);
	free(result);
	return (end_result);
}

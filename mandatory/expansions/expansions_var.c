/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:26:28 by anikitin          #+#    #+#             */
/*   Updated: 2025/02/05 18:25:35 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_exit_status(char *data, int pov[2])
{
	char	*tmp;

	tmp = ft_itoa(our_static("exit status", -1));
	pov[0]++;
	pov[1] = pov[0];
	while (data[pov[0]] && data[pov[0]] != ' '
		&& data[pov[0]] != '\"' && data[pov[0]] != '\''
		&& data[pov[0]] != '$')
		pov[0]++;
	tmp = append_remaining_data(data, pov, tmp, 0);
	return (tmp);
}

char	*get_var_value(char *var_name, t_env *envp_list)
{
	t_env	*cursor;

	cursor = envp_list;
	while (cursor)
	{
		if (!ft_strncmp(var_name, cursor->key, ft_strlen(var_name))
			&& ft_strlen(var_name) == ft_strlen(cursor->key) && cursor->value)
			return (ft_strdup(cursor->value));
		cursor = cursor->next;
	}
	return (ft_strdup(""));
}

char	*get_var(char *data, int *i, t_env *envp_list)
{
	char	*var_name;
	char	*var_value;
	int		start;

	start = *i;
	var_name = NULL;
	while (data[*i] && (ft_is(data[*i], "alnum")
			|| data[*i] == '_'))
	{
		if ((data[start] >= '0' && data[start] <= '9'))
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
	if (*i > start)
	{
		var_name = ft_substr(data, start, *i - start);
		var_value = get_var_value(var_name, envp_list);
		free(var_name);
	}
	else
		var_value = ft_strdup("");
	return (var_value);
}

char	*handle_var_value(char *data, int pov[2], t_info *info)
{
	if (!data[pov[0] + 1])
	{
		pov[0]++;
		return (ft_strdup("$"));
	}
	pov[0]++;
	if (data[pov[0]] == '$')
	{
		pov[0]++;
		return (ft_strdup(""));
	}
	if (ft_is(data[pov[0]], "alnum")
		|| data[pov[0]] == '_')
		return (get_var(data, &pov[0], info->envp_list));
	else if (data[pov[0]] == '?')
		return (handle_exit_status(data, pov));
	return (ft_strdup(""));
}

char	*handle_variable(char *data, int pov[2], char *result, t_info *info)
{
	char	*before_var;
	char	*var_value;
	char	*tmp;

	before_var = NULL;
	tmp = NULL;
	var_value = NULL;
	before_var = ft_substr(data, pov[1], pov[0] - pov[1]);
	if (!before_var)
		before_var = ft_strdup("");
	var_value = handle_var_value(data, pov, info);
	tmp = ft_strjoin(result, before_var);
	if (result)
		free(result);
	result = ft_strjoin(tmp, var_value);
	free(tmp);
	free(before_var);
	free(var_value);
	return (result);
}

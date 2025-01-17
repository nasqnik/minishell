/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:32:36 by meid              #+#    #+#             */
/*   Updated: 2025/01/17 17:25:23 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_ato_shlvl(char *str)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	sign = 1;
	res = 0;
	skip_and_set_sign(&str, &i, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		if ((sign == 1 && res > 9223372036854775807ULL)
			|| (sign == -1 && res > 9223372036854775808ULL))
			return (ft_strdup("1"));
		i++;
	}
	if (sign == 1 && res == 9223372036854775807ULL)
		return (ft_strdup("0"));
	res++;
	if ((sign == 1 && res > 9223372036854775807ULL)
		|| (sign == -1 && res > 9223372036854775808ULL))
		return (ft_strdup("1"));
	return (ft_strdup(ft_itoa(sign * (int)res)));
}

char	*shlvl_value(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (!((value[i] >= '0' && value[i] <= '9')
				|| (value[0] == '-') || (value[0] == '+')))
			return (ft_strdup("1"));
		i++;
	}
	return (ft_ato_shlvl(value));
}

void	shlvl(t_info *info)
{
	char	*tmp_str;
	t_env	*tmp;

	tmp_str = NULL;
	tmp = info->envp_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "SHLVL") == 0)
		{
			tmp->flag = 1;
			if (!(tmp->value))
				tmp->value = ft_strdup("1");
			else
			{
				tmp_str = shlvl_value(tmp->value);
				free(tmp->value);
				tmp->value = tmp_str;
			}
		}
		tmp = tmp->next;
	}
	if (search_in_env(info, "SHLVL") == NULL)
		new_env(info, ft_strdup("SHLVL"), ft_strdup("1"), 1);
}

void	add_default_env_empty_oldpwd(t_info *info)
{
	t_env	*tmp;
	char	buf[1024];

	tmp = info->envp_list;
	if (search_in_env(info, "PWD") == NULL)
	{
		if (getcwd(buf, sizeof(buf)) == NULL)
			return ;
		new_env(info, ft_strdup("PWD"), ft_strdup(buf), 1);
	}
	if (search_in_env(info, "OLDPWD") == NULL)
		new_env(info, ft_strdup("OLDPWD"), NULL, 0);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			tmp->flag = 0;
			if (tmp->value)
				free(tmp->value);
			tmp->value = NULL;
		}
		tmp = tmp->next;
	}
}

void	initialize(t_info *info, char **env)
{
	info->buffer = NULL;
	info->token_list = NULL;
	info->ast_tree = NULL;
	info->envp_array = ft_allocate_env(env);
	info->envp_list = NULL;
	info->i = 0;
	info->export_tmp = NULL;
	info->stdout = dup(STDOUT_FILENO);
	info->stdin = dup(STDIN_FILENO);
	info->temporary = NULL;
	if (info->stdout == -1 || info->stdin == -1)
	{
		perror("dup failed");
		exit(EXIT_FAILURE);
	}
	if (!info->envp_array)
	{
		info->envp_array = create_non_existing_env();
		env_to_list(info, 0);
	}
	else if (info->envp_array)
		env_to_list(info, 1);
	add_default_env_empty_oldpwd(info);
	shlvl(info);
}

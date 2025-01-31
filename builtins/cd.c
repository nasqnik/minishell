/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:40:08 by meid              #+#    #+#             */
/*   Updated: 2025/01/31 13:05:36 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_pwd(t_info *info, char *buf, int *flago)
{
	t_env		*tmp;

	tmp = info->envp_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			(*flago) = 1;
			if (tmp->value)
				free(tmp->value);
			tmp->flag = 1;
			tmp->value = ft_strdup(buf);
			break ;
		}
		tmp = tmp->next;
	}
}

void	set_oldpwd(t_info *info, char *oldpwd, int pwd_is_not_there)
{
	t_env		*tmp;

	tmp = info->envp_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0 && pwd_is_not_there == 1)
		{
			tmp->flag = 1;
			if (tmp->value)
				free(tmp->value);
		}
		else if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			tmp->flag = 1;
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(oldpwd);
			break ;
		}
		tmp = tmp->next;
	}
}

void	change_pwd_in_env(t_info *info, char *oldpwd)
{
	char		buf[1024];
	int			flago;
	static int	pwd_is_not_there;

	flago = 0;
	pwd_is_not_there = 0;
	if (getcwd(buf, sizeof(buf)) == NULL)
		return ;
	info->pwd = buf;
	set_pwd(info, buf, &flago);
	if (flago == 0)
		pwd_is_not_there++;
	else
		pwd_is_not_there = 0;
	set_oldpwd(info, oldpwd, pwd_is_not_there);
	if (pwd_is_not_there == 2)
		pwd_is_not_there = 0;
}

int	ft_cd(t_info *info, char **args)
{
	char	*str;
	char	*env_search;
	char	buf[1024];

	env_search = NULL;
	if (getcwd(buf, sizeof(buf)) == NULL)
		return (1);
	info->pwd = buf;
	str = NULL;
	if (!(args[1]))
	{
		env_search = search_in_env(info, "HOME");
		if (env_search)
			str = ft_strtrim_sides(env_search);
		else
			return (handle_error(info, NULL, 0, 11), 1);
	}
	else if (args[1] && args[1][0] == '\0')
		return (0);
	else if (args[1] && args[1][0] == '-')
	{
		env_search = search_in_env(info, "OLDPWD");
		if (env_search)
			str = ft_strtrim_sides(env_search);
		else if (args[1][1] != '\0')
			return (handle_error(info, args[1], 0, 15), 1);
		else
			return (handle_error(info, NULL, 0, 16), 1);
	}
	else
		str = ft_strdup(args[1]);
	if (chdir(str))
		return (handle_error(info, str, 0, 0), free(str), 1);
	free(str);
	return (change_pwd_in_env(info, buf), 0);
}

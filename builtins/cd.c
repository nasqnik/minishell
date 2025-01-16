/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:40:08 by meid              #+#    #+#             */
/*   Updated: 2025/01/16 19:41:20 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd_in_env(t_info *f, char *oldpwd)
{
	char		buf[1024];
	t_env		*tmp;
	int			flago;
	static int	pwd_is_not_there;

	flago = 0;
	pwd_is_not_there = 0;
	if (getcwd(buf, sizeof(buf)) == NULL)
		return ;
	f->pwd = buf;
	tmp = f->envp_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			flago = 1;
			if (tmp->value)
				free(tmp->value);
			tmp->flag = 1;
			tmp->value = ft_strdup(buf);
			break ;
		}
		tmp = tmp->next;
	}
	if (flago == 0)
		pwd_is_not_there++;
	else
		pwd_is_not_there = 0;
	tmp = f->envp_list;
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
	if (pwd_is_not_there == 2)
		pwd_is_not_there = 0;
}

int	ft_cd(t_info *info, char **args, int i)
{
	(void)i;
	char	*str;
	char	*sub;
	char	*home = NULL;
	char	buf[1024];

	if (getcwd(buf, sizeof(buf)) == NULL)
		return 1;
	info->pwd = buf;
	str = NULL;
	sub = NULL;
	if (!(args[1]))
	{
		home = search_in_env(info, "HOME");
		if (home)
			str = ft_strdup(home);
		else
			return (handle_error(info, NULL, 0, 11), 1);
	}
	else if (args[1][0] == '~')
	{
		home = search_in_env(info, "HOME");
		if (home)
		{
			sub = ft_substr(args[i], 1, ft_strlen(args[i]) - 1);
			str = ft_strjoin(home, sub);
			free(sub);
		}
	}
	else
		str = args[1];
	if (chdir(str))
		return (handle_error(info, str, 0, 0), 1);
	return (change_pwd_in_env(info, buf), 0);
}

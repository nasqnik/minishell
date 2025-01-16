/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_pwd_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:06:41 by meid              #+#    #+#             */
/*   Updated: 2025/01/16 18:32:21 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_new_line(char **args, int *i, int *j, int *line_flag)
{
	while (args[(*i)] && args[(*i)][0] == '-' && args[(*i)][1] == 'n')
	{
		while (args[(*i)][(*j)] == 'n')
			(*j)++;
		if (args[(*i)][(*j)] == '\0')
		{
			(*line_flag) = 1;
			(*i)++;
		}
		else
			break ;
		if (args[(*i)] && ft_strcmp(args[(*i)], " ") == 0)
			(*i)++;
	}
}

int	ft_echo(char **args, int i)
{
	int	line_flag;
	int	fd;
	int	j;

	line_flag = 0;
	fd = 1;
	j = 2;
	check_new_line(args, &i, &j, &line_flag);
	if (args[i])
	{
		ft_putstr_fd(args[i], fd);
		i++;
	}
	while (args[i])
	{
		ft_putchar_fd(' ', fd);
		ft_putstr_fd(args[i], fd);
		i++;
	}
	if (line_flag == 0)
		ft_putstr_fd("\n", fd);
	return (0);
}

int	ft_pwd(void)
{
	int		fd;
	char	buf[1024];

	fd = 1;
	if (getcwd(buf, sizeof(buf)) == NULL)
		return (1);
	ft_putstr_fd(buf, fd);
	ft_putchar_fd('\n', fd);
	return (0);
}

int	ft_env(t_info *info, char **args, int i)
{
	int		fd;
	t_env	*tmp;

	if (args[i] != NULL)
		return (handle_error(info, args[i], 0, 0), 1);
	i = 0;
	fd = 1;
	tmp = info->envp_list;
	while (tmp)
	{
		if (tmp->env && tmp->flag == 1)
		{
			ft_putstr_fd(tmp->key, fd);
			ft_putchar_fd('=', fd);
			if (tmp->value)
				ft_putstr_fd(tmp->value, fd);
			ft_putchar_fd('\n', fd);
		}
		tmp = tmp->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_pwd_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:06:41 by meid              #+#    #+#             */
/*   Updated: 2025/01/29 20:23:23 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

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
	int	j;

	line_flag = 0;
	j = 2;
	check_new_line(args, &i, &j, &line_flag);
	if (args[i])
	{
		printf("%s", args[i]);
		i++;
	}
	while (args[i])
	{
		if (*args[i])
			printf(" ");
		printf("%s", args[i]);
		i++;
	}
	if (line_flag == 0)
		printf("\n");
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

static void	print_without_first_and_last(char *str)
{
	int	i;

	i = 1;
	while (str[i + 1] != '\0')
	{
		ft_putchar_fd(str[i], 1);
		i++;
	}
}

int	ft_env(t_info *info, char **args, int i)
{
	t_env	*tmp;

	if (args[i] != NULL)
		return (handle_error(info, args[i], 0, 0), 1);
	i = 0;
	tmp = info->envp_list;
	while (tmp)
	{
		if (tmp->env && tmp->flag == 1)
		{
			ft_putstr_fd(tmp->key, 1);
			ft_putchar_fd('=', 1);
			if (tmp->value)
				print_without_first_and_last(tmp->value);
			ft_putchar_fd('\n', 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

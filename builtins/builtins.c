/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:48:36 by meid              #+#    #+#             */
/*   Updated: 2025/01/13 20:00:35 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **args, int i)
{
	int	line_flag;
	int	fd;
	int j;

	line_flag = 0;
	fd = 1;
	j = 2;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		while(args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
		{
			line_flag = 1;
			i++;
		}
		else
			break ;
		if (args[i] && ft_strcmp(args[i], " ") == 0)
			i++;
	}
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

int	ft_cd(t_info *info, char **args, int i)
{
	(void)i;
	char	*str;
	char	*sub;
	char	*home = NULL;
	char	buf[1024];

	if (getcwd(buf, sizeof(buf)) == NULL) // for oldpwd
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
			str = ft_strjoin(home, sub); // allocated
			free(sub);
		}
	}
	else
		str = args[1];
	// i++;
	if (chdir(str))
		return (handle_error(info, str, 0, 0), 1);
	// if (args[i])
	// 	return (handle_error(info, args[i - 1], 0, 0), 1);
	return (change_pwd_in_env(info, buf), 0);
}

int	ft_env(t_info *info, char **args, int i)
{
	int		fd;
	t_env	*tmp;

	if (args[i] != NULL) // we should not handell more than env alone
		return (handle_error(info, args[i], 0, 0), 1);
	i = 0;
	fd = 1;
	// char	*find_path(char *command, t_info *info, flag);
	tmp = info->envp_list;
	while (tmp)
	{
		if (tmp->env && tmp->flag == 1)
		{
			
			// printf("            aysha flag = |%d|\n", tmp->flag);
			// printf("            aysha env = |%s|\n", tmp->env);
			// printf("            aysha key = |%s|\n", tmp->key);
			// printf("            aysha value = |%s|\n", tmp->value);
			// if (tmp->value != NULL)
			// {
				ft_putstr_fd(tmp->key, fd);
				ft_putchar_fd('=', fd);
				if (tmp->value)
					ft_putstr_fd(tmp->value, fd);
				ft_putchar_fd('\n', fd);	
			// }
				// printf("          comes here\n");
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_exit(t_info *info, char **args, int i, int j)
{
	int	fd;
	int	exit_code;

	fd = 1;
	exit_code = 0;
	ft_putstr_fd("exit\n", 1);
	while (args[i])
	{
		if (i > 1)
			return (print_the_error(info, NULL, 4, fd), 0);
		while (args[i][j])
		{
			if (!(args[i][j] >= '0' && args[i][j] <= '9'))
			{
				handle_error(info, args[i], 0, 5);
				free_and_set_null(info, 2);
				exit(255);
			}
			j++;
		}
		exit_code = ft_atoi(args[i]); // change it to make any number less than
		// 256 and if it is very long it should return an error 
		i++;
	}
	free_and_set_null(info, 2);
	exit(exit_code);
}

int	ft_pwd()
{
	int		fd;
	char	buf[1024];

	fd = 1;
	if (getcwd(buf, sizeof(buf)) == NULL)
		return (1); // dont know what to do here
	ft_putstr_fd(buf, fd);
	ft_putchar_fd('\n', fd);
	return (0);
}

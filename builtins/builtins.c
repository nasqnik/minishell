/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:48:36 by meid              #+#    #+#             */
/*   Updated: 2025/01/01 10:44:16 by meid             ###   ########.fr       */
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
	return (42);
}

int	ft_cd(t_info *info, char **args, int i)
{
	int		fd;
	char	*str;
	char	*sub;
	char	*home;

	fd = 1;
	str = NULL;
	sub = NULL;
	if (!(args[i]))
		return (0);
	if (args[i][0] == '~')
	{
		home = search_in_env(info, "HOME");
		sub = ft_substr(args[i], 1, ft_strlen(args[i]) - 1);
		str = ft_strjoin(home, sub); // allocated
		free(sub);
	}
	else
		str = args[i];
	i++;
	if (chdir(str))
		return (print_the_error(str, 0, fd), 0);
	// free(str); // <i should free but thisw make problems for a reason>
	if (args[i])
		return (print_the_error(args[i - 1], 1, fd), 0);
	return (change_pwd_in_env(info), 42);
}

int	ft_env(t_info *info, char **args, int i)
{
	int		fd;
	t_env	*tmp;

	if (args[i] != NULL) // we should not handell more than env alone
		return (0);
	i = 0;
	fd = 1;
	tmp = info->envp_list;
	while (tmp)
	{
		if (tmp->value[0] != '\0')
		{
			ft_putstr_fd(tmp->key, fd);
			ft_putchar_fd('=', fd);
			ft_putstr_fd(tmp->value, fd);
			ft_putchar_fd('\n', fd);	
		}
		// else
		// {
		// 	printf("i am here but not\n");
		// 	printf("%s\n", tmp->key);
		// }
		tmp = tmp->next;
	}
	return (42);
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
			return (print_the_error(NULL, 4, fd), 0);
		while (args[i][j])
		{
			if (!(args[i][j] >= '0' && args[i][j] <= '9'))
				return (print_the_error(args[1], 5, fd), 0);
			j++;
		}
		exit_code = ft_atoi(args[i]);
		i++;
	}
	ft_clear_tokens(&(info->token_list));
	ft_clear_tree(info->ast_tree);
	ft_clear_list(&(info->envp_list));
	close(info->stdout);
	close(info->stdin);
    free(info->buffer);
    info->buffer = NULL;
	exit(exit_code);
}

int	ft_pwd(char **args, int i)
{
	int		fd;
	char	buf[1024];

	if (args[i] != NULL) // we should not handell more than env alone
		return (0);
	i = 0;
	fd = 1;
	if (getcwd(buf, sizeof(buf)) == NULL)
		return (0);
	ft_putstr_fd(buf, fd);
	ft_putchar_fd('\n', fd);
	return (42);
}

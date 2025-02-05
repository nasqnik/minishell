/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:11:03 by meid              #+#    #+#             */
/*   Updated: 2025/02/05 18:20:02 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	handle_error(t_info *info, char *msg, int what_am_i, int flag)
{
	if (what_am_i == 0)
	{
		our_static("exit status", 1);
		print_the_error(info, msg, flag, 2);
	}
	else if (what_am_i == 1)
		perror("minicat");
	else if (what_am_i == 2)
	{
		our_static("exit status", 258);
		ft_putstr_fd("minicat: syntax error near unexpected token `", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\'\n", 2);
	}
}

void	print_after_arg(t_info *info, int flag, int fd)
{
	(void)info;
	if (flag == 2)
		ft_putstr_fd("\033[31m: ambiguous redirect\033[00m", fd);
	if (flag == 0 || flag == 10 || flag == 12)
		ft_putstr_fd("\033[31m: no such file or directory\033[00m", fd);
	if (flag == 3)
		ft_putstr_fd("\033[31m': not an identifier\033[00m", fd);
	if (flag == 5)
		ft_putstr_fd("\033[31m: numeric argument required\033[00m", fd);
	if (flag == 6)
		ft_putstr_fd("\033[31m: it's a directory\033[00m", fd);
	if (flag == 11)
		ft_putstr_fd("\033[31mHOME not set\033[00m", fd);
	if (flag == 13)
		ft_putstr_fd("\033[31m: Permission denied\033[00m", fd);
	if (flag == 14)
		ft_putstr_fd("\033[31m: command not found\033[00m", fd);
	if (flag == 15)
		ft_putstr_fd("\033[31m: invalid option\033[00m", fd);
	if (flag == 16)
		ft_putstr_fd("\033[31mOLDPWD not set\033[00m", fd);
	if (flag == 17)
		ft_putstr_fd("\033[31m: file argument required\033[00m", fd);
	if (flag != 100)
		ft_putchar_fd('\n', fd);
}

void	print_the_error(t_info *info, char *args, int flag, int fd)
{
	(void)info;
	ft_putstr_fd("\033[31mminicat: \033[00m", fd);
	if (flag == 0 || flag == 11 || flag == 15 || flag == 16)
		ft_putstr_fd("\033[31mcd: \033[00m", fd);
	if (flag == 10)
		ft_putstr_fd("\033[31menv: \033[00m", fd);
	if (flag == 1)
		ft_putstr_fd("\033[31mcd: string not in pwd: \033[00m", fd);
	if (flag == 3)
		ft_putstr_fd("\033[31mexport: `\033[00m", fd);
	if (flag == 4)
		ft_putstr_fd("\033[31mexit: too many arguments\033[00m", fd);
	if (flag == 5)
		ft_putstr_fd("\033[31mexit: \033[00m", fd);
	if (args)
		ft_putstr_fd(args, fd);
	print_after_arg(info, flag, fd);
}

void	safe_free(void **ptr)
{
	if (ptr && *ptr)
	{
		printf("free\n");
		free(*ptr);
		*ptr = NULL;
	}
}

void	bye_bey(t_info *info, char flag)
{
	handle_error(info, NULL, 1, 0);
	free_and_set_null(info, 2);
	if (flag == 'm')
		exit (12);
	exit (1);
}

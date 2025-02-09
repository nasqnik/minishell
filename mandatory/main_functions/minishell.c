/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:27:53 by meid              #+#    #+#             */
/*   Updated: 2025/02/05 16:37:20 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_3(t_info *info)
{
	info->stdout = dup(1);
	if (info->stdout == -1)
		perror("dup failed for stdout");
	info->stdin = dup(0);
	if (info->stdin == -1)
		perror("dup failed for stdin");
}

void	dup_and_close(t_info *info)
{
	if (info->stdout != -1 && dup2(info->stdout, 1) == -1)
	{
		perror("dup2 failed for stdout");
	}
	if (info->stdin != -1 && dup2(info->stdin, 0) == -1)
	{
		perror("dup2 failed for stdin");
	}
	if (info->stdout != -1)
	{
		close(info->stdout);
		info->stdout = -1;
	}
	if (info->stdin != -1)
	{
		close(info->stdin);
		info->stdin = -1;
	}
}

void	cntrl_d(t_info *info)
{
	write(2, "exit\n", 15);
	free_and_set_null(info, 2);
	exit(1);
}

int	buffer_is_big(char *str, t_env	*envp_list)
{
	t_env	*tmp;
	int		len;

	tmp = envp_list;
	len = 0;
	while (tmp)
	{
		len += ft_strlen(tmp->env) - 2;
		tmp = tmp->next;
	}
	len += ft_strlen(str);
	if (len > ARG_MAX)
	{
		printf("minishell: Argument list too long\n");
		return (1);
	}
	return (0);
}

void	minishell(t_info *info)
{
	while (1)
	{
		dup_3(info);
		castom_signals();
		free_and_set_null(info, 1);
		if (isatty(0))
			info->buffer = readline("mini_cat$ ");
		else
			info->buffer = readline("");
		if (!info->buffer || buffer_is_big(info->buffer, info->envp_list))
			cntrl_d(info);
		if (info->buffer)
		{
			add_history(info->buffer);
			if (parsing(info))
			{
				dup_and_close(info);
				continue ;
			}
			free(info->buffer);
			info->buffer = NULL;
			execution(info, info->ast_tree);
			dup_and_close(info);
		}
	}
}

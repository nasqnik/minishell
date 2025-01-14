/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:48:46 by meid              #+#    #+#             */
/*   Updated: 2025/01/14 12:07:26 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_and_set_null(t_info *info, int flag)
{
	if (info->token_list)
		ft_clear_tokens(&(info->token_list));
	if (info->ast_tree)
		ft_clear_tree(info->ast_tree);
	if (info->stdout)
		close(info->stdout);
	if (info->stdin)
		close(info->stdin);
	if (flag == 1)
	{
		info->stdout = dup(STDOUT_FILENO);
		info->stdin = dup(STDIN_FILENO);
	}
	else
	{
		if (info->envp_array)
			free_array(info->envp_array);
		if (info->envp_list)
			ft_clear_list(&(info->envp_list));
	}
	info->token_list = NULL;
	info->ast_tree = NULL;
}

int	ft_is(int c, char *str)
{
	if (ft_strcmp(str, "alnum") == 0)
	{
		return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A'
				&& c <= 'Z'));
	}
	else if (ft_strcmp(str, "space") == 0)
		return (c == 32 || (c >= 9 && c <= 13));
	else if (ft_strcmp(str, "quote") == 0)
		return (c == 39 || c == 34);
	else if (ft_strcmp(str, "op") == 0)
		return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
	else if (ft_strcmp(str, "operator") == 0)
		return (c == '|' || c == '>' || c == '<' || c == '&');
	else if (ft_strcmp(str, "brackets") == 0)
		return (c == '(' || c == ')');
	return (0);
}

int	our_static(char *str, int set)
{
	static int	exit_status;

	exit_status = 0;
	if (ft_strcmp(str, "exit status") == 0)
	{
		if (set != -1)
		{
			exit_status = set;
		}
		return (exit_status);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:48:46 by meid              #+#    #+#             */
/*   Updated: 2025/02/05 08:23:39 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	null_(t_info *info)
{
	info->token_list = NULL;
	info->ast_tree = NULL;
}

void	free_and_set_null(t_info *info, int flag)
{
	if (info->token_list)
		ft_clear_tokens(&(info->token_list));
	if (info->ast_tree)
		ft_clear_tree(info->ast_tree);
	if (info->subtree_lest)
		ft_clear_subtrees(&info->subtree_lest);
	if (flag != 1)
	{
		if (info->envp_array)
			free_array(info->envp_array);
		if (info->envp_list)
			ft_clear_list(&(info->envp_list));
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
	null_(info);
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

	if (ft_strcmp(str, "exit status") == 0)
	{
		if (set != -1)
			exit_status = set;
		return (exit_status);
	}
	return (0);
}

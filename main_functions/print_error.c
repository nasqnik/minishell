/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:11:03 by meid              #+#    #+#             */
/*   Updated: 2025/02/03 09:19:45 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

// const char	*token_type_to_string(t_token_type type)
// {
// 	switch (type) {
// 		case WORD: return ":WORD";
// 		case PIPE: return ":PIPE";
// 		case REDIRECT_IN: return ":REDIRECT_IN (<)";
// 		case REDIRECT_OUT: return ":REDIRECT_OUT (>)";
// 		case REDIRECT_APPEND: return ":REDIRECT_APPEND (>>)";
// 		case HEREDOC: return ":HEREDOC (<<)";
// 		case LOGIC_AND: return ":LOGIC_AND";
// 		case LOGIC_OR: return ":LOGIC_OR";
// 		case BRACKET: return ":BRACKET";
// 		case COMMAND: return ":COMMAND";
// 		case ARGUMENT: return ":ARGUMENT";
// 		case FILENAME: return ":FILENAME";
// 		case DELIMITER: return ":DELIMITER";
// 		default: return ":UNKNOWN TOKEN";
// 	}
// }

// void	print_list(t_tokens	*list)
// {
// 	t_tokens	*tmp;

// 	tmp = list;
// 	printf("the list\n");
// 	if (list)
// 	{
// 		while (tmp)
// 		{
// 			printf("data: |%s|\ttype: %s\n", tmp->data,
// 			token_type_to_string(tmp->type));
// 			tmp = tmp->next;
// 		}
// 	}
// }

// void	print_ast(t_tree *node, int depth, char *flag)
// {
// 	int i;
// 	i = 0;
// 	if (!node)
// 	{
// 		printf("there is no nodes\n");
// 		return ;
// 	}
// 	printf("\n");
// 	while (i < depth)
// 	{
// 		printf("  ");
// 		i++;
// 	}
// 	printf("\033[95mflag :%s \033[00m\n", flag);
// 	printf("\033[95m Node type: %s\033[00m\n",
// 			token_type_to_string(node->type));
// 	printf("\033[95m depth: %d\033[00m\n", depth);
// 	if (node->type == COMMAND)
// 	{
// 		char **str = node->args;
// 		int j = 0;
// 		if (str[j])
// 		{
// 			printf("command: %s\n", str[j]);
// 			j++;
// 		}
// 		while (str[j])
// 		{
// 			printf("arg: |%s|\n", str[j]);
// 			j++;
// 		}
// 	}
// 	if (node->type >= REDIRECT_IN && node->type <= HEREDOC)
// 		printf("file %s\n", node->file);
// 	if (node->type == BRACKET)
// 		printf("bracket %s\n", node->file);
// 	print_ast(node->left, depth + 1, "left");
// 	print_ast(node->right, depth + 1, "right");
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:11:03 by meid              #+#    #+#             */
/*   Updated: 2025/01/02 19:02:43 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// if what_am_i = 0 builtins   else if == 1 binary  else normail msg 
void	handle_error(t_info *info, char *msg, int what_am_i, int flag)
{
	// (void
	if (what_am_i == 0)
		print_the_error(info, msg, flag, 1);
	else if (what_am_i == 1)
		perror("minicat");
	else if (what_am_i == 2)
	{
		info->exit_status = 258;
		ft_putstr_fd("minicat: syntax error near unexpected token `", 1);
		ft_putstr_fd(msg, 1);
		ft_putstr_fd("\'\n", 1);
	}
	printf("our stativ in the handle error: %d\n", our_static(info, "exit status", info->exit_status));
	// if (info->token_list)
	// 	ft_clear_tokens(&(info->token_list));
	// if (info->ast_tree)
    //     ft_clear_tree(info->ast_tree);
	// if (info->envp_list)
	// 	ft_clear_list(&(info->envp_list));
	// if (info->buffer)
    //     free(info->buffer);
	// if (info->stdout)
	// 	close(info->stdout);
	// if (info->stdin)
	//     close(info->stdin);
	// info->token_list = NULL;
	// info->ast_tree = NULL;
	// info->envp_list = NULL;
	// info->stdout = dup(STDOUT_FILENO);
	// info->stdin = dup(STDIN_FILENO);
    // info->buffer = NULL;
	
}

void	print_the_error(t_info *info ,char *args, int flag, int fd)
{
	info->exit_status = 1;
	ft_putstr_fd("\033[31mminicat: \033[00m", fd);
	if (flag == 0)
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
	if (flag == 0 || flag == 10)
		ft_putstr_fd("\033[31m: no such file or directory\033[00m", fd);
	if (flag == 3)
		ft_putstr_fd("\033[31m': not an identifier\033[00m", fd);
	if (flag == 5)
		ft_putstr_fd("\033[31m: numeric argument required\033[00m", fd);
	if (flag != 100)
		ft_putchar_fd('\n', fd);
}

const char	*token_type_to_string(t_token_type type)
{
	switch (type) {
		case WORD: return ":WORD";
		case PIPE: return ":PIPE";
		case REDIRECT_IN: return ":REDIRECT_IN (<)";
		case REDIRECT_OUT: return ":REDIRECT_OUT (>)";
		case REDIRECT_APPEND: return ":REDIRECT_APPEND (>>)";
		case HEREDOC: return ":HEREDOC (<<)";
		case LOGIC_AND: return ":LOGIC_AND";
		case LOGIC_OR: return ":LOGIC_OR";
		case BRACKET: return ":BRACKET";
		case COMMAND: return ":COMMAND";
		case ARGUMENT: return ":ARGUMENT";
		case FILENAME: return ":FILENAME";
		case DELIMITER: return ":DELIMITER";
		default: return ":UNKNOWN TOKEN";
	}
}

// void	print_after_expansions(t_first *f)
// {
// 	t_tokens	*tmp;
// 	t_w_tmp		*tmp_data;

// 	tmp = f->token_list;
// 	tmp_data = NULL;
// 	printf("\nAFTER EXPANSIONS\n");
// 	while (tmp)
// 	{
// 		if (tmp->data_type == 's')
// 			printf("string :   #%s#  \n", (char *)tmp->data);
// 		if (tmp->data_type == 'l')
// 		{
// 			if (tmp->data != NULL)
// 			{
// 				tmp_data = (t_w_tmp *)tmp->data;
// 				while (tmp_data)
// 				{
// 					printf("list :   #%s#  ", tmp_data->data);
// 					tmp_data = tmp_data->next;
// 				}
// 			}
// 		}
// 		printf("	  type: %s\n", token_type_to_string(tmp->type));
// 		tmp = tmp->next;
// 	}
// }

void	print_list(t_tokens	*list)
{
	t_tokens	*tmp;

	tmp = list;
	printf("the list\n");
	if (list)
	{
		while (tmp)
		{
			printf("data: |%s|\ttype: %s\n", tmp->data, token_type_to_string(tmp->type));
			tmp = tmp->next;
		}
	}
}

// void	print_env(t_first *f, int flag)
// {
// 	t_list	*tmp;
// 	int		i;

// 	tmp = f->envp_list;
// 	i = 0;
// 	while (tmp)
// 	{
// 		if (flag == 0)
// 			printf("%s\n", f->envp_array[i]);
// 		else
// 		{
// 			printf("key: %s\n", tmp->key);
// 			printf("value: %s\n", tmp->value);
// 		}
// 		tmp = tmp->next;
// 		i++;
// 	}
// }



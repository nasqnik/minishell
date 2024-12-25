/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:11:03 by meid              #+#    #+#             */
/*   Updated: 2024/12/25 17:59:42 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_error(t_info *info, char *msg, int flag)
{
	printf("\033[31m %s\033[00m\n", msg);
	if (flag <= 1)
	{
		ft_clear_tokens(&(info->token_list));
		ft_clear_list(&(info->envp_list));
		// info->error_flag = 1;
		// free(f->buffer);
		//f->buffer = NULL;
	}
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

// void	print_the_error(char *args, int flag, int fd)
// {
// 	if (flag == 0)
// 		ft_putstr_fd("\033[31mcd: no such file or directory: \033[00m", fd);
// 	if (flag == 1)
// 		ft_putstr_fd("\033[31mcd: string not in pwd: \033[00m", fd);
// 	if (flag == 2)
// 		ft_putstr_fd("\033[31mzsh: no matches found: \033[00m", fd);
// 	if (flag == 3)
// 		ft_putstr_fd("\033[31mexport: \033[00m", fd);
// 	if (flag == 4)
// 		ft_putstr_fd("\033[31mminishell: exit: too many arguments\033[00m", fd);
// 	if (flag == 5)
// 		ft_putstr_fd("\033[31mminishell: exit: \033[00m", fd);
// 	if (args)
// 		ft_putstr_fd(args, fd);
// 	if (flag == 3)
// 		ft_putstr_fd("\033[31not an identifier: \033[00m", fd);
// 	if (flag == 5)
// 		ft_putstr_fd("\033[31m: numeric argument required\033[00m", fd);
// 	ft_putchar_fd('\n', fd);
// }

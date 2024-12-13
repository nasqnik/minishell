/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:11:03 by meid              #+#    #+#             */
/*   Updated: 2024/12/13 16:50:54 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(t_first *f, char *msg, int flag)
{
	printf("\033[31m %s\033[00m\n", msg);
	if (flag <= 1)
	{
		ft_clear_tokens(&(f->token_list));
		ft_clear_list(&(f->envp_list));
		free(f->buffer);
		f->buffer = NULL;
		f->error_flag = 1;
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
		case ENV_VAR: return ":ENV_VAR";
		case WSPACE: return ":SPACE";
		case D_QUOTES: return ":D_QUOTES";
		case S_QUOTES: return ":S_QUOTES";
		case LOGIC_AND: return ":LOGIC_AND";
		case LOGIC_OR: return ":LOGIC_OR";
		case BRACKET: return ":BRACKET";
		case COMMAND: return ":COMMAND";
		case FLAG: return ":FLAG";
		case ARGUMENT: return ":ARGUMENT";
		case FILENAME: return ":FILENAME";
		case DELIMITER: return ":DELIMITER";
		default: return ":UNKNOWN TOKEN";
	}
}

void	print_after_expansions(t_first *f)
{
	t_tokens	*tmp;
	t_w_tmp		*tmp_data;

	tmp = f->token_list;
	tmp_data = NULL;
	printf("\nAFTER EXPANSIONS\n");
	while (tmp)
	{
		if (tmp->data_type == 's')
			printf("string :   #%s#  \n", (char *)tmp->data);
		if (tmp->data_type == 'l')
		{
			if (tmp->data != NULL)
			{
				tmp_data = (t_w_tmp *)tmp->data;
				while (tmp_data)
				{
					printf("list :   #%s#  ", tmp_data->data);
					tmp_data = tmp_data->next;
				}
			}
		}
		printf("	  type: %s\n", token_type_to_string(tmp->type));
		tmp = tmp->next;
	}
}

void	print_list(t_tokens	*list)
{
	t_tokens	*tmp;

	tmp = list;
	printf("the list\n");
	if (list)
	{
		while (tmp)
		{
			printf("s: %s\n", (char *)tmp->data);
			tmp = tmp->next;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:11:03 by meid              #+#    #+#             */
/*   Updated: 2024/12/10 14:24:59 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_error(t_first *f, char *msg, int flag)
{
    printf("\033[31m %s\033[00m\n", msg);
    if (flag <= 1)
    {
        ft_clear_tokens(&(f->token_list));
        free(f->buffer);
        f->buffer = NULL;
        f->error_flag = 1; 
    }
}

const char *token_type_to_string(t_token_type type) {
    switch (type) {
        case WORD: return "WORD";
        case PIPE: return "PIPE";
        case REDIRECT_IN: return "REDIRECT_IN (<)";
        case REDIRECT_OUT: return "REDIRECT_OUT (>)";
        case REDIRECT_APPEND: return "REDIRECT_APPEND (>>)";
        case HEREDOC: return "HEREDOC (<<)";
        case ENV_VAR: return "ENV_VAR";
        case WSPACE: return "SPACE";
        case D_QUOTES: return "D_QUOTES";
        case S_QUOTES: return "S_QUOTES";
        case LOGIC_AND: return "LOGIC_AND";
        case LOGIC_OR: return "LOGIC_OR";
        case BRACKET: return "BRACKET";
        default: return "UNKNOWN TOKEN";
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:11:03 by meid              #+#    #+#             */
/*   Updated: 2024/12/06 14:59:04 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_error(t_first *f, char *msg, int flag)
{
    (void)f;
    printf("\033[31m %s\033[00m\n", msg);
    if (flag == 1)
        printf("\033[31mfree list\033[00m\n");
    // i think we should use a signal here
    return ;
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
        case SPACE: return "SPACE";
        case D_QUOTES: return "D_QUOTES";
        case S_QUOTES: return "S_QUOTES";
        case LOGIC_AND: return "LOGIC_AND";
        case LOGIC_OR: return "LOGIC_OR";
        case BRACKET: return "BRACKET";
        case EQUATION: return "EQUATION";
        case SUBSHELL: return "SUBSHELL";
        default: return "UNKNOWN TOKEN";
    }
}

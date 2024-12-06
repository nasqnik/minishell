/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:05:51 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/06 16:08:05 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_brackets(char *str, t_first *f)
{
    int close = 0;
    int brackets_num = 0;
    if (str[f->i] == '(')
    {
        while (str[f->i] == '(')
        {
            brackets_num++;
            f->i++;
        }
        while (str[f->i] && str[f->i] != ')' 
            && ((brackets_num > 1 && (ft_isdigit(str[f->i]) == 1 
            || ft_isop(str[f->i]) == 1 || ft_isspace(str[f->i]) == 1)) || (brackets_num == 1)))
            f->i++;
        while (str[f->i] && str[f->i] == ')')
        {
            f->i++;
            close++;
        }
        if (close != brackets_num)
            handle_error(f, "<<<close (( with ))>>>", 1);
    }
    return (brackets_num);
}

int check_operator_type(int flag, char cur)
{
    if (flag == 'o')
    {
        if (cur == '|')
            return PIPE;
        else if (cur == '>')
            return REDIRECT_OUT;
        else if (cur == '<')
            return REDIRECT_IN;
    }
    else
    {
        if (cur == '&')
            return LOGIC_AND;
        else if (cur == '|')
            return LOGIC_OR;
        else if (cur ==  '>')
            return REDIRECT_APPEND;
        else if (cur == '<')
            return HEREDOC;
    }
    return 0;
}
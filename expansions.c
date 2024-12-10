/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:16:00 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/10 15:48:41 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void expand_envp(t_tokens *token, t_first *f)
{
    // int i;
    char *env_value;
    char *new_token_data;
    
    // i = 0;
    // if (token->data[i] == '?' && ft_strlen(token->data) == 1) // add $?
        
    // else
    env_value = search_in_env(f, token->data);
    if (env_value)
    {
        new_token_data = ft_substr(env_value, 0, ft_strlen(env_value)); // ft_strdup?
        free(token->data);
        token->data = new_token_data;
        return ;
    }
    
}


// void expand_d_quotes(t_tokens *token, t_first *f)
// {
//     char *data;
//     char *result;
//     char *before_var;
//     char *tmp2;
//     char *tmp3;
//     t_list *list_cursor;
//     char *var_name;
    
//     int i;
//     int start;
//     int var_start;
    
//     char *var_value;

//     data = token->data;
//     result = ft_strdup("");
//     i = 0;
//     start = 0;

//     while (data[i])
//     {
//         if (data[i] == '$')
//         {
//             before_var = ft_substr(data, start, i);
//             i++;

//             var_start = i;
//             while (data[i] && ft_isalnum(data[i]))
//                 i++;
//             if (i > var_start)
//                 var_name = ft_substr(data, var_start, i);
            
//             list_cursor = f->envp_list;
            
//             while (list_cursor)
//             {
//                 if (!ft_strncmp(var_name, list_cursor->key, ft_strlen(var_name)))
//                 {
//                     var_value = list_cursor->value;
//                     break ;
//                 }
//                 list_cursor = list_cursor->next;
//             }
    
//         }
//         i++;
//     }
// }
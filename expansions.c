/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:16:00 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/13 17:14:39 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void expand_envp(t_tokens *token, t_first *f)
{
    char *env_value;
    char *new_token_data;
    
    env_value = NULL;
    new_token_data = NULL;
    if (ft_strlen(token->data) == 1)
    {
        if (((char *)(token->data))[0] == '?') 
            new_token_data = ft_itoa(f->exit_status);  
        else if (((char *)(token->data))[0] == '_') //print the last argument to the last command
            new_token_data = ft_strdup(f->last_arg);
    }
    else 
    {
        env_value = search_in_env(f, token->data);
        if (env_value)
            new_token_data = ft_strdup(env_value);
    }
    if (new_token_data)
    {
        free(token->data);
        token->data = new_token_data;
    }
}


void expand_d_quotes(t_tokens *token, t_first *f)
{
    char *data;
    char *result;
    int i;
    int start;
    
    result = ft_strdup("");
    data = token->data;
    i = 0;
    start = 0;
    while (data[i])
    {
        if (data[i] == '$')
        {
            result = handle_variable(data, &i, result, f->envp_list);
            start = i;
        }
        else
            i++;
    }
    if (start < i)
        result = append_remaining_data(data, start, i, result);
    free(token->data);
    token->data = result;
}

// void expand_d_quotes(t_tokens *token, t_first *f)
// {
//     char *data;
//     char *result;
//     char *before_var;
//     char *tmp;
//     char *tmp2;
//     t_list *list_cursor;
//     int i;
//     int start;
//     int var_start;
//     char *var_name;
//     char *var_value;

//     data = token->data;
//     result = ft_strdup("");
//     i = 0;
//     start = 0;

//     while (data[i])
//     {
//         if (data[i] == '$')
//         {
//             // Get the part before the variable
//             before_var = ft_substr(data, start, i - start);

//             // Check if there's a character after '$'
//             if (data[i + 1])
//                 i++;

//             // Start of the variable name
//             var_start = i;

//             // Traverse the variable name
//             while (data[i] && (ft_is(data[i], "alnum") || data[i] == '_'))
//                 i++;

//             // Check if a valid variable name exists
//             if (i > var_start)
//             {
//                 var_name = ft_substr(data, var_start, i - var_start);
//                 var_value = NULL;

//                 // Search for the variable in the environment list
//                 list_cursor = f->envp_list;
//                 while (list_cursor)
//                 {
//                     if (!ft_strncmp(var_name, list_cursor->key, ft_strlen(var_name)) &&
//                         ft_strlen(var_name) == ft_strlen(list_cursor->key))
//                     {
//                         var_value = ft_strdup(list_cursor->value);
//                         break;
//                     }
//                     list_cursor = list_cursor->next;
//                 }
//                 free(var_name);

//                 // Use an empty string if the variable is not found
//                 if (!var_value)
//                     var_value = ft_strdup("");
//             }
//             else // No valid variable name, treat as literal '$'
//             {
//                 var_value = ft_strdup("$");
//             }

//             // Concatenate result with the part before the variable and the variable value
//             tmp = ft_strjoin(result, before_var);
//             free(result);
//             result = ft_strjoin(tmp, var_value);
//             free(tmp);
//             free(before_var);
//             free(var_value);

//             // Update the start position
//             start = i;
//         }
//         else
//         {
//             i++;
//         }
//     }

//     // Append any remaining part of the string
//     if (start < i)
//     {
//         tmp = ft_substr(data, start, i - start);
//         tmp2 = ft_strjoin(result, tmp);
//         free(result);
//         result = tmp2;
//         free(tmp);
//     }

//     // Replace the old data with the new expanded string
//     free(token->data);
//     token->data = result;
// }

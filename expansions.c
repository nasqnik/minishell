/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:16:00 by anikitin          #+#    #+#             */
/*   Updated: 2024/12/10 17:49:37 by anikitin         ###   ########.fr       */
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
        if (token->data[0] == '?') 
            new_token_data = ft_itoa(f->exit_status);  
        else if (token->data[0] == '_') //print the last argument to the last command
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
    
    char *before_var;
    char *tmp;
    char *tmp2;

    t_list *list_cursor;
    
    int i;
    int start;
    
    int var_start;
    char *var_name;
    char *var_value;

    data = token->data;
    result = ft_strdup("");
    i = 0;
    start = 0;

    while (data[i])
    {
        if (data[i] == '$')
        {
            before_var = ft_substr(data, start, i - start);
            i++;

            var_start = i;
            while (data[i] && (ft_isalnum(data[i]) || data[i] == '_'))
                i++;
            if (i > var_start)
            {
                var_name = ft_substr(data, var_start, i - var_start);
                var_value = NULL;
                
                list_cursor = f->envp_list;
            
                while (list_cursor)
                {
                    if (!ft_strncmp(var_name, list_cursor->key, ft_strlen(var_name)))
                    {
                        var_value = ft_strdup(list_cursor->value);
                        break ;
                    }
                    list_cursor = list_cursor->next;
                }
                free(var_name);
                if (!var_value)
                    var_value = ft_strdup("");
            }
            else
                var_value = ft_strdup("$");
            tmp = ft_strjoin(result, before_var);
            free(result);
            result = ft_strjoin(tmp, var_value);
            free(tmp);
            free(before_var);
            free(var_value);

            start = i;
        }
        i++;
    }
    if (start < i)
    {
        tmp = ft_substr(data, start, i - start);
        tmp2 = ft_strjoin(result, tmp);
        free(result);
        result = tmp2;
        free(tmp);
    }
    free(token->data);
    token->data = result;
}
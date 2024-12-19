/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:07:24 by meid              #+#    #+#             */
/*   Updated: 2024/12/19 16:41:33 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int invalid_identifier(char *str, int flag)
{
    int i = 0;
    
    if (str[i] >= '0' && str[i] <= '9')
        return (1);
    while (str[i])
    { 
        if ((!(ft_isalnum(str[i])) && str[i] != '_' && str[i] != '=')
            || (str[i] == '=' && flag == 2))
            return (2);
        i++; 
    }
    return (0);
}



// 1. Starts with a Number
// 1VAR
// 123ABC
// 5_variable
// 2. Contains Special Characters
// VAR-NAME (Hyphen -)
// VAR@NAME (At symbol @)
// VAR#NAME (Hash #)
// VAR.NAME (Dot .)
// VAR+NAME (Plus +)
// 3. Starts with a Special Character
// -VAR (Hyphen -)
// @NAME (At symbol @)
// #COMMENT (Hash #)
// 4. Contains Spaces
// MY VAR (Space in the name)
// VAR (Leading space)
// VAR (Trailing space)
// 5. Starts with a Non-Alphabetic Symbol
// !VAR (Exclamation mark !)
// *VAR (Asterisk *)
// ?VAR (Question mark ?)
// 6. Empty or Missing Variable Name
// export =value (No name, just a value)
// 7. Uses Reserved Words or Syntax
// if (Keyword in Bash)
// for (Keyword in Bash)
// case (Keyword in Bash)
// Correct Identifier Rules Recap:
// Must start with a letter or an underscore (_).
// Can only contain letters, numbers, and underscores.
// Must not contain spaces or special characters.
// Let me know if you need more examples or further clarifications!
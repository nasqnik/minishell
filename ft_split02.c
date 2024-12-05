/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 07:57:35 by meid              #+#    #+#             */
/*   Updated: 2024/12/04 09:08:08 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"

int ft_part_num(char *str, char main_separator, char *first_sub, char *last_sub) {
    int count = 0, in_part = 0, i = 0;
    while (str[i])
    {
        if (first_sub && str[i] == first_sub[0])
        {
            count++;
            i++;
            while (str[i] && str[i] != last_sub[0])
                i++; 
            if (str[i] == last_sub[0] && str[i + 1] == last_sub[1])
                i += 2;
        }
        else if (str[i] == main_separator)
        {
            in_part = 0;
            i++;
        }
        else
        {
            if (in_part == 0)
            {
                count++;
                in_part = 1;
            }
            i++;
        }
    }
    return count;
}

char **ft_split2(char *str, char main_separator, char *first_sub, char *last_sub)
{
    int part_num = ft_part_num(str, main_separator, first_sub, last_sub);
    printf("%d\n", part_num);
    return (NULL);
}

int main(void)
{
    char *str = "mariam ew $(( 4546   )) ewoiu rg $())";
    char **res = ft_split2(str, 32, "$((", "))");
    // int i = 0;
    // while (res[i])
    // {
    //     printf("string[%d]: %s", i, res[i]);
    //     i++;
    // }
}
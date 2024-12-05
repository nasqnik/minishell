/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issomething2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:34:36 by meid              #+#    #+#             */
/*   Updated: 2024/12/05 21:51:14 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	while ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isascii(int c)
{
	while (c >= 0 && c <= 127)
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	while (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isprint(int c)
{
	while (c >= 32 && c <= 126)
		return (1);
	return (0);
}

int ft_isspace(int c)
{
	if (c == 32)
		return (1);
	return (0);
}

int ft_isquote(int c)
{
	if (c == 39 || c == 34 || c == 40)
		return (1);
	return (0);
}
int ft_close(int c)
{
	if (c == 40)
		return (41);
	else
		return (c);
}

int ft_isop(int c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
		return (1);
	return (0);
}

int ft_isoperator(int c)
{
	if(c == '|' || c == '>' || c == '<' || c == '&')
		return (1);
	return (0);
}
int ft_is_open_parenthesis(int c)
{
	if (c == 39)
		return (39);
	if (c == 34)
		return (34);
	if (c == 40)
		return (40);
	return (0);
}

int ft_is_close_parenthesis(int c,int c2)
{
 	if (c == 39)
	{
		if (c2 == 39)
			return (1);
	}
	if (c == 34)
	{
		if (c2 == 34)
			return (1);
	}
	if (c == 40)
	{
		if (c2 == 41)
			return (1);
	}
	return (0);
}


// void tokens(char *str)
// {
//     int i;
//     i = 0;
//     int len;
//     char flag = 'n';
    
//     while (str[i])
//     {   
//         len = i;
//         if (ft_isalnum(str[i]) == 1)
//         {
// 			flag = 'n';

//             while (str[i] && ft_isspace(str[i]) == 0)
//                 i++;
//         }
//         else if (str[i] && ft_isspace(str[i]) == 1)
//         {
//             flag = 's'; 
//             while (str[i] && ft_isspace(str[i]) == 1)
//                 i++;
//         }
        
//     if (flag == 's')
//         len = 1;
//     else
//         len = i - len;
//     }
// }

// int main(void)
// {
//     tokens("echo lol pov");
// }

// 39  '
// 34  "
// 40  (

// open parenthesis or simply left parenthesis.

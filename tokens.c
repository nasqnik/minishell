/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:33:53 by meid              #+#    #+#             */
/*   Updated: 2024/12/05 22:32:32 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// void tokens(t_first *f, char *str)
// {
//     f->i = 0;
//     int len;
//     char flag = 'n';
    
//     while (str[f->i])
//     {   
//         len = f->i;
//         if (ft_isalnum(str[f->i]) == 1)
//         {
// 			flag = 'n';

//             while (str[f->i] && ft_isspace(str[f->i]) == 0)
//                 f->i++;
//         }
//         else if (str[f->i] && ft_isspace(str[f->i]) == 1)
//         {
//             flag = 's'; 
//             while (str[f->i] && ft_isspace(str[f->i]) == 1)
//                 f->i++;
//         }
//         if (flag == 's')
//             len = 1;
//         else
//             len = f->i - len;
        
//     }
// }
// m a r i a m         a   n  a \0
// 0 1 2 3 4 5 6 7 8 9 10 11 12  13


t_tokens *ft_lstlastt(t_tokens *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_tokens *ft_create_token(t_first *f, int len, int flag, char *str)
{
    t_tokens *new;
    
    new = malloc(sizeof(t_tokens));
    if (new)
    {
        if (flag != 's')
            new->data = ft_substr(str, f->i - len, len);
        else
        {
            new->data = malloc(2);
            new->data = " \0";
        }
        new->len = len;
        new->type = flag;
        new->next = NULL;
    }
    return (new);
}

void	add_back_token(t_tokens **lst, t_tokens *new)
{
    static int i = 1;
	t_tokens	*last;

    if (*lst == NULL)
    {
        *lst = new;
        return ;
    }
	last = ft_lstlastt(*lst);
    i++;
	last->next = new;
}


t_tokens *operators_token(char *str, t_first *f , int len)  // handel ||   |   &&   >> << > <
{
    char flag = 'o';
    char cur = str[f->i];
    
    f->i++;
    if (str[f->i] == cur)
    {
        f->i++;
        flag = 'O';
    }
    if (cur == '&' && flag != 'O') //    \ (backslash) not required so we will not handel echo \&
        handle_error(f, "you cant use one &", 1);
    len = f->i - len;
    return (ft_create_token(f, len, flag, str));
}

t_tokens *dollar_token(char *str, t_first *f , int len)  // this can be shorter <now i am lazy to think>
{
    char flag;
    f->i++;
    flag = 'E'; // expansion
    if (str[f->i] == ' ')
        return (ft_create_token(f, f->i - len, 's', str));
    if (str[f->i] == '(')
    {
        f->i++;
        flag = 'e';// expansion but with ()
        if (str[f->i] == '(')
            flag = 'u'; // equation
    }
    if (flag == 'u')
    {
        while (str[f->i] && (ft_isdigit(str[f->i]) == 1 || str[f->i] == 32 || ft_isop(str[f->i]) == 1))
            f->i++;
        if (str[f->i] != ')' && str[++f->i] != ')')
            handle_error(f, "<<<close (( with ))>>>", 1);
        f->i += 2;
    }
    else
    {
        while (str[f->i] && ((str[f->i] != ')' && flag == 'e') || (str[f->i] != ' ' && flag == 'E')))
            f->i++;
        if (str[f->i] != ')' && flag == 'e')
            handle_error(f, "<<<close (( with ))>>>", 1);
        if (flag == 'e')
            f->i++;
    }
    len = f->i - len;
    return (ft_create_token(f, len, flag, str));
}
    

t_tokens *quote_token(char *str, t_first *f , int len)
{
    char close = ft_close(str[f->i]);
    f->i++;
    while (str[f->i] && str[f->i] != close)
        f->i++;
    if (str[f->i] && str[f->i] == close)
        f->i++;
    else
        handle_error(f, "you did not close like this "" | '' | ()", 1);
    len = f->i - len;
    return (ft_create_token(f, len, 'q', str)); 
}

t_tokens *alnum_token(char *str, t_first *f , int len)
{
    while (str[f->i] && ft_isspace(str[f->i]) == 0)
        f->i++;
    len = f->i - len;
    return (ft_create_token(f, len, 'n', str)); 
}

t_tokens *delimiter_token(char *str, t_first *f)
{
    while (str[f->i] && ft_isspace(str[f->i]) == 1)
        f->i++;
    return (ft_create_token(f, 1, 's', str));
}
void tokens(t_first *f, char *str)
{
    t_tokens *current_token;
    f->i = 0;
    int len;
    f->token_list = NULL;
    
    while (str[f->i])
    {   
        len = f->i;
        if (str[f->i] == '$')                                // handel $      $()     $(())    //  handel $(())  not handled $(((())))
            current_token = dollar_token(str, f, len);
        else if (ft_isquote(str[f->i]) == 1)                 // handel () "" ''   // handel ("") // not handled (())
            current_token = quote_token(str, f, len); 
        else if (ft_isoperator(str[f->i]) == 1) // handel ||   |   &&   >> << > <
            current_token = operators_token(str, f, len);
        else if (ft_isalnum(str[f->i]) == 1)
            current_token = alnum_token(str, f, len);
        else if (ft_isspace(str[f->i]) == 1)
            current_token = delimiter_token(str, f);
        else
        {
            printf("what did you give : |%c|?\n", str[f->i]);
        }
        printf("string #%s#  len #%d#   flag #%c#\n", current_token->data, current_token->len, current_token->type);
        add_back_token(&f->token_list, current_token);
    }
    printf("the list\n");
    t_tokens *tmp = f->token_list;
    while(tmp)
    {
        printf("s: %s\n", tmp->data);
        tmp = tmp->next;
    }
} // echo $_ handel this later

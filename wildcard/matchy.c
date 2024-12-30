/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matchy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:11:54 by meid              #+#    #+#             */
/*   Updated: 2024/12/30 11:57:01 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_check_rest(char *file, char *wildcard, int *wc, int *i)
{
    int tmp;
    char close;
    int flag = 1;

    tmp = (*wc);
    while (wildcard[tmp] != '*')
    {
        if ((flag == 1 && (wildcard[tmp] == '\'' || wildcard[tmp] == '\"'))
            || (flag == 2 && wildcard[tmp] == close))
        {
            if (flag == 1)
            {
                close = wildcard[tmp];
                tmp++;
                flag = 2;
            }
            else
            {
                close = '\0';
                tmp++;
                flag = 1;
            }
        }
        else
        {
            if (file[(*i)] && wildcard[tmp] != file[(*i)])
                break ;
            if (file[(*i)] == '\0' || wildcard[tmp] == '\0')
                break ;
            if (file[(*i)] && wildcard[tmp] == file[(*i)])
            {
                tmp++;
                (*i)++;
            }
        }
    }
    if (wildcard[tmp] != '*')
    {
        (*wc)--;
        return ;
    }
    (*wc) = tmp;
}

int ft_mid_with(char *file, char *wildcard, int wc)
{
    int i = 0;
    int tmp = 0;
    if (file[i])
    {
        while (wildcard[wc] == '*')
        {
            wc++;
            if (!wildcard[wc])
                break ;
            while (file[i])
            {
                if (wildcard[wc] && wildcard[wc] == file[i])
                {
                    ft_check_rest(file, wildcard, &wc, &i);
                    break ;
                }
                else if (wildcard[wc] == '\'' || wildcard[wc] == '\"')
                {
                    tmp = wc + 1;
                    if (wildcard[tmp] && wildcard[tmp] == file[i])
                    {   
                        ft_check_rest(file, wildcard, &wc, &i);
                        break ;
                    }
                    else
                        i++;
                }
                else
                    i++;
            }
        }
    }
    if (wildcard[wc] == '\0')
        return (1);
    return (0);
}

int	ft_strat_with(char *str, char *start)
{
	int	start_len;

	start_len = ft_strlen(start);
	if (ft_strncmp(str, start, start_len) == 0)
		return (1);
	return (0);
}

int	ft_end_with(char *str, char *end)
{
	if (ft_strcmp_end(str, end) == 1)
		return (1);
	return (0);
}

char *start_sub(char *wildcard, int *i, int *j)
{
    int count;
    char close;
    char *str;
    
    count = 0;
    (*i) = 0;
    while (wildcard[(*i)] && wildcard[(*i)] != '*')
    {
        if (wildcard[(*i)] == '\'' || wildcard[(*i)] == '\"')
        {
            close = wildcard[(*i)++];
            while (wildcard[(*i)] && wildcard[(*i)] != close)
            {
                count++;
                (*i)++;
            }
            (*i)++;
        }
        else
        {
            count++;
            (*i)++;
        }
    }
    str = malloc(sizeof(char) * (count + 1));
    if (!str)
        return (NULL);
    (*i) = 0;
    while (wildcard[(*i)] && wildcard[(*i)] != '*')
    {
        if (wildcard[(*i)] == '\'' || wildcard[(*i)] == '\"')
        {
            close = wildcard[(*i)++];
            while (wildcard[(*i)] && wildcard[(*i)] != close)
                str[(*j)++] = wildcard[(*i)++];
            (*i)++;
        }
        else
        {
            str[(*j)++] = wildcard[(*i)++];
        }
    }
    str[(*j)] = '\0';
    return (str);
}

char *end_sub(char *wildcard, int *i, int *j)
{
    int count;
    char open;
    char *str;
    
    count = 0;
    (*i) = ft_strlen(wildcard) - 1;
    while ((*i) >= 0 && wildcard[(*i)] != '*')
    {
        if (wildcard[(*i)] == '\'' || wildcard[(*i)] == '\"')
        {
            open = wildcard[(*i)--];
            while ((*i) >= 0  && wildcard[(*i)] != open)
            {
                count++;
                (*i)--;
            }
            (*i)--;
        }
        else
        {
            count++;
            (*i)--;
        }
    }
    (*j) = count - 1;
    str = malloc(sizeof(char) * (count + 1));
    if (!str)
        return (NULL);
    (*i) = ft_strlen(wildcard) - 1;
    while ((*i) >= 0 && wildcard[(*i)] != '*')
    {
        if (wildcard[(*i)] == '\'' || wildcard[(*i)] == '\"')
        {
            open = wildcard[(*i)--];
            while ((*i) >= 0 && wildcard[(*i)] != open)
                str[(*j)--] = wildcard[(*i)--];
            (*i)--;
        }
        else
        {
            str[(*j)--] = wildcard[(*i)--];
        }
    }
    (*j) = count;
    // printf("%d\n", *j);
    // printf("%c\n", str[(*j)]);
    str[count] = '\0';
    return (str);
}

int	ft_matchy(char *file, char *wildcard, int wildcard_count)
{
	int		i;
	int		j;
	int		start;
	int 	start_f;
	int		end;
	int		end_f = 0;
	char	*tmp_file;
	char *sub_str = NULL;
	(void)wildcard_count;
	if (!file || !wildcard)
		return (0);
    printf("the file: %s\n", file);
	(void)file;
	i = 0;
	start = 0;
	j = 0;
	sub_str = start_sub(wildcard, &i, &j); // 12''"23"'4'5*678 => res : 122345 // so it delets any " ' and <i> is the pos of the first and <j> is the len of the sub str
	if (ft_strat_with(file, sub_str) == 0)
	{
		printf("the problem in the start\n");
		return (0);
	}
	start = i; // start of wildcard
	start_f = j; // start of the file
	free(sub_str);
	sub_str = end_sub(wildcard ,&i, &j);
	end = i;
    end_f = ft_strlen(file) - j - 1;
	if (ft_end_with(file, sub_str) == 0)
	{
		printf("the problem at the end\n");
		return (0);
	}
	free(sub_str);
	sub_str = ft_substr(wildcard, start, end - start + 1);
	tmp_file = ft_substr(file, start_f, end_f - start_f + 1);
	if (tmp_file && who_many_wildcard(sub_str) >= 2)
	{
		if (sub_str)
		{
			if (ft_mid_with(tmp_file, sub_str, 0) == 0)
				return (0);
		}
	}
	free(sub_str);
	free(tmp_file);
	return (1);
}
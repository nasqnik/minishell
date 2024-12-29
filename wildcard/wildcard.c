/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:37:44 by meid              #+#    #+#             */
/*   Updated: 2024/12/29 14:01:39 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_check_rest(char *file, char *wildcard, int *wc, int *i)
{
    int tmp;
    char close;
    int flag = 1;

    tmp = (*wc);
    // tmp++;
    // (*i)++;
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

// int	ft_mid_with(char *file, char *wildcard, int start, int end)
// {
// 	int	i;
// 	char close;

// 	i = 0;
// 	while (file[i])
// 	{
// 		if (wildcard[start] == '*')
// 		{
// 			start++;
// 			if (start == end)
// 				break ;
// 			while (wildcard[start] != '*')
// 			{
// 				if (file[i] == '\0' || wildcard[start] == '\0')
// 					break ;
// 				if (file[i])
// 				{
// 					if (file[i] == '\'' || file[i] == '\"')
// 					{
						
// 					}
// 				if (file[i] && wildcard[start] == file[i])
// 					start++;
// 				}
// 				if (start == end)
// 					break ;
// 				i++;
// 			}
// 		}
// 		else
// 			i++;
// 	}
// 	if (wildcard[start] == '\0')
// 		return (1);
// 	return (0);
// }


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
	printf("\n count : %d\n", count);
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
	int		end_f;
	char	*tmp_file;
	char *sub_str = NULL;
	(void)wildcard_count;
	printf("\n---------------------------------\n");
	printf("the file: %s\n", file);
	if (!file || !wildcard)
		return (0);
	(void)file;
	i = 0;
	start = 0;
	j = 0;
	sub_str = start_sub(wildcard, &i, &j);
	if (ft_strat_with(file, sub_str) == 0)
	{
		printf("the problem in the start\n");
		return (0);
	}
	start = i;
	start_f = j;
	printf("after the strat: i:%d j:%d start:%d start_f:%d\n", i, j, start, start_f);
	printf("after the strat: wildcard: %s wildcard[i]: %c file : %s file[j] : %c\n", wildcard, wildcard[i], file, file[j]);
	printf("sub_str<wildcard>: %s\n", sub_str);
	free(sub_str);
	sub_str = end_sub(wildcard ,&i, &j);
	end = i;
	end_f = j;
	if (ft_end_with(file, sub_str) == 0)
	{
		printf("the problem at the end\n");
		return (0);
	}
	// if (end_f == 0)
	// 	end_f = ft_strlen(wildcard) - 1;
	printf("after the end: i:%d j:%d end:%d end_f:%d\n", i, j, end, end_f);
	printf("after the end: wildcard: %s wildcard[i]: %c file : %s file[j] : %c\n", wildcard, wildcard[i], file, file[j]);
	printf("sub_str<wildcard>: %s\n", sub_str);
	free(sub_str);
	sub_str = ft_substr(wildcard, start, end - start + 1);
	printf("mid part of wildcard: %s\n", sub_str);
	printf(" end_f: %d\n",  end_f);
	printf("tmp_file = ft_substr(%s, %d, %d);\n", file, start_f,  end_f - start_f + 1);
	tmp_file = ft_substr(file, start_f, end_f - start_f + 1);
	printf("tmp_file %s", tmp_file);
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
	printf("\n---------------------------------\n");
	return (1);
}

void	disply_files_dir(t_info *info, int flag, char *sub_str,
		int wildcard_count)
{
	char			buf[1024];
	DIR				*dir;
	struct dirent	*entry;

	(void)wildcard_count;
	(void)sub_str;
	getcwd(buf, sizeof(buf));
	dir = opendir(buf);
	if (dir != NULL)
		printf("Directory opened successfully.\n");
	while ((entry = readdir(dir)) != NULL)
	{
		if ((entry->d_name[0] != '.' && flag == 0) || (flag == 1
				&& ft_matchy(entry->d_name, sub_str, wildcard_count) == 1))
		{
			printf("match: %s\n", entry->d_name);
			prossing_files(info, entry);
			printf("info->tmp:%s\n", info->temporary);
		}
	}
	closedir(dir);
}

void	wildcard(t_info *info, char **exp_res)
{
	if (*exp_res)
	{
		info->temporary = NULL;
		int wildcard_pos = ft_there_wildcard(*exp_res);
		if (wildcard_pos != -1)
		{
			char *clean_data = clean_wildcard(*exp_res);
			int clean_len = ft_strlen(clean_data);
			int wildcard_count = who_many_wildcard(clean_data);
			wildcard_pos = ft_there_wildcard(clean_data);
			printf("%d", wildcard_count);
			if (clean_len == 1)
				disply_files_dir(info, 0, NULL, wildcard_count);
			else
				disply_files_dir(info, 1, clean_data, wildcard_count);
			if (info->temporary)
			{
				free(*exp_res);
				(*exp_res) = ft_strdup(info->temporary);
				free(info->temporary);
			}
		}
	}
}
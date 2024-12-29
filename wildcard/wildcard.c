/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:37:44 by meid              #+#    #+#             */
/*   Updated: 2024/12/28 20:01:43 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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


char *start_sub(char *wildcard, int *i)
{
    int j;
    int count;
    char close;
    char *str;
    
    count = 0;
    j = 0;
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
                str[j++] = wildcard[(*i)++];
            (*i)++;
        }
        else
        {
            str[j++] = wildcard[(*i)++];
        }
    }
    str[j] = '\0';
    return (str);
}

char *end_sub(char *wildcard, int *i)
{
    int j;
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
    j = count - 1;
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
                str[j--] = wildcard[(*i)--];
            (*i)--;
        }
        else
        {
            str[j--] = wildcard[(*i)--];
        }
    }
    str[count] = '\0';
    return (str);
}

int	ft_matchy(char *file, char *wildcard, int wildcard_count)
{
	int		i;
	int		start;
	int		j;
	char	*tmp;
	int		end;

	(void)i;
	(void)start;
	(void)j;
	(void)tmp;
	(void)end;
	(void)wildcard_count;

	char *sub_str = NULL;

	if (!file || !wildcard)
		return (0);
	(void)file;
	i = 0;
	start = 0;
	j = 0;
	sub_str = start_sub(wildcard, &i);
	printf("sub_string: %s\n\n", sub_str);
	printf("file: %s\n", file);
	printf("i:%d\n", i);
	if (ft_strat_with(file, sub_str) == 0)
	{
		printf("the problem in the start\n");
		return (0);
	}
	start = i;
	free(sub_str);
	sub_str = end_sub(wildcard ,&i);
	end = i;
	printf("sub_string: %s\n\n", sub_str);
	if (ft_end_with(file, sub_str) == 0)
	{
		printf("the problem at the end\n");
		return (0);
	}
	free(sub_str);
	// sub_str = ft_substr(wildcard, start, end); // i did not add the function here yet
	// printf("the mid %s", sub_str);
	// if (sub_str)
	// {
	// 	if (ft_mid_with(file, wildcard, 0) == 0)
	// 		return (0);
	// }
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
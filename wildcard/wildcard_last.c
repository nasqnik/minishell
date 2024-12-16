/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_last.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:37:44 by meid              #+#    #+#             */
/*   Updated: 2024/12/16 21:16:45 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int ft_strat_with(char *str, char *start, int len)
{
    int start_len = len;
    if (ft_strncmp(str, start, start_len) == 0)
        return (1);
    return (0);    
}

int ft_end_with(char *str, char *end)
{
    if (ft_strcmp_end(str, end) == 1)
        return (1);
    return (0);
}


int ft_mid_with(char *file, char *wildcard, int start, int end)
{
    int i = 0;
    while (file[i])
    {
        if (wildcard[start] == '*')
        {
            start++;
            if (start == end)
                break ;
            while (wildcard[start] != '*')
            {
                if (file[i] == '\0' || wildcard[start] == '\0')
                    break ;
                if (file[i] && wildcard[start] == file[i])
                    start++;
                if (start == end)
                    break ;
                i++;
            }
        }
        else
            i++;
    }
    if (wildcard[start] == '\0')
        return (1);
    return (0);
}

int ft_matchy(char *file, char *wildcard, int wildcard_count)
{
    if (!file || !wildcard)
        return (0);
    (void)file;
    int i = 0;
    int start = 0;
    int j = 0;
    int w_len = ft_strlen(wildcard);
    
    while (wildcard[i] && wildcard[i] != '*')
        i++;
    if (ft_strat_with (file, wildcard, i) == 0)
        return (0);
    start = i + 1;
    i = 0;
    while (wildcard[i])
    {
        if (wildcard[i] == '*')
            j++;
        if (j == wildcard_count)
            break ;
        i++;
    }
    char *tmp = ft_substr(wildcard, i + 1, w_len - i);
    int end = i - 1;
    if (ft_end_with(file, tmp) == 0)
        return (0);
    if (ft_mid_with(file, wildcard, start - 1, end + 1) == 0)
        return (0);
    return (1);
}

void disply_files_dir(t_first *f, int flag, char *sub_str, int wildcard_count)
{
    (void)wildcard_count;
    (void)sub_str;
    char buf[1024];
    DIR *dir;
    struct dirent *entry;

    getcwd(buf, sizeof(buf));
    dir = opendir(buf);
    if (dir != NULL)
        printf("Directory opened successfully.\n");
    while ((entry = readdir(dir)) != NULL)
    {
        if ((entry->d_name[0] != '.' && flag == 0)
            || (flag == 1 && ft_matchy(entry->d_name, sub_str, wildcard_count) == 1))
        {
            printf("match: %s\n", entry->d_name);
            prossing_files(f, entry);
        }
    }
    closedir(dir);
}

void wildcard_str(t_first *f)
{
    (void)f;
    t_tokens *tmp = f->token_list;
    f->temporary = NULL;
    while(tmp)
    {
        int wildcard_pos = ft_there_wildcard(tmp->data);
        if (tmp->type == WORD && wildcard_pos != -1)
        {
            char *clean_data = clean_wildcard(tmp->data);
            int clean_len = ft_strlen(clean_data);
            int wildcard_count = who_many_wildcard(clean_data);
            wildcard_pos = ft_there_wildcard(clean_data);
            printf("%d",  wildcard_count);
            if (clean_len == 1)
                disply_files_dir(f, 0, NULL, wildcard_count);
            else
                disply_files_dir(f, 1, clean_data, wildcard_count);
            if (f->temporary)
            {
                free(tmp->data);
                tmp->data = f->temporary;
                // free(f->temporary);
                f->temporary = NULL;
            }
        }
        tmp = tmp->next;
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:56:46 by meid              #+#    #+#             */
/*   Updated: 2024/12/14 13:42:10 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_strat_with(char *str, char *start)
{
    int start_len = ft_strlen(start);
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

int matchy_matchy(char *file, char *patren)
{
    int i = 0;
    int j = 0;
    while (file[i])
    {
        while (patren[j] && patren[j] == '*')
            j++;
        if (patren[j] && patren[j] == file[i])
            j++;
        i++;
    }
    if (patren[j] == '\0')
        return (1);
    return (0);
}

void prossing_files(t_first *f, struct dirent *entry)
{
    char *tmp;

    tmp = NULL;
    if (f->temporary == NULL)
    {
        f->temporary = ft_strdup(entry->d_name);
        if (!f->temporary)
            return ;
    }
    else
    {
        tmp = ft_strjoin(f->temporary, " ");
        if (!tmp)
            return ;
        free (f->temporary);
        f->temporary = ft_strjoin(tmp, entry->d_name);
        if (!f->temporary)
            return ;
        free(tmp);
    }
}

void disply_files_dir(t_first *f, int flag, char *sub_str)
{
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
            || (flag == 1 && ft_end_with(entry->d_name, sub_str) == 1)
            || (flag == 2 && ft_strat_with(entry->d_name, sub_str) == 1)
            || (flag == 3 && matchy_matchy(entry->d_name, sub_str) == 1))
        {
            // if (flag < 0 && sub_str[0] == '.')   
            prossing_files(f, entry);
        }
    }
    closedir(dir);
}

int ft_there_wildcard(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == '*')
            return (i);
        i++;
    }
    return (-1);
}

int who_many_wildcard(char *str)
{
    int i = 0;
    int count = 0;
    while (str[i])
    {
        if (str[i] == '*')
            count++;
        i++;
    }
    return (count);
}

char *clean_wildcard(char *data) {
    char *result = malloc(ft_strlen(data) + 1); // Allocate memory for the cleaned string
    if (!result)
        return NULL;

    int i = 0;  // Index for `data`
    int j = 0;  // Index for `result`
    int wildcard_found = 0; // Flag to track consecutive '*' sequences

    while (data[i]) {
        if (data[i] == '*') {
            if (!wildcard_found) {
                result[j++] = '*'; // Add only one '*' for a sequence
                wildcard_found = 1; // Mark that a '*' sequence was added
            }
        } else {
            result[j++] = data[i]; // Copy non-* characters
            wildcard_found = 0;   // Reset the flag for non-* characters
        }
        i++;
    }

    result[j] = '\0'; // Null-terminate the result
    return result;
}

void basic_case(t_first *f, char *clean_data, int clean_len, int wildcard_pos)
{
    if (wildcard_pos == 0)
    {
        if (clean_len == 1)
            disply_files_dir(f, 0, NULL);
        else
            disply_files_dir(f, 1, clean_data + 1);
    }
    else if (wildcard_pos == clean_len - 1)
    {
        char *string = clean_data;
        int len = clean_len;
        if (len > 0)
            string[len - 1] = '\0';
        disply_files_dir(f, 2, string);
    }
    else
    {
        disply_files_dir(f, 3, clean_data);
    }
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
            if (wildcard_count == 1)
                basic_case(f, clean_data, clean_len, wildcard_pos);
            else
            {
                disply_files_dir(f, 3, clean_data);
            }
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
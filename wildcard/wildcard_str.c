/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:56:46 by meid              #+#    #+#             */
/*   Updated: 2024/12/13 21:31:57 by meid             ###   ########.fr       */
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

void prossing_files(t_first *f, struct dirent *entry)
{
    char *tmp;

    tmp = NULL;
    if (f->tmp_data == NULL)
    {
        f->tmp_data = ft_strdup(entry->d_name);
        if (!f->tmp_data)
            return ;
    }
    else
    {
        tmp = ft_strjoin(f->tmp_data, " ");
        if (!tmp)
            return ;
        free (f->tmp_data);
        f->tmp_data = ft_strjoin(tmp, entry->d_name);
        if (!f->tmp_data)
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
            || (flag == 2 && ft_strat_with(entry->d_name, sub_str) == 1))
            prossing_files(f, entry);
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

void wildcard_str(t_first *f)
{
    (void)f;
    t_tokens *tmp = f->token_list;
    f->tmp_data = NULL;
    while(tmp)
    {
        int wildcard_pos = ft_there_wildcard(tmp->data);
        if (tmp->type == COMMAND && wildcard_pos != -1)
        {   
            
            if (wildcard_pos == 0)
            {
                if (tmp->len == 1)
                    disply_files_dir(f, 0, NULL);
                else
                    disply_files_dir(f, 1, tmp->data + 1);
            }
            else if (wildcard_pos == tmp->len - 1)
            {
                char *string = (char *)tmp->data;
                int len = tmp->len;
                if (len > 0) {
                    string[len - 1] = '\0';
                }
                disply_files_dir(f, 2, string);
            }
            if (f->tmp_data)
            {
                free(tmp->data);
                tmp->data = f->tmp_data;
                free(f->tmp_data);
                f->tmp_data = NULL;
            }
        }
        tmp = tmp->next;
    }
}

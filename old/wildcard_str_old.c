/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_str_old.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:56:46 by meid              #+#    #+#             */
/*   Updated: 2024/12/14 11:31:23 by meid             ###   ########.fr       */
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

char *prossing_files(struct dirent *entry, char *temporary)
{
    char *tmp;

    tmp = NULL;
    if (temporary == NULL)
    {
        temporary = ft_strdup(entry->d_name);
        if (!temporary)
            return ;
    }
    else
    {
        tmp = ft_strjoin(temporary, " ");
        if (!tmp)
            return ;
        free (temporary);
        temporary = ft_strjoin(tmp, entry->d_name);
        if (!temporary)
            return ;
        free(tmp);
    }
	return(temporary)
}


char *disply_files_dir(t_first *f, int flag, char *sub_str)
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
            prossing_files(f, entry, temporary);
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

void check_for_each_wildcard(t_first *f, t_tokens *tmp, int wildcard_pos)
{
	char **data = ft_split(tmp->data);
	int index = 0;
	char *string = NULL;
	if (wildcard_pos == 0)
	{
		if (tmp->len == 1)
	   		f->temporary[index] = disply_files_dir(f, 0, NULL);
		else
	    	f->temporary[index] = disply_files_dir(f, 1, tmp->data + 1);
	}
	else if (wildcard_pos == tmp->len - 1)
	{
		string = (char *)tmp->data;
		int len = tmp->len;
		if (len > 0)
	    string[len - 1] = '\0';
		f->temporary[index] = disply_files_dir(f, 2, string);
	}
	if (f->temporary[index])
	{
		index++;
		// free(tmp->data);
		// tmp->data = f->temporary;
		// // free(f->temporary);
		// f->temporary = NULL;
	}
	f->temporary[index] = NULL;
}	


char *ft_double_array_to_array(char **array)
{
	char *str = NULL; 
	char *tmp = NULL; 
	int i = 0;
	if (array[i])
	{
		str = ft_strdup(array[i]);
		i++;
	}
	while (array[i])
	{
		tmp = ft_strjoin(str, " ");
		free(str);
		str = ft_strjoin(tmp, array[i]);
		free(tmp);
		i++;
	}
	printf("str: %s\n", str);
	return (str);
}

void wildcard_str(t_first *f)
{
    (void)f;
    t_tokens *tmp = f->token_list;
	f->temporary = NULL;
    while(tmp)
    {
        int wildcard_pos = ft_there_wildcard(tmp->data);
        if (tmp->type == ARGUMENT && wildcard_pos != -1)
            check_for_each_wildcard(f, tmp, wildcard_pos);
		if (f->temporary)
		{
			free(tmp->data);
			tmp->data = ft_double_array_to_array(f->temporary);
			f->temporary = NULL;
		}
        tmp = tmp->next;
		
    }
}

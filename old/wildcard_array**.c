/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:56:46 by meid              #+#    #+#             */
/*   Updated: 2024/12/14 10:39:48 by meid             ###   ########.fr       */
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


char *disply_files_dir(int flag, char *sub_str)
{
    char buf[1024];
    DIR *dir;
    struct dirent *entry;
	char *tmp = NULL;
	char *temporary = NULL;

    getcwd(buf, sizeof(buf));
    dir = opendir(buf);
    if (dir != NULL)
        printf("Directory opened successfully.\n");
    while ((entry = readdir(dir)) != NULL)
    {
        if ((entry->d_name[0] != '.' && flag == 0) 
            || (flag == 1 && ft_end_with(entry->d_name, sub_str) == 1)
            || (flag == 2 && ft_strat_with(entry->d_name, sub_str) == 1))
		{
			if (temporary == NULL)
			{
				temporary = ft_strdup(entry->d_name);
				if (!temporary)
					return NULL;
			}
			else
			{
				tmp = ft_strjoin(temporary, " ");
				if (!tmp)
					return NULL;
				free (temporary);
				temporary = ft_strjoin(tmp, entry->d_name);
				if (!temporary)
					return NULL;
				free(tmp);
			}	
		}
    }
	
    closedir(dir);
	return (temporary);
}

int ft_there_quote(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (ft_is(str[i], "quote"))
            return (i);
        i++;
    }
    return (-1);
}

char **trem_quotes(char **data)
{
	int i = 0;
	char *tmp_data = NULL; 
	while (data[i])
	{
		if (ft_there_quote(data[i]))
		{
			tmp_data = ft_strtrim(data[i], "\"\'");
			if (tmp_data)
				free(data[i]);
			data[i] = tmp_data;
		}
		i++;
	}
	return (data);
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
static void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void check_for_each_wildcard(t_first *f, t_tokens *tmp)
{
	char **data = ft_split(tmp->data, ' ');
	
	char **clean_data = trem_quotes(data);
	free_array(data);
	char *tmp_data = NULL;
	char *tmp_data02 = NULL;
	
	int i = 0;
	f->temporary = NULL;
	int j = 0;
	char *string = NULL;
	
	while (clean_data[i])
	{
		int wildcard_pos = ft_there_wildcard(clean_data[i]);
		if (wildcard_pos == 0)
		{
			if (ft_strlen(clean_data[i]) == 1)
				tmp_data02 = disply_files_dir(0, NULL);
			else
				tmp_data02 = disply_files_dir(1, clean_data[i] + 1);
		}
		else if (wildcard_pos == ft_strlen(clean_data[i]) - 1)
		{
			string = clean_data[i];
			int len = ft_strlen(clean_data[i]);
			if (len > 0)
			string[len - 1] = '\0';
			tmp_data02 = disply_files_dir(2, string);
		}
		if (tmp_data02)
		{
			if (j == 0)
			{
				f->temporary = ft_strdup(tmp_data02);
				free(tmp_data02);
				j = 1;
			}
			else
			{
				tmp_data = ft_strjoin(f->temporary, " ");
				free(f->temporary);
				f->temporary = ft_strjoin(tmp_data, tmp_data02);
				free(tmp_data);
				free(tmp_data02);
				tmp_data = NULL;
				tmp_data02 = NULL;
			}
		}
		i++;
	}
}	

void wildcard_str(t_first *f)
{
    (void)f;
    t_tokens *tmp = f->token_list;
    while(tmp)
    {
        int wildcard_pos = ft_there_wildcard(tmp->data);
		if (tmp->type == ARGUMENT && wildcard_pos != -1)
		{
			check_for_each_wildcard(f, tmp);
		}
		if (f->temporary)
		{
			free(tmp->data);
			tmp->data = f->temporary;
			f->temporary = NULL;
		}	
        tmp = tmp->next;
		
    }
}

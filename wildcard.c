/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:49:49 by meid              #+#    #+#             */
/*   Updated: 2024/12/12 18:28:17 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_tmp(t_w_tmp **lst)
{
	t_w_tmp	*current;
	t_w_tmp	*tmp;

	if (!lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
            free (tmp->data);
            tmp->data = NULL;   
		free(tmp);
        tmp = NULL;
	}
	*lst = NULL;
}

t_w_tmp	*ft_data_lstnew(char *con)
{
	t_w_tmp	*new;
 
	new = malloc((sizeof(t_w_tmp)));
	if (new)
	{
        new->data = ft_strdup(con);
		new->next = NULL;
	}
	return (new);
}

static t_w_tmp	*ft_lstlast(t_w_tmp *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
static void	ft_lstadd_back(t_w_tmp **lst, t_w_tmp *new)
{
	t_w_tmp	*last;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

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
void search_for_pattern(t_first *f, int flag, char *sub_str)
{
    char buf[1024];
    getcwd(buf, sizeof(buf));
    printf("%s\n", buf);
    DIR *dir = opendir(buf);
    struct dirent *entry;
    int j = 0;
    while ((entry = readdir(dir)) != NULL && j != 2)
    {
        if ((flag == 1 && ft_end_with(entry->d_name, sub_str) == 1) || (flag == 2 && ft_strat_with(entry->d_name, sub_str) == 1))
        {
            f->tmp = ft_data_lstnew(entry->d_name);
            j = 2;
        }
    }
    while ((entry = readdir(dir)) != NULL) {
        if ((flag == 1 && ft_end_with(entry->d_name, sub_str) == 1) || (flag == 2 && ft_strat_with(entry->d_name, sub_str) == 1))
        {
            t_w_tmp *new_node = ft_data_lstnew(entry->d_name);
            if (!new_node)
                return ;
            ft_lstadd_back(&f->tmp, new_node);   
        }
    }
    closedir(dir);
}

void disply_files_dir(t_first *f)
{
    char buf[1024];
    getcwd(buf, sizeof(buf));
    DIR *dir = opendir(buf);
    if (dir != NULL) {
        printf("Directory opened successfully.\n");
    }
    struct dirent *entry;
    int j = 0;
    printf("start from here\n");
    while ((entry = readdir(dir)) != NULL && j != 2)
    {
        if (entry->d_name[0] != '.')
        {
            f->tmp = ft_data_lstnew(entry->d_name);
            j = 2;
        }
    }
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.')
        {
            t_w_tmp *new_node = ft_data_lstnew(entry->d_name);
            if (!new_node)
                return ;
            ft_lstadd_back(&f->tmp, new_node);   
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

void *deep_copy_tmp(t_first *f, void *data)
{
    t_w_tmp *copy;
    t_w_tmp *tmp1;
    tmp1= f->tmp;
    
    if (tmp1)
        copy = ft_data_lstnew(tmp1->data);
    tmp1 = tmp1->next;
    while (tmp1)
    {
        t_w_tmp *cur = ft_data_lstnew(tmp1->data);
        if (!cur)
            return (NULL);
        ft_lstadd_back(&copy, cur);
        tmp1 = tmp1->next;
    }
    data = copy;
    return (data);
}

void wildcard(t_first *f)
{
    (void)f;
    t_tokens *tmp = f->token_list;
    while(tmp)
    {
        int wildcard_pos = ft_there_wildcard(tmp->data);
        (void)wildcard_pos;
        if (tmp->type == WORD && wildcard_pos != -1)
        {
            
            if (wildcard_pos == 0)
            {
                if (tmp->len == 1)
                    disply_files_dir(f);
                else
                    search_for_pattern(f, 1, tmp->data + 1);
            }
            else if (wildcard_pos == tmp->len - 1)
            {
                char *string = (char *)tmp->data;
                int len = tmp->len;
                if (len > 0) {
                    string[len - 1] = '\0';
                }
                search_for_pattern(f, 2, string);
            }
            if (f->tmp != NULL)
            {
                free(tmp->data);
                tmp->data_type = 'l';
                // tmp->data = f->tmp;
                tmp->data = deep_copy_tmp(f, tmp->data);
                ft_clear_tmp(&f->tmp);
            }
        }
        tmp = tmp->next;
    }
}

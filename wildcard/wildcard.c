/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:37:44 by meid              #+#    #+#             */
/*   Updated: 2025/02/05 10:52:45 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	end_is_dot(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	while (len != 0)
	{
		if (str[len] == '*')
			break ;
		if (str[len] != '\"' || str[len] != '\'' || str[len] != '.')
			return (0);
		if (str[len] == '.')
			return (1);
		len--;
	}
	return (0);
}

int	is_matching_quote(char *wildcard, char *file, int *wc, int i)
{
	int	tmp;

	tmp = *wc + 1;
	if (wildcard[tmp] && wildcard[tmp] == file[i])
	{
		return (1);
	}
	return (0);
}

static void	disply_files_dir(t_info *info, int flag, char *sub_str)
{
	char			buf[1024];
	DIR				*dir;
	struct dirent	*entry;
	char			*tmp_file;

	tmp_file = NULL;
	(void)sub_str;
	getcwd(buf, sizeof(buf));
	dir = opendir(buf);
	if (dir == NULL)
		printf("Directory is not opened\n");
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if ((entry->d_name[0] != '.' && flag == 0) || (flag == 1
				&& ft_matchy(entry->d_name, sub_str, tmp_file, 0) == 1))
		{
			prossing_files(info, entry);
		}
	}
	closedir(dir);
}

int	wildcard(t_info *info, char **exp_res)
{
	int		wildcard_pos;
	char	*clean_data;

	if (*exp_res)
	{
		info->temporary = NULL;
		wildcard_pos = ft_there_wildcard(*exp_res);
		if (wildcard_pos != -1)
		{
			clean_data = clean_wildcard(*exp_res);
			if (ft_strlen(clean_data) == 1)
				disply_files_dir(info, 0, NULL);
			else
				disply_files_dir(info, 1, clean_data);
			free(clean_data);
			if (info->temporary)
			{
				free(*exp_res);
				(*exp_res) = ft_strdup(info->temporary);
				free(info->temporary);
				return (1);
			}
		}
	}
	return (0);
}

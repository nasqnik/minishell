/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:37:44 by meid              #+#    #+#             */
/*   Updated: 2024/12/30 12:27:29 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	disply_files_dir(t_info *info, int flag, char *sub_str)
{
	char			buf[1024];
	DIR				*dir;
	struct dirent	*entry;

	(void)sub_str;
	getcwd(buf, sizeof(buf));
	dir = opendir(buf);
	if (dir != NULL)
		printf("Directory opened successfully.\n");
	while ((entry = readdir(dir)) != NULL)
	{
		if ((entry->d_name[0] != '.' && flag == 0) || (flag == 1
				&& ft_matchy(entry->d_name, sub_str) == 1))
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
			if (clean_len == 1)
				disply_files_dir(info, 0, NULL);
			else
				disply_files_dir(info, 1, clean_data);
			if (info->temporary)
			{
				free(*exp_res);
				(*exp_res) = ft_strdup(info->temporary);
				free(info->temporary);
			}
		}
	}
}
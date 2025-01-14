/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:32:36 by meid              #+#    #+#             */
/*   Updated: 2025/01/14 13:10:57 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize(t_info *info, char **env)
{
	info->buffer = NULL;
	info->token_list = NULL;
	info->ast_tree = NULL;
	info->envp_array = ft_allocate_env(env);
	info->envp_list = NULL;
	info->i = 0;
	info->export_tmp = NULL;
	info->stdout = dup(STDOUT_FILENO);
	info->stdin = dup(STDIN_FILENO);
	if (info->stdout == -1 || info->stdin == -1)
	{
		perror("dup failed");
		exit(EXIT_FAILURE);
	}
	if (!info->envp_array)
	{
		info->envp_array = create_non_existing_env();
		env_to_list(info, 0);
	}
	else if (info->envp_array)
		env_to_list(info, 1);
}

char	**ft_allocate_env(char **env)
{
	int		i;
	char	**env_array;

	if (!env || !(*env))
		return (NULL);
	i = ft_arraylen(env);
	env_array = malloc(sizeof(char *) * (i + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	while (env[i])
	{
		env_array[i] = ft_strdup(env[i]);
		if (!env_array[i])
		{
			while (--i >= 0)
				free(env_array[i]);
			free(env_array);
			return (NULL);
		}
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

char	**create_non_existing_env(void)
{
	char	**new_env;
	char	buf[1024];

	new_env = malloc(sizeof(char *) * 4);
	if (!new_env)
	{
		perror("malloc failed in create_non_existing_env");
		exit(EXIT_FAILURE);
	}
	if (getcwd(buf, sizeof(buf)) == NULL)
		return (NULL);
	new_env[0] = ft_strjoin("PWD=", buf);
	new_env[1] = ft_strdup("SHLVL=1");
	new_env[2] = ft_strdup("OLDPWD");
	new_env[3] = NULL;
	return (new_env);
}

void	env_to_list(t_info *info, int flag)
{
	t_env	*new_node;
	int		k;
	int		env_size;

	env_size = 0;
	new_node = NULL;
	if (!(info->envp_array) || !(*(info->envp_array)))
		return ;
	while (info->envp_array[env_size])
		env_size++;
	info->envp_list = env_lstnew(info->envp_array[0], 1);
	if (!info->envp_list)
		return ;
	k = 1;
	while (k < env_size)
	{
		if (flag == 0 && k == 2)
			new_node = env_lstnew(info->envp_array[k], 0);
		else
			new_node = env_lstnew(info->envp_array[k], 1);
		if (!new_node)
			return ;
		env_lstadd_back(&info->envp_list, new_node);
		k++;
	}
}

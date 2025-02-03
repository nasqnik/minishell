/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:09:33 by meid              #+#    #+#             */
/*   Updated: 2025/02/03 13:28:45 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_quotes(char *str)
{
	int		len;
	char	*result;

	len = ft_strlen(str);
	result = (char *)malloc(len + 3);
	if (!result)
		return (NULL);
	result[0] = '"';
	ft_strcpy(result + 1, str);
	result[len + 1] = '"';
	result[len + 2] = '\0';
	return (result);
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

void	ft_clear_list(t_env **lst)
{
	t_env	*current;
	t_env	*tmp;

	if (!lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp->env);
		free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
	*lst = NULL;
}

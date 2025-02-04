/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:49:36 by meid              #+#    #+#             */
/*   Updated: 2025/02/04 20:27:16 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(t_env *lst)
{
	int	counter;

	counter = 0;
	while (lst)
	{
		++counter;
		lst = lst->next;
	}
	return (counter);
}

char	*skip_the_quotes(t_env *env_cur, int *c_val)
{
	char	*temp_value;

	temp_value = ft_strtrim_sides(env_cur->value);
	if (!temp_value)
		return (NULL);
	(*c_val) = ft_strlen(temp_value);
	return (temp_value);
}

void	set_some_val(int i[3], int *c_key, int *c_val, t_env *env_cur)
{
	i[1] = 0;
	i[2] = 0;
	(*c_key) = ft_strlen(env_cur->key);
	(*c_val) = 0;
}

void	loop(int i[3], char ***new_env_array, t_env *env_cur, int counter)
{
	int		c_key;
	int		c_val;
	char	*tmp_value;

	tmp_value = NULL;
	while (i[0] < counter)
	{
		set_some_val(i, &c_key, &c_val, env_cur);
		if (env_cur->value)
			tmp_value = skip_the_quotes(env_cur, &c_val);
		(*new_env_array)[(i[0])] = malloc((c_key + c_val + 2) * sizeof(char));
		while (i[2] < c_key)
			(*new_env_array)[(i[0])][i[1]++] = env_cur->key[i[2]++];
		(*new_env_array)[(i[0])][i[1]++] = '=';
		i[2] = 0;
		while (i[2] < c_val)
			(*new_env_array)[(i[0])][i[1]++] = tmp_value[i[2]++];
		(*new_env_array)[(i[0])][i[1]] = '\0';
		env_cur = env_cur->next;
		if (tmp_value)
			free(tmp_value);
		tmp_value = NULL;
		(i[0])++;
	}
}

void	update_envp_array(t_info *info, t_env *env_cur, int counter)
{
	char	**new_env_array;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	new_env_array = malloc((counter + 1) * sizeof(char *));
	if (!new_env_array)
	{
		perror("malloc: ");
		return ;
	}
	new_env_array[counter] = NULL;
	loop(i, &new_env_array, env_cur, counter);
	new_env_array[i[0]] = NULL;
	if (info->envp_array)
		free_array(info->envp_array);
	info->envp_array = new_env_array;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:49:36 by meid              #+#    #+#             */
/*   Updated: 2025/01/21 11:45:16 by meid             ###   ########.fr       */
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

void	skip_the_quotes(t_env *env_cur, int *c_val)
{
	(*c_val) = ft_strlen(env_cur->value);
	if ((*c_val) > 0 && env_cur->value[0] == '"')
	{
		env_cur->value++;
		(*c_val)--;
	}
	if ((*c_val) > 0 && env_cur->value[(*c_val) - 1] == '"')
	{
		env_cur->value[(*c_val) - 1] = '\0';
		(*c_val)--;
	}
}

void	loop(int *i, char ***new_env_array, t_env *env_cur, int counter)
{
	int		j;
	int		x;
	int		c_key;
	int		c_val;

	while (*i < counter)
	{
		j = 0;
		x = 0;
		c_key = ft_strlen(env_cur->key);
		c_val = 0;
		if (env_cur->value)
			skip_the_quotes(env_cur, &c_val);
		(*new_env_array)[(*i)] = malloc((c_key + c_val + 2) * sizeof(char));
		while (x < c_key)
			(*new_env_array)[(*i)][j++] = env_cur->key[x++];
		(*new_env_array)[(*i)][j++] = '=';
		x = 0;
		while (x < c_val)
			(*new_env_array)[(*i)][j++] = env_cur->value[x++];
		(*new_env_array)[(*i)][j] = '\0';
		env_cur = env_cur->next;
		(*i)++;
	}
}

void	update_envp_array(t_info *info, t_env *env_cur, int counter)
{
	char	**new_env_array;
	int		i;

	i = 0;
	new_env_array = malloc((counter + 1) * sizeof(char *));
	if (!new_env_array)
	{
		perror("malloc: ");
		return ;
	}
	new_env_array[counter] = NULL;
	loop(&i, &new_env_array, env_cur, counter);
	new_env_array[i] = NULL;
	if (info->envp_array)
		free_array(info->envp_array);
	info->envp_array = new_env_array;
}

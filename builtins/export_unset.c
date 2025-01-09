/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:30:05 by meid              #+#    #+#             */
/*   Updated: 2025/01/09 17:54:11 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_export_error(t_info *info, char *str)
{
	if (invalid_identifier(str, 1))
	{
		print_the_error(info, str, 3, 1);
		our_static("exit status", 1);
		return (1);
	}
	return (0);
}

void	new_env(t_info *info, char *search_for, char *value, char flago, int flagoooo)
{
	(void)flago;
	char	*the_str;
	char	*tmpo;

	the_str = NULL;
	tmpo = NULL;
	tmpo = ft_strjoin(search_for, "=");
	free(search_for);
	the_str = ft_strjoin(tmpo, value);
	free(value);
	free(tmpo);
	env_lstadd_back(&info->envp_list, env_lstnew(the_str, 1));
	free(the_str);
}
int	check_env_there(t_info *info, char *search_for, char *value, char flago, int flagoooo)
{
	(void)flago;
	t_env	*tmp;
	char *tmp_joined = NULL;
	char *tmpo = NULL;

	tmp = info->envp_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, search_for) == 0 && flagoooo == 0)
			return (1);
		if (ft_strcmp(tmp->key, search_for) == 0)
		{
			if (flago == 'n')
			{
				free(tmp->env);
				tmpo = ft_strjoin(search_for, "=");
				tmp->env = ft_strjoin(tmpo, value);
				free(tmpo);
				free(tmp->value);
				tmp->value = value;
			}
			else
			{
				tmp_joined = ft_strjoin(tmp->value, value);
				free(tmp->value);
				free(value);
				tmp->value = tmp_joined;
				free(tmp->env);
				tmpo = ft_strjoin(search_for, "=");
				tmp->env = ft_strjoin(tmpo, tmp_joined);
				free(tmpo);
			}
			free(search_for);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_export(t_info *info, char **args, int i)
{
	char	*value;
	int		j;
	int		flag;
	char	*search_for;
	char flago;
	int flagoooo = 0; 
	int return_value = 0;

	value = NULL;
	j = 0;
	flag = 0;
	search_for = NULL;
	flago = 'n';
	if (!args[i])
	{
		env_sort(info, info->envp_list);
		return (0);
	}
	while (args[i])
	{
		if (handle_export_error(info, args[i]))
		{
			i++;
			return_value = 1;
			continue;
		}
		else if (ft_strcmp(args[i], " ") != 0)
		{
			j = 0;
			while (args[i][j] && args[i][j] != '=')
				j++;
			if (args[i][j - 1] == '+')
			{
				flago = 'y';
				search_for = ft_substr(args[i], 0, j - 1);
				j++;
			}
			else
				search_for = ft_substr(args[i], 0, j);
			if (args[i][j] == '=')
				flagoooo = 1;
			if (args[i][j + 1])
				value = ft_substr(args[i], j + 1, ft_strlen(args[i]) - j - 1);
			else
				value = NULL;
			if (check_env_there(info, search_for, value, flago, flagoooo))
				flag = 1;
			if (flag == 0)
				new_env(info, search_for, value, flago, flagoooo);
		}
		i++;
	}
	printf("return_value %d\n", return_value);
	return (return_value);
}

void	search_to_unset(t_env *tmp, char *str)
{
	t_env	*tmp1;

	tmp1 = NULL;
	while (tmp)
	{
		if (tmp->next && ft_strcmp(tmp->next->key, str) == 0)
		{
			if (tmp->next->next)
				tmp1 = tmp->next->next;
			free(tmp->next->env);
			free(tmp->next->value);
			free(tmp->next->key);
			free(tmp->next);
			tmp->next = tmp1;
		}
		tmp = tmp->next;
	}
}

int	ft_unset(t_info *info, char **args, int i)
{
	t_env *tmp;
	int fd;
	int return_value = 0;

	tmp = NULL;
	fd = 1;
	while (args[i])
	{
		if (invalid_identifier(args[i], 2))
		{
			print_the_error(info, args[i], 3, fd);
			printf("our_static: %d\n", our_static("exit status", 1));
			return_value = 1;
			i++;
			continue ;
		}
		else if (ft_strcmp(args[i], " ") != 0)
		{
			tmp = info->envp_list;
			search_to_unset(tmp, args[i]);
		}
		i++;
	}
	return (return_value);
}
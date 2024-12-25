/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:30:05 by meid              #+#    #+#             */
/*   Updated: 2024/12/22 20:29:35 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_export_error(char *str)
{
	int	fd;

	fd = 1;
	if (invalid_identifier(str, 1))
	{
		if (invalid_identifier(str, 1) == 2)
			return (print_the_error(str, 2, fd), 1);
		else
			return (print_the_error(str, 3, fd), 1);
	}
	return (0);
}

void	new_env(t_first *f, char *search_for, char *value)
{
	char	*the_str;
	char	*tmpo;

	the_str = NULL;
	tmpo = NULL;
	tmpo = ft_strjoin(search_for, "=");
	free(search_for);
	the_str = ft_strjoin(tmpo, value);
	free(value);
	free(tmpo);
	env_lstadd_back(&f->envp_list, env_lstnew(the_str));
	free(the_str);
}
int	check_env_there(t_first *f, char *search_for, char *value)
{
	t_list	*tmp;

	tmp = f->envp_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, search_for) == 0)
		{
			free(search_for);
			free(tmp->value);
			tmp->value = value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_export(t_first *f, char **args, int i)
{
	char	*value;
	int		j;
	int		flag;
	char	*search_for;

	value = NULL;
	j = 0;
	flag = 0;
	search_for = NULL;
	while (args[i])
	{
		if (handle_export_error(args[i]))
			return (1);
		else if (ft_strcmp(args[i], " ") != 0 && ft_strfind(args[i], '=') == 1)
		{
			j = 0;
			while (args[i][j] != '=')
				j++;
			search_for = ft_substr(args[i], 0, j);
			value = ft_substr(args[i], j + 1, ft_strlen(args[i]) - j - 1);
			if (check_env_there(f, search_for, value))
				flag = 1;
			if (flag == 0)
				new_env(f, search_for, value);
		}
		i++;
	}
	return (42);
}

void	search_to_unset(t_list *tmp, char *str)
{
	t_list	*tmp1;

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

int	ft_unset(t_first *f, char **args, int i)
{
	t_list *tmp;
	int fd;

	tmp = NULL;
	fd = 1;
	while (args[i])
	{
		if (invalid_identifier(args[i], 2))
			return (print_the_error(args[i], 2, fd), 0);
		else if (ft_strcmp(args[i], " ") != 0)
		{
			tmp = f->envp_list;
			search_to_unset(tmp, args[i]);
		}
		i++;
	}
	return (42);
}
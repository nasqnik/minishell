/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:07:24 by meid              #+#    #+#             */
/*   Updated: 2025/02/05 11:38:38 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

char	*search_in_env(t_info *info, char *key)
{
	t_env	*tmp;

	tmp = info->envp_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	invalid_identifier(char *str, int flag)
{
	int	i;
	int	flago;

	i = 0;
	flago = 0;
	if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
		return (1);
	while (str[i])
	{
		if ((str[i] == '+' && (!str[i + 1] || (str[i + 1]
						&& str[i + 1] != '='))) || (str[i] == '=' && i == 0))
			return (1);
		if ((!(ft_isalnum(str[i])) && str[i] != '_' && str[i] != '='
				&& str[i] != '+') || (str[i] == '=' && flag == 2)
			|| ((str[i] == '=' && ft_strlen(str) == 1)))
			return (1);
		if (str[i] != '=')
			flago++;
		if (str[i] == '=')
			break ;
		i++;
	}
	if (flag == 1 && flago == 0)
		return (1);
	return (0);
}

int	ft_meow(t_info *info, char **args, int i, int j)
{
	int	count;

	count = 1;
	while (args[i])
	{
		if (i > 1)
			return (print_the_error(info, NULL, 4, 2), 0);
		while (args[i][j])
		{
			if (!(args[i][j] >= '0' && args[i][j] <= '9'))
				return (print_the_error(info, args[1], 5, 2), 0);
			j++;
		}
		count = ft_atoi(args[i]);
		i++;
	}
	while (count > 0)
	{
		ft_putstr_fd("meow 😺\n", 2);
		count--;
	}
	return (0);
}

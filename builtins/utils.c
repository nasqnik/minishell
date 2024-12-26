/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:07:24 by meid              #+#    #+#             */
/*   Updated: 2024/12/26 08:13:15 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
		return (1);
	while (str[i])
	{
		if ((!(ft_isalnum(str[i])) && str[i] != '_' && str[i] != '=')
			|| (str[i] == '=' && flag == 2))
			return (2);
		i++;
	}
	return (0);
}

void	change_pwd_in_env(t_info *f)
{
	char	buf[1024];
	t_env	*tmp;

	if (getcwd(buf, sizeof(buf)) == NULL)
		return ;
	tmp = f->envp_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(buf);
		}
		tmp = tmp->next;
	}
}

int	ft_meow(char **args, int i, int j)
{
	int	fd;
	int	count;

	fd = 1;
	count = 1;
	while (args[i])
	{
		if (i > 1)
			return (print_the_error(NULL, 4, fd), 0);
		while (args[i][j])
		{
			if (!(args[i][j] >= '0' && args[i][j] <= '9'))
				return (print_the_error(args[1], 5, fd), 0);
			j++;
		}
		count = ft_atoi(args[i]);
		i++;
	}
	while (count > 0)
	{
		ft_putstr_fd("meow 😺\n", fd);
		count--;
	}
	return (42);
}

// 1. Starts with a Number
// 1VAR
// 123ABC
// 5_variable
// 2. Contains Special Characters
// VAR-NAME (Hyphen -)
// VAR@NAME (At symbol @)
// VAR#NAME (Hash #)
// VAR.NAME (Dot .)
// VAR+NAME (Plus +)
// 3. Starts with a Special Character
// -VAR (Hyphen -)
// @NAME (At symbol @)
// #COMMENT (Hash #)
// 4. Contains Spaces
// MY VAR (Space in the name)
// VAR (Leading space)
// VAR (Trailing space)
// 5. Starts with a Non-Alphabetic Symbol
// !VAR (Exclamation mark !)
// *VAR (Asterisk *)
// ?VAR (Question mark ?)
// 6. Empty or Missing Variable Name
// export =value (No name, just a value)
// 7. Uses Reserved Words or Syntax
// if (Keyword in Bash)
// for (Keyword in Bash)
// case (Keyword in Bash)
// Correct Identifier Rules Recap:
// Must start with a letter or an underscore (_).
// Can only contain letters, numbers, and underscores.
// Must not contain spaces or special characters.
// Let me know if you need more examples or further clarifications!
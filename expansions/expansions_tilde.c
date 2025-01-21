/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_tilde.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:37:41 by anikitin          #+#    #+#             */
/*   Updated: 2025/01/17 19:26:26 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*extract_username(char *str, int pov[2])
{
	int		len;
	char	*username;

	len = 1;
	username = NULL;
	while (str[len] && str[len] != '/')
	{
		if (str[len] == '\"' || str[len] == '\'')
		{
			pov[0] += len;
			return (ft_substr(str, 0, len));
		}
		len++;
	}
	pov[0] += len;
	username = ft_substr(str, 1, len - 1);
	if (!username)
		username = ft_strdup("");
	return (username);
}

static char	*search_user(char *str, int pov[2], char *result)
{
	char	*username;
	char	*loc;

	username = NULL;
	loc = NULL;
	username = extract_username(str, pov);
	if (username)
	{
		loc = ft_strjoin("/Users/", username);
		if (access(loc, F_OK) == -1)
		{
			free(result);
			free(loc);
			free(username);
			return (ft_substr(str, 0, pov[0]));
		}
	}
	free(result);
	free(username);
	return (loc);
}

static char	*sub_after_tilde(char *str, int pov[2], int i)
{
	char	*sub;

	sub = NULL;
	while (str[pov[0]] && str[pov[0]] != '\''
		&& str[pov[0]] != '\"'
		&& str[pov[0]] != '$')
		pov[0]++;
	sub = ft_substr(str, i, pov[0] - i);
	printf("sub: %s\n", sub);
	printf("i: %c\n", str[i]);
	if (!sub)
		sub = ft_strdup("");
	return (sub);
}

static char	*get_home(t_info *info, char *str, int *i)
{
	char	*home;

	home = NULL;
	if ((str[1] == '+' || str[1] == '-')
		&& (str[2] == '\0' || str[2] == '/'))
	{
		printf("i in get_home: %c\n", str[*i]);
		if (str[1] == '+')
			home = search_in_env(info, "PWD");
		else
			home = search_in_env(info, "OLDPWD");
		(*i)++;
	}
	else
		home = search_in_env(info, "HOME");
	return (home);
}

char	*tilda_string(t_info *info, char *str, int pov[2], char *result)
{
	char	*home;
	char	*sub;
	int		i;

	i = 1;
	if (str[0] == '~' && (ft_strlen(str) == 1 || (str[1]
				&& (str[1] == '/' || str[1] == '+' || str[1] == '-'))))
	{
		home = get_home(info, str, &i);
		if (home)
		{
			sub = sub_after_tilde(str, pov, i);
			free(result);
			result = ft_strjoin(home, sub);
			free(sub);
			return (result);
		}
	}
	else if (str[0] == '~' && (str[1] && ft_is(str[1], "alnum")))
		return (search_user(str, pov, result));
	pov[0]++;
	if (pov[1] < pov[0])
		return (append_remaining_data(str, pov, result, 0));
	free(result);
	return (ft_strdup("~"));
}

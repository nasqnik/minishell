/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mid_part.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:15:10 by meid              #+#    #+#             */
/*   Updated: 2025/01/15 15:57:13 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	skip_quotes(char *wildcard, int *tmp, char *close, int *flag)
{
	if (*flag == 1)
	{
		*close = wildcard[*tmp];
		(*tmp)++;
		*flag = 2;
	}
	else
	{
		*close = '\0';
		(*tmp)++;
		*flag = 1;
	}
	return (1);
}

static int	match_file_char(char *file, char *wildcard, int *tmp, int *i)
{
	if (file[*i] && wildcard[*tmp] != file[*i])
		return (0);
	if (file[*i] == '\0' || wildcard[*tmp] == '\0')
		return (0);
	if (file[*i] && wildcard[*tmp] == file[*i])
	{
		(*tmp)++;
		(*i)++;
	}
	return (1);
}

void	ft_check_rest(char *file, char *wildcard, int *wc, int *i)
{
	int		tmp;
	char	close;
	int		flag;

	tmp = *wc;
	close = '\0';
	flag = 1;
	while (wildcard[tmp] != '*')
	{
		if ((flag == 1 && (wildcard[tmp] == '\'' || wildcard[tmp] == '\"'))
			|| (flag == 2 && wildcard[tmp] == close))
		{
			skip_quotes(wildcard, &tmp, &close, &flag);
		}
		else if (!match_file_char(file, wildcard, &tmp, i))
			break ;
	}
	if (wildcard[tmp] != '*')
	{
		(*wc)--;
		return ;
	}
	*wc = tmp;
}

static void	process_wildcard(char *file, char *wildcard, int *wc, int *i)
{
	while (file[*i])
	{
		if (wildcard[*wc] && wildcard[*wc] == file[*i])
		{
			ft_check_rest(file, wildcard, wc, i);
			break ;
		}
		else if (wildcard[*wc] == '\'' || wildcard[*wc] == '\"')
		{
			if (is_matching_quote(wildcard, file, wc, *i))
			{
				ft_check_rest(file, wildcard, wc, i);
				break ;
			}
			else
				(*i)++;
		}
		else
			(*i)++;
	}
}

int	ft_mid_with(char *file, char *wildcard, int wc)
{
	int	i;

	i = 0;
	while (file[i])
	{
		while (wildcard[wc] == '*')
		{
			wc++;
			if (!wildcard[wc])
				return (1);
			process_wildcard(file, wildcard, &wc, &i);
		}
	}
	return (wildcard[wc] == '\0');
}

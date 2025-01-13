/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:07:24 by meid              #+#    #+#             */
/*   Updated: 2025/01/13 19:29:26 by meid             ###   ########.fr       */
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
	int len;
	int flago;

	i = 0;
	flago = 0;
	len = ft_strlen(str);
	if (str[i] >= '0' && str[i] <= '9')
		return (1);
	while (str[i])
	{
		if ((str[i] == '+' && (!str[i + 1] || (str[i + 1] && str[i + 1] != '=')))
			|| (str[i] == '=' && i == 0))
			return (1);
		if ((!(ft_isalnum(str[i])) && str[i] != '_' && str[i] != '=' && str[i] != '+')
			|| (str[i] == '=' && flag == 2) || ((str[i] == '=' && len == 1)))
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

void	change_pwd_in_env(t_info *f, char *oldpwd)
{
	char	buf[1024];
	t_env	*tmp;
	// char	*tmp_old;
	// int flag = 0;
	int flago = 0;
	
	(void)oldpwd;
	static int pwd_is_not_there = 0;

	// printf("1\n");
	if (getcwd(buf, sizeof(buf)) == NULL)
		return ;
	f->pwd = buf;
	tmp = f->envp_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			// printf("pwd is there\n");
			// printf("2\n");
			flago = 1;
			// tmp_old = ft_strdup(tmp->value);
			
			if (tmp->value)
				free(tmp->value);
			tmp->flag = 1;
			// printf(":::%s\n", buf);
			tmp->value = ft_strdup(buf);
			break;
		}
		tmp = tmp->next;
	}
	if (flago == 0)
	{
			// printf("3\n");
		pwd_is_not_there++;
	}
	else
		pwd_is_not_there = 0;
	tmp = f->envp_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0 && pwd_is_not_there == 1)
		{
			// printf("the first time i did not see that pwd is not in env\n");
				// printf("4\n");
			// printf("llllllllll\n");
			tmp->flag = 1;
			if (tmp->value)
				free(tmp->value);
		}
		else if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			tmp->flag = 1;
			// printf("5\n");
			if (tmp->value)
				free(tmp->value);
			// printf("flag: %d\n", tmp->flag);
			// printf("the old pwd in cd function is : %s", oldpwd);
			tmp->value = ft_strdup(oldpwd);
			// if (!tmp->value)
			// 	printf("it is null to here crazyyyy\n");
			// printf("%s\n", tmp->value);
			break;
		}
		tmp = tmp->next;
	}
	if (pwd_is_not_there == 2)
	{
		// printf("6\n");
		pwd_is_not_there = 0;
	}
}

int	ft_meow(t_info *info, char **args, int i, int j)
{
	int	fd;
	int	count;

	fd = 1;
	count = 1;
	while (args[i])
	{
		if (i > 1)
			return (print_the_error(info, NULL, 4, fd), 0);
		while (args[i][j])
		{
			if (!(args[i][j] >= '0' && args[i][j] <= '9'))
				return (print_the_error(info, args[1], 5, fd), 0);
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
	return (0);
}



















// the_stack *array_to_linked_list(int *numbers,int count)
// {
//     the_stack *list = ft_lstnew(numbers[0]);
//     int i = 1;
//     while (i < count)
//     {
//         the_stack *new_node = ft_lstnew(numbers[i]);
//         if (!new_node)
//             return (0);
//         ft_lstadd_back(&list, new_node);
//         i++;       
//     }
//     return (list);
// }

void print_export(t_info *info)
{
	t_env *tmp1 = info->envp_list;
	while(tmp1)
	{
		// printf("flagggg : %d\n", tmp1->flag);
		// 	if (!tmp1->value)
		// 		printf("value is null\n");
		printf("declare -x "); 
		printf("%s", tmp1->key);
		if (tmp1->flag == 1 && tmp1->value)
			printf("=\"%s\"", tmp1->value);
		if (tmp1->flag == 1 && !(tmp1->value))
			printf("=\"\"");
		printf("\n");
		tmp1 = tmp1->next;
	}
}

void env_sort(t_info *info, t_env *envp_list)
{
    t_env *tmp = envp_list;
    while (tmp && tmp->env)
    {
		// printf("affff\n");
        // Create a new node for the sorted list
        t_env *new_node = env_lstnew(tmp->env, tmp->flag);
        if (!new_node)
            return; // Handle memory allocation failure
        // Insert the new node in the correct sorted position in export_tmp
        t_env **current = &info->export_tmp;
        while (*current && ft_strcmp((*current)->env, new_node->env) < 0)
        {
            current = &((*current)->next);
        }
        new_node->next = *current;
        *current = new_node;
        tmp = tmp->next;
    }
	print_export(info);
	ft_clear_list(&info->export_tmp);
	info->export_tmp = NULL;
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:48:46 by meid              #+#    #+#             */
/*   Updated: 2025/01/12 12:32:29 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_and_set_null(t_info *info, int flag)
{
	if (info->token_list)
		ft_clear_tokens(&(info->token_list));
	if (info->ast_tree)
        ft_clear_tree(info->ast_tree);
	if (info->stdout)
		close(info->stdout);
	if (info->stdin)
	    close(info->stdin);
	if (flag == 1) // between the calls
	{
		info->stdout = dup(STDOUT_FILENO);
		info->stdin = dup(STDIN_FILENO);
	}
	else // at the end or exit
	{
		if (info->envp_array)
			free_array(info->envp_array);
		if (info->envp_list)
			ft_clear_list(&(info->envp_list));
	}
	info->token_list = NULL;
	info->ast_tree = NULL;
}

char **ft_allocate_env(char **env)
{
    int i = 0;
    char **env_array;

    if (!env || !(*env))
        return (NULL);

    while (env[i])
        i++;
    env_array = malloc(sizeof(char *) * (i + 1));
    if (!env_array)
        return (NULL);
    i = 0;
    while (env[i])
    {
        env_array[i] = ft_strdup(env[i]);
        if (!env_array[i]) // Handle strdup failure
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

char **create_non_existing_env(void)
{
	char **new_env;

	new_env = malloc(sizeof(char *) * 4);
	if (!new_env)
	{
		perror("malloc failed in create_non_existing_env");
    	exit(EXIT_FAILURE);
	}
	char	buf[1024];
	if (getcwd(buf, sizeof(buf)) == NULL) // for oldpwd
		return NULL;
	new_env[0] = ft_strjoin("PWD=", buf);
	new_env[1] = ft_strdup("SHLVL=1");
	new_env[2] = ft_strdup("OLDPWD");
	new_env[3] = NULL;
	return(new_env);	
}


void	initialize(t_info *info, char **env)
{
	info->buffer = NULL;
	info->token_list = NULL;
	info->ast_tree = NULL;
	info->envp_array = ft_allocate_env(env);
	info->envp_list = NULL;
	info->i = 0;
	info->export_tmp = NULL;
	info->stdout = dup(STDOUT_FILENO);
	info->stdin = dup(STDIN_FILENO);
	if (info->stdout == -1 || info->stdin == -1) {
    	perror("dup failed");
    	exit(EXIT_FAILURE);
	}
	if (!info->envp_array)
	{
		info->envp_array = create_non_existing_env();
		env_to_list(info, 0);
	}
	else if (info->envp_array)
	{		
		env_to_list(info, 1);
	}
	// if (info->envp_list)
	// 	printf("loll:info->envp_list[0]: %s\n", info->envp_list->env);
	
	// f->last_arg = "empty";
	// signal(SIGINT, handle_signal);
	// signal(SIGQUIT, SIG_IGN);
}

int	ft_is(int c, char *str)
{
	if (ft_strcmp(str, "alnum") == 0)
	{
		return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A'
				&& c <= 'Z'));
	}
	else if (ft_strcmp(str, "space") == 0)
		return (c == 32 || (c >= 9 && c <= 13));
	else if (ft_strcmp(str, "quote") == 0)
		return (c == 39 || c == 34);
	else if (ft_strcmp(str, "op") == 0)
		return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
	else if (ft_strcmp(str, "operator") == 0)
		return (c == '|' || c == '>' || c == '<' || c == '&');
	else if (ft_strcmp(str, "brackets") == 0)
		return (c == '(' || c == ')');
	return (0);
}


int our_static(char *str, int set)
{
	static int exit_status = 0;

	if (ft_strcmp(str, "exit status") == 0)
	{
		if (set != -1)
		{
			exit_status = set;
		}
		return (exit_status);
	}
	return (0);
}



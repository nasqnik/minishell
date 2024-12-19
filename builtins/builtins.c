/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:48:36 by meid              #+#    #+#             */
/*   Updated: 2024/12/19 16:48:42 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_echo(char **args, int i)
{
    int line_flag = 0;
    int fd = 1;
    if (args[i] && ft_strcmp(args[i], "-n") == 0)
    {
        line_flag = 1;
        i++;
        if (args[i] && ft_strcmp(args[i], " ") == 0)
            i++;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], fd);
        i++;
    }
    if (line_flag == 0)
        ft_putstr_fd("\n", fd);
}

void ft_cd(t_first *f, char **args, int i)
{
    int fd = 1;
    char *str = NULL;
    char *sub = NULL;
    if (!(args[i]))
        return ;
    if (args[i][0] == '~')
    {
        
        char *home = search_in_env(f, "HOME");
        sub = ft_substr(args[i], 1, ft_strlen(args[i]) - 1);
        str = ft_strjoin(home ,sub);
        free(sub);
    }
    else
        str = args[i];
    i++;
    if (chdir(str))
    {
        ft_putstr_fd("\033[31mcd: no such file or directory: \033[00m", fd);
        ft_putstr_fd(str, fd);
        ft_putchar_fd('\n', fd);
        return ;      
    }
    free(str);
    if (args[i])
    {
        ft_putstr_fd("\033[31mcd: string not in pwd: \033[00m", fd);
        ft_putstr_fd(args[i - 1], fd);
        ft_putchar_fd('\n', fd);
        return ;
    }
    char buf[1024];
    if (getcwd(buf, sizeof(buf)) == NULL)
        return ;
    t_list *tmp = f->envp_list; 
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

void ft_export(t_first *f, char **args, int i)
{
    int fd = 1;
    char *search_for = NULL;
    char *value = NULL;
    int j = 0;
    int value_start = 0;
    t_list *tmp = NULL;
    char *the_str = NULL;
    char *tmpo = NULL;
    int flag = 0;
    while(args[i])
    {   
        if (invalid_identifier(args[i], 1))
        {
            if (invalid_identifier(args[i], 1) == 2)
                ft_putstr_fd("\033[31mzsh: no matches found: \033[00m", fd);
            else
                ft_putstr_fd("\033[31mexport: not an identifier: \033[00m", fd);
            ft_putstr_fd(args[i], fd);
            ft_putchar_fd('\n', fd);
        }
        else if (ft_strcmp(args[i], " ") != 0 && ft_strfind(args[i], '=') == 1)
        {
            j = 0;
            while(args[i][j] != '=')
                j++;
            value_start = j;
            search_for = ft_substr(args[i], 0, j);
            while (args[i][j])
                j++;
            value = ft_substr(args[i], value_start + 1, j - 1 - value_start);
            tmp = f->envp_list;
            while (tmp)
            {
                if (ft_strcmp(tmp->key, search_for) == 0)
                {
                    free(search_for);
                    free(tmp->value);
                    tmp->value = value;
                    flag = 1;
                }
                tmp = tmp->next;
            }
            if (flag == 0)
            {
                tmpo = ft_strjoin(search_for, "=");
                free(search_for);
                the_str = ft_strjoin(tmpo, value);
                free(value);
                free(tmpo);
                env_lstadd_back(&f->envp_list, env_lstnew(the_str));
                free(the_str);
            }   
        }
        i++;
    }
}

void ft_unset(t_first *f, char **args, int i)
{
    t_list *tmp = NULL;
    t_list *tmp1 = NULL;
    int fd = 1;
    while(args[i])
    {   
        if (invalid_identifier(args[i], 2))
        {
            ft_putstr_fd("\033[31zsh: no matches foundl: \033[00m", fd);
            ft_putstr_fd(args[i], fd);
            ft_putchar_fd('\n', fd);
        }
        else if (ft_strcmp(args[i], " ") != 0)
        {
            tmp = f->envp_list;
            while (tmp)
            {
                if (tmp->next && ft_strcmp(tmp->next->key, args[i]) == 0)
                {
                    if (tmp->next->next)
                        tmp1 = tmp->next->next;
                    free (tmp->next->env);
                    free (tmp->next->value);
                    free (tmp->next->key);
                    tmp->next = tmp1;
                }
                tmp = tmp->next;
            }
        }
        
        i++;
    }
}

void ft_env(t_first *f,char **args, int i)
{
    if (args[i] != NULL) // we should not handell more than env alone
        return ;
    i = 0;
    int fd = 1;
    t_list *tmp = f->envp_list;
    while (tmp)
    {
        ft_putstr_fd(tmp->key, fd);
        ft_putchar_fd('=', fd);
        ft_putstr_fd(tmp->value, fd);
        ft_putchar_fd('\n', fd);
        tmp = tmp->next;
    }
}

void ft_exit(t_first *f, char **args, int i)
{
    (void)args;
    // cd: no such file or directory:;
    
    int fd = 1;
    int j = 0;
    int exit_code = 0;
    ft_putstr_fd("exit\n", 1);
    while (args[i])
    {
        if (i > 1)
        {
            ft_putstr_fd("minishell: exit: ", fd);
            ft_putstr_fd("\033[31mtoo many arguments\033[00m", fd);
            ft_putchar_fd('\n', fd);
            return ;
        }
        while (args[i][j])
        {
            if (!(args[i][j] >= '0' && args[i][j] <= '9'))
                {
                    ft_putstr_fd("minishell: exit: ", fd);
                    ft_putstr_fd(args[1], fd);
                    ft_putstr_fd("\033[31m: numeric argument required\033[00m", fd);
                    ft_putchar_fd('\n', fd);
                    return ;
                }
            j++;
        }
        exit_code = ft_atoi(args[i]);
        i++;
    }
    ft_clear_tokens(&(f->token_list));
	ft_clear_tree(f->ast_tree);
    ft_clear_list(&(f->envp_list));
    exit(exit_code);
}

void ft_pwd(char **args, int i)
{
    if (args[i] != NULL) // we should not handell more than env alone
        return ;
    i = 0;
    int fd = 1;
    char buf[1024];
    if (getcwd(buf, sizeof(buf)) == NULL)
        return ;
    ft_putstr_fd(buf , fd);
    ft_putchar_fd('\n', fd);
}

void ft_meow(char **args, int i)
{
    int fd = 1;
    int j = 0;
    int count = 1;
    while (args[i])
    {
        if (i > 1)
        {
            ft_putstr_fd("minishell: meow: ", fd);
            ft_putstr_fd("\033[31mtoo many arguments\033[00m", fd);
            ft_putchar_fd('\n', fd);
            return ;
        }
        while (args[i][j])
        {
            if (!(args[i][j] >= '0' && args[i][j] <= '9'))
                {
                    ft_putstr_fd("minishell: meow: ", fd);
                    ft_putstr_fd(args[1], fd);
                    ft_putstr_fd("\033[31m: numeric argument required\033[00m", fd);
                    ft_putchar_fd('\n', fd);
                    return ;
                }
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
}
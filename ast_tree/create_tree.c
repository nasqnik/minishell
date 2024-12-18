/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:06:15 by meid              #+#    #+#             */
/*   Updated: 2024/12/18 15:32:12 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void fill_in_args(t_tree *node, t_tokens **tokens)
{
    int i = 0;
    t_tokens *tmp = (*tokens);
    
    while (tmp && ((tmp->type == COMMAND 
            || tmp->type == ARGUMENT
            || tmp->type == FLAG || tmp->type == FILENAME
            || tmp->type == DELIMITER) 
            || (tmp->type >= REDIRECT_IN && tmp->type <= HEREDOC)))
    {
        if (tmp->type == COMMAND 
            || tmp->type == ARGUMENT || 
                tmp->type == FLAG)
            i++;
        printf("loop : 4\n");
        tmp = tmp->next;
    }
    printf("i: %i\n", i);
    if (i != 0)
    {
        node->args = malloc(sizeof(char *) * (i + 1));
        i = 0;
         tmp = (*tokens);
    while (tmp && ((tmp->type == COMMAND 
            || tmp->type == ARGUMENT
            || tmp->type == FLAG || tmp->type == FILENAME
            || tmp->type == DELIMITER) 
            || (tmp->type >= REDIRECT_IN && tmp->type <= HEREDOC)))
        {
            printf("loop : 5\n");
            if (tmp->type == COMMAND 
            || tmp->type == ARGUMENT || 
                tmp->type == FLAG)
            {
                node->args[i] = ft_strdup(tmp->data);
                i++;    
            }
            tmp = tmp->next;
        }
            node->args[i] = NULL;
    }
}
// echo hi | grep "lol"

t_tree *create_ast_tree(t_tokens **token)
{
    return create_ast_and(token);
}

t_tree *create_ast_and(t_tokens **tokens)
{
    printf("create_ast_logic\n");
    t_tree *left = create_ast_or(tokens);
    printf("i chaneged my place\n");
    if (!*tokens)
        printf("i am lost: 1\n");
    while (*tokens && (*tokens)->type == LOGIC_AND)
    {
        printf("loop : 1\n");
            printf("if : 1\n");
            t_tree *node = malloc(sizeof(t_tree));
            node->type = (*tokens)->type;
            node->file = NULL;
            node->args = NULL;
            *tokens = (*tokens)->next;
            
            node->left = left;
            node->right = create_ast_or(tokens);
            

            left = node;
    }
    return left;
}

t_tree *create_ast_or(t_tokens **tokens)
{
    printf("create_ast_logic\n");
    t_tree *left = create_ast_pipe(tokens);
    printf("i chaneged my place\n");
    if (!*tokens)
        printf("i am lost: 1\n");
    while (*tokens && (*tokens)->type == LOGIC_OR)
    {
        printf("loop : 1\n");
            printf("if : 1\n");
            t_tree *node = malloc(sizeof(t_tree));
            node->type = (*tokens)->type;
            node->file = NULL;
            node->args = NULL;
            *tokens = (*tokens)->next;
            
            node->left = left;
            node->right = create_ast_pipe(tokens);
            

            left = node;
    }
    return left;
}

t_tree *create_ast_pipe(t_tokens **tokens)
{
    printf("create_ast_pipe\n");
    t_tree *left = create_ast_redirections(tokens);
    if (!*tokens)
        printf("i am lost: 2\n");
    while (*tokens && (*tokens)->type == PIPE)
    {
        printf("if : 2\n");
        t_tree *node = malloc(sizeof(t_tree));
        node->type = PIPE;
        node->file = NULL;
        node->args = NULL;
        *tokens = (*tokens)->next;

        node->left = left;
        node->right = create_ast_redirections(tokens);

        left = node; 
    }
    return left;
}

t_tree *create_ast_redirections(t_tokens **tokens)
{
    printf("create_ast_redirections\n");
    t_tree *cmd = create_ast_command(tokens);
    if (!*tokens)
        printf("i am lost: 3\n");
    while (*tokens && ((*tokens)->type >= REDIRECT_IN && (*tokens)->type <= HEREDOC))
    {
        printf("loop : 3\n");
        t_tree *node = malloc(sizeof(t_tree));
        node->type = (*tokens)->type;
        node->args = NULL;
        *tokens = (*tokens)->next;

        if (*tokens && (*tokens)->type == FILENAME)
        {
            node->file = ft_strdup((*tokens)->data);
            *tokens = (*tokens)->next;
        }
        if (*tokens)
            printf("1 current token type: %d\n", (*tokens)->type);
        while ((*tokens) && ((*tokens)->type == COMMAND 
            || (*tokens)->type == ARGUMENT
            || (*tokens)->type == FLAG))
            *tokens = (*tokens)->next;
        node->right = NULL;
        node->left = cmd;
        cmd = node;
    }
    return cmd;
}
t_tree *create_ast_command(t_tokens **tokens)
{
    printf("create_ast_command\n");

    t_tree *node = malloc(sizeof(t_tree));
    
    node->type = COMMAND;
    fill_in_args(node, tokens);
    
    if (!*tokens)
        printf("i am lost: 4\n");
    while ((*tokens) && ((*tokens)->type == COMMAND 
            || (*tokens)->type == ARGUMENT || 
                (*tokens)->type == FLAG))
        (*tokens) = (*tokens)->next;
    if (*tokens)
        printf("2 current token type: %d\n", (*tokens)->type);
    node->file = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}


void print_ast(t_tree *node, int depth, char *flag)
{
    // printf("\033[95m start printing \033[00m\n");
    // printf("\033[95m i am almost in\033[00m\n");
    if (!node) return;
    // printf("\033[95m i am in \033[00m\n");

    printf("\n");
    for (int i = 0; i < depth; i++)
        printf("  ");

    printf("\033[95mflag :%s \033[00m\n", flag);
    printf("\033[95m Node type: %s\033[00m\n", token_type_to_string(node->type));
    printf("\033[95m depth: %d\033[00m\n", depth);
    if (node->type == COMMAND)
    {
        char **str = node->args;
        int j = 0;
        if (str[j])
        {
            printf("command: %s\n", str[j]);
            j++;
        }
        while (str[j])
        {
            printf("arg: %s\n", str[j]);
            j++;
        }
    }
    if (node->type >= REDIRECT_IN && node->type <= HEREDOC)
        printf("file %s\n", node->file);
    // else
    //     printf("data %s\n", node->data);
    
    print_ast(node->left, depth + 1, "left");
    print_ast(node->right, depth + 1, "right");
}

// hi i sd > lo | po > lp | lol
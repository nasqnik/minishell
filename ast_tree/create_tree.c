/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:06:15 by meid              #+#    #+#             */
/*   Updated: 2025/01/08 16:55:10 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void fill_in_args(t_tree *node, t_tokens **tokens)
{
    int i = 0;
    if (!(*tokens))
        return ;
    t_tokens *tmp = (*tokens);
    
    while (tmp && ((tmp->type == COMMAND 
            || tmp->type == ARGUMENT
            || tmp->type == FILENAME
            || tmp->type == DELIMITER) 
            || (tmp->type >= REDIRECT_IN && tmp->type <= HEREDOC)))
    {
        if (tmp->type == COMMAND 
            || tmp->type == ARGUMENT)
            i++;
        tmp = tmp->next;
    }
    if (i != 0)
    {
        node->args = malloc(sizeof(char *) * (i + 1));
        if (!node->args) return ;
        i = 0;
         tmp = (*tokens);
    while (tmp && ((tmp->type == COMMAND 
            || tmp->type == ARGUMENT
            || tmp->type == FILENAME
            || tmp->type == DELIMITER) 
            || (tmp->type >= REDIRECT_IN && tmp->type <= HEREDOC)))
        {
            if (tmp->type == COMMAND 
            || tmp->type == ARGUMENT)
            {
                node->args[i] = ft_strdup(tmp->data);
                i++;    
            }
            tmp = tmp->next;
        }
            node->args[i] = NULL;
    }
}

t_tree *create_ast_tree(t_tokens **token)
{
    // printf("tree\n");
    return create_ast_and(token);
}

t_tree *create_ast_and(t_tokens **tokens)
{
    t_tree *node;
    t_tree *left;

    // printf("&& 1\n");
    left = create_ast_or(tokens);
    if (!(*tokens) || (*tokens)->type != LOGIC_AND)
        return left;
    // printf("&& 2\n");

    node = malloc(sizeof(t_tree));
    if (!node)
        return NULL;
    node->type = LOGIC_AND;
    node->file = NULL;
    node->args = NULL;
    node->left = left;
    node->fd = -1;
    *tokens = (*tokens)->next;
    node->right = create_ast_and(tokens);
    return node;
}

t_tree *create_ast_or(t_tokens **tokens)
{
    t_tree *node;
    t_tree *left;

    // printf("|| 1\n");
    left = create_ast_pipe(tokens);
    // printf("|| 2\n");
    if (!(*tokens) || (*tokens)->type != LOGIC_OR)
        return left;

    node = malloc(sizeof(t_tree));
    if (!node)
        return NULL;
    node->type = LOGIC_OR;
    node->file = NULL;
    node->args = NULL;
    node->left = left;
    node->fd = -1;
    *tokens = (*tokens)->next;
    node->right = create_ast_or(tokens);
    return node;
}

t_tree *create_ast_pipe(t_tokens **tokens)
{
    t_tree *node;
    t_tree *left;
    // printf("| 1\n");
    left = create_ast_redirections(tokens); // create_ast_heredoc(tokens);
    // printf("hiiiii\n");
    if (!(*tokens) || (*tokens)->type != PIPE)
        return left;
    // printf("| 2\n");
    node = malloc(sizeof(t_tree));
    if (!node)
        return NULL;
    node->type = PIPE;
    node->file = NULL;
    node->args = NULL;
    node->left = left;
    node->fd = -1;
    *tokens = (*tokens)->next;
    node->right = create_ast_pipe(tokens);
    return node;
}

t_tree *create_ast_redirections(t_tokens **tokens)
{
    t_tree *cmd;
    t_tree *node;
    t_tree *tmp;
    t_tree *first;
    
    int i = 0;
    int flag = 0;
    tmp = NULL;
    first = NULL;
    // printf("<. _ .> 1\n");
    cmd = create_ast_command(tokens);
    while (*tokens && ((*tokens)->type >= REDIRECT_IN && (*tokens)->type <= HEREDOC))
    {
        // printf("<. _ .> 2\n");
        flag = 1;
        node = malloc(sizeof(t_tree));
        if (!node) return NULL;
        node->type = (*tokens)->type;
        node->args = NULL;
        *tokens = (*tokens)->next;
        if (*tokens && ((*tokens)->type == FILENAME || (*tokens)->type == DELIMITER))
            node->file = ft_strdup((*tokens)->data);
        if (tmp)
            tmp->left = node;
        else
        {
            first = node;
            node->left = NULL;
        }
        tmp = node;
        if (*tokens && ((*tokens)->type == FILENAME || (*tokens)->type == DELIMITER))
        {
            *tokens = (*tokens)->next;
        }
        while ((*tokens) && ((*tokens)->type == COMMAND 
            || (*tokens)->type == ARGUMENT))
        {
            if ((*tokens)->type == COMMAND && !cmd)
            {
                cmd = create_ast_command(tokens);
                continue;
            }
            *tokens = (*tokens)->next;
        }
        node->right = NULL;
        node->fd = -1;
        i++;
    }
    if (flag == 1)
        node->left = cmd;
    if (i == 0)
        return (cmd);
    else
        return (first);
}


t_tree *create_ast_command(t_tokens **tokens)
{
    t_tree *node;

    if (!tokens || !(*tokens))
        return NULL;
    if ((*tokens)->type == BRACKET || (*tokens)->type == COMMAND)
    {
        node = malloc(sizeof(t_tree));
        if (!node)
            return NULL;
        if ((*tokens)->type == BRACKET)
        {
            node->type = BRACKET;
            node->file = ft_strdup((*tokens)->data);
            node->args = NULL;
            (*tokens) = (*tokens)->next;
        }
        else if ((*tokens)->type == COMMAND)
        {
            node->type = COMMAND;
            fill_in_args(node, tokens);
            while ((*tokens) && ((*tokens)->type == COMMAND || (*tokens)->type == ARGUMENT))
                (*tokens) = (*tokens)->next;
            node->file = NULL;
        }
        node->fd = -1;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    return NULL; 
    
    // if (*(tokens) == NULL)
    //     return NULL;
    // node = malloc(sizeof(t_tree));
    // if (!node)
    //     return NULL;
    // // printf("%s\n", token_type_to_string((*tokens)->type));
    // if ((*tokens) && ((*tokens)->type == BRACKET))
    // {
    //     //  printf(" BRACKET 1\n");
    //     node->type = BRACKET;
    //     node->file = ft_strdup((*tokens)->data);
    //     node->args = NULL;
    //     (*tokens) = (*tokens)->next;
    // }
    // else
    // {
    //     // printf(" COMMAND 2\n");
    //     node->type = COMMAND;
    //     fill_in_args(node, tokens);
    //     while ((*tokens) && ((*tokens)->type == COMMAND 
    //         || (*tokens)->type == ARGUMENT))
    //     (*tokens) = (*tokens)->next;
    //     node->file = NULL;
    // }
    // node->left = NULL;
    // node->right = NULL;
    // return (node);
}


void print_ast(t_tree *node, int depth, char *flag)
{
    // printf("\033[95m start printing \033[00m\n");
    // printf("\033[95m i am almost in\033[00m\n");
    if (!node) 
    {
        printf("there is no nodes\n");
        return;
    }
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
            printf("arg: |%s|\n", str[j]);
            j++;
        }
    }
    if (node->type >= REDIRECT_IN && node->type <= HEREDOC)
    {
        printf("file %s\n", node->file);
    }
    if (node->type == BRACKET)
    {   
        printf("bracket %s\n", node->file);
    }
    
    // else
    //     printf("data %s\n", node->data);
    
    print_ast(node->left, depth + 1, "left");
    print_ast(node->right, depth + 1, "right");
}
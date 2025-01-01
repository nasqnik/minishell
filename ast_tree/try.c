#include "minishell.h"

t_tree *create_ast_redirections(t_tokens **tokens)
{
    t_tree *cmd;
    t_tree *node;
    t_tree *tmp;
    
    if ((*tokens))
        printf("<> 1: %s:::%s\n", (*tokens)->data, token_type_to_string((*tokens)->type));
    cmd = create_ast_command(tokens);
    if ((*tokens))
        printf("<> 2: %s:::%s\n", (*tokens)->data, token_type_to_string((*tokens)->type));
    int i = 0;
    int flag = 0;
    tmp = NULL;
    while (*tokens && ((*tokens)->type >= REDIRECT_IN && (*tokens)->type <= HEREDOC))
    {
        flag = 1;
        // if ((*tokens)->type == REDIRECT_OUT)
        //     printf("\n----------%d------------lol\n", i);
        printf("<> 2: %s:::%s:::%i\n", (*tokens)->data, token_type_to_string((*tokens)->type), i);
        node = malloc(sizeof(t_tree));
        if (!node) return NULL;
        node->type = (*tokens)->type;
        node->file = NULL;
        node->args = NULL;
        *tokens = (*tokens)->next;

        if (*tokens && ((*tokens)->type == FILENAME || (*tokens)->type == DELIMITER))
            node->file = ft_strdup((*tokens)->data);
        node->right = NULL;
        if (tmp)
            tmp->left = node;
        else
            node->left = NULL;
        tmp = node;
        if (*tokens && ((*tokens)->type == FILENAME || (*tokens)->type == DELIMITER))
            *tokens = (*tokens)->next;
        while ((*tokens) && ((*tokens)->type == COMMAND 
            || (*tokens)->type == ARGUMENT))
            *tokens = (*tokens)->next;
        i++;
    }
    if (flag == 1)
        node->left = cmd;
    return (cmd);
}



// t_tree *create_ast_pipe(t_tokens **tokens)
// {
//     t_tree *left;
//     t_tree *node;
//     // t_tree *tmp;
//     // t_tree *first;
//     static int i = 0;
    
//     // tmp = NULL;
//     // first = NULL;
//     if ((*tokens))
//         printf("| 1: %s:::%s\n", (*tokens)->data, token_type_to_string((*tokens)->type));
//     left = create_ast_redirections(tokens);  
//     if ((*tokens))
//         printf("| 2: %s:::%s\n", (*tokens)->data, token_type_to_string((*tokens)->type));
//     while (*tokens && (*tokens)->type == PIPE)
//     {
//         node = malloc(sizeof(t_tree));
//         if (!node) return NULL;
//         node->type = PIPE;
//         node->file = NULL;
//         node->args = NULL;
//         if (i == 0)
//             node->left = left;
//         *tokens = (*tokens)->next;
//         if (i != 0)
//             node->left = create_ast_redirections(tokens);
//         printf("%d:   %s:::%s\n", i, (*tokens)->data, token_type_to_string((*tokens)->type));
//         i++;
//         node->right = create_ast_pipe(tokens);
//     }
//     if (i == 0)
//         return (left);
//     else
//         return (node);
// }
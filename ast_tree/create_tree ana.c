/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree ana.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:06:15 by meid              #+#    #+#             */
/*   Updated: 2024/12/18 08:22:45 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int 

// void	create_tree(t_tokens *token)
// {
//     t_tree *ast_node;
//     t_tokens *start = token;
//     t_tokens *head;

//     while (token != NULL)
//     {
//         if (token->next)
//         {
//             if (token->next->type == LOGIC_AND || token->next->type == LOGIC_OR)
//             {
//                 head = token->next;
//                 token->next = NULL;
//                 // ast_node = malloc(sizeof(t_tree));
//                 // ast_node->data = token->data;
//                 // ast_node->left = ;
//                 // if (token->next)
//                 //     ast_node->right = token->next;
//             }
            
//         }

//     }
// }

// void	create_tree(t_tokens *token)
// {
//     t_tree *ast_node;
//     t_tokens *start = token;
//     t_tokens *head;

//     while (token != NULL)
//     {
//         if (token->next)
//         {
//             if (token->next->type == LOGIC_AND || token->next->type == LOGIC_OR)
//                 break ;
//         }
//         token = token->next;
//     }
//     head = token->next;
//                 token->next = NULL;
//                 // ast_node = malloc(sizeof(t_tree));
//                 // ast_node->data = token->data;
//                 // ast_node->left = ;
//                 // if (token->next)
//                 //     ast_node->right = token->next;
// }


// t_tree *create_ast_tree(t_tokens **tokens)
// {
//     return create_ast_logic(tokens);
// }

// t_tree *create_ast_logic(t_tokens **tokens)
// {
//     t_tree *left = create_ast_pipe(tokens);
    
//     while (*tokens && ((*tokens)->type == LOGIC_AND || (*tokens)->type == LOGIC_OR))
//     {
//         t_tree *node = malloc(sizeof(t_tree));
//         node->type = LOGIC_AND;
//         *tokens = (*tokens)->next;
        
//         node->left = left;
//         node->right = create_ast_pipe(tokens);

//         left = node; 
//     }
//     return left;
// }

// t_tree *create_ast_pipe(t_tokens **tokens)
// {
//     t_tree *left = create_ast_redirections(tokens);

//     while (*tokens && (*tokens)->type == PIPE)
//     {
//         t_tree *node = malloc(sizeof(t_tree));
//         node->type = PIPE;
//         *tokens = (*tokens)->next;

//         node->left = left;
//         node->right = create_ast_redirections(tokens);

//         left = node; 
//     }
//     return left;
// }

// t_tree *create_ast_redirections(t_tokens **tokens)
// {
//     t_tree *cmd = create_ast_command(tokens);

//     while (*tokens && ((*tokens)->type >= REDIRECT_IN && (*tokens)->type <= HEREDOC))
//     {
//         t_tree *node = malloc(sizeof(t_tree));
//         node->type = REDIRECT_APPEND;
//         *tokens = (*tokens)->next;

//         if (*tokens && (*tokens)->type == FILENAME)
//         {
//             node->file = ft_strdup((*tokens)->data);
//             *tokens = (*tokens)->next;
//         }
//         node->left = cmd;
//         cmd = node;
//     }
//     return cmd;
// }

// t_tree *create_ast_command(t_tokens **tokens)
// {
//     t_tree *node = malloc(sizeof(t_tree));
//     node->type = COMMAND;
//     node->args = NULL;

//     while (*tokens && ((*tokens)->type == WORD 
//             || (*tokens)->type == ENV_VAR || 
//                 (*tokens)->type == FLAG))
//     {
//         // append_to_args(node->args, (*tokens)->data);
//         *tokens = (*tokens)->next;
//     }
//     node->left = NULL;
//     node->right = NULL;
//     return node;
// }


// void append_to_args(char ***args, char *new_arg)
// {
//     int i;
//     i = 0;
//     if (*args)
//     {
//         while (*(args[i]))
//             i++;
//     }
    

    
    
// }

// void print_ast(t_tree *node, int depth)
// {
//     	printf("\033[95m start printing \033[00m\n");
//     printf("\033[95m i am almost in\033[00m\n");
//     if (!node) return;
//     printf("\033[95m i am in \033[00m\n");

//     printf("\n");
//     for (int i = 0; i < depth; i++)
//         printf("  ");


//     printf("\033[95m Node type: %s\033[00m\n", token_type_to_string(node->type));
//     printf("depth: %d\n", depth);
    
//     print_ast(node->left, depth + 1);
//     printf("\033[95m pov\033[00m\n");
//     print_ast(node->right, depth + 1);
// }
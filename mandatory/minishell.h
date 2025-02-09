/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:13:28 by meid              #+#    #+#             */
/*   Updated: 2025/02/05 18:41:32 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "assert.h"
# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

int						rl_replace_line(const char *text, int clear_undo);

# define TRUE 1
# define FALSE 0

# ifndef ARG_MAX
#  define ARG_MAX 262144
# endif

typedef enum e_token_type
{
	WORD,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HEREDOC,
	PIPE,
	LOGIC_AND,
	LOGIC_OR,
	BRACKET,
	COMMAND,
	ARGUMENT,
	FILENAME,
	DELIMITER
}						t_token_type;

typedef struct s_tokens
{
	char				*data;
	int					type;
	int					fd;
	struct s_tokens		*next;
}						t_tokens;

typedef struct s_env
{
	char				*env;
	char				*key;
	char				*value;
	int					flag;
	struct s_env		*next;
}						t_env;

typedef struct s_tree
{
	int					type;
	char				*file;
	char				**args;
	int					fd;
	struct s_tree		*left;
	struct s_tree		*right;
}						t_tree;

typedef struct s_subtree
{
	t_tree				*tree;
	struct s_subtree	*next;
}						t_subtree;

typedef struct s_info
{
	t_env				*envp_list;
	t_env				*export_tmp;
	char				*buffer;
	t_tokens			*token_list;
	t_tree				*ast_tree;
	char				**envp_array;
	t_subtree			*subtree_lest;
	int					i;
	int					stdout;
	int					stdin;
	char				*temporary;
	char				*pwd;
}						t_info;

//---------------------------main_functions--------------------------------//

//-----------minishell.c-----------//
void					minishell(t_info *info);

//-----------initialize.c-----------//
void					initialize(t_info *info, char **env);

//-----------env_utils.c-----------//
t_env					*env_lstnew(char *env_var, int flag);
void					env_lstadd_back(t_env **lst, t_env *neww);

//-----------update_envp_array.c-----------//
void					update_envp_array(t_info *info, t_env *env_cur,
							int counter);
int						ft_lstsize(t_env *lst);

//-----------print_error.c-----------//
void					handle_error(t_info *info, char *msg, int what_am_i,
							int flag);
void					print_the_error(t_info *info, char *args, int flag,
							int fd);
const char				*token_type_to_string(t_token_type type);
void					print_list(t_tokens *list);
void					print_ast(t_tree *node, int depth, char *flag);
void					safe_free(void **ptr);
void					bye_bey(t_info *info, char flag);

//-----------signals.c-----------//
void					castom_signals(void);
void					handle_sig(int sig);
void					disable_echoctl(void);
//----------------------------------------------- to delete
void					castom_ing(void);
void					castom_dfl(void);
void					handle_heredoc_sig(int sig);

//-----------utils.c-----------//
void					free_and_set_null(t_info *info, int flag);
int						ft_is(int c, char *str);
int						our_static(char *str, int set);

//-----------initialize_utils.c-----------//
char					*add_quotes(char *str);
char					**ft_allocate_env(char **env);
char					**create_non_existing_env(void);
void					env_to_list(t_info *info, int flag);
void					ft_clear_list(t_env **lst);

//--------------------------------parsing------------------------------------//

//-----------parsing.c-----------//

int						parsing(t_info *info);
int						lexer(t_info *info, char *str);

//----------rename_tokens.c-----------//
int						rename_tokens(t_info *info);
t_tokens				*tokens_after_redirect(t_info *info, t_tokens *cursor,
							int *j);

//-----------token_list.c-----------//
t_tokens				*ft_lstlast_token(t_tokens *lst);
t_tokens				*ft_create_token(t_info *info, int len, int type,
							char *str);
void					add_back_token(t_tokens **lst, t_tokens *neww);
void					ft_clear_tokens(t_tokens **token_list);

//-----------token_types.c-----------//
t_tokens				*operators_token(char *str, t_info *info, int len);
t_tokens				*bracket_token(char *str, t_info *info, int len);
t_tokens				*word_token(char *str, t_info *info, int len);

//-----------verify_logic.c-----------//
int						print_error_from_return_value(t_info *info,
							int to_return, t_tokens *cursor);
int						verify_logic(t_info *info);

//-----------verify_logic02.c-----------//
int						control_operators(t_tokens *cursor, int index);
int						redirection_operators(t_tokens *cursor);
int						subshell_rules(t_tokens *cursor, int flag);

//---------------------------------execution----------------------------------//

//-----------exec_logic.c-----------//
void					execution(t_info *info, t_tree *tree);

//-----------exec_pipe.c-----------//
void					execution_pipe(t_info *info, t_tree *tree);
pid_t					handle_left_pipe(t_info *info, t_tree *tree,
							int pipefd[2]);
pid_t					handle_right_pipe(t_info *info, t_tree *tree,
							int pipefd[2]);

//-----------exec_command.c-----------//
void					execute_command(t_info *info, t_tree *tree);

//-----------exec_binary_command.c-----------//
void					binary(t_info *info, t_tree *tree);
int						execute_binary(t_info *info, char *command,
							char **args);

//-----------exec_redirection.c-----------//
void					execution_redirection(t_info *info, t_tree *tree);
int						handle_redirect_in(t_info *info, t_tree *tree);
int						handle_redirect_out(t_info *info, t_tree *tree);
int						handle_redirect_append(t_info *info, t_tree *tree);
int						get_file(int read_from, t_tree *tree, t_info *info);

//-----------here_doc03.c-----------//
void					here_doc(t_info *info, t_tokens *list);

//-----------here_doc04.c-----------//
void					read_and_expand(t_info *info, int read_from, int fd,
							t_tree *tree);
int						here_docs_ahead(t_tokens *list);

//-----------subshell.c-----------//
void					subshell(t_info *info, t_tree *tree);
char					*ft_strtrim_sides(char *str);

//-----------utils.c-----------//
int						check_permissions(const char *file, int mode);
void					signals_exit_statue(int status);

//-------------------------------wildcard----------------------------------//

//-----------wildcard.c-----------//
int						is_matching_quote(char *wildcard, char *file, int *wc,
							int i);
int						wildcard(t_info *info, char **exp_res);
int						end_is_dot(char *str);

//-----------matchy.c-----------//
int						ft_matchy(char *file, char *wildcard, char *tmp_file,
							int lol);
int						ft_end_with(char *str, char *end);
int						ft_strat_with(char *str, char *start);
int						ft_mid_with(char *file, char *wildcard, int wc);

//-----------mid_part.c-----------//
int						ft_mid_with(char *file, char *wildcard, int wc);
//-----------end_part.c-----------//
char					*end_sub(char *wildcard, int *i, int *j);
int						special_strlen(const char *str);
int						finalcheck(char *file, char *wildcard);
//-----------start_part.c-----------//
char					*start_sub(char *wildcard, int *i, int *j);

//-----------utils.c-----------//
int						who_many_wildcard(char *str);
void					prossing_files(t_info *info, struct dirent *entry);
char					*clean_wildcard(const char *data);
int						ft_there_wildcard(char *str);

//----------------------------------builtins----------------------------------//

//-----------cd.c-----------//
int						ft_cd(t_info *info, char **args);

//-----------exit.c-----------//
int						ft_exit(t_info *info, char **args, int i, int j);
int						skip_and_set_sign(char **str, int *i, int *sign);

//-----------echo_pwd_env.c-----------//
int						ft_echo(char **args, int i);
int						ft_pwd(void);
int						ft_env(t_info *info, char **args, int i);

//-----------export_utils.c-----------//
int						handle_export_error(t_info *info, char *str);
void					print_export(t_info *info);
void					env_sort(t_info *info, t_env *envp_list);
void					new_env(t_info *info, char *search_for, char *value,
							int flagoooo);

//-----------export.c-----------//
int						ft_export(t_info *info, char **args, int i);

//-----------unset.c-----------//
int						ft_unset(t_info *info, char **args, int i);

//-----------utils.c-----------//
int						ft_meow(t_info *info, char **args, int i, int j);
int						invalid_identifier(char *str, int flag);
char					*search_in_env(t_info *info, char *key);

//-------------------------------expansions----------------------------------//

//-----------expand_command.c-----------//
void					expand_command(t_info *info, t_tree *tree);

//-----------expand_heredoc.c-----------//
char					*process_expansion_heredoc(char *arg, t_info *info,
							char **tmp_to_clean);

//-----------expand_redirection.c-----------//
int						expand_redirection(t_info *info, t_tree *tree);

//-----------expansions_dquotes.c-----------//
char					*handle_d_var_value(char *data, int pov[2],
							t_info *info);
char					*handle_d_variable(char *data, int pov[2], char *result,
							t_info *info);

//-----------expansions_tilde.c-----------//
char					*tilda_string(t_info *info, char *str, int pov[2],
							char *result);

//-----------expansions_utils.c-----------//
char					*append_remaining_data(char *data, int pov[2],
							char *result, int flag);
char					*clean_quotes(char *result);

//-----------expansions_var.c-----------//
char					*handle_variable(char *data, int pov[2], char *result,
							t_info *info);
char					*handle_var_value(char *data, int pov[2], t_info *info);
char					*get_var(char *data, int *i, t_env *envp_list);
char					*handle_exit_status(char *data, int pov[2]);

//-----------expand_var_heredoc.c-----------//
char					*handle_hd_var_value(char *data, int pov[2],
							t_info *info);
char					*handle_hd_variable(char *data, int pov[2],
							char *result, t_info *info);

//-----------expansions.c-----------//
char					*process_expansion(char *arg, t_info *info);
char					*expand_variables(char *str, int *pos, t_info *info);

//---------------------------------ast_tree-----------------------------------//

//-----------clear_tree.c-----------//
void					ft_clear_tree(t_tree *node);
void					ft_clear_subtrees(t_subtree **subtree_list);

void					add_subtree(t_info *info, t_tree *subtree);

//-----------create_tree.c-----------//
t_tree					*create_ast_tree(t_tokens **token);
t_tree					*create_ast_and(t_tokens **tokens);
t_tree					*create_ast_or(t_tokens **tokens);
t_tree					*create_ast_pipe(t_tokens **tokens);

//-----------tree_command.c-----------//
t_tree					*create_ast_command(t_tokens **tokens);

//-----------tree_redirections.c-----------//
t_tree					*create_ast_redirections(t_tokens **tokens);

void					free_array(char **array);

#endif
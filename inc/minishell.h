/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:58:59 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/29 13:57:39 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../llist/llist.h"
# include "../ntree/ntree.h"

/*	numeric const	*/
# define TRUE 1
# define FALSE 0
# define BAD_FD -1
# define NO_REDIR 0
# define REDIR_PB -3
# define MALLOC_FAIL -2
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define LAST_RETURN_STATUS 1023 // tmp const ; must be a var declared in main

/*	char const	*/
# define DELIM " \t<>&|()"
# define S_QUOTE '\''
# define D_QUOTE '\"'
# define PREFIX_EXPORT "declare -x "

/*	here_doc	*/
# define HD_PROMPT "here_doc > "
# define HD_START "/tmp/.here_doc"
# define HD_END ".txt"

/*	error msg	*/
# define ERR_SYNTAX "minishell: syntax error near unexpected token "
# define ERR_QUOTE "bad number of quotes "
# define ERR_PARENTHESE "unexpected EOF while looking for matching `)'"
# define ERR_PERMDEN "Permission denied"
# define ERR_NSFD "No such file or directory"
# define ERR_CNF "Command not found"
# define ERR_AMB_REDIR "ambiguous redirect"
# define ERR_ID_EXPORT "not a valid identifier"
# define ERR_TMA "too many arguments"
# define ERR_DUP_IN "minishell: infile dup2"
# define ERR_DUP_OUT "minishell: outfile dup2"
# define ERR_EXECVE "minishell: execve"
# define ERR_PIPE "minishell: pipe"
# define ERR_FORK "minishell: fork"

typedef enum e_type
{
	or,
	and,
	ppipe,
	great,
	less,
	dgreat,
	dless,
	compound,
	word,
	error,
	COMPLETE_COMMAND,
	COMPOUND_COMMAND,
	LOGICAL_EXPRESSION,
	PIPELINE,
	SIMPLE_COMMAND,
	CMD_NAME,
	CMD_ARG,
	CMD_PREFIX,
	CMD_SUFFIX,
	REDIRECTION,
	OPERATOR,
	FILENAME,
	AND,
	OR,
	HERE_DOC,
	HERE_END,
}	t_type;

typedef struct s_token
{
	t_type	type;
	void	*data;
}	t_token;

typedef struct s_cmd
{
	int				fd_in;
	int				fd_out;
	int				index;
	char			*name;
	char			*fullname;
	char			**args;
	int				exist;
	int				is_exec;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_info
{
	t_cmd			*cmds;
	t_cmd			*cmd_start;
	pid_t			last_pid;
	char			**envp;
	int				exit_code;
}	t_info;

typedef int (*t_f)(char **);
typedef int (*t_execute_ast_fun)(t_ntree *ast);

/*	parsing - lexing */
t_llist	*lsttok(const char *str);
void	lstreduce(t_llist	**llst);
t_llist	*tokenization(t_llist *llst);
t_llist	*type_token(t_llist	*token_list);
t_llist	*token_to_leaf(t_llist	*token_list);
int		check_syntax(t_llist *token_list);

/*	utils token	*/
int		is_str_op_p(const char *str);
int		is_str_cl_p(const char *str);
int		is_str_quote(const char *str);
int		is_str_operator(const char *str);
int		is_str_blank(const char *str);
t_llist	*new_llst_with_compound(t_llist *start);

/*	lsttok_utils	*/
int		isdelim(int c);
char	*strfind(const char *str, int c);
char	*strfind_not(const char *str, int c);
char	*strfind_if(const char *str, int (*f)(int));

/* create_command_utils*/
t_ntree	*create_cmd_name(t_llist *leaf);
t_llist	*find_cmd_name(t_llist	*leaf_list);

/*	token_type_predicate	*/
int		is_str_or(const char *str);
int		is_str_and(const char *str);
int		is_str_pipe(const char *str);
int		is_str_great(const char *str);
int		is_str_less(const char *str);
int		is_str_dgreat(const char *str);
int		is_str_dless(const char *str);
int		is_str_compound(const char *str);
int		is_str_word(const char *str);

/*	check_syntax_utils*/
int		is_token_word(t_token *token);
int		is_token_redirection_operator(t_token *token);
int		is_token_pipe(t_token *token);
int		is_token_logical_operator(t_token *token);
int		is_token_operator(t_token *token);

/*	ast */
t_ntree	*ast_new(t_type type, void *data, t_llist *children);
void	ast_free(t_ntree *ast);
void	ast_print(t_ntree *ast);
int		is_node_inside(t_ntree *node, t_type types[], size_t n);
int		is_node_equal(t_ntree *node, t_type search_type);
t_llist	*create_child(t_llist	*leaf, t_ntree *(*create)(t_llist *));
t_ntree	*create_complete_command(t_llist	*token_list);
t_ntree	*create_compound_command(t_llist *leaf_list);
t_ntree	*create_pipeline(t_llist *token_list);
t_ntree	*create_logical_expression(t_llist	*token_list);
t_ntree	*create_command(t_llist	*token_list);
t_llist	*create_suffixes(t_llist *leaf_list);
t_llist	*create_prefixes(t_llist *leaf_list);
t_ntree	*create_redirection(t_llist	*leaf_list);
t_ntree	*create_classic_redirection(t_llist *leaf_list);
t_ntree	*create_here_doc(t_llist *leaf_list);
int		is_node_word(t_ntree	*node);
int		is_node_logical_operator(t_ntree	*node);
int		is_node_pipe(t_ntree	*node);
int		is_node_redirection(t_ntree	*node);
int		is_node_compound(t_ntree	*node);

/* t_cmd	*/
int		get_fd_in(t_ntree *simple_command_node);
int		get_fd_out(t_ntree *simple_command_node);
char	*get_command_name(t_ntree *simple_command_node);
char	**get_command_args(t_ntree *simple_command_node, char *command_name);
void	cmd_add_back(t_cmd **cmds, t_cmd *new_cmd);
t_cmd	*cmd_new(t_ntree *simple_command_node, int index, char **envp);
t_cmd	*cmd_last(t_cmd *cmds);
void	cmd_clear(t_cmd **cmds);

/*	utils general	*/
char	*strjoin(const char *s1, const char *s2);
char	*strjoin2(const char *s1, const char *s2);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);
char	*strjoin3(char const *s1, char const *s2, char const *s3);
char	*str_one_char_join(char *str, char c);
void	*ft_realloc(void *ptr, size_t size);
char	**charmatrix_dup(char **src_matrix);
char	**charmatrix_add_one(char **src_matrix, char *entry);
char	**charmatrix_del_one(char **src_matrix, char *key);
char	**charmatrix_buble_sort(char **src_matrix);

/*	dollar expansion	*/
int		is_c_dollar(int c);
int		is_c_quote(int c);
int		is_there_a_blank(char *str);
int		is_str_quote_enclosed(const char *str);
int		is_c_blank_nl_dollar_s_d_quote(int c);
int		check_amb_redir(char *str, char **envp);
char	*get_key(char *line);
char	*get_key_2(char *line);
char	*get_value(char *line);
char	*expand_wd(char *word, char **envp);
char	*extract_wd(char *start, char *end);
char	*expand_dollar(char *str, char **envp, int last_status);
char	*expand_dollar_here_doc(char *str, char **envp, int last_status);
char	*expand_dollar_redir_file(char *str, char **envp);

/*	general expansion	*/
char	*rm_peer_quotes(char *str);
char	*get_next_word_not_expanded(char **ret, char *str, char *word_end);

/*	redirections	*/
int		open_in(const char *filename);
int		open_here_doc(const char *lim, char **envp, int last_status);
int		open_out(t_type type, const char *filename);
void	manage_redir(t_ntree *ast, char **envp, int last_status);
void	manage_here_doc(t_ntree *ast, char **envp, int last_status);

/*	execution	*/
t_execute_ast_fun	get_execute_function(t_ntree *ast);
int		execute_ast(t_ntree *ast);
int		execute_complete_command(t_ntree *ast);
int		execute_logical_expression(t_ntree *ast);
int		execute_compound_command(t_ntree *ast);
int		execute_pipeline(t_ntree *ast);
int		execute(char *cmd_name, char **cmd_args, t_info *info);
int		analyze_status(t_info *info);
void	wait_cmds(t_info *info);
t_type	get_redirection_type(t_ntree *redirection_node);
int		manage_pipeline(t_ntree *ast, char **envp);
int		manage_dollar_expansion(t_llist *leaf_list, char **envp, int last_status);
int		manage_quote_remove(t_llist *leaf_list);
t_info	*get_pipex_info(t_ntree *pipeline_node, char **envp);
char	*get_full_cmd_name(char *cmd_name, char **envp);
char	**get_path(char **envp);
int		pipex(t_info *info);

/*	printers	*/
void	print_item(void *item);

void	print_env(char **envp, char *prefix);
void	print_envar_bad(char *var, char **envp);
void	print_llist(t_llist *start);
void	print_token(t_token *token);
void	print_token_error(t_token token);
void	err_builtin(char *builtin, char *arg, char *err);
void	err_msg(char *str, char *err);

/* ntree functions */
t_ntree	*ntree_new(void *data, t_llist *children);
void	ntree_free(t_ntree *ntree, t_del_fun del);
void	ntree_print(t_ntree *ntree, void (*print)(void *));
char	*type_to_string(t_type type);
t_llist	*lexer(const char *line);
t_ntree	*parser(t_llist	*token_list);
void	free_token(t_token *token);
void	free_node(t_token *token);
t_token	*token_new(t_type type, void *data);
t_token	*get_token(t_ntree *ast);
void	ast_print(t_ntree *ast);
void	print_leaf(t_ntree *leaf);

/* builtins	*/
int		pwd(void);
int		echo(char **argv);
int		cd(char *path, char **envp);
int		env(char **envp, char *prefix);
int		unset(char **args, char ***envp);
int		export(char **args, char ***envp);
int		exit_blt(char **args, char **envp, void *truc);

/*	builtins utils	*/
char	*get_envalue(char *key, char **envp);
int		supp_envar(char *key, char ***envp);
int		add_envar(char *key, char *value, char ***envp);
int		mod_envar(char *key, char *new_value, char **envp);
int		is_var_set(char *key, char **envp);
int		exec_builtin(char **cmd_args, char ***envp);

/*	builtins check	*/
int		is_a_builtin(char **args);
int		check_echo(char **args);
int		check_cd(char **args);
int		check_pwd(char **args);
int		check_env(char **args);
int		check_export(char **args);
int		check_unset(char **args);
int		check_exit(char **args);

char 	*type_to_string(t_type type);
t_llist		*lexer(const char *line);
t_ntree		*parser(t_llist	*token_list);
int			is_prev_here_operator(t_llist *leaf_list);
t_llist	*wildcard_list(t_llist *token_list, char **envp);
t_llist	*expand_token_list(t_llist *token_list, char **envp, int last_status);

#endif

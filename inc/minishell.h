/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:58:59 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/09 19:18:20 by aguyon           ###   ########.fr       */
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
# define ALLOC_FAIL -2
# define LINE_EMPTY -4
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define EAMBREDIR 42
# define CONTINUE 1000
# define EXIT 1001
# define OK 1002
# define CODE_ALLOC 1
# define BUILTIN_ERR_CODE 2

/*	char const	*/
# define DELIM " \t<>&|()"
# define S_QUOTE '\''
# define D_QUOTE '\"'
# define PREFIX_EXPORT "declare -x "
# define LLINTMIN_CHAR "-9223372036854775808"

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
# define ERR_CNF "command not found"
# define ERR_AMB_REDIR "ambiguous redirect\n"
# define ERR_ID_EXPORT "not a valid identifier"
# define ERR_TMA "too many arguments"
# define ERR_NMR "numeric argument required"
# define ERR_DUP_IN "minishell: infile dup2"
# define ERR_DUP_OUT "minishell: outfile dup2"
# define ERR_EXECVE "minishell: execve"
# define ERR_PIPE "minishell: pipe"
# define ERR_FORK "minishell: fork"
# define ERR_ALLOC "Cannot allocate memory"

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
	ambigous_word,
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
	t_ntree			*root_ast;
	char			**envp;
	int				exit_code;
}	t_info;

typedef int	(*t_f)(char **);
typedef int	(*t_execute_ast_fun)(t_ntree *ast);

extern int	g_exit_status;

/*	parsing - lexing */
t_llist	*lsttok(const char *str);
void	lstreduce(t_llist	**llst);
// t_llist	*tokenization(t_llist *llst);
t_llist	*type_token(t_llist	*token_list);
t_llist	*token_to_leaf(t_llist	*token_list);
int		check_syntax(t_llist *token_list);
t_llist	*leaf_node_dup(t_llist *leaf_node);

/*	utils token	*/
t_llist	*new_llst_with_compound(t_llist *start);

/*	lsttok_utils	*/
int		isdelim(int c);
char	*strfind(const char *str, int c);
char	*strfind_not(const char *str, int c);
char	*strfind_if(const char *str, int (*f)(int));

/* create_command_utils*/
t_ntree	*create_cmd_name(t_llist *leaf);
t_llist	*find_cmd_name(t_llist *begin, t_llist *end);

/*	string_predicate	*/
int		is_str_or(const char *str);
int		is_str_and(const char *str);
int		is_str_pipe(const char *str);
int		is_str_great(const char *str);
int		is_str_less(const char *str);
int		is_str_dgreat(const char *str);
int		is_str_dless(const char *str);
int		is_str_compound(const char *str);
int		is_str_word(const char *str);
int		is_str_redirection(const char *str);
int		is_str_builtin(const char *str);
int		is_str_op_p(const char *str);
int		is_str_cl_p(const char *str);
int		is_str_quote(const char *str);
int		is_str_operator(const char *str);
int		is_str_blank(const char *str);

/*	ast */
t_ntree	*ast_new(t_type type, void *data, t_llist *children);
t_ntree	*ast_dup(t_ntree *ast);
void	ast_free(t_ntree *ast);
void	ast_print(t_ntree *ast);
int		is_node_inside(t_ntree *node, t_type types[], size_t n);
int		is_node_equal(t_ntree *node, t_type search_type);
t_llist	*create_child_range(t_llist	*begin, t_llist *end, t_ntree *(*create)(t_llist *, t_llist *));
t_llist	*create_child(t_llist *llist, t_ntree *(*create)(t_llist *));
t_ntree	*create_complete_command(t_llist	*leaf_list);
t_ntree	*create_compound_command(t_llist	*leaf);
t_ntree	*create_pipeline(t_llist	*begin, t_llist *end);
t_ntree	*create_logical_expression(t_llist	*begin, t_llist *end);
t_ntree	*create_command(t_llist	*begin, t_llist *end);
t_llist	*create_suffixes(t_llist	*begin, t_llist *end);
t_llist	*create_prefixes(t_llist	*begin, t_llist *end);
t_ntree	*create_redirection(t_llist	*begin, t_llist *end);
t_ntree	*create_classic_redirection(t_llist	*begin, t_llist *end);
t_ntree	*create_here_doc(t_llist	*begin, t_llist *end);
int		is_node_word(t_ntree	*node);
int		is_node_logical_operator(t_ntree	*node);
int		is_node_pipe(t_ntree	*node);
int		is_node_redirection(t_ntree	*node);
int		is_node_compound(t_ntree	*node);

/* token */
int		is_token_word(t_token *token);
int		is_token_pipe(t_token *token);
int		is_token_logical_operator(t_token *token);
int		is_token_operator(t_token *token);
int		is_token_redirection(t_token *token);
int		is_token_here_doc(t_token *token);
int		is_token_error(t_token *token);
t_token	*token_new(t_type type, void *data);
t_token	*token_dup(t_token *token);
void	token_free(t_token *token);
void	token_print(t_token *token);
int		is_type_inside(t_type type, const t_type types[], size_t n);

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
int		ft_atoi_ll_novf(const char *nptr, long long int *nb);

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
char	*expand_dollar(char *str, char **envp);
char	*expand_dollar_here_doc(char *str, char **envp);
char	*expand_dollar_redir_file(char *str, char **envp);

/*	general expansion	*/
char	*rm_peer_quotes(char *str);
char	*get_next_word_not_expanded(char **ret, char *str, char *word_end);

/*	redirections	*/
int		open_in(const char *filename);
int		open_here_doc(const char *lim, char **envp);
int		open_out(t_type type, const char *filename);
void	manage_redir(t_ntree *ast, char **envp);
void	manage_here_doc(t_ntree *ast, char **envp);
/*	utils	*/
t_type	get_redirection_type(t_ntree *redirection_node);
char	*get_redirection_filename(t_ntree *redirection_node);
char	*get_here_end(t_ntree *here_doc_node);
int		open_redirections(t_type type, const char *filename);
void	free_and_exit(t_info *info, int status);

/*	execution	*/
void	*get_execute_function(t_ntree *ast);
int		execute_ast(t_ntree *ast);
int		execute_complete_command(t_ntree *ast);
int		execute_logical_expression(t_ntree *ast);
int		execute_compound_command(t_ntree *ast);
int		execute_pipeline(t_ntree *ast);
int		execute(char **cmd_args, t_info *info);
int		analyze_status(t_info *info);
void	wait_cmds(t_info *info);
t_type	get_redirection_type(t_ntree *redirection_node);
int		manage_pipeline(t_ntree *ast, t_ntree *root, char **envp);
int		manage_dollar_expansion(t_llist *leaf_list, char **envp);
t_llist *get_ambigous_node(t_llist *node);
t_llist	*llst_remove_quote(t_llist *token_list);
t_llist	*llst_expand_dollar(t_llist *token_list, char **envp);
t_llist *llst_expand_wildcard(t_llist *token_list, char **envp);
t_info	*get_pipex_info(t_ntree *pipeline_node, t_ntree *root, char **envp);
char	*get_full_cmd_name(char *cmd_name, char **envp);
char	**get_path(char **envp);
int		pipex(t_info *info);

/*	printers	*/
void	print_item(void *item);
void	print_env(char **envp, char *prefix);
void	print_envar_bad(char *var, char **envp);
void	print_llist(t_llist *start);
void	print_token_error(t_token token);
void	err_builtin(const char *builtin, const char *arg, const char *err);
void	err_msg(const char *str, const char *err);

/* ntree functions */
char	*type_to_string(t_type type);
t_llist	*tokenization(const char *line);
t_ntree	*parser(t_llist	*token_list);
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
int		exit_blt(char **args, t_info *info);

/*	builtins utils	*/
char	*get_envalue(char *key, char **envp);
int		supp_envar(char *key, char ***envp);
int		add_envar(char *key, char *value, char ***envp);
int		mod_envar(char *key, char *new_value, char **envp);
int		is_var_set(char *key, char **envp);
int		exec_builtin(char *cmd_name, char **args, char ***envp, t_info *info);
int		redir_solo_builtin(t_cmd *cmd);
int		exec_solo_builtin(t_cmd *cmd, t_info *info);

/*	builtins check	*/
int		is_a_builtin(char **args, char *cmd_name);
int		check_echo(char **args);
int		check_cd(char **args);
int		check_pwd(char **args);
int		check_env(char **args);
int		check_export(char **args);
int		check_unset(char **args);
int		check_exit(char **args);

/*	signal */
void	set_prompt_signals(void);
void	set_parent_signals(void);
void	set_child_signals(void);
void	set_here_doc_signals(void);
void	handle_prompt_signals(int signum);
void	handle_parent_signals(int signum);
void	handle_here_doc_signals(int signum);

char	*type_to_string(t_type type);
t_llist	*lexer(const char *line);
t_ntree	*parser(t_llist	*token_list);
int		is_prev_here_operator(t_llist *leaf_list);
t_llist	*wildcard_list(t_llist *token_list, char **envp);
char	*get_pwd(char **envp);
int		match(char *pattern, char *text);
t_llist	*node_dup(t_llist *node);
t_llist	*expand_token_list(t_llist *token_list, char **envp);

/*	cleanup	*/
void	data_cleanup(char **data);
void	token_list_cleanup(t_llist **token_list);
void	ast_cleanup(t_ntree **ast);

/*	main_utils	*/
void	reader_loop(char **envp);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:58:59 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/25 14:40:50 by aguyon           ###   ########.fr       */
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
# include <stdbool.h>
# include <readline/readline.h>
# include <assert.h>
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
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define CODE_ALLOC 1
# define BUILTIN_ERR_CODE 2

/*	char const	*/
# define DELIM " \t<>&|()"
# define WHITESPACE " \t\n\r\v\f"
# define D_QUOTE 34
# define S_QUOTE 39
# define PFX_EXPORT "declare -x "
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
# define ERR_IAD "Is a directory"
# define ERR_INVOPT "invalid option"
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
# define PWD_USAGE "pwd: usage: pwd [-LP]\n"
# define ENV_USAGE "env: usage (minishell): env\n"
# define EXPORT_USAGE "export: usage (minishell): export [name[=value] ...]\n"
# define UNSET_USAGE "unset: usage (minishell): unset [name ...]\n"

typedef enum e_type
{
	or = 1,
	and,
	ppipe,
	great,
	less,
	dgreat,
	dless,
	opening_parenthesis,
	closing_parenthesis,
	newline,
	word,
	error,
	ambiguous_word,
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

typedef enum e_state
{
	OK = 0,
	CONTINUE = -1,
	EXIT = -2,
}	t_state;

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

typedef enum e_error
{
	SUCCESS = 0,
	ERRFD = -1,
	ERRALLOC = -2,
	ERRSIGINT = -3,
	ERRBUILTIN = -4,
}	t_error;

typedef struct s_info
{
	t_cmd			*cmds;
	t_cmd			*cmd_start;
	pid_t			last_pid;
	int				exit_code;
}	t_info;

typedef struct s_minishell
{
	t_ntree			*ast;
	t_llist			*here_doc_files;
	char			**envp;
	unsigned char	status;
}	t_minishell;

typedef int	(*t_f)(char **);
typedef int	(*t_execute_ast_fun)(t_minishell *minishell, t_ntree *ast);

extern int	g_last_signum;

/*	parsing - lexing */
t_llist	*lsttok(const char *str);
t_llist	*type_token(t_llist	*token_list);
t_llist	*token_to_leaf(t_llist	*token_list);
int		check_syntax(t_llist *token_list);
t_llist	*leaf_node_dup(t_llist *leaf_node);
t_ntree	*leaf_new(const t_token *token);

/*	lsttok_utils	*/
int		isdelim(int c);
char	*strfind(const char *str, int c);
char	*strfind_not(const char *str, int c);
char	*strfind_if(const char *str, int (*f)(int));

/* create_command_utils*/
t_ntree	*create_cmd_name(t_llist *leaf);
t_llist	*find_cmd_name(t_llist *begin, t_llist *end);

/*	string_predicate	*/
bool	is_str_or(const char *str);
bool	is_str_and(const char *str);
bool	is_str_pipe(const char *str);
bool	is_str_great(const char *str);
bool	is_str_less(const char *str);
bool	is_str_dgreat(const char *str);
bool	is_str_dless(const char *str);
bool	is_str_compound(const char *str);
bool	is_str_word(const char *str);
bool	is_str_redirection(const char *str);
bool	is_str_builtin(const char *str);
bool	is_str_op_p(const char *str);
bool	is_str_cl_p(const char *str);
bool	is_str_quote(const char *str);
bool	is_str_operator(const char *str);
bool	is_str_blank(const char *str);
bool	is_str_empty_quote(const char *str);
bool	is_str_enclosed_quote(const char *str);

/*	ast */
t_ntree	*ast_new(t_type type, void *data, t_llist *children);
t_ntree	*ast_dup(t_ntree *ast);
void	ast_free(t_ntree *ast);
void	ast_print(t_ntree *ast);
bool	is_node_inside(t_token *token, t_type types[], size_t n);
bool	is_node_equal(t_token *token, t_type search_type);
t_llist	*create_child_range(t_llist	*begin, t_llist *end, \
	t_ntree *(*create)(t_llist *, t_llist *));
t_llist	*create_child(t_llist *llist, t_ntree *(*create)(t_llist *));
t_ntree	*create_complete_command(t_llist *leaf_list);
t_ntree	*create_compound_command(t_llist *begin, t_llist *end);
t_ntree	*create_pipeline(t_llist *begin, t_llist *end);
t_ntree	*create_logical_expression(t_llist	*begin, t_llist *end);
t_ntree	*create_command(t_llist	*begin, t_llist *end);
t_llist	*create_suffixes(t_llist *begin, t_llist *end);
t_llist	*create_prefixes(t_llist *begin, t_llist *end);
t_ntree	*create_redirection(t_llist *begin, t_llist *end);
t_ntree	*create_classic_redirection(t_llist	*begin, t_llist *end);
t_ntree	*create_here_doc(t_llist *begin, t_llist *end);
bool	is_node_word(t_token *token);
bool	is_node_logical_operator(t_token *token);
bool	is_node_pipe(t_token *token);
bool	is_node_opening_parenthesis(t_token *token);
bool	is_node_redirection(t_token *token);
bool	is_node_closing_parenthesis(t_token *token);
bool	is_range_compound(t_llist *begin, t_llist *end);

/* token */
bool	is_token_opening_parenthesis(t_token *token);
bool	is_token_closing_parenthesis(t_token *token);
bool	is_token_logical_operator(t_token *token);
bool	is_token_pipe(t_token *token);
bool	is_token_word(t_token *token);
bool	is_token_redirection(t_token *token);
bool	is_token_error(t_token *token);
bool	is_token_ambiguous_word(t_token *token);
t_token	*token_new(t_type type, void *data);
t_token	*token_dup(t_token *token);
void	token_free(t_token *token);
void	token_print(t_token *token);
bool	is_type_inside(t_type type, const t_type types[]);

/*	llst_token	*/
t_llist	*llst_token_new(t_type type, char *data);
t_token	*llst_token_get(t_llist *node);
char	*llst_token_get_data(t_llist *node);
t_type	llst_token_get_type(t_llist *node);

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
void	ft_bzero_matrix(char **matrix, size_t n);

/* syntax check*/
int		check_logical_operator(t_llist *node);
int		check_pipe(t_llist *node);
int		check_redirection(t_llist *node);
int		check_opening_parenthesis(t_llist *node);
int		check_closing_parenthesis(t_llist *node);
int		check_newline(t_llist *node);

/*	dollar expansion	*/
int		is_c_dollar(int c);
int		is_c_quote(int c);
int		is_there_a_blank(char *str);
int		is_str_quote_enclosed(const char *str);
int		is_c_end_envar(int c);
int		is_whitespace(int c);
int		check_amb_redir(char *str, char **envp);
char	*get_key(char *line);
char	*get_key_2(char *line);
char	*get_value(char *line);
char	*expand_wd(char *word, char **envp);
char	*extract_wd(char *start, char *end);
char	*expand_dollar(char *str, char **envp, int status);
char	*expand_dollar_here_doc(char *str, char **envp, int status);
char	*expand_dollar_redir_file(char *str, char **envp, int status);

/*	general expansion	*/
char	*rm_peer_quotes(char *str);
char	*get_next_word_not_expanded(char **ret, char *str, char *word_end);

/*	redirections	*/
int		open_in(const char *filename);
int		open_here_doc(const char *lim, t_minishell *minishell);
int		open_out(t_type type, const char *filename);
void	manage_redir(t_ntree *ast, char **envp);
t_state	manage_here_doc(t_ntree *ast, t_minishell *minishell);
int		create_tmp_file(char *pathname, t_minishell *minishell);
/*	utils	*/
t_type	get_redirection_type(t_ntree *redirection_node);
char	*get_redirection_filename(t_ntree *redirection_node);
char	*get_here_end(t_ntree *here_doc_node);
int		open_redirections(t_type type, const char *filename);
void	free_and_exit(t_minishell *minishell);
void	free_and_exit_child(t_minishell *minishell);
void	free_loop(t_minishell *minishell);

/*	execution	*/
void	*get_execute_function(t_ntree *ast);
int		execute_ast(t_minishell *minishell);
int		execute_complete_command(t_minishell *minishell, t_ntree *ast);
int		execute_logical_expression(t_minishell *minishell, t_ntree *ast);
int		execute_pipeline(t_minishell *minishell, t_ntree *ast);
void	execute(char **cmd_args, t_info *info, t_minishell *minishell);
int		analyze_status(t_info *info);
void	wait_cmds(t_info *info);
t_type	get_redirection_type(t_ntree *redirection_node);
int		manage_pipeline(t_minishell *minishell, t_ntree *ast);
int		manage_dollar_expansion(t_llist *leaf_list, char **envp);
t_info	*get_pipex_info(t_minishell *minishell, t_ntree *pipeline_node);
char	*get_full_cmd_name(char *cmd_name, char **envp);
char	**get_path(char **envp);
int		pipex(t_minishell *minishell, t_info *info);

/*	expansion	*/
t_llist	*llst_remove_quote(t_llist *token_list);
char	*remove_quote(char *str);
t_llist	*llst_expand_dollar(t_llist *token_list, char **envp, int status);
t_llist	*llst_word_splitting(t_llist *token_list);
int		is_prev_redir_operator(t_llist *node);
t_llist	*new_field_node(char *str, size_t start, size_t len);
t_llist	*llst_expand_wildcard(t_llist *token_list);
t_llist	*ambigous_node_new(t_llist *node);
bool	check_ambigous_redirect(t_llist *node, int nb_matched_files);

/*	printers	*/
void	print_item(void *item);
void	print_env(char **envp, char *prefix);
void	print_envar_bad(char *var, char **envp);
void	print_llist(t_llist *start);
void	print_syntax_error(const char *str);
void	err_builtin(const char *builtin, const char *arg, const char *err);
void	err_msg(const char *str, const char *err);
void	print_err_ambiguous(const char *str);
void	print_err_quotes(void);
void	print_signal(int signum);

/* ntree functions */
char	*type_to_string(t_type type);
t_llist	*tokenization(const char *line);
t_ntree	*parser(t_llist	*token_list);
t_token	*get_token(t_ntree *ast);
void	ast_print(t_ntree *ast);
void	print_leaf(t_ntree *leaf);

/* builtins	*/
int		pwd(char **args);
int		echo(char **argv);
int		cd(char **args, char ***envp);
int		env(char **args, char **envp, char *prefix, int quote);
int		unset(char **args, char ***envp);
int		export(char **args, char ***envp);
int		exit_blt(char **args, t_minishell *minishell);

/*	builtins utils	*/
char	*get_envalue(char *key, char **envp);
int		supp_envar(char *key, char ***envp);
int		add_envar(char *key, char *value, char ***envp);
int		mod_envar(char *key, char *new_value, char **envp);
int		concat_envar(char *key, char *new_value, char **envp);
int		is_var_set(char *key, char **envp);
int		is_key_valid(char *key, char *line);
int		exec_builtin(char *cmd_name, char **args, t_minishell *minishell);
int		redir_solo_builtin(t_cmd *cmd);
int		exec_solo_builtin(t_cmd *cmd, t_minishell *minishell);

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
bool	is_prev_here_operator(t_llist *leaf_list);
t_llist	*wildcard_list(t_llist *token_list, char **envp);
char	*get_pwd(char **envp);
int		match(const char *pattern, const char *text);
t_llist	*node_dup(t_llist *node);
t_state	expand_token_list(t_llist **token_list, t_minishell *minishell);
t_ntree	*new_leaf(t_token *token);
char	*get_next_split_word_node(char *str, bool *is_inside_simple_quote,
			bool *is_inside_double_quote);
bool	check_quotes(t_llist *token_list);

/*	main_utils	*/
void	reader_loop(t_minishell *minishell);

#endif

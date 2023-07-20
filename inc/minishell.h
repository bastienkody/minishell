/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:58:59 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/20 16:09:44 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../llist/llist.h"
# include "../libft/libft.h"
# include "../btree/btree.h"

/*	numeric const	*/
# define TRUE 1
# define FALSE 0
# define BAD_FD -1
# define MALLOC_FAIL_REDIR -2

/*	char const	*/
# define DELIM " \t<>&|()"
# define S_QUOTE '\''
# define D_QUOTE '\"'

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
}	t_type;

typedef void *(*t_funptr)();
typedef int (*t_predicate)(void *);
typedef void (*t_unary_fun)(void *);
typedef void *(*t_unary_op)(void *);
typedef void *(*t_binary_op)(void *, void *);
typedef void (*t_del_fun)(void *);

typedef struct s_token
{
	t_type	type;
	void	*data;
}	t_token;

typedef struct s_ast
{
	t_type	type;
	void	*data;
	t_llist	*children;
}	t_ast;

typedef struct s_ntree
{
	void	*data;
	t_llist	*children;
}	t_ntree;

/*	parsing - lexing */
t_llist	*lsttok(const char *str);
void	lstreduce(t_llist	**llst);
t_llist	*tokenization(t_llist *llst);
t_llist	*type_token(t_llist	*token_list);
t_btree	*create_tree(t_llist *token_list);
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
t_llist	*create_child(t_llist	*leaf, t_ntree *(*create)(t_llist *));
t_ntree	*create_complete_command(t_llist	*token_list);
t_ntree	*create_compound_command(t_llist *leaf_list);
t_ntree	*create_pipeline(t_llist *token_list);
t_ntree	*create_logical_expression(t_llist	*token_list);
t_ntree	*create_command(t_llist	*token_list);
t_llist	*create_suffixes(t_llist *leaf_list);
t_llist	*create_prefixes(t_llist *leaf_list);
t_ntree	*create_redirection(t_llist	*leaf_list);
void	free_ast(t_ast *ast);
int		is_node_word(t_ntree	*node);
int		is_node_logical_operator(t_ntree	*node);
int		is_node_pipe(t_ntree	*node);
int		is_node_redirection(t_ntree	*node);
int		is_node_compound(t_ntree	*node);

/*	utils general	*/
char	*strjoin(const char *s1, const char *s2);
char	*strjoin2(const char *s1, const char *s2);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);
char	*str_one_char_join(char *str, char c);
void	*ft_realloc(void *ptr, size_t size);

/*	dollar expansion	*/
int		is_c_dollar(int c);
int		is_c_quote(int c);
int		is_there_a_blank(char *str);
int		is_str_quote_enclosed(char *str);
int		is_c_blank_nl_dollar_s_d_quote(int c);
int		check_amb_redir(char *str, char **envp);
char	*get_key(char *line);
char	*get_value(char *line);
char	*expand_wd(char *word, char **envp);
char	*extract_wd(char *start, char *end);
char	*expand_dollar(char *str, char **envp);
char	*expand_dollar_here_doc(char *str, char **envp);
char	*expand_dollar_redir_file(char *str, char **envp);
int		expand_dollar_quotes_on_ast(t_ast *ast, char **envp);

/*	general expansion	*/
char	*rm_peer_quotes(char *str);
char	*get_next_word_not_expanded(char **ret, char *str, char *word_end);

/*	redirections	*/
int		open_in(char *filename, char **envp);
int		open_here_doc(char *lim, char **envp);
int		open_out(int type, char *filename, char **envp, t_ast *ast);
void	manage_redir(t_ast *ast, char **envp);
void	manage_here_doc(t_ast *ast, char **envp);

/*	execution	*/
int		execute(char *cmd_name, char **cmd_args, char **envp);
int		analyze_status(int status);
char	*get_full_cmd_name(char *cmd_name, char **envp);
char	**get_path(char **envp);

/*	printers	*/
void	print_item(void *item);
void	print_llist(t_llist *start);
void	print_token(t_token *token);
void	print_token_error(t_token token);
void	err_msg(char *str, char *err);
void	print_ast_full(t_ast *ast);
void	print_ast_text(t_ast *ast);
void	print_tree(t_ast *ast);

/* ntree functions */
t_ntree	*ntree_new(void *data, t_llist *children);
void	ntree_free(t_ntree *ntree, t_del_fun del);
void	ntree_print(t_ntree *ntree, void (*print)(void *));


char	*type_to_string(t_type type);
t_llist	*lexer(const char *line);
t_ntree	*parser(t_llist	*token_list);
void	free_token(t_token *token);
t_token	*token_new(t_type type, void *data);
#endif

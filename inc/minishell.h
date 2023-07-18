/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:58:59 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/18 17:45:30 by aguyon           ###   ########.fr       */
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
# include "../ntree/ntree.h"

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

typedef struct s_token
{
	char	*text;
	t_type	type;
}	t_token;

union u_data
{
	char	*text;
	int		fd;
	void	*nothing;
};

typedef struct s_node
{
	t_type			type;
	union	u_data	data;

}	t_node;

typedef struct s_ast
{
	t_type	type;
	void	*data;
	t_llist	*children;
}	t_ast;

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

/*	ast */
t_ast	*new_ast(t_type	type, void *data, t_llist *children);
t_llist	*create_child(t_llist	*leaf, t_ast *(*create)(t_llist *));
t_ast	*create_complete_command(t_llist	*token_list);
t_ast	*create_compound_command(t_llist *leaf_list);
t_ast	*create_pipeline(t_llist *token_list);
t_ast	*create_logical_expression(t_llist	*token_list);
t_ast	*create_command(t_llist	*token_list);
t_llist	*create_suffixes(t_llist *leaf_list);
t_llist	*create_prefixes(t_llist *leaf_list);
t_ast	*create_redirection(t_llist	*leaf_list);
void	free_ast(t_ast *ast);
int		is_node_word(t_ast	*node);
int		is_node_logical_operator(t_ast	*node);
int		is_node_pipe(t_ast	*node);
int		is_node_redirection(t_ast	*node);
int		is_node_compound(t_ast	*node);

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
int		open_out(int type, char *filename, char **envp);

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
void	print_tree(t_ast *ast, bool flag[256], int depth, int islast);

const char *type_to_string(t_type type);
t_llist	*lexer(const char *line);
t_ast	*parser(t_llist	*token_list);
void	free_token(t_token *token);
#endif

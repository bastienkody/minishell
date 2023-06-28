/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:58:59 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/28 14:01:57 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "../llist/llist.h"
# include "../libft/libft.h"
# include "../btree/btree.h"
# include "../ntree/ntree.h"
# include <readline/readline.h>
# include <readline/history.h>

# define TRUE 1
# define DELIM " \t<>&|()"

/*	error msg	*/
# define ERR_SYNTAX "minishell: syntax error near unexpected token "
# define ERR_QUOTE "bad number of quotes "
# define ERR_PARENTHESE "unexpected EOF while looking for matching `)'"

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
int		check_syntax(t_llist	*token_list);

/*	utils token	*/
t_llist	*new_llst_with_compound(t_llist *start);
int		is_str_op_p(const char *str);
int		is_str_cl_p(const char *str);
int		is_str_quote(const char *str);
int		is_str_operator(const char *str);
int		is_str_blank(const char *str);

/*	utils	*/
char	*strjoin(const char *s1, const char *s2);

/*	lsttok_utils	*/
char	*strfind_if(const char *str, int (*f)(int));
char	*strfind(const char *str, int c);
char	*strfind_not(const char *str, int c);
int		isdelim(int c);

/*	printers	*/
void	print_item(void *item);
void	print_llist(t_llist *start, void f(void *));
void	print_token(t_token *token);

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
#endif

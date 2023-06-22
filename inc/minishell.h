/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:58:59 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/21 16:46:10 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "../llist/llist.h"
# include "../libft/libft.h"
# include "../btree/btree.h"
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
	word,
	subshell,
	error,
}	t_type;

typedef struct s_token
{
	char	*text;
	t_type	type;
}	t_token;

/*	parsing - lexing */
t_llist	*lsttok(const char *str);

void	lstreduce(t_llist	**llst);
t_llist	*tokenization(t_llist *llst);

t_llist	*type_token(t_llist	*token_list);
t_btree	*create_tree(t_llist *token_list);

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
#endif

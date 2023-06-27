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
# include <fcntl.h>
# include <unistd.h>
# include "../llist/llist.h"
# include "../libft/libft.h"
# include "../btree/btree.h"
# include <readline/readline.h>
# include <readline/history.h>

/*	numeric const	*/
# define TRUE 1
# define FALSE 0
# define BAD_FD -1

/*	alphabetic const	*/
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

/*	utils	*/
void	*ft_realloc(void *ptr, size_t size);
char	*strjoin(const char *s1, const char *s2);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);
char	*str_one_char_join(char *str, char c);

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

/*	basics expansion	*/
char	*get_key(char *line);
char	*get_value(char *line);
char	*expand_wd(char *word, char **envp);
char	*extract_wd(char *start, char *end);

/*	dollar expansion	*/
int		is_c_dollar(int c);
int		is_c_blank_nl_dollar(int c);
int		is_str_quote_enclosed(char *str);
char	*expand_dollar_here_doc(char *str, char **envp);

/*	redirections	*/
int		open_here_doc(char *lim, char **envp);

/*	printers	*/
void	print_item(void *item);
void	print_llist(t_llist *start);
void	print_token(t_token *token);

#endif

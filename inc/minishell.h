#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "../llist/llist.h"
# include "../libft/libft.h"
# include "../llist/llist.h"
# include <readline/readline.h>
# include <readline/history.h>

# define TRUE 1
# define DELIM " \t<>&|()"

/*	error msg	*/
# define ERR_SYNTAX "minishell: syntax error near unexpected token "
# define ERR_QUOTE "bad number of quotes "

/*	parsing - token */
t_llist	*lsttok(const char *str, const char *delim);
void	lstreduce(t_llist	**llst);
t_llist	*tokenization(t_llist *llst);

/*	utils token	*/
t_llist	*join_token(t_llist *begin, t_llist *end);
int is_str_open_parenth(const char *str);
int is_str_close_parenth(const char *str);
int		is_str_quote(const char *str);
int		is_str_operator(const char *str);
int 	is_str_space(const char *str);

/*	utils	*/
char	*strjoin(const char s1, const char s2);

#endif

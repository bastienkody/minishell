#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include "../llist/llist.h"
#include "../libft/libft.h"
#include "../llist/llist.h"
#include <readline/readline.h>
#include <readline/history.h>

#define TRUE 1
#define DELIM " \t|&\'\"()=$#" // ajout du #  ; aussi peut on supprimer le = ?

/*	error msg	*/
#define ERR_SYNTAX "minishell: syntax error near unexpected token "


/*	parsing - lexing */
t_llist	*lsttok(const char *str, const char *delim);
t_llist	*lexem_join(t_llist **llst);

#endif

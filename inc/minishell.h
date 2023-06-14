#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include "../llist/llist.h"
#include "../libft/libft.h"
#include "../llist/llist.h"
#include <readline/readline.h>
#include <readline/history.h>
/* compilation with -lreadline */

#define TRUE 1
#define DELIM " |&\'\"()=$#" // bastien a antonin : ajout du #  ; aussi peut on supprimer le = ?

/*	parsing - lexing */
t_llist	*lsttok(const char *str, const char *delim);
t_llist	*lexem_join(t_llist **llst);

#endif

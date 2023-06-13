#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
/* compilation with -lreadline */

#define TRUE 1
#define DELIM " |&\'\"()"


t_list	*lsttok(const char *str, const char *delim);

#endif

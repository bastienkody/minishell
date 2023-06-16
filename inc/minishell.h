/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:20:52 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/16 15:41:11 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include "../llist/llist.h"
#include "../libft/libft.h"
#include "../llist/llist.h"
#include <readline/readline.h>
#include <readline/history.h>

#define TRUE 1
#define DELIM " \t<>&|()"

/*	error msg	*/
#define ERR_SYNTAX "minishell: syntax error near unexpected token "

/*	parsing - lexing */
t_llist	*lsttok(const char *str);

void	lstreduce(t_llist	**llst);
t_llist	*tokenization(t_llist *llst);

/*	utils token	*/
int	is_str_quote(const char *str);
int	is_str_operator(const char *str);
int is_str_space(const char *str);

//lsttok_utils
char	*strfind_if(const char *str, int (*f)(int));
char	*strfind(const char *str, int c);
char	*strfind_not(const char *str, int c);
int		isdelim(int c);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:20:52 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/16 14:21:26 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../llist/llist.h"
# include <readline/readline.h>
# include <readline/history.h>
/* compilation with -lreadline */

# define TRUE 1
# define DELIM " \t|&()"

t_llist	*lsttok(const char *str);
void	lstreduce(t_llist	**llst);

//lsttok_utils
char	*strfind_if(const char *str, int (*f)(int));
char	*strfind(const char *str, int c);
char	*strfind_not(const char *str, int c);
int		isdelim(int c);

#endif

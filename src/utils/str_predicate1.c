/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_predicate1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:54:34 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/15 10:43:59 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_str_or(const char *str)
{
	return (ft_strcmp(str, "||") == 0);
}

bool	is_str_and(const char *str)
{
	return (ft_strcmp(str, "&&") == 0);
}

bool	is_str_pipe(const char *str)
{
	return (ft_strcmp(str, "|") == 0);
}

bool	is_str_great(const char *str)
{
	return (ft_strcmp(str, ">") == 0);
}

bool	is_str_less(const char *str)
{
	return (ft_strcmp(str, "<") == 0);
}

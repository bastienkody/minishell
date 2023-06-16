/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstreduce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:02:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/15 19:55:33 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_str_quote(const char *str)
{
	return (strcmp(str, "\"") == 0 || strcmp(str, "\'") == 0);
}

int	is_str_operator(const char *str)
{
	return (strcmp(str, "&") == 0 || strcmp(str, "|") == 0);
}

int	is_str_space(const char *str)
{
	return (strcmp(str, " ") == 0 || strcmp(str, "\t") == 0);
}

int	is_str_op_p(const char *str)
{
	return (strcmp(str, "(") == 0);
}

int	is_str_cl_p(const char *str)
{
	return (strcmp(str, ")") == 0);
}

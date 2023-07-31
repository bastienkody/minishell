/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:02:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/29 17:05:24 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_str_quote(const char *str)
{
	return (ft_strcmp(str, "\"") == 0 || ft_strcmp(str, "\'") == 0);
}

int	is_str_operator(const char *str)
{
	return (ft_strcmp(str, "&") == 0 || ft_strcmp(str, "|") == 0);
}

int	is_str_blank(const char *str)
{
	while (*str != '\0')
	{
		if (strchr(" \t", *str) == NULL)
			return (0);
		str++;
	}
	return (1);
}

int	is_str_op_p(const char *str)
{
	return (ft_strcmp(str, "(") == 0);
}

int	is_str_cl_p(const char *str)
{
	return (ft_strcmp(str, ")") == 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:30:08 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/22 16:30:09 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_c_blank_nl_dollar_s_d_quote(int c)
{
	const char	*envar_delim = " \t\n$\'\"";

	return (ft_strchr(envar_delim, c) != NULL);
}

int	is_there_a_blank(char *str)
{
	const char	*blank_char = " \t";

	while (str && *str)
	{
		if (ft_strchr(blank_char, *str))
			return (1);
		str++;
	}
	return (0);
}

/*	false=0, singlq=1, doubleq=2	*/
int	is_c_quote(int c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

int	is_str_quote_enclosed(char *str)
{
	if ((str[0] == '\'') && str[0] == str[ft_strlen(str) - 1])
		return (1);
	if ((str[0] == '\"') && str[0] == str[ft_strlen(str) - 1])
		return (2);
	return (0);
}

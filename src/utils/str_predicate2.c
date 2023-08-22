/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_predicate2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:54:39 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/21 17:10:28 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_str_dgreat(const char *str)
{
	return (ft_strcmp(str, ">>") == 0);
}

bool	is_str_dless(const char *str)
{
	return (ft_strcmp(str, "<<") == 0);
}

static bool	check_parenthesis(const char *text)
{
	int	n;

	n = 0;
	while (*text && n >= 0)
	{
		if (*text == '(')
			n++;
		else if (*text == ')')
			n--;
		text++;
	}
	return (n == 0);
}

bool	is_str_compound(const char *str)
{
	const size_t	len = ft_strlen(str);

	if (len > 2 && str[0] == '(' && str[len - 1] == ')')
		return (check_parenthesis(str));
	return (0);
}

bool	is_str_word(const char *str)
{
	(void)str;
	return (1);
}

bool	is_str_quoted_word(const char *str)
{
	return (ft_strchr("\'\"", str[0]) && str[0] == str[ft_strlen(str) - 1]);
}
